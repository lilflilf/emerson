#ifndef SQLITCLASS_H
#define SQLITCLASS_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include "Interface/definition.h"


class SQLITCLASS
{
private:
    static QString DatabaseDir;
    static QString WorkOrderFile;
    static QString PartDBFile;
    static QString SpliceDBFile;
    static QString WireDBFile;
private:
    QSqlDatabase WorkOrderDBObj;
    QSqlDatabase PartDBObj;
    QSqlDatabase SpliceDBObj;
    QSqlDatabase WireDBObj;
private:
//    bool CreateNewWireTable();
//    bool CreateNewSpliceTable();
//    bool CreateNewPartTable();
//    bool CreateNewWorkOrderTable();

public:
    bool InsertRecordIntoWireTable(WireElementStructure* _WireElement);
    bool InsertRecordIntoPresetTable(PresetElement* _PresetElement);
    bool InsertRecordIntoPartTable(PartElement* _PartElement);
    bool InsertRecordIntoWorkOrderTable(WorkOrder* _WorkOrder);
    bool QueryEntireWireTable(QMap<int, QString>* _Index);
    bool QueryEntirePresetTable(QMap<int, QString>* _Index);
    bool QueryEntirePartTable(QMap<int, QString>* _Index);
    bool QueryEntireWorkOrderTable(QMap<int, QString>* _Index);
    bool QueryOneWireTable(int ID, QString Name, WireElementStructure* _WireElement);
    bool QueryOnePresetTable(int ID, QString Name, PresetElement* _PresetElement);
    bool QueryOnePartTable(int ID, QString Name, PartElement* _PartElement);
    bool QueryOneWorkOrderTable(int ID, QString Name, WorkOrder* _WorkOrder);

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
