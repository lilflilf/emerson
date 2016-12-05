#include "DBMaintenanceLogTable.h"
#include "Interface/Maintenance/MaintenanceLog.h"
#include <QDebug>

DBMaintenanceLogTable* DBMaintenanceLogTable::_instance = NULL;
QString DBMaintenanceLogTable::MaintenanceLogDBFile = "MaintenanceLog.db";
QString DBMaintenanceLogTable::DatabaseDir = "c:\\BransonData\\History\\";
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

bool DBMaintenanceLogTable::CreateNewTable()
{
    QSqlQuery query(MaintenanceLogDBObj);
    bool bResult = MaintenanceLogDBObj.open();

//    bResult = query.exec(SQLSentence[CREATE_OPERATOR_TABLE]);   //run SQL

    if(bResult == false)
        qDebug() << "SQL ERROR:"<< query.lastError();

    MaintenanceLogDBObj.close();

    return bResult;
}

int DBMaintenanceLogTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    int iResult = -1;
    if(_obj == NULL)
        return false;

    QSqlQuery query(MaintenanceLogDBObj);
    bResult = MaintenanceLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }

//    query.prepare(SQLSentence[INSERT_OPERATOR_TABLE]);
    query.addBindValue(((MaintenanceLogElement*)_obj)->MaintenanceType);
    query.addBindValue(((MaintenanceLogElement*)_obj)->MaintenanceMsg);
    QDateTime TimeLabel = QDateTime::fromTime_t(((MaintenanceLogElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((MaintenanceLogElement*)_obj)->OperatorID);

    bResult = query.exec();
    if (bResult == false)   //run SQL
        qDebug() << "SQL ERROR:"<< query.lastError();
    else
        iResult = query.lastInsertId().toInt(&bResult);
    if(bResult == false)
        iResult = -1;
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

//    bResult = query.exec(SQLSentence[QUERY_ENTIRE_OPERATOR_TABLE]);
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
        qDebug() << "SQL ERROR:"<< query.lastError();
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
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_OPERATOR_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(TypeDefine);

    bResult = query.exec();
    if(bResult == false)
    {
        MaintenanceLogDBObj.close();
        qDebug() << "SQL ERROR:"<< query.lastError();
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
    ((MaintenanceLogElement*)_obj)->OperatorID = query.value("OperaterID").toInt();
    MaintenanceLogDBObj.close();
    return bResult;
}

bool DBMaintenanceLogTable::DeleteEntireTable()
{
    QSqlQuery query(MaintenanceLogDBObj);
    bool bResult = MaintenanceLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

//    bResult = query.exec(SQLSentence[DELETE_ENTIRE_OPERATOR_TABLE]);
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
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
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

//    query.prepare(SQLSentence[DELETE_ONE_RECORD_OPERATOR_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(TypeDefine);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
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
        qDebug() << "SQL ERROR1:"<< query.lastError();
        return bResult;
    }

//    query.prepare(SQLSentence[UPDATE_ONE_RECORD_OPERATOR_TABLE]);
    query.addBindValue(((MaintenanceLogElement*)_obj)->MaintenanceType);
    query.addBindValue(((MaintenanceLogElement*)_obj)->MaintenanceMsg);
    QDateTime TimeLabel = QDateTime::fromTime_t(((MaintenanceLogElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((MaintenanceLogElement*)_obj)->OperatorID);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
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
//    query.prepare("SELECT ID, OperatorName FROM Operator WHERE CreatedDate >= ?"
//                  " AND CreatedDate <= ?");
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
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    MaintenanceLogDBObj.close();
    return bResult;
}
