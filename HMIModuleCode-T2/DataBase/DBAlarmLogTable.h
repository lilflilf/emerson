#ifndef DBALARMHISTORYTABLE_H
#define DBALARMHISTORYTABLE_H

#include "Sqlit3Class.h"
class DBAlarmLogTable : public SQLITCLASS
{
private:
    static QString AlarmLogDBFile;
    static QString DatabaseDir;
private:
    QSqlDatabase AlarmLogDBObj;
public:
    virtual bool CreateNewTable();
    virtual int InsertRecordIntoTable(void* _obj);
    virtual bool UpdateRecordIntoTable(void* _obj);
    virtual bool QueryEntireTable(QMap<int, QString>* _obj);
    virtual bool QueryOneRecordFromTable(int ID, QString Name, void* _obj);
    virtual bool QueryOneRecordFromTable(int ID, void* _obj);
    virtual bool DeleteEntireTable();
    virtual bool DeleteOneRecordFromTable(int ID, QString Name);

    virtual bool QueryOnlyUseName(QString Name, QMap<int, QString> *_obj);
    virtual bool QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj);

public:
    static DBAlarmLogTable* Instance();
protected:
    DBAlarmLogTable();
private:
    static DBAlarmLogTable* _instance;
public:
    ~DBAlarmLogTable();
};

#endif // DBALARMHISTORYTABLE_H
