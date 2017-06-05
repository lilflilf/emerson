#include "CSVAlarmLogData.h"
#include "Modules/typedef.h"
#include "DataBase/DBAlarmLogTable.h"
#include "DataBase/DBPresetTable.h"
#include "Interface/AlarmElement.h"
#include "Interface/PresetElement.h"
#include "Interface/VariantToString.h"
#include <QFile>
CSVAlarmLogData* CSVAlarmLogData::_instance = NULL;
CSVAlarmLogData* CSVAlarmLogData::Instance()
{
    if(_instance == 0){
        _instance = new CSVAlarmLogData();
    }
    return _instance;
}

CSVAlarmLogData::CSVAlarmLogData()
{

}

CSVAlarmLogData::~CSVAlarmLogData()
{

}

bool CSVAlarmLogData::ExportData(int ID, QString fileUrl)
{
    UNUSED(ID);
    UNUSED(fileUrl);
    return true;
}

QString CSVAlarmLogData::HeaderString()
{
    QString sHeader;
    sHeader = QObject::tr("Date") + "\t" + QObject::tr("Time") + "\t" +
            QObject::tr("Alarm/Error Type") + "\t" +
            QObject::tr("Alarm/Error Level") + "\t" +
            QObject::tr("Message") + "\t" + QObject::tr("Splice Name");
     return sHeader;
}

QString CSVAlarmLogData::AlarmLogEvent(void* AlarmLogObj)
{
    VariantToString* _Var2Str = VariantToString::Instance();
    DBPresetTable* _PresetDB = DBPresetTable::Instance();
    PresetElement PresetObj;
    QString sLogEvent;
    QDateTime TimeLabel = QDateTime::fromTime_t(((AlarmElement*) AlarmLogObj)->CreatedDate);
    QString sDate = TimeLabel.toString("yyyy/MM/dd");
    QString sTime = TimeLabel.toString("hh:mm:ss");
    sLogEvent = sDate + "\t";
    sLogEvent += sTime + "\t";
    QString AlarmType = ((AlarmElement*)AlarmLogObj)->AlarmType;
    sLogEvent += AlarmType + "\t";
    sLogEvent += _Var2Str->AlarmLevelToString(AlarmType);
    sLogEvent += ((AlarmElement*)AlarmLogObj)->AlarmMsg + "\t";
    int SpliceID = ((AlarmElement*)AlarmLogObj)->SpliceID;
    bool bResult = _PresetDB->QueryOneRecordFromTable(SpliceID, &PresetObj);
    if(bResult == false)
        sLogEvent += " ";
    else
        sLogEvent += PresetObj.SpliceName;
    return sLogEvent;
}

bool CSVAlarmLogData::ExportData(QList<int> IDList, QString fileUrl)
{
    DBAlarmLogTable* _AlarmLogDB = DBAlarmLogTable::Instance();
    AlarmElement AlarmLogObj;
    QString RowStr;
    QStringList ResultList;
    QString HeadStr = "";
    QString fileSource;
    bool bResult = false;
    ResultList.clear();
    for(int i = 0; i < IDList.size(); i++)
    {
        bResult = _AlarmLogDB->QueryOneRecordFromTable(IDList[i], &AlarmLogObj);
        if(bResult == false)
            continue;

        RowStr = AlarmLogEvent(&AlarmLogObj);
        ResultList.push_back(RowStr);
    }
    HeadStr = HeaderString();
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

    QDateTime TimeLabel = QDateTime::currentDateTime();
    QString TimeStr = TimeLabel.toString("yyyy/MM/dd hh:mm:ss");
    QString TitleStr = "Alarm Log Data " + TimeStr;
    out << TitleStr << '\n'
        << HeadStr << '\n';
    for(int i = 0; i < ResultList.size(); i++)
    {
        out << ResultList[i] << '\n';
    }
    csvFile.close();
    return true;
}

QString CSVAlarmLogData::GetExportString(int ID)
{
    UNUSED(ID);
    return "";
}

int CSVAlarmLogData::ImportData(QString StrValue)
{
    UNUSED(StrValue);
    return 0;
}
