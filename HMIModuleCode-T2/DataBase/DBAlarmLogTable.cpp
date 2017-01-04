#include "DBAlarmLogTable.h"
#include "Interface/AlarmElement.h"
#include <QDebug>

DBAlarmLogTable* DBAlarmLogTable::_instance = NULL;
QString DBAlarmLogTable::AlarmLogDBFile = "AlarmLog.db";
QString DBAlarmLogTable::DatabaseDir = "c:\\BransonData\\History\\";
const QString SQLSentence[] = {
    "CREATE TABLE AlarmLog ("                       /*0 Create Alarm Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "AlarmMsg VARCHAR, CreatedDate VARCHAR, "
    "AlarmType VARCHAR, SpliceID INT, OperatorID INT, IsReseted BOOLEAN)",

    "INSERT INTO AlarmLog ("                        /*1 Insert record into Alarm Table*/
    "AlarmMsg, CreatedDate, AlarmType, "
    "SpliceID, OperatorID, IsReseted) "
    "VALUES (?, ?, ?, ?, ?, ?)",

    "SELECT ID, AlarmType FROM AlarmLog",           /*2 Query Entire Alarm Table */

    "SELECT * FROM AlarmLog WHERE ID = ? AND AlarmType = ?",
                                                /*3 Query One Record From Alarm Table */
    "SELECT * FROM AlarmLog WHERE ID = ?",         /*4 Query One Record Only Use ID */

    "DELETE FROM AlarmLog",                        /*5 Delete Entire Alarm Table*/

    "DELETE FROM AlarmLog WHERE ID = ? AND AlarmType = ?",
                                                /*6 Delete One Record from Alarm Table*/

    "UPDATE AlarmLog SET AlarmMsg = ?, CreatedDate = ?, AlarmType = ?, "
    "SpliceID = ?, OperatorID = ? , IsReseted = ? WHERE ID = ?",
                                                /*7 Update One Record to Alarm Table*/

};
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
    bResult = query.exec(SQLSentence[CREATE]);   //run SQL
    if(bResult == false)
        qDebug() << "Alarm Table SQL ERROR:"<< query.lastError();
    AlarmLogDBObj.close();

    return bResult;
}

int DBAlarmLogTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    int iResult = -1;
    if(_obj == NULL)
        return false;

    QSqlQuery query(AlarmLogDBObj);
    bResult = AlarmLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }
    query.prepare(SQLSentence[INSERT]);
    query.addBindValue(((AlarmElement*)_obj)->AlarmMsg);
    QDateTime TimeLabel = QDateTime::currentDateTime();
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((AlarmElement*)_obj)->AlarmType);
    query.addBindValue(((AlarmElement*)_obj)->SpliceID);
    query.addBindValue(((AlarmElement*)_obj)->OperatorID);
    query.addBindValue(((AlarmElement*)_obj)->IsReseted);

    bResult = query.exec();
    if (bResult == false)   //run SQL
        qDebug() << "Alarm Table SQL ERROR:"<< query.lastError();
    else
        query.lastInsertId().toInt(&bResult);
    if(bResult == false)
        iResult = -1;
    AlarmLogDBObj.close();
    return iResult;
}

bool DBAlarmLogTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(AlarmLogDBObj);
    bool bResult = AlarmLogDBObj.open();
    if(bResult == false)
        return bResult;

    bResult = query.exec(SQLSentence[QUERY_ENTIRE_TABLE]);
    if (bResult == true)
    {
        _obj->clear();
        while(query.next())
        {
            _obj->insert(query.value("ID").toInt(),
                           query.value("AlarmType").toString());
        }
    }
    else
    {
        qDebug() << "Alarm Table SQL ERROR:"<< query.lastError();
    }

    AlarmLogDBObj.close();

    return bResult;
}

bool DBAlarmLogTable::QueryOneRecordFromTable(int ID, QString AlarmType, void *_obj)
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

    query.prepare(SQLSentence[QUERY_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(AlarmType);

    bResult = query.exec();
    if(bResult == false)
    {
        AlarmLogDBObj.close();
        qDebug() << "Alarm Table SQL ERROR:"<< query.lastError();
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
    ((AlarmElement*)_obj)->AlarmType = query.value("AlarmType").toString();
    ((AlarmElement*)_obj)->SpliceID = query.value("SpliceID").toInt();
    ((AlarmElement*)_obj)->OperatorID = query.value("OperatorID").toInt();
    ((AlarmElement*)_obj)->IsReseted = query.value("IsReseted").toBool();
    AlarmLogDBObj.close();
    return bResult;
}

bool DBAlarmLogTable::QueryOneRecordFromTable(int ID, void* _obj)
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

    query.prepare(SQLSentence[QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);

    bResult = query.exec();
    if(bResult == false)
    {
        AlarmLogDBObj.close();
        qDebug() << "Alarm Table SQL ERROR:"<< query.lastError();
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
    ((AlarmElement*)_obj)->AlarmType = query.value("AlarmType").toString();
    ((AlarmElement*)_obj)->SpliceID = query.value("SpliceID").toInt();
    ((AlarmElement*)_obj)->OperatorID = query.value("OperatorID").toInt();
    ((AlarmElement*)_obj)->IsReseted = query.value("IsReseted").toBool();
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

    bResult = query.exec(SQLSentence[DELETE_ENTIRE_TABLE]);
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    AlarmLogDBObj.close();
    return bResult;
}

bool DBAlarmLogTable::DeleteOneRecordFromTable(int ID, QString AlarmType)
{
    QSqlQuery query(AlarmLogDBObj);
    bool bResult = AlarmLogDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[DELETE_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(AlarmType);

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
        qDebug() << "Alarm Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[UPDATE_ONE_RECORD]);
    query.addBindValue(((AlarmElement*)_obj)->AlarmMsg);
    QDateTime TimeLabel = QDateTime::fromTime_t(((AlarmElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((AlarmElement*)_obj)->AlarmType);
    query.addBindValue(((AlarmElement*)_obj)->SpliceID);
    query.addBindValue(((AlarmElement*)_obj)->OperatorID);
    query.addBindValue(((AlarmElement*)_obj)->AlarmID);
    query.addBindValue(((AlarmElement*)_obj)->IsReseted);

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
    query.prepare("SELECT ID, AlarmType FROM AlarmLog WHERE CreatedDate >= ?"
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
                           query.value("AlarmType").toString());
    }
    else
    {
        qDebug() << "ALarm Table SQL ERROR:"<< query.lastError();
    }

    AlarmLogDBObj.close();
    return bResult;
}

bool DBAlarmLogTable::QueryUseNameAndTime(QString AlarmType, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(AlarmLogDBObj);
    bool bResult = AlarmLogDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, AlarmType FROM AlarmLog WHERE "
                  "AlarmType = ? AND CreatedDate >= ? AND CreatedDate <= ?");
    query.addBindValue(AlarmType);
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
                           query.value("AlarmType").toString());
    }
    else
    {
        qDebug() << "Alarm Table SQL ERROR:"<< query.lastError();
    }

    AlarmLogDBObj.close();
    return bResult;
}

bool DBAlarmLogTable::QueryOnlyUseField(QString FieldName, QVariant Value, QMap<int, QString> *_obj, bool Orderby)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(AlarmLogDBObj);
    bool bResult = AlarmLogDBObj.open();
    if(bResult == false)
        return bResult;

    if(bResult == true)
    {
        QString queryStr = "";
        if(Orderby == true)
            queryStr = QString("SELECT ID, AlarmType FROM AlarmLog WHERE %1 = ? ORDER BY CreatedDate ASC").arg(FieldName);
        else
            queryStr = QString("SELECT ID, AlarmType FROM AlarmLog WHERE %1 = ? ORDER BY CreatedDate DESC").arg(FieldName);
        query.prepare(queryStr);
        query.addBindValue(Value);
        bResult = query.exec();
    }
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("AlarmType").toString());
    }
    else
    {
        qDebug() << "Alarm Table SQL ERROR:"<< query.lastError();
    }

    AlarmLogDBObj.close();
    return bResult;

}
