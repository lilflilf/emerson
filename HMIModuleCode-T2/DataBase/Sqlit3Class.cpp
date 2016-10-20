#include "Sqlit3Class.h"
#include "sqlsentence.h"
#include <QDebug>

SQLITCLASS* SQLITCLASS::_instance = 0;
QString SQLITCLASS::DatabaseDir  = "c:\\BransonData\\Library\\";
QString SQLITCLASS::PartDBFile   = "Part.db";
QString SQLITCLASS::SpliceDBFile = "Splice.db";
QString SQLITCLASS::WireDBFile   = "Wire.db";
#define SQLCREATEWIRETABLE ;

SQLITCLASS* SQLITCLASS::Instance()
{
    if(_instance == 0){
        _instance = new SQLITCLASS();
    }
    return _instance;
}

SQLITCLASS::SQLITCLASS()
{
    PartDBObj = QSqlDatabase::addDatabase("QSQLITE");
    PartDBObj.setDatabaseName(DatabaseDir + PartDBFile);
    SpliceDBObj = QSqlDatabase::addDatabase("QSQLITE");
    SpliceDBObj.setDatabaseName(DatabaseDir + SpliceDBFile);
    SQL_Execute(&SpliceDBObj,SQLSentence[CREATESPLICETABLE]);
    WireDBObj   = QSqlDatabase::addDatabase("QSQLITE");
    WireDBObj.setDatabaseName(DatabaseDir + WireDBFile);
    SQL_Execute(&WireDBObj,SQLSentence[CREATEWIRETABLE]);
    InsertRecordIntoWireTable(&WireDBObj);

}

SQLITCLASS::~SQLITCLASS()
{
    PartDBObj.close();
    SpliceDBObj.close();
    WireDBObj.close();
}

//bool SQLITCLASS::CreateNewWireTable()
//{


//}



//bool SQLITCLASS::CreateNewDatabase()
//{
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName(DatabaseDir + DatabaseFile);
//    return db.open();
//}

//bool SQLITCLASS::CreateNewTable()
//{

//}


bool SQLITCLASS::SQL_Execute(QSqlDatabase *_DBObject, QString SQL_Sentence)
{
    qDebug() << "SQL_Execute" << SQL_Sentence;

    bool bResult = _DBObject->open();
    if(bResult == false)
        return bResult;

    QSqlQuery query;
    if (query.exec(SQL_Sentence))   //run SQL
        bResult = true;
    else
    {
        bResult = false;
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    _DBObject->close();

    return bResult;
}

 bool SQLITCLASS::InsertRecordIntoWireTable(QSqlDatabase *_DBObject)
 {
     bool bResult = _DBObject->open();
     if(bResult == false)
         return bResult;

     QSqlQuery query;

     query.prepare("INSERT INTO Wire (WireName, CreatedDate, OperatorID, Color,"
                   "StripeTye, StripeColor, Gauge, MetalType, HorizontalLocation,"
                   "VerticalLocation, VerticalPosition)"
                   "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
     query.addBindValue("JerryWang");
     query.addBindValue("20161019");
     query.addBindValue("JW");
     query.addBindValue("GREEN");
     query.addBindValue(0);
     query.addBindValue("YELLOW");
     query.addBindValue(50);
     query.addBindValue(0);
     query.addBindValue(0);
     query.addBindValue(1);
     query.addBindValue(0);
     //query.value()

     if (query.exec())   //run SQL
         bResult = true;
     else
     {
         bResult = false;
         qDebug() << "SQL ERROR:"<< query.lastError();
     }

     _DBObject->close();

     return bResult;
 }
