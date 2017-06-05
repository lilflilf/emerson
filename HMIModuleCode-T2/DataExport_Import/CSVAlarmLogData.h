#ifndef CSVALARMLOGDATA_H
#define CSVALARMLOGDATA_H
#include <QString>
#include "DataClass.h"

class CSVAlarmLogData : public DataClass
{
private:
    QString HeaderString();
    QString AlarmLogEvent(void* AlarmLogObj);
public:
    virtual bool ExportData(int ID, QString fileUrl);
    virtual bool ExportData(QList<int> IDList, QString fileUrl);
    virtual QString GetExportString(int ID);
    virtual int ImportData(QString StrValue);
public:
    static CSVAlarmLogData* Instance();
protected:
    CSVAlarmLogData();
private:
    static CSVAlarmLogData* _instance;
public:
    ~CSVAlarmLogData();
};

#endif // CSVALARMLOGDATA_H
