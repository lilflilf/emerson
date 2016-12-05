#ifndef DBPRESETTABLE_H
#define DBPRESETTABLE_H

#include "Sqlit3Class.h"
enum{
    CREATE_SPLICE_TABLE = 0,
    INSERT_SPLICE_TABLE = 1,
    QUERY_ENTIRE_SPLICE_TABLE = 2,
    QUERY_ONE_RECORD_SPLICE_TABLE = 3,
    DELETE_ENTIRE_SPLICE_TABLE = 4,
    DELETE_ONE_RECORD_SPLICE_TABLE = 5,
    UPDATE_ONE_RECORD_SPLICE_TABLE = 6,
};

class DBPresetTable : public SQLITCLASS
{
private:
    static QString SpliceDBFile;
    static QString DatabaseDir;
private:
    QSqlDatabase SpliceDBObj;

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
    static DBPresetTable* Instance();
protected:
    DBPresetTable();
    void InsertTestDataIntoTable();
private:
    static DBPresetTable* _instance;
public:
    ~DBPresetTable();
};

#endif // DBPRESETTABLE_H
