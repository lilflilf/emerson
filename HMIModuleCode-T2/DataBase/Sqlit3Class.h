#ifndef SQLITCLASS_H
#define SQLITCLASS_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include <QDateTime>
//#include "Interface/Definition.h"
//#include "sqlsentence.h"

enum{
    CREATE = 0,
    INSERT = 1,
    QUERY_ENTIRE_TABLE = 2,
    QUERY_ONE_RECORD = 3,
    QUERY_ONE_RECORD_ONLY_ID = 4,
    DELETE_ENTIRE_TABLE = 5,
    DELETE_ONE_RECORD = 6,
    UPDATE_ONE_RECORD = 7,
};

class SQLITCLASS
{
public:
    virtual bool CreateNewTable() = 0;
    virtual int InsertRecordIntoTable(void* _obj) = 0;
    virtual bool UpdateRecordIntoTable(void* _obj) = 0;
    virtual bool QueryEntireTable(QMap<int, QString>* _obj) = 0;
    virtual bool QueryOneRecordFromTable(int ID, QString Name, void* _obj) = 0;
    virtual bool QueryOneRecordFromTable(int ID, void* _obj) = 0;
    virtual bool DeleteEntireTable() = 0;
    virtual bool DeleteOneRecordFromTable(int ID, QString Name) = 0;

    virtual bool QueryOnlyUseName(QString Name, QMap<int, QString>* _obj) = 0;
    virtual bool QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString>* _obj) = 0;
    virtual bool QueryUseNameAndTime(QString Name, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj) = 0;
};

#endif // SQLITCLASS_H
