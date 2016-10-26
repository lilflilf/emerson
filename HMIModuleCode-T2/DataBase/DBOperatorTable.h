#ifndef DBOPERATORTABLE_H
#define DBOPERATORTABLE_H

#include "Sqlit3Class.h"
class DBOperatorTable : public SQLITCLASS
{
private:
    static QString OperatorDBFile;
    static QString DatabaseDir;
private:
    QSqlDatabase OperatorDBObj;
public:
    virtual bool CreateNewTable();
    virtual bool InsertRecordIntoTable(void* _obj);
    virtual bool UpdateRecordIntoTable(void* _obj);
    virtual bool QueryEntireTable(QMap<int, QString>* _obj);
    virtual bool QueryOneRecordFromTable(int ID, QString Name, void* _obj);
    virtual bool DeleteEntireTable();
    virtual bool DeleteOneRecordFromTable(int ID, QString Name);

public:
    static DBOperatorTable* Instance();
protected:
    DBOperatorTable();
private:
    static DBOperatorTable* _instance;
public:
    ~DBOperatorTable();
};

#endif // DBOPERATORTABLE_H
