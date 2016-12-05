#ifndef DBOPERATORTABLE_H
#define DBOPERATORTABLE_H

#include "Sqlit3Class.h"
enum{
    CREATE_OPERATOR_TABLE = 0,
    INSERT_OPERATOR_TABLE = 1,
    QUERY_ENTIRE_OPERATOR_TABLE = 2,
    QUERY_ONE_RECORD_OPERATOR_TABLE = 3,
    DELETE_ENTIRE_OPERATOR_TABLE = 4,
    DELETE_ONE_RECORD_OPERATOR_TABLE = 5,
    UPDATE_ONE_RECORD_OPERATOR_TABLE = 6,
};

class DBOperatorTable : public SQLITCLASS
{
private:
    static QString OperatorDBFile;
    static QString DatabaseDir;
private:
    QSqlDatabase OperatorDBObj;
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
    static DBOperatorTable* Instance();
protected:
    DBOperatorTable();
private:
    static DBOperatorTable* _instance;
public:
    ~DBOperatorTable();
};

#endif // DBOPERATORTABLE_H
