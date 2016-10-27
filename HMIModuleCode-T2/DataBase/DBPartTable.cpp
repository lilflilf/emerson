#include "DBPartTable.h"
#include "Modules/UtilityClass.h"
#include <QDebug>

DBPartTable* DBPartTable::_instance = NULL;
QString DBPartTable::PartDBFile   = "Part.db";
QString DBPartTable::DatabaseDir = "c:\\BransonData\\Library\\";
DBPartTable* DBPartTable::Instance()
{
    if(_instance == 0){
        _instance = new DBPartTable();
    }
    return _instance;
}

DBPartTable::DBPartTable()
{
    PartDBObj = QSqlDatabase::addDatabase("QSQLITE", "PartDBObjConnect");
    PartDBObj.setDatabaseName(DatabaseDir + PartDBFile);
    if(PartDBObj.open())
    {
        if(!PartDBObj.tables().contains("Part"))
            CreateNewTable();
    }
    PartDBObj.close();
}

DBPartTable::~DBPartTable()
{
    PartDBObj.close();
}

bool DBPartTable::CreateNewTable()
{
    QSqlQuery query(PartDBObj);
    bool bResult = PartDBObj.open();

    bResult = query.exec(SQLSentence[CREATE_PART_TABLE]);   //run SQL

    if(bResult == false)
        qDebug() << "SQL ERROR:"<< query.lastError();

    PartDBObj.close();

    return bResult;
}

bool DBPartTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    if(_obj == NULL)
        return false;

    QSqlQuery query(PartDBObj);
    bResult = PartDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }

    UtilityClass *_Utility = UtilityClass::Instance();

    query.prepare(SQLSentence[INSERT_PART_TABLE]);

    query.addBindValue(((PartElement*)_obj)->PartName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((PartElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((PartElement*)_obj)->OperatorID);
    query.addBindValue(((PartElement*)_obj)->PartTypeSetting.ProcessMode);
    query.addBindValue(((PartElement*)_obj)->PartTypeSetting.WorkStations.
                       TotalWorkstation);
    query.addBindValue(((PartElement*)_obj)->PartTypeSetting.WorkStations.
                       MaxSplicesPerWorkstation);
    query.addBindValue(((PartElement*)_obj)->PartTypeSetting.BoardLayout.Rows);
    query.addBindValue(((PartElement*)_obj)->PartTypeSetting.BoardLayout.
                       Columns);
    query.addBindValue(((PartElement*)_obj)->PartTypeSetting.BoardLayout.
                       MaxSplicesPerZone);
    query.addBindValue(((PartElement*)_obj)->NoOfSplice);

    QString tmpJson;
    _Utility->MapJsonToString(&((PartElement*)_obj)->SpliceIndex,tmpJson);
    query.addBindValue(tmpJson);

    bResult = query.exec();
    if (bResult == false)   //run SQL
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    PartDBObj.close();
    return bResult;
}

bool DBPartTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(PartDBObj);
    bool bResult = PartDBObj.open();
    if(bResult == false)
        return bResult;

    bResult = query.exec(SQLSentence[QUERY_ENTIRE_PART_TABLE]);
    if (bResult == true)
    {
        _obj->clear();
        while(query.next())
        {
            _obj->insert(query.value("ID").toInt(),
                           query.value("PartName").toString());
        }
    }
    else
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    PartDBObj.close();

    return bResult;
}

bool DBPartTable::QueryOneRecordFromTable(int ID, QString Name, void *_obj)
{
    if(_obj == NULL)
        return false;

    UtilityClass *_Utility = UtilityClass::Instance();
    QSqlQuery query(PartDBObj);
    bool bResult = PartDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[QUERY_ONE_RECORD_PART_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        PartDBObj.close();
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        PartDBObj.close();
        return bResult;
    }

    ((PartElement*)_obj)->PartID = query.value("ID").toInt();
    ((PartElement*)_obj)->PartName = query.value("PartName").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((PartElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((PartElement*)_obj)->OperatorID = query.value("OperatorID").toInt();
    ((PartElement*)_obj)->PartTypeSetting.ProcessMode =
            (enum PROCESSMODE)query.value("ProcessMode").toInt();
    ((PartElement*)_obj)->PartTypeSetting.WorkStations.TotalWorkstation =
            query.value("TotalWorkstation").toInt();
    ((PartElement*)_obj)->PartTypeSetting.WorkStations.MaxSplicesPerWorkstation =
            query.value("MaxSplicesPerWorkstation").toInt();
    ((PartElement*)_obj)->PartTypeSetting.BoardLayout.Rows = query.value("Rows").toInt();
    ((PartElement*)_obj)->PartTypeSetting.BoardLayout.Columns = query.value("Columns").toInt();
    ((PartElement*)_obj)->PartTypeSetting.BoardLayout.MaxSplicesPerZone =
            query.value("MaxSplicePerZone").toInt();
    QString tmpStr = query.value("JSONSplice").toString();
    _Utility->StringJsonToMap(tmpStr, &((PartElement*)_obj)->SpliceIndex);

    ((PartElement*)_obj)->NoOfSplice = ((PartElement*)_obj)->SpliceIndex.size();

    PartDBObj.close();
    return bResult;
}

bool DBPartTable::DeleteEntireTable()
{
    QSqlQuery query(PartDBObj);
    bool bResult = PartDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.exec(SQLSentence[DELETE_ENTIRE_PART_TABLE]);
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    PartDBObj.close();
    return bResult;
}

bool DBPartTable::DeleteOneRecordFromTable(int ID, QString Name)
{
    QSqlQuery query(PartDBObj);
    bool bResult = PartDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[DELETE_ONE_RECORD_PART_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }
    PartDBObj.close();
    return bResult;
}

bool DBPartTable::UpdateRecordIntoTable(void *_obj)
{
    if(_obj == NULL)
        return false;
    UtilityClass* _Utility = UtilityClass::Instance();
    QSqlQuery query(PartDBObj);
    bool bResult = PartDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR1:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[UPDATE_ONE_RECORD_PART_TABLE]);
    query.addBindValue(((PartElement*)_obj)->PartName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((PartElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((PartElement*)_obj)->OperatorID);
    query.addBindValue(((PartElement*)_obj)->PartTypeSetting.ProcessMode);
    query.addBindValue(((PartElement*)_obj)->PartTypeSetting.WorkStations.TotalWorkstation);
    query.addBindValue(((PartElement*)_obj)->PartTypeSetting.WorkStations.MaxSplicesPerWorkstation);
    query.addBindValue(((PartElement*)_obj)->PartTypeSetting.BoardLayout.Rows);
    query.addBindValue(((PartElement*)_obj)->PartTypeSetting.BoardLayout.Columns);
    query.addBindValue(((PartElement*)_obj)->PartTypeSetting.BoardLayout.MaxSplicesPerZone);
    query.addBindValue(((PartElement*)_obj)->SpliceIndex.size());
    QString tmpStr;
    _Utility->MapJsonToString(&((PartElement*)_obj)->SpliceIndex, tmpStr);
    query.addBindValue(tmpStr);
    query.addBindValue(((PartElement*)_obj)->PartID);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }
    PartDBObj.close();
    return bResult;
}

bool DBPartTable::QueryOnlyUseName(QString Name, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(PartDBObj);
    bool bResult = PartDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, PartName FROM Part WHERE PartName = ?");
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("PartName").toString());
    }
    else
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    PartDBObj.close();
    return bResult;
}

bool DBPartTable::QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(PartDBObj);
    bool bResult = PartDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, WireName FROM Wire WHERE CreatedDate >= ?"
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
                           query.value("PartName").toString());
    }
    else
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    PartDBObj.close();
    return bResult;
}
