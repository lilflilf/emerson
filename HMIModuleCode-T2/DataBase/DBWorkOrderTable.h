#ifndef DBWORKORDERTABLE_H
#define DBWORKORDERTABLE_H

#include "Sqlit3Class.h"
#include "DBPartTable.h"
class DBWorkOrderTable: public SQLITCLASS
{
private:
    static QString WorkOrderFile;
    static QString DatabaseDir;
private:
    QSqlDatabase WorkOrderDBObj;
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

    bool exportData(int workOrderId, QString fileUrl);
    int importData(QString value,QMap<int, QString> partMap);
public:
    static DBWorkOrderTable* Instance();
protected:
    DBWorkOrderTable();
    bool InsertTestDataIntoTable();
    DBPartTable *partTable;
private:
    static DBWorkOrderTable* _instance;
public:
    ~DBWorkOrderTable();
};

#endif // DBWORKORDERTABLE_H
