#ifndef DBWIRETABLE_H
#define DBWIRETABLE_H

#include "Sqlit3Class.h"
class DBWireTable : public SQLITCLASS
{
private:
    static QString WireDBFile;
    static QString DatabaseDir;
private:
    QSqlDatabase WireDBObj;

public:
    virtual bool CreateNewTable();
    virtual bool InsertRecordIntoTable(void* _obj);
    virtual bool UpdateRecordIntoTable(void* _obj);
    virtual bool QueryEntireTable(QMap<int, QString>* _obj);
    virtual bool QueryOneRecordFromTable(int ID, QString Name, void* _obj);
    virtual bool DeleteEntireTable();
    virtual bool DeleteOneRecordFromTable(int ID, QString Name);

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
