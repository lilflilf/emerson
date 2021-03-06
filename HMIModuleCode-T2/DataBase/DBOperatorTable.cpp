#include "DBOperatorTable.h"
#include "Interface/Settings/OperatorLibrary.h"
#include "Modules/typedef.h"
#include <QDebug>
#include "Interface/Settings/OperatorLibrary.h"

DBOperatorTable* DBOperatorTable::_instance = NULL;
QString DBOperatorTable::OperatorDBFile = "Operator.db";
QString DBOperatorTable::DatabaseDir = "c:\\BransonData\\Library\\";

const QString SQLSentence[] = {
    "CREATE TABLE Operator ("                        /*0 Create Operator Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, OperatorName VARCHAR, "
    "CreatedDate VARCHAR, WhoCreatedNewID INT, Password VARCHAR UNIQUE, "
    "PermissionLevel ENUM)",

    "INSERT INTO Operator (OperatorName, "           /*1 Insert record into Operator Table */
    "CreatedDate, WhoCreatedNewID, Password, "
    "PermissionLevel)VALUES(?, ?, ?, ?, ?)",

    "SELECT ID, OperatorName FROM Operator",         /*2 Query Entire Operator Table */
                                                     /*3 Query One Record From Operator Table*/
    "SELECT * FROM Operator WHERE ID = ? AND OperatorName = ?",
    "SELECT * FROM Operator WHERE ID = ?",           /*4 Query One Record Only USE ID*/

    "DELETE FROM Operator",                          /*5 Delete Entire Operator Table*/
    "DELETE FROM Operator WHERE ID = ? AND OperatorName = ?",
                                                     /*6 Delete One Record from Part Table*/
    "UPDATE Operator Set OperatorName = ?, "         /*7 Update one Record to Operator Table */
    "CreatedDate = ?, WhoCreatedNewID = ?, Password = ?, "
    "PermissionLevel = ? WHERE ID = ?",
};

DBOperatorTable* DBOperatorTable::Instance()
{
    if(_instance == 0){
        _instance = new DBOperatorTable();
    }
    return _instance;
}

DBOperatorTable::DBOperatorTable()
{
    bool bResult = false;
    OperatorDBObj = QSqlDatabase::addDatabase("QSQLITE", "OperatorDBObjConnect");
    OperatorDBObj.setDatabaseName(DatabaseDir + OperatorDBFile);
    if(OperatorDBObj.open())
    {
        if(!OperatorDBObj.tables().contains("Operator"))
        {
            bResult = CreateNewTable();
            if(bResult == true)
            {
                InitializeUserInfo();
            }
        }
    }
    OperatorDBObj.close();
}

DBOperatorTable::~DBOperatorTable()
{
    OperatorDBObj.close();
}

bool DBOperatorTable::InitializeUserInfo()
{
    int bResult = ERROR;
    OperatorElement OperatorObj;
    OperatorObj.OperatorName = "BRANSON";
    OperatorObj.Password = "218114191514";
    OperatorObj.PermissionLevel = OperatorElement::BRANSON;
    QDateTime TimeLabel = QDateTime::fromString("2017/06/06 12:38:00");
    OperatorObj.CreatedDate = TimeLabel.toTime_t();
    OperatorObj.WhoCreatedNewID = -1;
    bResult = InsertRecordIntoTable(&OperatorObj);
    if(bResult == ERROR)
        return false;
    OperatorObj.OperatorName = "DEFAULT";
    OperatorObj.Password = "0000";
    OperatorObj.PermissionLevel = OperatorElement::INITIAL;
    TimeLabel = QDateTime::fromString("2017/06/06 12:38:00");
    OperatorObj.CreatedDate = TimeLabel.toTime_t();
    OperatorObj.WhoCreatedNewID = -1;
    bResult = InsertRecordIntoTable(&OperatorObj);
    if(bResult == ERROR)
        return false;
    else
        return true;
}

void DBOperatorTable::SwitchDBObject(bool IsModularProduction)
{
    UNUSED(IsModularProduction);
    return;
}

bool DBOperatorTable::CreateNewTable()
{
    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();

    bResult = query.exec(SQLSentence[SQLITCLASS::CREATE]);   //run SQL

    if(bResult == false)
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();

    OperatorDBObj.close();

    return bResult;
}

int DBOperatorTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    int iResult = ERROR;
    if(_obj == NULL)
        return false;

    QSqlQuery query(OperatorDBObj);
    bResult = OperatorDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }
    qDebug()<<"InsertRecordIntoTable"<<((OperatorElement*)_obj)->WhoCreatedNewID;
    query.prepare(SQLSentence[SQLITCLASS::INSERT]);
    query.addBindValue(((OperatorElement*)_obj)->OperatorName);
    QDateTime TimeLabel = QDateTime::currentDateTime();
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((OperatorElement*)_obj)->WhoCreatedNewID);
    query.addBindValue(((OperatorElement*)_obj)->Password);
    query.addBindValue(((OperatorElement*)_obj)->PermissionLevel);

    bResult = query.exec();
    if (bResult == false)   //run SQL
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
    else
        iResult = query.lastInsertId().toInt(&bResult);
    if(bResult == false)
        iResult = ERROR;
    OperatorDBObj.close();
    return iResult;
}

bool DBOperatorTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();
    if(bResult == false)
        return bResult;

    bResult = query.exec(SQLSentence[SQLITCLASS::QUERY_ENTIRE_TABLE]);
    if (bResult == true)
    {
        _obj->clear();
        while(query.next())
        {
            _obj->insert(query.value("ID").toInt(),
                           query.value("OperatorName").toString());
        }
    }
    else
    {
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
    }

    OperatorDBObj.close();

    return bResult;
}

bool DBOperatorTable::QueryOneRecordFromTable(int ID, QString Name, void *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        OperatorDBObj.close();
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        OperatorDBObj.close();
        return bResult;
    }

    ((OperatorElement*)_obj)->OperatorID = query.value("ID").toInt();
    ((OperatorElement*)_obj)->OperatorName = query.value("OperatorName").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((OperatorElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((OperatorElement*)_obj)->WhoCreatedNewID = query.value("WhoCreatedNewID").toInt();
    ((OperatorElement*)_obj)->Password = query.value("Password").toString();
    ((OperatorElement*)_obj)->PermissionLevel = (OperatorElement::PASSWORDCONTROL)query.value("PermissionLevel").toInt();
    OperatorDBObj.close();
    return bResult;
}

bool DBOperatorTable::QueryOneRecordFromTable(int ID, void *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);

    bResult = query.exec();
    if(bResult == false)
    {
        OperatorDBObj.close();
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        OperatorDBObj.close();
        return bResult;
    }

    ((OperatorElement*)_obj)->OperatorID = query.value("ID").toInt();
    ((OperatorElement*)_obj)->OperatorName = query.value("OperatorName").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((OperatorElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((OperatorElement*)_obj)->WhoCreatedNewID = query.value("WhoCreatedNewID").toInt();
    ((OperatorElement*)_obj)->Password = query.value("Password").toString();
    ((OperatorElement*)_obj)->PermissionLevel = (OperatorElement::PASSWORDCONTROL)query.value("PermissionLevel").toInt();
    OperatorDBObj.close();
    return bResult;
}

bool DBOperatorTable::QueryOneRecordFromTable(int ID, QStringList &ResultStr)
{
    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);

    bResult = query.exec();
    if(bResult == false)
    {
        OperatorDBObj.close();
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        OperatorDBObj.close();
        return bResult;
    }

    ResultStr.clear();
    ResultStr.append(query.value("ID").toString());
    ResultStr.append(query.value("OperatorName").toString());
    ResultStr.append(query.value("CreatedDate").toString());
    ResultStr.append(query.value("WhoCreatedNewID").toString());
    ResultStr.append(query.value("Password").toString());
    ResultStr.append(query.value("PermissionLevel").toString());
    OperatorDBObj.close();
    return bResult;
}

bool DBOperatorTable::DeleteEntireTable()
{
    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.exec(SQLSentence[SQLITCLASS::DELETE_ENTIRE_TABLE]);
    if(bResult == false)
    {
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
    }

    OperatorDBObj.close();
    return bResult;
}

bool DBOperatorTable::DeleteOneRecordFromTable(int ID, QString Name)
{
    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::DELETE_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
    }
    OperatorDBObj.close();
    return bResult;
}

bool DBOperatorTable::UpdateRecordIntoTable(void *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR1:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::UPDATE_ONE_RECORD]);
    query.addBindValue(((OperatorElement*)_obj)->OperatorName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((OperatorElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((OperatorElement*)_obj)->WhoCreatedNewID);
    query.addBindValue(((OperatorElement*)_obj)->Password);
    query.addBindValue(((OperatorElement*)_obj)->PermissionLevel);
    query.addBindValue(((OperatorElement*)_obj)->OperatorID);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
    }
    OperatorDBObj.close();
    return bResult;
}

bool DBOperatorTable::QueryOnlyUseName(QString Name, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, OperatorName FROM Part WHERE OperatorName = ?");
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("OperatorName").toString());
    }
    else
    {
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
    }

    OperatorDBObj.close();
    return bResult;
}

bool DBOperatorTable::QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, OperatorName FROM Operator WHERE CreatedDate >= ?"
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
                           query.value("OperatorName").toString());
    }
    else
    {
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
    }

    OperatorDBObj.close();
    return bResult;
}

bool DBOperatorTable::QueryUseNameAndTime(QString Name, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, OperatorName FROM Operator "
                  "WHERE OperatorName = ? AND CreatedDate >= ?"
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
                           query.value("OperatorName").toString());
    }
    else
    {
        qDebug() << "Operator Table SQL ERROR:"<< query.lastError();
    }

    OperatorDBObj.close();
    return bResult;
}
