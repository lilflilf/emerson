#ifndef CSVMAINTENANCELOGDATA_H
#define CSVMAINTENANCELOGDATA_H
#include <QString>
#include "DataClass.h"

class CSVMaintenanceLogData : public DataClass
{
private:
    QString HeaderString();
    QString MaintenanceLogEvent(void* MaintenanceLogObj);
public:
    virtual bool ExportData(int ID, QString fileUrl);
    virtual bool ExportData(QList<int> IDList, QString fileUrl);
    virtual QString GetExportString(int ID);
    virtual int ImportData(QString StrValue);
public:
    static CSVMaintenanceLogData* Instance();
protected:
    CSVMaintenanceLogData();
private:
    static CSVMaintenanceLogData* _instance;
public:
    ~CSVMaintenanceLogData();
};

#endif // CSVMAINTENANCELOGDATA_H
