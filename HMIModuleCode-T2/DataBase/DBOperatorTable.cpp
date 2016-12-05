#include "DBOperatorTable.h"
#include "Interface/Settings/OperatorLibrary.h"
#include <QDebug>

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

    "DELETE FROM Operator",                          /*4 Delete Entire Operator Table*/
    "DELETE FROM Operator WHERE ID = ? AND OperatorName = ?",
                                                     /*5 Delete One Record from Part Table*/
    "UPDATE Operator Set OperatorName = ?, "         /*6 Update one Record to Operator Table */
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
    OperatorDBObj = QSqlDatabase::addDatabase("QSQLITE", "OperatorDBObjConnect");
    OperatorDBObj.setDatabaseName(DatabaseDir + OperatorDBFile);
    if(OperatorDBObj.open())
    {
        if(!OperatorDBObj.tables().contains("Operator"))
            CreateNewTable();
    }
    OperatorDBObj.close();
}

DBOperatorTable::~DBOperatorTable()
{
    OperatorDBObj.close();
}

bool DBOperatorTable::CreateNewTable()
{
    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();

    bResult = query.exec(SQLSentence[CREATE_OPERATOR_TABLE]);   //run SQL

    if(bResult == false)
        qDebug() << "SQL ERROR:"<< query.lastError();

    OperatorDBObj.close();

    return bResult;
}

int DBOperatorTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    int iResult = -1;
    if(_obj == NULL)
        return false;

    QSqlQuery query(OperatorDBObj);
    bResult = OperatorDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[INSERT_OPERATOR_TABLE]);
    query.addBindValue(((OperatorElement*)_obj)->OperatorName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((OperatorElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((OperatorElement*)_obj)->WhoCreatedNewID);
    query.addBindValue(((OperatorElement*)_obj)->Password);
    query.addBindValue(((OperatorElement*)_obj)->PermissionLevel);

    bResult = query.exec();
    if (bResult == false)   //run SQL
        qDebug() << "SQL ERROR:"<< query.lastError();
    else
        iResult = query.lastInsertId().toInt(&bResult);
    if(bResult == false)
        iResult = -1;
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

    bResult = query.exec(SQLSentence[QUERY_ENTIRE_OPERATOR_TABLE]);
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
        qDebug() << "SQL ERROR:"<< query.lastError();
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
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[QUERY_ONE_RECORD_OPERATOR_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        OperatorDBObj.close();
        qDebug() << "SQL ERROR:"<< query.lastError();
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
    ((OperatorElement*)_obj)->PermissionLevel = (enum PASSWORDCONTROL)query.value("PermissionLevel").toInt();
    OperatorDBObj.close();
    return bResult;
}

bool DBOperatorTable::DeleteEntireTable()
{
    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.exec(SQLSentence[DELETE_ENTIRE_OPERATOR_TABLE]);
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
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
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[DELETE_ONE_RECORD_OPERATOR_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
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

    query.prepare(SQLSentence[UPDATE_ONE_RECORD_OPERATOR_TABLE]);
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
        qDebug() << "SQL ERROR:"<< query.lastError();
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
        qDebug() << "SQL ERROR:"<< query.lastError();
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
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    OperatorDBObj.close();
    return bResult;
}


