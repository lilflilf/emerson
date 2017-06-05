#include "CSVMaintenanceLogData.h"
#include "Modules/typedef.h"
#include "DataBase/DBMaintenanceLogTable.h"
#include "Interface/Maintenance/MaintenanceLog.h"
#include <QFile>
CSVMaintenanceLogData* CSVMaintenanceLogData::_instance = NULL;
CSVMaintenanceLogData* CSVMaintenanceLogData::Instance()
{
    if(_instance == 0){
        _instance = new CSVMaintenanceLogData();
    }
    return _instance;
}

CSVMaintenanceLogData::CSVMaintenanceLogData()
{

}

CSVMaintenanceLogData::~CSVMaintenanceLogData()
{

}

bool CSVMaintenanceLogData::ExportData(int ID, QString fileUrl)
{
    UNUSED(ID);
    UNUSED(fileUrl);
    return true;
}

QString CSVMaintenanceLogData::HeaderString()
{
    QString sHeader;
    sHeader = QObject::tr("Date") + "\t" + QObject::tr("Time") + "\t" +
            QObject::tr("Maintenance Type") + "\t" +
            QObject::tr("Message");
     return sHeader;
}

QString CSVMaintenanceLogData::MaintenanceLogEvent(void* MaintenanceLogObj)
{
    QString sLogEvent;
    QDateTime TimeLabel = QDateTime::fromTime_t(((MaintenanceLogElement*)MaintenanceLogObj)->CreatedDate);
    QString sDate = TimeLabel.toString("yyyy/MM/dd");
    QString sTime = TimeLabel.toString("hh:mm:ss");
    sLogEvent = sDate + "\t";
    sLogEvent += sTime + "\t";
    QString MaintenanceType = ((MaintenanceLogElement*)MaintenanceLogObj)->MaintenanceType;
    sLogEvent += MaintenanceType + "\t";
    sLogEvent += ((MaintenanceLogElement*)MaintenanceLogObj)->MaintenanceMsg;
    return sLogEvent;
}

bool CSVMaintenanceLogData::ExportData(QList<int> IDList, QString fileUrl)
{
    DBMaintenanceLogTable* _MaintenanceLogDB = DBMaintenanceLogTable::Instance();
    MaintenanceLogElement MaintenanceLogObj;
    QString RowStr;
    QStringList ResultList;
    QString HeadStr = "";
    QString fileSource;
    bool bResult = false;
    ResultList.clear();
    for(int i = 0; i < IDList.size(); i++)
    {
        bResult = _MaintenanceLogDB->QueryOneRecordFromTable(IDList[i], &MaintenanceLogObj);
        if(bResult == false)
            continue;

        RowStr = MaintenanceLogEvent(&MaintenanceLogObj);
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
    QString TitleStr = "Maintenance Log Data " + TimeStr;
    out << TitleStr << '\n'
        << HeadStr << '\n';
    for(int i = 0; i < ResultList.size(); i++)
    {
        out << ResultList[i] << '\n';
    }
    csvFile.close();
    return true;
}

QString CSVMaintenanceLogData::GetExportString(int ID)
{
    UNUSED(ID);
    return "";
}

int CSVMaintenanceLogData::ImportData(QString StrValue)
{
    UNUSED(StrValue);
    return 0;
}
