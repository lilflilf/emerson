#include "DBWorkOrderTable.h"
#include "Modules/UtilityClass.h"
#include <QDebug>

DBWorkOrderTable* DBWorkOrderTable::_instance = NULL;
QString DBWorkOrderTable::WorkOrderFile = "WorkOrder.db";
QString DBWorkOrderTable::DatabaseDir = "c:\\BransonData\\Library\\";
DBWorkOrderTable* DBWorkOrderTable::Instance()
{
    if(_instance == 0){
        _instance = new DBWorkOrderTable();
    }
    return _instance;
}

DBWorkOrderTable::DBWorkOrderTable()
{
    WorkOrderDBObj = QSqlDatabase::addDatabase("QSQLITE", "WorkOrderDBObjConnect");
    WorkOrderDBObj.setDatabaseName(DatabaseDir + WorkOrderFile);
    if(WorkOrderDBObj.open())
    {
        if(!WorkOrderDBObj.tables().contains("WorkOrder"))
            CreateNewTable();
    }
    WorkOrderDBObj.close();
}

DBWorkOrderTable::~DBWorkOrderTable()
{
    WorkOrderDBObj.close();
}

bool DBWorkOrderTable::CreateNewTable()
{
    QSqlQuery query(WorkOrderDBObj);
    bool bResult = WorkOrderDBObj.open();

    bResult = query.exec(SQLSentence[CREATE_WORKORDER_TABLE]);   //run SQL

    if(bResult == false)
        qDebug() << "SQL ERROR:"<< query.lastError();

    WorkOrderDBObj.close();

    return bResult;
}

bool DBWorkOrderTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    if(_obj == NULL)
        return false;

    QSqlQuery query(WorkOrderDBObj);
    bResult = WorkOrderDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }

    UtilityClass *_Utility = UtilityClass::Instance();

    query.prepare(SQLSentence[INSERT_WORKORDER_TABLE]);

    query.addBindValue(((WorkOrderElement*)_obj)->WorkOrderName);
    query.addBindValue(((WorkOrderElement*)_obj)->CreatedDate);
    query.addBindValue(((WorkOrderElement*)_obj)->OperatorID);
    query.addBindValue(((WorkOrderElement*)_obj)->NoOfPart);
    query.addBindValue(((WorkOrderElement*)_obj)->Quantity);
    query.addBindValue(((WorkOrderElement*)_obj)->CurrentPartCount);
    query.addBindValue(((WorkOrderElement*)_obj)->CurrentSplice.SpliceID);
    query.addBindValue(((WorkOrderElement*)_obj)->CurrentSplice.SpliceName);
    query.addBindValue(((WorkOrderElement*)_obj)->WorkOrderDone);

    QString tmpJson;
    _Utility->MapJsonToString(&((WorkOrderElement*)_obj)->PartIndex, tmpJson);
    query.addBindValue(tmpJson);

    _Utility->MapJsonToString(&((WorkOrderElement*)_obj)->MissSpliceList, tmpJson);
    query.addBindValue(tmpJson);

    bResult = query.exec();   //run SQL

    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }
    WorkOrderDBObj.close();

    return bResult;
}

bool DBWorkOrderTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;
    QSqlQuery query(WorkOrderDBObj);
    bool bResult = WorkOrderDBObj.open();
    if(bResult == false)
        return bResult;

    bResult = query.exec(SQLSentence[QUERY_ENTIRE_WORKORDER_TABLE]);
    if (bResult == true)
    {
        _obj->clear();
        while(query.next())
        {
            _obj->insert(query.value("ID").toInt(),
                           query.value("WorkOrderName").toString());
        }
    }
    else
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    WorkOrderDBObj.close();
    return bResult;
}

bool DBWorkOrderTable::QueryOneRecordFromTable(int ID, QString Name, void *_obj)
{
    if(_obj == NULL)
        return false;
    UtilityClass *_Utility = UtilityClass::Instance();
    QSqlQuery query(WorkOrderDBObj);
    bool bResult = WorkOrderDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[QUERY_ONE_RECORD_WORKORDER_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        WorkOrderDBObj.close();
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        WorkOrderDBObj.close();
        return bResult;
    }

    ((WorkOrderElement*)_obj)->WorkOrderID = query.value("ID").toInt();
    ((WorkOrderElement*)_obj)->WorkOrderName = query.value("WorkOrderName").toString();
    ((WorkOrderElement*)_obj)->CreatedDate = query.value("CreatedDate").toString();
    ((WorkOrderElement*)_obj)->OperatorID = query.value("OperatorID").toString();
    QString tmpStr = query.value("JSONPartIndex").toString();
    _Utility->StringJsonToMap(tmpStr, &((WorkOrderElement*)_obj)->PartIndex);
    ((WorkOrderElement*)_obj)->NoOfPart = ((WorkOrderElement*)_obj)->PartIndex.size();
    ((WorkOrderElement*)_obj)->Quantity = query.value("Quantity").toInt();
    ((WorkOrderElement*)_obj)->CurrentPartCount = query.value("CurrentPartCount").toInt();
    tmpStr = query.value("JSONMissSpliceList").toString();
    _Utility->StringJsonToMap(tmpStr, &((WorkOrderElement*)_obj)->MissSpliceList);
    ((WorkOrderElement*)_obj)->CurrentSplice.SpliceID = query.value("CurrentSpliceID").toInt();
    ((WorkOrderElement*)_obj)->CurrentSplice.SpliceName = query.value("CurrentSpliceName").toString();
    ((WorkOrderElement*)_obj)->WorkOrderDone = query.value("WorkOrderDone").toBool();

    WorkOrderDBObj.close();

    return bResult;
}

bool DBWorkOrderTable::DeleteEntireTable()
{
    QSqlQuery query(WorkOrderDBObj);
    bool bResult = WorkOrderDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.exec(SQLSentence[DELETE_ENTIRE_WORKORDER_TABLE]);
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }
    WorkOrderDBObj.close();
    return bResult;
}

bool DBWorkOrderTable::DeleteOneRecordFromTable(int ID, QString Name)
{
    QSqlQuery query(WorkOrderDBObj);
    bool bResult = WorkOrderDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[DELETE_ONE_RECORD_WORKORDER_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }
    WorkOrderDBObj.close();
    return bResult;
}

bool DBWorkOrderTable::UpdateRecordIntoTable(void *_obj)
{
    if(_obj == NULL)
        return false;
    UtilityClass* _Utility = UtilityClass::Instance();
    QSqlQuery query(WorkOrderDBObj);
    bool bResult = WorkOrderDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR1:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[UPDATE_ONE_RECORD_WORKORDER_TABLE]);
    query.addBindValue(((WorkOrderElement*)_obj)->WorkOrderName);
    query.addBindValue(((WorkOrderElement*)_obj)->CreatedDate);
    query.addBindValue(((WorkOrderElement*)_obj)->OperatorID);
    query.addBindValue(((WorkOrderElement*)_obj)->PartIndex.size());
    query.addBindValue(((WorkOrderElement*)_obj)->Quantity);
    query.addBindValue(((WorkOrderElement*)_obj)->CurrentPartCount);
    query.addBindValue(((WorkOrderElement*)_obj)->CurrentSplice.SpliceID);
    query.addBindValue(((WorkOrderElement*)_obj)->CurrentSplice.SpliceName);
    query.addBindValue(((WorkOrderElement*)_obj)->WorkOrderDone);
    QString tmpStr;
    _Utility->MapJsonToString(&((WorkOrderElement*)_obj)->PartIndex, tmpStr);
    query.addBindValue(tmpStr);
    _Utility->MapJsonToString(&((WorkOrderElement*)_obj)->MissSpliceList, tmpStr);
    query.addBindValue(tmpStr);
    query.addBindValue(((WorkOrderElement*)_obj)->WorkOrderID);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }
    WorkOrderDBObj.close();
    return bResult;
}
