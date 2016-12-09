#ifndef DBPARTTABLE_H
#define DBPARTTABLE_H

#include "Sqlit3Class.h"

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
    virtual bool QueryOneRecordFromTable(int ID, void* _obj);
    virtual bool DeleteEntireTable();
    virtual bool DeleteOneRecordFromTable(int ID, QString Name);

    virtual bool QueryOnlyUseName(QString Name, QMap<int, QString> *_obj);
    virtual bool QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj);
    virtual bool QueryUseNameAndTime(QString Name, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj);
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
