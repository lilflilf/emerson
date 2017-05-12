#include "DBHarnessTable.h"
#include "Modules/UtilityClass.h"
#include "Interface/HarnessElement.h"
#include "Interface/interface.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonParseError>
#include <QFile>
#include <QDir>

DBHarnessTable* DBHarnessTable::_instance = NULL;
QString DBHarnessTable::HarnessDBFile   = "Harness.db";
QString DBHarnessTable::DatabaseDir = "c:\\BransonData\\Library\\";
QString DBHarnessTable::ModularDatabaseDir = "c:\\BransonData\\Modular Production\\";

const QString SQLSentence[] = {
    "CREATE TABLE Harness ("                       /*0 Create Harness Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "HarnessName VARCHAR UNIQUE, "
    "CreatedDate VARCHAR, OperatorID INT, "
    /* PartTypeSetting */
    "ProcessMode ENUM,"
    "TotalWorkstation INT, MaxSplicesPerWorkstation INT, "
    "Rows INT, Columns INT, MaxSplicesPerZone INT, "
    "NoOfSplice INT, JSONSplice VARCHAR)",

    "INSERT INTO Harness ("                        /*1 Insert record into Harness Table*/
    "HarnessName, CreatedDate, OperatorID, "
    "ProcessMode, TotalWorkstation, MaxSplicesPerWorkstation, "
    "Rows, Columns, MaxSplicesPerZone, NoOfSplice, JSONSplice) "
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",

    "SELECT ID, HarnessName FROM Harness",            /*2 Query Entire Harness Table */

    "SELECT * FROM Harness WHERE ID = ? AND HarnessName = ?",
                                                   /*3 Query One Record From Harness Table */
    "SELECT * FROM Harness WHERE ID = ?",          /*4 Query One Record Only Use ID */

    "DELETE FROM Harness",                         /*5 Delete Entire Harness Table*/

    "DELETE FROM Harness WHERE ID = ? AND HarnessName = ?",
                                                /*6 Delete One Record from Harness Table*/

    "UPDATE Harness SET HarnessName = ?, CreatedDate = ?, OperatorID = ?, "
    "ProcessMode = ?, TotalWorkstation = ?, MaxSplicesPerWorkstation = ?, "
    "Rows = ?, Columns = ?, MaxSplicesPerZone = ?, NoOfSplice = ?, JSONSplice = ? "
    "WHERE ID = ?",                             /*7 Update One Record to Harness Table*/

};

DBHarnessTable* DBHarnessTable::Instance()
{
    if(_instance == 0){
        _instance = new DBHarnessTable();
    }
    return _instance;
}

DBHarnessTable::DBHarnessTable()
{
//    spliceTable = DBPresetTable::Instance();
    HarnessDBObj = QSqlDatabase::addDatabase("QSQLITE", "HarnessDBObjConnect");
    HarnessDBObj.setDatabaseName(DatabaseDir + HarnessDBFile);
    if(HarnessDBObj.open())
    {
        if(!HarnessDBObj.tables().contains("Harness")) {
            CreateNewTable();
//            InsertTestDataIntoTable();
        }
    }
    HarnessDBObj.close();
}

bool DBHarnessTable::OpenDBObject()
{
    bool bResult = false;
    struct BransonMessageBox tmpMsgBox;
    InterfaceClass* _Interface = InterfaceClass::Instance();
    QDir DBDirectory;
    mIsModularProduction = _Interface->StatusData.EnableModularFlag;
    if(mIsModularProduction == true)
    {
        if (DBDirectory.exists(ModularDatabaseDir + HarnessDBFile) == false)
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

    QSqlQuery query(HarnessDBObj);
    if(HarnessDBObj.open() == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        bResult = false;
    }else
        bResult = true;
    return bResult;
}

void DBHarnessTable::SwitchDBObject(bool IsModularProduction)
{
    mIsModularProduction = IsModularProduction;
    {HarnessDBObj.close();}
    if(mIsModularProduction == true)
    {
        HarnessDBObj.setDatabaseName(ModularDatabaseDir + HarnessDBFile);
    }
    else
    {
        HarnessDBObj.setDatabaseName(DatabaseDir + HarnessDBFile);
    }

    OpenDBObject();
    HarnessDBObj.close();
}

DBHarnessTable::~DBHarnessTable()
{
    HarnessDBObj.close();
}

bool DBHarnessTable::CreateNewTable()
{
    QSqlQuery query(HarnessDBObj);
    bool bResult = HarnessDBObj.open();

    bResult = query.exec(SQLSentence[SQLITCLASS::CREATE]);   //run SQL

    if(bResult == false)
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();

    HarnessDBObj.close();

    return bResult;
}

int DBHarnessTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    int iResult = -1;
    if(_obj == NULL)
        return false;

    QSqlQuery query(HarnessDBObj);
    bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }

    UtilityClass *_Utility = UtilityClass::Instance();

    query.prepare(SQLSentence[SQLITCLASS::INSERT]);

    query.addBindValue(((HarnessElement*)_obj)->HarnessName);
    QDateTime TimeLabel = QDateTime::currentDateTime();
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((HarnessElement*)_obj)->OperatorID);
    query.addBindValue(((HarnessElement*)_obj)->HarnessTypeSetting.ProcessMode);
    query.addBindValue(((HarnessElement*)_obj)->HarnessTypeSetting.WorkStations.
                       TotalWorkstation);
    query.addBindValue(((HarnessElement*)_obj)->HarnessTypeSetting.WorkStations.
                       MaxSplicesPerWorkstation);
    query.addBindValue(((HarnessElement*)_obj)->HarnessTypeSetting.BoardLayout.Rows);
    query.addBindValue(((HarnessElement*)_obj)->HarnessTypeSetting.BoardLayout.
                       Columns);
    query.addBindValue(((HarnessElement*)_obj)->HarnessTypeSetting.BoardLayout.
                       MaxSplicesPerZone);
    query.addBindValue(((HarnessElement*)_obj)->NoOfSplice);


    QString tmpJson;
    _Utility->MapJsonToString(&((HarnessElement*)_obj)->SpliceList,tmpJson);
    query.addBindValue(tmpJson);

    bResult = query.exec();
    if (bResult == false)   //run SQL
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
    else
        iResult = query.lastInsertId().toInt(&bResult);
    if(bResult == false)
        iResult = -1;
    HarnessDBObj.close();
    return iResult;
}

bool DBHarnessTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(HarnessDBObj);
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
                           query.value("HarnessName").toString());
        }
    }
    else
    {
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
    }

    HarnessDBObj.close();

    return bResult;
}

bool DBHarnessTable::QueryOneRecordFromTable(int ID, QString Name, void *_obj)
{
    if(_obj == NULL)
        return false;

    UtilityClass *_Utility = UtilityClass::Instance();
    QSqlQuery query(HarnessDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        HarnessDBObj.close();
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        HarnessDBObj.close();
        return bResult;
    }

    ((HarnessElement*)_obj)->HarnessID = query.value("ID").toInt();
    ((HarnessElement*)_obj)->HarnessName = query.value("HarnessName").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((HarnessElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((HarnessElement*)_obj)->OperatorID = query.value("OperatorID").toInt();
    ((HarnessElement*)_obj)->HarnessTypeSetting.ProcessMode =
            (enum PROCESSMODE)query.value("ProcessMode").toInt();
    ((HarnessElement*)_obj)->HarnessTypeSetting.WorkStations.TotalWorkstation =
            query.value("TotalWorkstation").toInt();
    ((HarnessElement*)_obj)->HarnessTypeSetting.WorkStations.MaxSplicesPerWorkstation =
            query.value("MaxSplicesPerWorkstation").toInt();
    ((HarnessElement*)_obj)->HarnessTypeSetting.BoardLayout.Rows = query.value("Rows").toInt();
    ((HarnessElement*)_obj)->HarnessTypeSetting.BoardLayout.Columns = query.value("Columns").toInt();
    ((HarnessElement*)_obj)->HarnessTypeSetting.BoardLayout.MaxSplicesPerZone =
            query.value("MaxSplicesPerZone").toInt();
    QString tmpStr = query.value("JSONSplice").toString();
    _Utility->StringJsonToMap(tmpStr, &((HarnessElement*)_obj)->SpliceList);

    ((HarnessElement*)_obj)->NoOfSplice = ((HarnessElement*)_obj)->SpliceList.size();

    HarnessDBObj.close();
    return bResult;
}

bool DBHarnessTable::QueryOneRecordFromTable(int ID, void *_obj)
{
    if(_obj == NULL)
        return false;

    UtilityClass *_Utility = UtilityClass::Instance();
    QSqlQuery query(HarnessDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);

    bResult = query.exec();
    if(bResult == false)
    {
        HarnessDBObj.close();
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        HarnessDBObj.close();
        return bResult;
    }

    ((HarnessElement*)_obj)->HarnessID = query.value("ID").toInt();
    ((HarnessElement*)_obj)->HarnessName = query.value("HarnessName").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((HarnessElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((HarnessElement*)_obj)->OperatorID = query.value("OperatorID").toInt();
    ((HarnessElement*)_obj)->HarnessTypeSetting.ProcessMode =
            (enum PROCESSMODE)query.value("ProcessMode").toInt();
    ((HarnessElement*)_obj)->HarnessTypeSetting.WorkStations.TotalWorkstation =
            query.value("TotalWorkstation").toInt();
    ((HarnessElement*)_obj)->HarnessTypeSetting.WorkStations.MaxSplicesPerWorkstation =
            query.value("MaxSplicesPerWorkstation").toInt();
    ((HarnessElement*)_obj)->HarnessTypeSetting.BoardLayout.Rows = query.value("Rows").toInt();
    ((HarnessElement*)_obj)->HarnessTypeSetting.BoardLayout.Columns = query.value("Columns").toInt();
    ((HarnessElement*)_obj)->HarnessTypeSetting.BoardLayout.MaxSplicesPerZone =
            query.value("MaxSplicesPerZone").toInt();
    QString tmpStr = query.value("JSONSplice").toString();
    _Utility->StringJsonToMap(tmpStr, &((HarnessElement*)_obj)->SpliceList);

    ((HarnessElement*)_obj)->NoOfSplice = ((HarnessElement*)_obj)->SpliceList.size();

    HarnessDBObj.close();
    return bResult;
}

bool DBHarnessTable::QueryOneRecordFromTable(int ID, QStringList &ResultStr)
{
    QSqlQuery query(HarnessDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);

    bResult = query.exec();
    if(bResult == false)
    {
        HarnessDBObj.close();
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        HarnessDBObj.close();
        return bResult;
    }

    ResultStr.clear();
    ResultStr.append(query.value("ID").toString());
    ResultStr.append(query.value("HarnessName").toString());
    ResultStr.append(query.value("CreatedDate").toString());
    ResultStr.append(query.value("OperatorID").toString());
    ResultStr.append(query.value("ProcessMode").toString());
    ResultStr.append(query.value("TotalWorkstation").toString());
    ResultStr.append(query.value("MaxSplicesPerWorkstation").toString());
    ResultStr.append(query.value("Rows").toString());
    ResultStr.append(query.value("Columns").toString());
    ResultStr.append(query.value("MaxSplicesPerZone").toString());
    ResultStr.append(query.value("NoOfSplice").toString());
    ResultStr.append(query.value("JSONSplice").toString());
    HarnessDBObj.close();
    return bResult;
}

bool DBHarnessTable::DeleteEntireTable()
{
    QSqlQuery query(HarnessDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.exec(SQLSentence[SQLITCLASS::DELETE_ENTIRE_TABLE]);
    if(bResult == false)
    {
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
    }

    HarnessDBObj.close();
    return bResult;
}

bool DBHarnessTable::DeleteOneRecordFromTable(int ID, QString Name)
{
    QSqlQuery query(HarnessDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::DELETE_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
    }
    HarnessDBObj.close();
    return bResult;
}

bool DBHarnessTable::UpdateRecordIntoTable(void *_obj)
{
    if(_obj == NULL)
        return false;
    UtilityClass* _Utility = UtilityClass::Instance();
    QSqlQuery query(HarnessDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR1:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[UPDATE_ONE_RECORD]);
    query.addBindValue(((HarnessElement*)_obj)->HarnessName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((HarnessElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((HarnessElement*)_obj)->OperatorID);
    query.addBindValue(((HarnessElement*)_obj)->HarnessTypeSetting.ProcessMode);
    query.addBindValue(((HarnessElement*)_obj)->HarnessTypeSetting.WorkStations.TotalWorkstation);
    query.addBindValue(((HarnessElement*)_obj)->HarnessTypeSetting.WorkStations.MaxSplicesPerWorkstation);
    query.addBindValue(((HarnessElement*)_obj)->HarnessTypeSetting.BoardLayout.Rows);
    query.addBindValue(((HarnessElement*)_obj)->HarnessTypeSetting.BoardLayout.Columns);
    query.addBindValue(((HarnessElement*)_obj)->HarnessTypeSetting.BoardLayout.MaxSplicesPerZone);
    query.addBindValue(((HarnessElement*)_obj)->SpliceList.size());
    QString tmpStr;
    _Utility->MapJsonToString(&((HarnessElement*)_obj)->SpliceList, tmpStr);
    query.addBindValue(tmpStr);
    query.addBindValue(((HarnessElement*)_obj)->HarnessID);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
    }
    HarnessDBObj.close();
    return bResult;
}

bool DBHarnessTable::QueryOnlyUseName(QString Name, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(HarnessDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, HarnessName FROM Harness WHERE HarnessName = ?");
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("HarnessName").toString());
    }
    else
    {
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
    }

    HarnessDBObj.close();
    return bResult;
}

bool DBHarnessTable::QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(HarnessDBObj);
    bool bResult = OpenDBObject();
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
                           query.value("HarnessName").toString());
    }
    else
    {
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
    }

    HarnessDBObj.close();
    return bResult;
}

bool DBHarnessTable::QueryUseNameAndTime(QString Name, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(HarnessDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, HarnessName FROM Harness "
                  "WHERE HarnessName = ? AND CreatedDate >= ?"
                  " AND CreatedDate <= ?");
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
                           query.value("HarnessName").toString());
    }
    else
    {
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
    }

    HarnessDBObj.close();
    return bResult;
}
