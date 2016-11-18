#include "DBAlarmLogTable.h"
#include <QDebug>

DBAlarmLogTable* DBAlarmLogTable::_instance = NULL;
QString DBAlarmLogTable::AlarmLogDBFile = "AlarmLog.db";
QString DBAlarmLogTable::DatabaseDir = "c:\\BransonData\\History\\";
DBAlarmLogTable* DBAlarmLogTable::Instance()
{
    if(_instance == 0){
        _instance = new DBAlarmLogTable();
    }
    return _instance;
}

DBAlarmLogTable::DBAlarmLogTable()
{
    AlarmLogDBObj = QSqlDatabase::addDatabase("QSQLITE", "AlarmLogDBObjConnect");
    AlarmLogDBObj.setDatabaseName(DatabaseDir + AlarmLogDBFile);
    if(AlarmLogDBObj.open())
    {
        if(!AlarmLogDBObj.tables().contains("AlarmLog"))
            CreateNewTable();
    }
    AlarmLogDBObj.close();
}

DBAlarmLogTable::~DBAlarmLogTable()
{
    AlarmLogDBObj.close();
}

bool DBAlarmLogTable::CreateNewTable()
{
    QSqlQuery query(AlarmLogDBObj);
    bool bResult = AlarmLogDBObj.open();

//    bResult = query.exec(SQLSentence[CREATE_OPERATOR_TABLE]);   //run SQL

    if(bResult == false)
        qDebug() << "SQL ERROR:"<< query.lastError();

    AlarmLogDBObj.close();

    return bResult;
}

bool DBAlarmLogTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    if(_obj == NULL)
        return false;

    QSqlQuery query(AlarmLogDBObj);
    bResult = AlarmLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }

//    query.prepare(SQLSentence[INSERT_OPERATOR_TABLE]);
    query.addBindValue(((AlarmElement*)_obj)->AlarmMsg);
    QDateTime TimeLabel = QDateTime::fromTime_t(((AlarmElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((AlarmElement*)_obj)->AlarmType);
    query.addBindValue(((AlarmElement*)_obj)->WeldResultID);
    query.addBindValue(((AlarmElement*)_obj)->OperatorID);

    bResult = query.exec();
    if (bResult == false)   //run SQL
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    AlarmLogDBObj.close();
    return bResult;
}

bool DBAlarmLogTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(AlarmLogDBObj);
    bool bResult = AlarmLogDBObj.open();
    if(bResult == false)
        return bResult;

//    bResult = query.exec(SQLSentence[QUERY_ENTIRE_OPERATOR_TABLE]);
    if (bResult == true)
    {
        _obj->clear();
        while(query.next())
        {
            _obj->insert(query.value("ID").toInt(),
                           query.value("AlarmMsg").toString());
        }
    }
    else
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    AlarmLogDBObj.close();

    return bResult;
}

bool DBAlarmLogTable::QueryOneRecordFromTable(int ID, QString AlarmMsg, void *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(AlarmLogDBObj);
    bool bResult = AlarmLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_OPERATOR_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(AlarmMsg);

    bResult = query.exec();
    if(bResult == false)
    {
        AlarmLogDBObj.close();
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        AlarmLogDBObj.close();
        return bResult;
    }

    ((AlarmElement*)_obj)->AlarmID = query.value("ID").toInt();
    ((AlarmElement*)_obj)->AlarmMsg = query.value("AlarmMsg").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((AlarmElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((AlarmElement*)_obj)->AlarmType = query.value("AlarmType").toInt();
    ((AlarmElement*)_obj)->WeldResultID = query.value("WeldResultID").toInt();
    ((AlarmElement*)_obj)->OperatorID = query.value("OperaterID").toInt();
    AlarmLogDBObj.close();
    return bResult;
}

bool DBAlarmLogTable::DeleteEntireTable()
{
    QSqlQuery query(AlarmLogDBObj);
    bool bResult = AlarmLogDBObj.open();
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

    AlarmLogDBObj.close();
    return bResult;
}

bool DBAlarmLogTable::DeleteOneRecordFromTable(int ID, QString AlarmMsg)
{
    QSqlQuery query(AlarmLogDBObj);
    bool bResult = AlarmLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

//    query.prepare(SQLSentence[DELETE_ONE_RECORD_OPERATOR_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(AlarmMsg);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }
    AlarmLogDBObj.close();
    return bResult;
}

bool DBAlarmLogTable::UpdateRecordIntoTable(void *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(AlarmLogDBObj);
    bool bResult = AlarmLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR1:"<< query.lastError();
        return bResult;
    }

//    query.prepare(SQLSentence[UPDATE_ONE_RECORD_OPERATOR_TABLE]);
    query.addBindValue(((AlarmElement*)_obj)->AlarmMsg);
    QDateTime TimeLabel = QDateTime::fromTime_t(((AlarmElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((AlarmElement*)_obj)->AlarmType);
    query.addBindValue(((AlarmElement*)_obj)->WeldResultID);
    query.addBindValue(((AlarmElement*)_obj)->OperatorID);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }
    AlarmLogDBObj.close();
    return bResult;
}

bool DBAlarmLogTable::QueryOnlyUseName(QString Name, QMap<int, QString> *_obj)
{
    _obj->clear();
    Name.clear();
    return true;
}

bool DBAlarmLogTable::QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(AlarmLogDBObj);
    bool bResult = AlarmLogDBObj.open();
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
                           query.value("AlarmMsg").toString());
    }
    else
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    AlarmLogDBObj.close();
    return bResult;
}
