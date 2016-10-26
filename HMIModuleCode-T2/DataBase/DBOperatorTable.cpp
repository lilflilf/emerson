#include "DBOperatorTable.h"
#include <QDebug>

DBOperatorTable* DBOperatorTable::_instance = NULL;
QString DBOperatorTable::OperatorDBFile = "Operator.db";
QString DBOperatorTable::DatabaseDir = "c:\\BransonData\\Library\\";
DBOperatorTable* DBOperatorTable::Instance()
{
    if(_instance == 0){
        _instance = new DBOperatorTable();
    }
    return _instance;
}

DBOperatorTable::DBOperatorTable()
{
    OperatorDBObj = QSqlDatabase::addDatabase("QSQLITE", "PartDBObjConnect");
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

//    bResult = query.exec(SQLSentence[CREATE_PART_TABLE]);   //run SQL
    bResult = query.exec("CREATE TABLE Operator ("                   /*0 Create Wire Table*/
                  "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "OperatorName VARCHAR UNIQUE, "
                  "CreatedDate VARCHAR, WhoCreatedNewID INT, Password VARCHAR, "
                  "PermissionLevel ENUM)");

    if(bResult == false)
        qDebug() << "SQL ERROR:"<< query.lastError();

    OperatorDBObj.close();

    return bResult;
}

bool DBOperatorTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    if(_obj == NULL)
        return false;

    QSqlQuery query(OperatorDBObj);
    bResult = OperatorDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }

//    UtilityClass *_Utility = UtilityClass::Instance();

//    query.prepare(SQLSentence[INSERT_PART_TABLE]);
    query.prepare("INSERT INTO Operator ( "
                  "OperatorName, CreatedDate, WhoCreatedNewID, Password, "
                  "PermissionLevel)VALUES(?, ?, ?, ?, ?)");
    query.addBindValue(((OperatorElement*)_obj)->OperatorName);
    query.addBindValue(((OperatorElement*)_obj)->CreatedDate);
    query.addBindValue(((OperatorElement*)_obj)->WhoCreatedNewID);
    query.addBindValue(((OperatorElement*)_obj)->Password);
    query.addBindValue(((OperatorElement*)_obj)->PermissionLevel);

    bResult = query.exec();
    if (bResult == false)   //run SQL
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    OperatorDBObj.close();
    return bResult;
}

bool DBOperatorTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();
    if(bResult == false)
        return bResult;

//    bResult = query.exec(SQLSentence[QUERY_ENTIRE_PART_TABLE]);
    bResult = query.exec("SELECT ID, OperatorName FROM Operator");
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

//    UtilityClass *_Utility = UtilityClass::Instance();
    QSqlQuery query(OperatorDBObj);
    bool bResult = OperatorDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_PART_TABLE]);
    query.prepare("SELECT * FROM Operator WHERE ID = ? AND OperatorName = ?");
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
    ((OperatorElement*)_obj)->CreatedDate = query.value("CreatedDate").toString();
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

//    bResult = query.exec(SQLSentence[DELETE_ENTIRE_PART_TABLE]);
    bResult = query.exec("DELETE FROM Operator");
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

//    query.prepare(SQLSentence[DELETE_ONE_RECORD_PART_TABLE]);
    query.prepare("DELETE FROM Operator WHERE ID = ? AND OperatorName = ?");
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

//    query.prepare(SQLSentence[UPDATE_ONE_RECORD_PART_TABLE]);
    query.prepare("UPDATE Operator Set OperatorName = ?, CreatedDate = ?, "
                  "WhoCreatedNewID = ?, Password = ?, PermissionLevel = ? WHERE ID = ?");
    query.addBindValue(((OperatorElement*)_obj)->OperatorName);
    query.addBindValue(((OperatorElement*)_obj)->CreatedDate);
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
