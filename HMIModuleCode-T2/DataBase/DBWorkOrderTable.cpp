#include "DBWorkOrderTable.h"
#include "Modules/UtilityClass.h"
#include "Interface/WorkOrderElement.h"
#include <QDebug>

DBWorkOrderTable* DBWorkOrderTable::_instance = NULL;
QString DBWorkOrderTable::WorkOrderFile = "WorkOrder.db";
QString DBWorkOrderTable::DatabaseDir = "c:\\BransonData\\Library\\";

const QString SQLSentence[] = {
    "CREATE TABLE WorkOrder ("                  /*0 Create WorkOrder Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "WorkOrderName VARCHAR UNIQUE, "
    "CreatedDate VARCHAR, OperatorID INT, "
    "NoOfPart INT, Quantity INT, CurrentPartCount INT, "
    "CurrentSpliceID INT, CurrentSpliceName VARCHAR, WorkOrderDone INT, "
    "JSONPartIndex VARCHAR, JSONMissSpliceList VARCHAR)",

    "INSERT INTO WorkOrder ("                   /*1 Insert record into Part Table*/
    "WorkOrderName, CreatedDate, OperatorID, "
    "NoOfPart, Quantity, CurrentPartCount, "
    "CurrentSpliceID, CurrentSpliceName, WorkOrderDone, "
    "JSONPartIndex, JSONMissSpliceList) "
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",

    "SELECT ID, WorkOrderName FROM WorkOrder",  /*2 Query Entire WorkOrder Table */

                                                /*3 Query One Record From Wire Table */
    "SELECT * FROM WorkOrder WHERE ID = ? AND WorkOrderName = ?",
    "SELECT * FROM WorkOrder WHERE ID = ?",     /*4 Query One Record only use ID */

    "DELETE FROM WorkOrder",                    /*5 Delete Entire WorkOrder Table*/

    "DELETE FROM WorkOrder WHERE ID = ? AND WorkOrderName = ?",
                                                /*6 Delete One Record from WorkOrder Table*/

    "UPDATE WorkOrder SET WorkOrderName = ?, CreatedDate = ?, OperatorID = ?, "
    "NoOfPart = ?, Quantity = ?, CurrentPartCount = ?, "
    "CurrentSpliceID = ?, CurrentSpliceName = ?, WorkOrderDone = ?, "
    "JSONPartIndex = ?, JSONMissSpliceList = ?"
    "WHERE ID = ?",                              /*7 Update One Record to WorkOrder Table*/

};

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
        if(!WorkOrderDBObj.tables().contains("WorkOrder")){
            CreateNewTable();
            InsertTestDataIntoTable();
        }
    }
    WorkOrderDBObj.close();
}

bool DBWorkOrderTable::InsertTestDataIntoTable()
{
    WorkOrderElement tmpWorkOrder;
    for (int i = 0; i < 2; i++)
    {
        if ( i == 0)
            tmpWorkOrder.WorkOrderName = "Honda CR-V";
        if ( i == 1)
            tmpWorkOrder.WorkOrderName = "VOLVO SPA V526 TT";
        tmpWorkOrder.CreatedDate = QDateTime::currentDateTime().toTime_t();
        tmpWorkOrder.OperatorID = 2;
        tmpWorkOrder.PartIndex.insert(1,"PartName");
        tmpWorkOrder.NoOfPart = tmpWorkOrder.PartIndex.size();

        tmpWorkOrder.Quantity = 10;
        tmpWorkOrder.CurrentPartCount = 30;

        tmpWorkOrder.MissSpliceList.insert(0, "MissSplice1");
        tmpWorkOrder.MissSpliceList.insert(1, "MissSplice2");
        tmpWorkOrder.MissSpliceList.insert(2, "MissSplice3");

        tmpWorkOrder.CurrentSplice.SpliceID = 5;
        tmpWorkOrder.CurrentSplice.SpliceName = "TestSplice";

        tmpWorkOrder.WorkOrderDone = false;
        InsertRecordIntoTable(&tmpWorkOrder);
    }
    return true;
}

DBWorkOrderTable::~DBWorkOrderTable()
{
    WorkOrderDBObj.close();
}

bool DBWorkOrderTable::CreateNewTable()
{
    QSqlQuery query(WorkOrderDBObj);
    bool bResult = WorkOrderDBObj.open();

    bResult = query.exec(SQLSentence[CREATE]);   //run SQL

    if(bResult == false)
        qDebug() << "SQL ERROR:"<< query.lastError();

    WorkOrderDBObj.close();

    return bResult;
}

int DBWorkOrderTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    int iResult = -1;
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

    query.prepare(SQLSentence[INSERT]);

    query.addBindValue(((WorkOrderElement*)_obj)->WorkOrderName);
    QDateTime TimeLabel = QDateTime::currentDateTime();
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
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
        qDebug() << "SQL ERROR:"<< query.lastError();
    else
        iResult = query.lastInsertId().toInt(&bResult);
    if(bResult == false)
        iResult = -1;
    WorkOrderDBObj.close();
    return iResult;
}

bool DBWorkOrderTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;
    QSqlQuery query(WorkOrderDBObj);
    bool bResult = WorkOrderDBObj.open();
    if(bResult == false)
        return bResult;

    bResult = query.exec(SQLSentence[QUERY_ENTIRE_TABLE]);
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

    query.prepare(SQLSentence[QUERY_ONE_RECORD]);
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
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((WorkOrderElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((WorkOrderElement*)_obj)->OperatorID = query.value("OperatorID").toInt();
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

bool DBWorkOrderTable::QueryOneRecordFromTable(int ID, void *_obj)
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

    query.prepare(SQLSentence[QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);

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
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((WorkOrderElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((WorkOrderElement*)_obj)->OperatorID = query.value("OperatorID").toInt();
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

    bResult = query.exec(SQLSentence[DELETE_ENTIRE_TABLE]);
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

    query.prepare(SQLSentence[DELETE_ONE_RECORD]);
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

    query.prepare(SQLSentence[UPDATE_ONE_RECORD]);
    query.addBindValue(((WorkOrderElement*)_obj)->WorkOrderName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((WorkOrderElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
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

bool DBWorkOrderTable::QueryOnlyUseName(QString Name, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WorkOrderDBObj);
    bool bResult = WorkOrderDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, WorkOrderName FROM WorkOrder WHERE WorkOrderName = ?");
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("WorkOrderName").toString());
    }
    else
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    WorkOrderDBObj.close();
    return bResult;
}

bool DBWorkOrderTable::QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WorkOrderDBObj);
    bool bResult = WorkOrderDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);

    query.prepare("SELECT ID, WorkOrderName FROM WorkOrder WHERE CreatedDate >= ?"
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
                           query.value("WorkOrderName").toString());
    }
    else
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    WorkOrderDBObj.close();
    return bResult;
}

bool DBWorkOrderTable::QueryUseNameAndTime(QString Name, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj)
{
    bool bResult = true;
    return bResult;
}
