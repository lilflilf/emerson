#include "DBMaintenanceLogTable.h"
#include "Interface/Maintenance/MaintenanceLog.h"
#include "Modules/typedef.h"
#include <QDebug>

DBMaintenanceLogTable* DBMaintenanceLogTable::_instance = NULL;
QString DBMaintenanceLogTable::MaintenanceLogDBFile = "MaintenanceLog.db";
QString DBMaintenanceLogTable::DatabaseDir = "c:\\BransonData\\History\\";

const QString SQLSentence[] = {
    "CREATE TABLE MaintenanceLog ("                 /*0 Create Maintenance Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "MaintenanceType VARCHAR, MaintenanceMsg VARCHAR, "
    "CreatedDate VARCHAR, OperatorID INT)",

    "INSERT INTO MaintenanceLog ("                       /*1 Insert record into Maintenance Table*/
    "MaintenanceType, MaintenanceMsg, CreatedDate, "
    "OperatorID) "
    "VALUES (?, ?, ?, ?)",

    "SELECT ID, MaintenanceType FROM MaintenanceLog",    /*2 Query Entire Maintenance Table */

    "SELECT * FROM MaintenanceLog WHERE ID = ? AND MaintenanceType = ?",
                                                      /*3 Query One Record From Maintenance Table */
    "SELECT * FROM MaintenanceLog WHERE ID = ?",         /*4 Query One Record Only Use ID */

    "DELETE FROM MaintenanceLog",                        /*5 Delete Entire Maintenance Table*/

    "DELETE FROM MaintenanceLog WHERE ID = ? AND MaintenanceType = ?",
                                                /*6 Delete One Record from Maintenance Table*/

    "UPDATE MaintenanceLog SET MaintenanceType = ?, MaintenanceMsg = ?, CreatedDate = ?, "
    "OperatorID = ? WHERE ID = ?",
                                                /*7 Update One Record to Maintenance Table*/

};

DBMaintenanceLogTable* DBMaintenanceLogTable::Instance()
{
    if(_instance == 0){
        _instance = new DBMaintenanceLogTable();
    }
    return _instance;
}

DBMaintenanceLogTable::DBMaintenanceLogTable()
{
    MaintenanceLogDBObj = QSqlDatabase::addDatabase("QSQLITE", "MaintenanceLogDBObjConnect");
    MaintenanceLogDBObj.setDatabaseName(DatabaseDir + MaintenanceLogDBFile);
    if(MaintenanceLogDBObj.open())
    {
        if(!MaintenanceLogDBObj.tables().contains("MaintenanceLog"))
            CreateNewTable();
    }
    MaintenanceLogDBObj.close();
}

DBMaintenanceLogTable::~DBMaintenanceLogTable()
{
    MaintenanceLogDBObj.close();
}

void DBMaintenanceLogTable::SwitchDBObject(bool IsModularProduction)
{
    UNUSED(IsModularProduction);
    return;
}

bool DBMaintenanceLogTable::CreateNewTable()
{
    QSqlQuery query(MaintenanceLogDBObj);
    bool bResult = MaintenanceLogDBObj.open();
    bResult = query.exec(SQLSentence[SQLITCLASS::CREATE]);   //run SQL
    if(bResult == false)
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
    MaintenanceLogDBObj.close();
    return bResult;
}

int DBMaintenanceLogTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    int iResult = ERROR;
    if(_obj == NULL)
        return false;

    QSqlQuery query(MaintenanceLogDBObj);
    bResult = MaintenanceLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Maintenance SQL Open:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[INSERT]);
    query.addBindValue(((MaintenanceLogElement*)_obj)->MaintenanceType);
    query.addBindValue(((MaintenanceLogElement*)_obj)->MaintenanceMsg);
    QDateTime TimeLabel = QDateTime::currentDateTime();
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((MaintenanceLogElement*)_obj)->OperatorID);

    bResult = query.exec();
    if (bResult == false)   //run SQL
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
    else
        iResult = query.lastInsertId().toInt(&bResult);
    if(bResult == false)
        iResult = ERROR;
    MaintenanceLogDBObj.close();
    return iResult;
}

bool DBMaintenanceLogTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(MaintenanceLogDBObj);
    bool bResult = MaintenanceLogDBObj.open();
    if(bResult == false)
        return bResult;

    bResult = query.exec(SQLSentence[SQLITCLASS::QUERY_ENTIRE_TABLE]);
    if (bResult == true)
    {
        _obj->clear();
        while(query.next())
        {
            _obj->insert(query.value("ID").toInt(),
                           query.value("MaintenanceType").toString());
        }
    }
    else
    {
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
    }

    MaintenanceLogDBObj.close();

    return bResult;
}

bool DBMaintenanceLogTable::QueryOneRecordFromTable(int ID, QString TypeDefine, void *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(MaintenanceLogDBObj);
    bool bResult = MaintenanceLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(TypeDefine);

    bResult = query.exec();
    if(bResult == false)
    {
        MaintenanceLogDBObj.close();
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        MaintenanceLogDBObj.close();
        return bResult;
    }

    ((MaintenanceLogElement*)_obj)->MaintenanceLogID = query.value("ID").toInt();
    ((MaintenanceLogElement*)_obj)->MaintenanceType = query.value("MaintenanceType").toString();
    ((MaintenanceLogElement*)_obj)->MaintenanceMsg = query.value("MaintenanceMsg").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((MaintenanceLogElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((MaintenanceLogElement*)_obj)->OperatorID = query.value("OperatorID").toInt();
    MaintenanceLogDBObj.close();
    return bResult;
}

bool DBMaintenanceLogTable::QueryOneRecordFromTable(int ID, void *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(MaintenanceLogDBObj);
    bool bResult = MaintenanceLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);

    bResult = query.exec();
    if(bResult == false)
    {
        MaintenanceLogDBObj.close();
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        MaintenanceLogDBObj.close();
        return bResult;
    }

    ((MaintenanceLogElement*)_obj)->MaintenanceLogID = query.value("ID").toInt();
    ((MaintenanceLogElement*)_obj)->MaintenanceType = query.value("MaintenanceType").toString();
    ((MaintenanceLogElement*)_obj)->MaintenanceMsg = query.value("MaintenanceMsg").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((MaintenanceLogElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((MaintenanceLogElement*)_obj)->OperatorID = query.value("OperatorID").toInt();
    MaintenanceLogDBObj.close();
    return bResult;
}

bool DBMaintenanceLogTable::QueryOneRecordFromTable(int ID, QStringList &ResultStr)
{
    QSqlQuery query(MaintenanceLogDBObj);
    bool bResult = MaintenanceLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);

    bResult = query.exec();
    if(bResult == false)
    {
        MaintenanceLogDBObj.close();
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        MaintenanceLogDBObj.close();
        return bResult;
    }
    ResultStr.clear();
    ResultStr.append(query.value("ID").toString());
    ResultStr.append(query.value("MaintenanceType").toString());
    ResultStr.append(query.value("MaintenanceMsg").toString());
    ResultStr.append(query.value("CreatedDate").toString());
    ResultStr.append(query.value("OperatorID").toString());
    MaintenanceLogDBObj.close();
    return bResult;
}

bool DBMaintenanceLogTable::DeleteEntireTable()
{
    QSqlQuery query(MaintenanceLogDBObj);
    bool bResult = MaintenanceLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.exec(SQLSentence[SQLITCLASS::DELETE_ENTIRE_TABLE]);
    if(bResult == false)
    {
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
    }

    MaintenanceLogDBObj.close();
    return bResult;
}

bool DBMaintenanceLogTable::DeleteOneRecordFromTable(int ID, QString TypeDefine)
{
    QSqlQuery query(MaintenanceLogDBObj);
    bool bResult = MaintenanceLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::DELETE_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(TypeDefine);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
    }
    MaintenanceLogDBObj.close();
    return bResult;
}

bool DBMaintenanceLogTable::UpdateRecordIntoTable(void *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(MaintenanceLogDBObj);
    bool bResult = MaintenanceLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::UPDATE_ONE_RECORD]);
    query.addBindValue(((MaintenanceLogElement*)_obj)->MaintenanceType);
    query.addBindValue(((MaintenanceLogElement*)_obj)->MaintenanceMsg);
    QDateTime TimeLabel = QDateTime::fromTime_t(((MaintenanceLogElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((MaintenanceLogElement*)_obj)->OperatorID);
    query.addBindValue(((MaintenanceLogElement*)_obj)->MaintenanceLogID);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
    }
    MaintenanceLogDBObj.close();
    return bResult;
}

bool DBMaintenanceLogTable::QueryOnlyUseName(QString Name, QMap<int, QString> *_obj)
{
    _obj->clear();
    Name.clear();
    return true;
}

bool DBMaintenanceLogTable::QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(MaintenanceLogDBObj);
    bool bResult = MaintenanceLogDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, MaintenanceType FROM MaintenanceLog WHERE CreatedDate >= ?"
                  " AND CreatedDate <= ?");
    QDateTime TimeLabel = QDateTime::fromTime_t(time_from);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    TimeLabel = QDateTime::fromTime_t(time_to);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));

    bResult = query.exec();
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("MaintenanceType").toString());
    }
    else
    {
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
    }

    MaintenanceLogDBObj.close();
    return bResult;
}

bool DBMaintenanceLogTable::QueryUseNameAndTime(QString TypeDefine, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(MaintenanceLogDBObj);
    bool bResult = MaintenanceLogDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, MaintenanceType FROM MaintenanceLog WHERE "
                  "MaintenanceType = ? AND CreatedDate >= ? "
                  "AND CreatedDate <= ?");
    query.addBindValue(TypeDefine);
    QDateTime TimeLabel = QDateTime::fromTime_t(time_from);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    TimeLabel = QDateTime::fromTime_t(time_to);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));

    bResult = query.exec();
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("MaintenanceType").toString());
    }
    else
    {
        qDebug() << "Maintenance Table SQL ERROR:"<< query.lastError();
    }

    MaintenanceLogDBObj.close();
    return bResult;
}
