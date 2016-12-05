#ifndef DBPARTTABLE_H
#define DBPARTTABLE_H

#include "Sqlit3Class.h"
enum{
    CREATE_PART_TABLE = 0,
    INSERT_PART_TABLE = 1,
    QUERY_ENTIRE_PART_TABLE = 2,
    QUERY_ONE_RECORD_PART_TABLE = 3,
    DELETE_ENTIRE_PART_TABLE = 4,
    DELETE_ONE_RECORD_PART_TABLE = 5,
    UPDATE_ONE_RECORD_PART_TABLE = 6,
};

class DBPartTable : public SQLITCLASS
{
private:
    static QString PartDBFile;
    static QString DatabaseDir;
private:
    QSqlDatabase PartDBObj;
public:
    virtual bool CreateNewTable();
    virtual int InsertRecordIntoTable(void* _obj);
    virtual bool UpdateRecordIntoTable(void* _obj);
    virtual bool QueryEntireTable(QMap<int, QString>* _obj);
    virtual bool QueryOneRecordFromTable(int ID, QString Name, void* _obj);
    virtual bool DeleteEntireTable();
    virtual bool DeleteOneRecordFromTable(int ID, QString Name);

    virtual bool QueryOnlyUseName(QString Name, QMap<int, QString> *_obj);
    virtual bool QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj);

public:
    static DBPartTable* Instance();
protected:
    DBPartTable();
    void InsertTestDataIntoTable();
private:
    static DBPartTable* _instance;
public:
    ~DBPartTable();
};

#endif // DBPARTTABLE_H
