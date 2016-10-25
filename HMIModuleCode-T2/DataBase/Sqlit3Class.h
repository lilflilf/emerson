#ifndef SQLITCLASS_H
#define SQLITCLASS_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include "Interface/definition.h"
#include "sqlsentence.h"

class SQLITCLASS
{
public:
    virtual bool CreateNewTable() = 0;
    virtual bool InsertRecordIntoTable(void* _obj) = 0;
    virtual bool UpdateRecordIntoTable(void* _obj) = 0;
    virtual bool QueryEntireTable(QMap<int, QString>* _obj) = 0;
    virtual bool QueryOneRecordFromTable(int ID, QString Name, void* _obj) = 0;
    virtual bool DeleteEntireTable() = 0;
    virtual bool DeleteOneRecordFromTable(int ID, QString Name) = 0;
};

#endif // SQLITCLASS_H
