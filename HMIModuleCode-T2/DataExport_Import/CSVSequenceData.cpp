#include "CSVSequenceData.h"
#include "Modules/typedef.h"
#include "DataBase/DBSequenceTable.h"
#include "Modules/UtilityClass.h"
#include "CSVPresetData.h"
#include "Interface/SequenceElement.h"
#include "DataBase/DBPresetTable.h"
#include "Interface/PresetElement.h"
#include <QFile>
CSVSequenceData* CSVSequenceData::_instance = NULL;
CSVSequenceData* CSVSequenceData::Instance()
{
    if(_instance == 0){
        _instance = new CSVSequenceData();
    }
    return _instance;
}

CSVSequenceData::CSVSequenceData()
{

}

CSVSequenceData::~CSVSequenceData()
{

}

bool CSVSequenceData::ExportData(int ID, QString fileUrl)
{
    DBSequenceTable* _SequenceDB = DBSequenceTable::Instance();
    CSVPresetData* _PresetData = CSVPresetData::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QMap<int,struct SEQUENCEATTRIBUTE> SpliceList;
    QStringList ListStr;
    QString RowStr = "";
    QString SpliceData = "";
    QString tmpSpliceData;
    QString fileSource;
    ListStr.clear();
    bool bResult = _SequenceDB->QueryOneRecordFromTable(ID, ListStr);
    if(bResult == false)
        return bResult;
    RowStr.clear();
    SpliceData.clear();
    SpliceList.clear();
    for(int i = 0; i < ListStr.size(); i++)
    {
        if(i == JSONSplice)
        {
            _Utility->StringJsonToMap(ListStr[i], &SpliceList);
            QMap<int, struct SEQUENCEATTRIBUTE>::const_iterator iterator = SpliceList.constBegin();
            while (iterator != SpliceList.constEnd()) {
                tmpSpliceData = _PresetData->GetExportString(iterator.key());
                SpliceData.append(tmpSpliceData + "|");
                ++iterator;
            }
            RowStr.append(ListStr[i] + ",");
            RowStr.append(SpliceData + ",");
        }
        else
            RowStr.append(ListStr[i] + ",");
    }

    fileSource = fileUrl;
    bResult = fileSource.contains("file:///");
    if(bResult == false)
        return bResult;
    fileSource = fileSource.mid(8);
    QFile csvFile(fileSource);
    bResult = csvFile.open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate);
    if(bResult == false)
        return bResult;
    QTextStream out(&csvFile);
    out << "Sequence Data" << '\n' << RowStr;
    csvFile.close();
    return true;
}

bool CSVSequenceData::ExportData(QList<int> IDList, QString fileUrl)
{
    UNUSED(IDList);
    UNUSED(fileUrl);
    return true;
}

QString CSVSequenceData::GetExportString(int ID)
{
    DBSequenceTable* _SequenceDB = DBSequenceTable::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    CSVPresetData* _SpliceData = CSVPresetData::Instance();
    QStringList ListStr;
    QString RowStr = "";
    QString tmpSpliceData;
    QString SpliceData = "";
    QString fileSource;
    QMap<int,struct SEQUENCEATTRIBUTE> SpliceList;
    ListStr.clear();
    bool bResult = _SequenceDB->QueryOneRecordFromTable(ID, ListStr);
    if(bResult == false)
        return RowStr;
    RowStr.clear();
    SpliceData.clear();
    SpliceList.clear();
    for(int i = 0; i< ListStr.size(); i++)
    {
        if(i == JSONSplice)
        {
            _Utility->StringJsonToMap(ListStr[i], &SpliceList);
            QMap<int, struct SEQUENCEATTRIBUTE>::const_iterator iterator = SpliceList.constBegin();
            while (iterator != SpliceList.constEnd()) {
                tmpSpliceData = _SpliceData->GetExportString(iterator.key());
                SpliceData.append(tmpSpliceData + "|");
                ++iterator;
            }
            RowStr.append(ListStr[i] + "@");
            RowStr.append(SpliceData + "@");
        }
        else
            RowStr.append(ListStr[i] + "@");
    }
    return RowStr;
}

bool CSVSequenceData::ParseSpliceData(QString StrSplice)
{
    QString TmpStr = StrSplice;
    QStringList SpliceList;
    CSVPresetData* _SpliceData = CSVPresetData::Instance();
    TmpStr.replace("*",",");
    SpliceList = TmpStr.split("|");
    SpliceIndexList.clear();
    for (int i = 0;i < SpliceList.count();i++)
    {
        if (SpliceList[i] != "")
            SpliceIndexList.append(_SpliceData->ImportData(SpliceList[i]));
    }
    return true;
}

void CSVSequenceData::ParseSequenceJOSN(QString SequenceJOSN)
{
    UtilityClass* _Utility = UtilityClass::Instance();
    QMap<int,struct SEQUENCEATTRIBUTE> SpliceList;
    QMap<int, struct SEQUENCEATTRIBUTE>::const_iterator iterator;
    DBPresetTable* _SpliceDB = DBPresetTable::Instance();
    PresetElement PresetObj;
    bool bResult = false;
    _Utility->StringJsonToMap(SequenceJOSN, &SpliceList);
    SpliceIndexMap.clear();
    for (int i = 0; i < SpliceIndexList.count(); i++)
    {
        if (SpliceIndexList[i] != -1)
        {
            bResult = _SpliceDB->QueryOneRecordFromTable(SpliceIndexList[i], &PresetObj);
            if(bResult == true)
            {
                iterator = SpliceList.find(SpliceIndexList[i]);
                if(iterator != SpliceList.constEnd())
                    SpliceIndexMap.insert(PresetObj.SpliceID, iterator.value());
            }
        }
    }
}

int CSVSequenceData::ImportData(QString StrValue)
{
    QString RowStr;
    QString TmpStr;
    QStringList DataList;
    bool bResult;
    SequenceElement SequenceObj;
    int ret = -1;
    DBSequenceTable* _SequenceDB = DBSequenceTable::Instance();
    RowStr = StrValue;
    DataList = RowStr.split(",");
    if(DataList.size() < SequenceEnd)
        return ret;

    TmpStr = DataList[SpliceString];
    ParseSpliceData(TmpStr);
    TmpStr = DataList[JSONSplice];
    ParseSequenceJOSN(TmpStr);

    SequenceObj.SequenceID = QString(DataList[SequenceID]).toInt(&bResult, DECIMALISM);
    SequenceObj.SequenceName = DataList[SequenceName];
    QDateTime TimeLabel =
            QDateTime::fromString(DataList[CreatedDate], "yyyy/MM/dd hh:mm:ss");
    SequenceObj.CreatedDate = TimeLabel.toTime_t();
    SequenceObj.OperatorID = QString(DataList[OperatorID]).toInt(&bResult, DECIMALISM);
    SequenceObj.SpliceList = SpliceIndexMap;
    SequenceObj.NoOfSplice = SequenceObj.SpliceList.size();

    ret = _SequenceDB->InsertRecordIntoTable(&SequenceObj);
    while(ret == ERROR)
    {
        qDebug()<<"harness";
        QMap<int, QString> tmpMap;
        _SequenceDB->QueryOnlyUseName(SequenceObj.SequenceName, &tmpMap);
        if(tmpMap.size() > 0)
        {
            SequenceObj.SequenceName += "(1)";
            ret = _SequenceDB->InsertRecordIntoTable(&SequenceObj);
        }else if(tmpMap.size() == 0)
            return ERROR;
    }
    return ret;
}
