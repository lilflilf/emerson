#ifndef SQLITCLASS_H
#define SQLITCLASS_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>



class SQLITCLASS
{
private:
    static QString DatabaseDir;
    static QString PartDBFile;
    static QString SpliceDBFile;
    static QString WireDBFile;
private:
    QSqlDatabase PartDBObj;
    QSqlDatabase SpliceDBObj;
    QSqlDatabase WireDBObj;
private:
//    bool CreateNewWireTable();
//    bool CreateNewSpliceTable();
//    bool CreateNewPartTable();
//    bool CreateNewWorkOrderTable();

public:
    bool CreateNewDatabase();
    bool InsertRecordIntoWireTable(QSqlDatabase *_DBObject);
private:
    bool SQL_Execute(QSqlDatabase *_DBObject, QString SQL_Sentence);
public:
    static SQLITCLASS* Instance();
protected:
    SQLITCLASS();
private:
    static SQLITCLASS* _instance;
public:
    ~SQLITCLASS();
};

#endif // SQLITCLASS_H
