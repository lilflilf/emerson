#include "CSVHarnessData.h"
#include "DataBase/DBHarnessTable.h"
#include "Modules/UtilityClass.h"
#include "CSVPresetData.h"
#include "Interface/HarnessElement.h"
#include "Modules/typedef.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
CSVHarnessData* CSVHarnessData::_instance = NULL;
CSVHarnessData* CSVHarnessData::Instance()
{
    if(_instance == 0){
        _instance = new CSVHarnessData();
    }
    return _instance;
}
CSVHarnessData::CSVHarnessData()
{

}

CSVHarnessData::~CSVHarnessData()
{

}

bool CSVHarnessData::ExportData(int ID, QString fileUrl)
{
    DBHarnessTable* _HarnessDB = DBHarnessTable::Instance();
    CSVPresetData* _PresetData = CSVPresetData::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QMap<int,struct HARNESSATTRIBUTE> SpliceList;
    QStringList ListStr;
    QString RowStr = "";
    QString SpliceData = "";
    QString tmpSpliceData;
    QString fileSource;
    ListStr.clear();
    bool bResult = _HarnessDB->QueryOneRecordFromTable(ID, ListStr);
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
            QMap<int, struct HARNESSATTRIBUTE>::const_iterator iterator = SpliceList.constBegin();
            while (iterator != SpliceList.constEnd()) {
                tmpSpliceData = _PresetData->GetExportString(iterator.key());
                SpliceData.append(tmpSpliceData + "|");
                ++iterator;
            }
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
    out << "WireData" << '\n' << RowStr;
    csvFile.close();
    return true;
}

QString CSVHarnessData::GetExportString(int ID)
{
    DBHarnessTable* _HarnessDB = DBHarnessTable::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    CSVPresetData* _SpliceData = CSVPresetData::Instance();
    QStringList ListStr;
    QString RowStr = "";
    QString tmpSpliceData;
    QString SpliceData = "";
    QString fileSource;
    QMap<int,struct HARNESSATTRIBUTE> SpliceList;
    ListStr.clear();
    bool bResult = _HarnessDB->QueryOneRecordFromTable(ID, ListStr);
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
            QMap<int, struct HARNESSATTRIBUTE>::const_iterator iterator = SpliceList.constBegin();
            while (iterator != SpliceList.constEnd()) {
                tmpSpliceData = _SpliceData->GetExportString(iterator.key());
                SpliceData.append(tmpSpliceData + "|");
                ++iterator;
            }
            RowStr.append(SpliceData + "@");
        }
        else
            RowStr.append(ListStr[i] + "@");
    }
    return RowStr;
}

int CSVHarnessData::ImportData(QString StrValue, QMap<int, QString> SpliceIDMap)
{
    QString RowStr;
    QStringList DataList;
    bool bResult;
    HarnessElement HarnessObj;
    int ret = -1;
    DBHarnessTable* _HarnessDB = DBHarnessTable::Instance();
    RowStr = StrValue;
    DataList = RowStr.split(",");
    if(DataList.size() < HarnessEnd)
        return ret;

    HarnessObj.HarnessID = QString(DataList[HarnessID]).toInt(&bResult, DECIMALISM);
    HarnessObj.HarnessName = DataList[HarnessName];
    QDateTime TimeLabel =
            QDateTime::fromString(DataList[CreatedDate], "yyyy/MM/dd hh:mm:ss");
    HarnessObj.CreatedDate = TimeLabel.toTime_t();
    HarnessObj.OperatorID = QString(DataList[OperatorID]).toInt(&bResult, DECIMALISM);
    HarnessObj.HarnessTypeSetting.ProcessMode =
            (PROCESSMODE)QString(DataList[ProcessMode]).toInt(&bResult, DECIMALISM);
    HarnessObj.HarnessTypeSetting.WorkStations.TotalWorkstation =
            QString(DataList[TotalWorkstation]).toInt(&bResult, DECIMALISM);
    HarnessObj.HarnessTypeSetting.WorkStations.MaxSplicesPerWorkstation =
            QString(DataList[MaxSplicesPerWorkstation]).toInt(&bResult, DECIMALISM);
    HarnessObj.HarnessTypeSetting.BoardLayout.Rows =
            QString(DataList[Rows]).toInt(&bResult, DECIMALISM);
    HarnessObj.HarnessTypeSetting.BoardLayout.Columns =
            QString(DataList[Columns]).toInt(&bResult, DECIMALISM);
    HarnessObj.HarnessTypeSetting.BoardLayout.MaxSplicesPerZone =
            QString(DataList[MaxSplicesPerZone]).toInt(&bResult, DECIMALISM);
    QMap<int, struct HARNESSATTRIBUTE> tmpMap;
    int i = 0;
    QMap<int, QString>::const_iterator iterator = SpliceIDMap.constBegin();
    while(iterator != SpliceIDMap.constEnd())
    {
        struct HARNESSATTRIBUTE tmp;
        tmp.SpliceID = iterator.key();
        tmp.SpliceName = iterator.value();
        tmpMap.insert(i, tmp);
        i++;
        ++iterator;
    }

    HarnessObj.SpliceList = tmpMap;
    HarnessObj.NoOfSplice = HarnessObj.SpliceList.size();

    ret = _HarnessDB->InsertRecordIntoTable(&HarnessObj);
    while(ret == ERROR)
    {
        qDebug()<<"harness";
        QMap<int, QString> tmpMap;
        _HarnessDB->QueryOnlyUseName(HarnessObj.HarnessName, &tmpMap);
        if(tmpMap.size() > 0)
        {
            HarnessObj.HarnessName += "(1)";
            ret = _HarnessDB->InsertRecordIntoTable(&HarnessObj);
        }else if(tmpMap.size() == 0)
            return ERROR;
    }
    return ret;
}
