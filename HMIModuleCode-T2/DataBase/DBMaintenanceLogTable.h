#ifndef DBMAINTENANCELOG_H
#define DBMAINTENANCELOG_H

#include "Sqlit3Class.h"
class DBMaintenanceLogTable : public SQLITCLASS
{
private:
    static QString MaintenanceLogDBFile;
    static QString DatabaseDir;
private:
    QSqlDatabase MaintenanceLogDBObj;

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
    virtual bool QueryUseNameAndTime(QString Name, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj);
    virtual void SwitchDBObject(bool IsModularProduction);

public:
    static DBMaintenanceLogTable* Instance();
protected:
    DBMaintenanceLogTable();
private:
    static DBMaintenanceLogTable* _instance;
public:
    ~DBMaintenanceLogTable();
};

#endif // DBMAINTENANCELOG_H
