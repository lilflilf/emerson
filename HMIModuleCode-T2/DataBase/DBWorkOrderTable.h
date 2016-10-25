#ifndef DBWORKORDERTABLE_H
#define DBWORKORDERTABLE_H

#include "Sqlit3Class.h"
class DBWorkOrderTable: public SQLITCLASS
{
private:
    static QString WorkOrderFile;
    static QString DatabaseDir;
private:
    QSqlDatabase WorkOrderDBObj;
public:
    virtual bool CreateNewTable();
    virtual bool InsertRecordIntoTable(void* _obj);
    virtual bool UpdateRecordIntoTable(void* _obj);
    virtual bool QueryEntireTable(QMap<int, QString>* _obj);
    virtual bool QueryOneRecordFromTable(int ID, QString Name, void* _obj);
    virtual bool DeleteEntireTable();
    virtual bool DeleteOneRecordFromTable(int ID, QString Name);

public:
    static DBWorkOrderTable* Instance();
protected:
    DBWorkOrderTable();
private:
    static DBWorkOrderTable* _instance;
public:
    ~DBWorkOrderTable();
};

#endif // DBWORKORDERTABLE_H
