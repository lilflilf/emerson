#ifndef DBWIRETABLE_H
#define DBWIRETABLE_H

#include "Sqlit3Class.h"
enum{
    CREATE_WIRE_TABLE = 0,
    INSERT_WIRE_TABLE = 1,
    QUERY_ENTIRE_WIRE_TABLE = 2,
    QUERY_ONE_RECORD_WIRE_TABLE = 3,
    DELETE_ENTIRE_WIRE_TABLE = 4,
    DELETE_ONE_RECORD_WIRE_TABLE = 5,
    UPDATE_ONE_RECORD_WIRE_TABLE = 6,
};

class DBWireTable : public SQLITCLASS
{
private:
    static QString WireDBFile;
    static QString DatabaseDir;
private:
    QSqlDatabase WireDBObj;

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
    static DBWireTable* Instance();
protected:
    DBWireTable();
private:
    static DBWireTable* _instance;
public:
    ~DBWireTable();
};

#endif // DBWIRETABLE_H
