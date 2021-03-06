#include "DBWorkOrderTable.h"
#include "Modules/UtilityClass.h"
#include "Interface/WorkOrderElement.h"
#include "Interface/interface.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonParseError>
#include <QFile>
#include <QDir>

DBWorkOrderTable* DBWorkOrderTable::_instance = NULL;
QString DBWorkOrderTable::WorkOrderFile = "WorkOrder.db";
QString DBWorkOrderTable::DatabaseDir = "c:\\BransonData\\Library\\";
QString DBWorkOrderTable::ModularDatabaseDir = "c:\\BransonData\\Modular Production\\";
const QString SQLSentence[] =
{
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
    if(_instance == 0)
    {
        _instance = new DBWorkOrderTable();
    }
    return _instance;
}

DBWorkOrderTable::DBWorkOrderTable()
{
    harnessTable = DBHarnessTable::Instance();
    WorkOrderDBObj = QSqlDatabase::addDatabase("QSQLITE", "WorkOrderDBObjConnect");
    WorkOrderDBObj.setDatabaseName(DatabaseDir + WorkOrderFile);
    if(WorkOrderDBObj.open())
    {
        if(!WorkOrderDBObj.tables().contains("WorkOrder"))
        {
            CreateNewTable();
//            InsertTestDataIntoTable();
        }
    }
    WorkOrderDBObj.close();
}

bool DBWorkOrderTable::OpenDBObject()
{
    bool bResult = false;
    struct BransonMessageBox tmpMsgBox;
    InterfaceClass* _Interface = InterfaceClass::Instance();
    QDir DBDirectory;
    mIsModularProduction = _Interface->StatusData.EnableModularFlag;
    if(mIsModularProduction == true)
    {
        if (DBDirectory.exists(ModularDatabaseDir + WorkOrderFile) == false)
        {
            tmpMsgBox.MsgTitle = QObject::tr("ERROR");
            tmpMsgBox.MsgPrompt = QObject::tr("Please make sure All the production files has been in the Modular Production!");
            tmpMsgBox.TipsMode = Critical;
            tmpMsgBox.func_ptr = NULL;
            _Interface->cMsgBox(&tmpMsgBox);
            qDebug()<<"Send Alarm signal";
            return bResult;
        }
    }

    QSqlQuery query(WorkOrderDBObj);
    if(WorkOrderDBObj.open() == false)
    {

        qDebug() << "SQL Open:"<< query.lastError();
        bResult = false;
    }
    else
        bResult = true;
    return bResult;
}

void DBWorkOrderTable::SwitchDBObject(bool IsModularProduction)
{
    mIsModularProduction = IsModularProduction;
    {WorkOrderDBObj.close();}
    if(mIsModularProduction == true)
    {
        WorkOrderDBObj.setDatabaseName(ModularDatabaseDir + WorkOrderFile);
    }
    else
    {
        WorkOrderDBObj.setDatabaseName(DatabaseDir + WorkOrderFile);
    }

    OpenDBObject();
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
        tmpWorkOrder.PartList.insert(1,"PartName");
        tmpWorkOrder.NoOfPart = tmpWorkOrder.PartList.size();

        tmpWorkOrder.Quantity = 10;
        tmpWorkOrder.CurrentPartCount = 30;

        tmpWorkOrder.MissPartList.insert(0, "MissSplice1");
        tmpWorkOrder.MissPartList.insert(1, "MissSplice2");
        tmpWorkOrder.MissPartList.insert(2, "MissSplice3");

        tmpWorkOrder.CurrentPartIndex.PartID = 5;
        tmpWorkOrder.CurrentPartIndex.PartName = "TestSplice";

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
    if(bResult == true)
        bResult = query.exec(SQLSentence[SQLITCLASS::CREATE]);   //run SQL
    if(bResult == false)
        qDebug() << "Work Order SQL ERROR:"<< query.lastError();

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
    bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }
    UtilityClass *_Utility = UtilityClass::Instance();
    query.prepare(SQLSentence[SQLITCLASS::INSERT]);
    query.addBindValue(((WorkOrderElement*)_obj)->WorkOrderName);
    QDateTime TimeLabel = QDateTime::currentDateTime();
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((WorkOrderElement*)_obj)->OperatorID);
    query.addBindValue(((WorkOrderElement*)_obj)->NoOfPart);
    query.addBindValue(((WorkOrderElement*)_obj)->Quantity);
    query.addBindValue(((WorkOrderElement*)_obj)->CurrentPartCount);
    query.addBindValue(((WorkOrderElement*)_obj)->CurrentPartIndex.PartID);
    query.addBindValue(((WorkOrderElement*)_obj)->CurrentPartIndex.PartName);
    query.addBindValue(((WorkOrderElement*)_obj)->WorkOrderDone);
    QString tmpJson;
    _Utility->MapJsonToString(&((WorkOrderElement*)_obj)->PartList, tmpJson);
    query.addBindValue(tmpJson);
    _Utility->MapJsonToString(&((WorkOrderElement*)_obj)->MissPartList, tmpJson);
    query.addBindValue(tmpJson);
    bResult = query.exec();   //run SQL
    if(bResult == false)
        qDebug() << "Work Order SQL ERROR:"<< query.lastError();
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
    bool bResult = OpenDBObject();
    if(bResult == false)
        return bResult;
    bResult = query.exec(SQLSentence[SQLITCLASS::QUERY_ENTIRE_TABLE]);
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
        qDebug() << "Work Order SQL ERROR:"<< query.lastError()<< __LINE__;
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
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "Work Order SQL ERROR:"<< query.lastError()<< __LINE__;
        return bResult;
    }
    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(Name);
    bResult = query.exec();
    if(bResult == false)
    {
        WorkOrderDBObj.close();
        qDebug() << "Work Order SQL ERROR:"<< query.lastError()<< __LINE__;
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
    _Utility->StringJsonToMap(tmpStr, &((WorkOrderElement*)_obj)->PartList);
    ((WorkOrderElement*)_obj)->NoOfPart = ((WorkOrderElement*)_obj)->PartList.size();
    ((WorkOrderElement*)_obj)->Quantity = query.value("Quantity").toInt();
    ((WorkOrderElement*)_obj)->CurrentPartCount = query.value("CurrentPartCount").toInt();
    tmpStr = query.value("JSONMissSpliceList").toString();
    _Utility->StringJsonToMap(tmpStr, &((WorkOrderElement*)_obj)->MissPartList);
    ((WorkOrderElement*)_obj)->CurrentPartIndex.PartID = query.value("CurrentSpliceID").toInt();
    ((WorkOrderElement*)_obj)->CurrentPartIndex.PartName = query.value("CurrentSpliceName").toString();
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
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "Work Order SQL ERROR:"<< query.lastError()<< __LINE__;
        return bResult;
    }
    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);
    bResult = query.exec();
    if(bResult == false)
    {
        WorkOrderDBObj.close();
        qDebug() << "Work Order SQL ERROR:"<< query.lastError()<< __LINE__;
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
    _Utility->StringJsonToMap(tmpStr, &((WorkOrderElement*)_obj)->PartList);
    ((WorkOrderElement*)_obj)->NoOfPart = ((WorkOrderElement*)_obj)->PartList.size();
    ((WorkOrderElement*)_obj)->Quantity = query.value("Quantity").toInt();
    ((WorkOrderElement*)_obj)->CurrentPartCount = query.value("CurrentPartCount").toInt();
    tmpStr = query.value("JSONMissSpliceList").toString();
    _Utility->StringJsonToMap(tmpStr, &((WorkOrderElement*)_obj)->MissPartList);
    ((WorkOrderElement*)_obj)->CurrentPartIndex.PartID = query.value("CurrentSpliceID").toInt();
    ((WorkOrderElement*)_obj)->CurrentPartIndex.PartName = query.value("CurrentSpliceName").toString();
    ((WorkOrderElement*)_obj)->WorkOrderDone = query.value("WorkOrderDone").toBool();
    WorkOrderDBObj.close();
    return bResult;
}

bool DBWorkOrderTable::DeleteEntireTable()
{
    QSqlQuery query(WorkOrderDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "Work Order SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.exec(SQLSentence[SQLITCLASS::DELETE_ENTIRE_TABLE]);
    if(bResult == false)
    {
        qDebug() << "Work Order SQL ERROR:"<< query.lastError();
    }
    WorkOrderDBObj.close();
    return bResult;
}

bool DBWorkOrderTable::DeleteOneRecordFromTable(int ID, QString Name)
{
    QSqlQuery query(WorkOrderDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "Work Order SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::DELETE_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "Work Order SQL ERROR:"<< query.lastError();
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
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR1:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::UPDATE_ONE_RECORD]);
    query.addBindValue(((WorkOrderElement*)_obj)->WorkOrderName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((WorkOrderElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((WorkOrderElement*)_obj)->OperatorID);
    query.addBindValue(((WorkOrderElement*)_obj)->PartList.size());
    query.addBindValue(((WorkOrderElement*)_obj)->Quantity);
    query.addBindValue(((WorkOrderElement*)_obj)->CurrentPartCount);
    query.addBindValue(((WorkOrderElement*)_obj)->CurrentPartIndex.PartID);
    query.addBindValue(((WorkOrderElement*)_obj)->CurrentPartIndex.PartName);
    query.addBindValue(((WorkOrderElement*)_obj)->WorkOrderDone);
    QString tmpStr;
    _Utility->MapJsonToString(&((WorkOrderElement*)_obj)->PartList, tmpStr);
    query.addBindValue(tmpStr);
    _Utility->MapJsonToString(&((WorkOrderElement*)_obj)->MissPartList, tmpStr);
    query.addBindValue(tmpStr);
    query.addBindValue(((WorkOrderElement*)_obj)->WorkOrderID);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "Work Order SQL ERROR:"<< query.lastError();
    }
    WorkOrderDBObj.close();
    return bResult;
}

bool DBWorkOrderTable::QueryOnlyUseName(QString Name, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WorkOrderDBObj);
    bool bResult = OpenDBObject();
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
        qDebug() << "Work Order SQL ERROR:"<< query.lastError();
    }

    WorkOrderDBObj.close();
    return bResult;
}

bool DBWorkOrderTable::QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WorkOrderDBObj);
    bool bResult = OpenDBObject();
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
        qDebug() << "Work Order SQL ERROR:"<< query.lastError();
    }

    WorkOrderDBObj.close();
    return bResult;
}

bool DBWorkOrderTable::QueryUseNameAndTime(QString Name, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WorkOrderDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, WorkOrderName FROM WorkOrder "
                  "WHERE WorkOrderName = ? AND CreatedDate >= ? AND CreatedDate <= ?");
    query.addBindValue(Name);
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
        qDebug() << "Work Order SQL ERROR:"<< query.lastError();
    }

    WorkOrderDBObj.close();
    return bResult;
}

bool DBWorkOrderTable::exportData(int workOrderId, QString fileUrl)
{
    qDebug() << "DBWorkOrderTable " << workOrderId << fileUrl;
    QString queryStr;
    QString lineValue = "";
    QSqlQuery query(WorkOrderDBObj);
    QString harnessData;
    bool bResult = OpenDBObject();
    QString tempHarnessData;
    QString fileSource;
    if(bResult == true)
    {
        queryStr = QString("SELECT * FROM WorkOrder WHERE ID == '%1'").arg(workOrderId);
        query.prepare(queryStr);
        bResult = query.exec();
        if (bResult) {
            bResult = query.next();
            if(bResult) {
                for (int i = 0;i < 12;i++)
                {
                    if (i == 10)
                    {
                        QJsonParseError json_error;
                        QJsonDocument parse_document = QJsonDocument::fromJson(query.value(i).toString().toLatin1(), &json_error);
                        if(json_error.error == QJsonParseError::NoError)
                        {
                            if(parse_document.isObject())
                            {
                                QJsonObject obj = parse_document.object();
                                QJsonObject::const_iterator iterator = obj.constBegin();
                                for(int i = 0; i< obj.count(); i++)
                                {
                                    iterator = obj.constFind(QString::number(i, 10));
                                    if(iterator != obj.constEnd())
                                    {
                                        QString value = iterator.value().toString();
                                        QStringList strList = value.split(";");
                                        tempHarnessData = harnessTable->GetExportString(((QString)strList.at(0)).toInt());
                                        harnessData.append(tempHarnessData + "$");
                                    }
                                }
                            }
                        }
                        lineValue.append(harnessData + ",");
                    }
                    else
                        lineValue.append(query.value(i).toString() + ",");
                }
                fileSource = fileUrl;
                if (fileSource.contains("file:///"))
                    fileSource = fileSource.mid(8);
                QFile csvFile(fileSource);
                if (csvFile.open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate))
                {
                    QTextStream out(&csvFile);
                    out << "WorkOrderData" << '\n' << lineValue;
                    csvFile.close();
                }
            }
        }
        WorkOrderDBObj.close();
    }
    return bResult;
}

int DBWorkOrderTable::importData(QString value, QMap<int, QString> partMap)
{
    QString lineData;
    QStringList lineList;
    WorkOrderElement myWorkOrder;
    bool ok;
    int ret;

    lineData = value;
    lineList = lineData.split(",");
    if (lineList.size() >= 11) {
        myWorkOrder.WorkOrderName = lineList[1];
        myWorkOrder.OperatorID = QString(lineList[3]).toInt(&ok,10);
        myWorkOrder.NoOfPart = partMap.size();
        myWorkOrder.Quantity = QString(lineList[5]).toInt(&ok,10);
        myWorkOrder.PartList = partMap;
    }
    ret = InsertRecordIntoTable(&myWorkOrder);
    while (ret == -1) {
        qDebug() << "part";
        QMap<int ,QString> tempMap;
        QueryOnlyUseName(myWorkOrder.WorkOrderName, &tempMap);
        if (tempMap.size() > 0) {
            myWorkOrder.WorkOrderName = myWorkOrder.WorkOrderName + "(1)";
            ret = InsertRecordIntoTable(&myWorkOrder);
        }
        else if (tempMap.size() == 0)
            return -1;
    }
    return ret;
}
