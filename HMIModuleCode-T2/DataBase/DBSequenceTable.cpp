#include "DBSequenceTable.h"
#include "Modules/UtilityClass.h"
#include "Interface/SequenceElement.h"
#include "Interface/interface.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonParseError>
#include <QFile>
#include <QDir>

DBSequenceTable* DBSequenceTable::_instance = NULL;
QString DBSequenceTable::SequenceDBFile   = "Sequence.db";
QString DBSequenceTable::DatabaseDir = "c:\\BransonData\\Library\\";
QString DBSequenceTable::ModularDatabaseDir = "c:\\BransonData\\Modular Production\\";

const QString SQLSentence[] = {
    "CREATE TABLE Sequence ("                       /*0 Create Sequence Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "SequenceName VARCHAR UNIQUE, "
    "CreatedDate VARCHAR, OperatorID INT, "
    "NoOfSplice INT, JSONSplice VARCHAR)",

    "INSERT INTO Sequence ("                        /*1 Insert record into Sequence Table*/
    "SequenceName, CreatedDate, OperatorID, "
    "NoOfSplice, JSONSplice) "
    "VALUES (?, ?, ?, ?, ?)",

    "SELECT ID, SequenceName FROM Sequence",        /*2 Query Entire Sequence Table */

    "SELECT * FROM Sequence WHERE ID = ? AND SequenceName = ?",
                                                    /*3 Query One Record From Sequence Table */
    "SELECT * FROM Sequence WHERE ID = ?",          /*4 Query One Record Only Use ID */

    "DELETE FROM Sequence",                         /*5 Delete Entire Sequence Table*/

    "DELETE FROM Sequence WHERE ID = ? AND SequenceName = ?",
                                                    /*6 Delete One Record from Sequence Table*/

    "UPDATE Sequence SET SequenceName = ?, CreatedDate = ?, OperatorID = ?, "
    "NoOfSplice = ?, JSONSplice = ? "
    "WHERE ID = ?",                                 /*7 Update One Record to Sequence Table*/

};

DBSequenceTable* DBSequenceTable::Instance()
{
    if(_instance == 0){
        _instance = new DBSequenceTable();
    }
    return _instance;
}

DBSequenceTable::DBSequenceTable()
{
//    spliceTable = DBPresetTable::Instance();
    SequenceDBObj = QSqlDatabase::addDatabase("QSQLITE", "SequenceDBObjConnect");
    SequenceDBObj.setDatabaseName(DatabaseDir + SequenceDBFile);
    if(SequenceDBObj.open())
    {
        if(!SequenceDBObj.tables().contains("Sequence")) {
            CreateNewTable();
//            InsertTestDataIntoTable();
        }
    }
    SequenceDBObj.close();
}

bool DBSequenceTable::OpenDBObject()
{
    bool bResult = false;
    struct BransonMessageBox tmpMsgBox;
    InterfaceClass* _Interface = InterfaceClass::Instance();
    QDir DBDirectory;
    mIsModularProduction = _Interface->StatusData.EnableModularFlag;
    if(mIsModularProduction == true)
    {
        if (DBDirectory.exists(ModularDatabaseDir + SequenceDBFile) == false)
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
    QSqlQuery query(SequenceDBObj);
    if(SequenceDBObj.open() == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        bResult = false;
    }else
        bResult = true;
    return bResult;
}

void DBSequenceTable::SwitchDBObject(bool IsModularProduction)
{
    mIsModularProduction = IsModularProduction;
    {SequenceDBObj.close();}
    if(mIsModularProduction == true)
    {
        SequenceDBObj.setDatabaseName(ModularDatabaseDir + SequenceDBFile);
    }
    else
    {
        SequenceDBObj.setDatabaseName(DatabaseDir + SequenceDBFile);
    }

    OpenDBObject();
    SequenceDBObj.close();
}

void DBSequenceTable::InsertTestDataIntoTable()
{
    struct SequenceElement tmpSequence;
    for (int i = 0; i < 7; i++)
    {
        if ( i == 0)
            tmpSequence.SequenceName = "32117-SHA-0001-00(INSTHARNESSS)";
        if ( i == 1)
            tmpSequence.SequenceName = "32200-SGA-2000-01(CABINHARNESS)";
        if ( i == 2)
            tmpSequence.SequenceName = "32751-TAA-A190-03(FRDOORHARNESS)";
        if ( i == 3)
            tmpSequence.SequenceName = "P5VH006Y0";
        if ( i == 4)
            tmpSequence.SequenceName = "P5VH006P0";
        if ( i == 5)
            tmpSequence.SequenceName = "P5VH006Z0";
        else
            tmpSequence.SequenceName = QString("P5VH006Z0 + %1").arg(i);

        tmpSequence.CreatedDate = QDateTime::currentDateTime().toTime_t();
        tmpSequence.OperatorID = 2;

        struct SEQUENCEATTRIBUTE SequenceAttribute;
        SequenceAttribute.SpliceName = "WangYIBIN";
        SequenceAttribute.SpliceID = 1;
        SequenceAttribute.Quantity = 10;
        tmpSequence.SpliceList.insert(0, SequenceAttribute);
        SequenceAttribute.SpliceName = "JWang";
        SequenceAttribute.SpliceID = 2;
        SequenceAttribute.Quantity = 20;
        tmpSequence.SpliceList.insert(1, SequenceAttribute);
        SequenceAttribute.SpliceName = "JW";
        SequenceAttribute.SpliceID = 2;
        SequenceAttribute.Quantity = 30;
        tmpSequence.SpliceList.insert(2, SequenceAttribute);
        tmpSequence.NoOfSplice = tmpSequence.SpliceList.size();
        InsertRecordIntoTable(&tmpSequence);
    }
}

DBSequenceTable::~DBSequenceTable()
{
    SequenceDBObj.close();
}

bool DBSequenceTable::CreateNewTable()
{
    QSqlQuery query(SequenceDBObj);
    bool bResult = SequenceDBObj.open();

    bResult = query.exec(SQLSentence[SQLITCLASS::CREATE]);   //run SQL

    if(bResult == false)
        qDebug() << "Sequence Table SQL ERROR:"<< query.lastError();

    SequenceDBObj.close();

    return bResult;
}

int DBSequenceTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    int iResult = -1;
    if(_obj == NULL)
        return false;

    QSqlQuery query(SequenceDBObj);
    bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }

    UtilityClass *_Utility = UtilityClass::Instance();
    query.prepare(SQLSentence[SQLITCLASS::INSERT]);
    query.addBindValue(((SequenceElement*)_obj)->SequenceName);
    QDateTime TimeLabel = QDateTime::currentDateTime();
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((SequenceElement*)_obj)->OperatorID);
    query.addBindValue(((SequenceElement*)_obj)->NoOfSplice);

    QString tmpJson;
    _Utility->MapJsonToString(&((SequenceElement*)_obj)->SpliceList,tmpJson);
    query.addBindValue(tmpJson);

    bResult = query.exec();
    if (bResult == false)   //run SQL
        qDebug() << "Sequence Table SQL ERROR:"<< query.lastError();
    else
        iResult = query.lastInsertId().toInt(&bResult);
    if(bResult == false)
        iResult = -1;
    SequenceDBObj.close();
    return iResult;
}

bool DBSequenceTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(SequenceDBObj);
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
                           query.value("SequenceName").toString());
        }
    }
    else
    {
        qDebug() << "Part Table SQL ERROR:"<< query.lastError();
    }

    SequenceDBObj.close();

    return bResult;
}

bool DBSequenceTable::QueryOneRecordFromTable(int ID, QString Name, void *_obj)
{
    if(_obj == NULL)
        return false;

    UtilityClass *_Utility = UtilityClass::Instance();
    QSqlQuery query(SequenceDBObj);
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
        SequenceDBObj.close();
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        SequenceDBObj.close();
        return bResult;
    }

    ((SequenceElement*)_obj)->SequenceID = query.value("ID").toInt();
    ((SequenceElement*)_obj)->SequenceName = query.value("SequenceName").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((SequenceElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((SequenceElement*)_obj)->OperatorID = query.value("OperatorID").toInt();
    QString tmpStr = query.value("JSONSplice").toString();
    _Utility->StringJsonToMap(tmpStr, &((SequenceElement*)_obj)->SpliceList);

    ((SequenceElement*)_obj)->NoOfSplice = ((SequenceElement*)_obj)->SpliceList.size();

    SequenceDBObj.close();
    return bResult;
}

bool DBSequenceTable::QueryOneRecordFromTable(int ID, void *_obj)
{
    if(_obj == NULL)
        return false;

    UtilityClass *_Utility = UtilityClass::Instance();
    QSqlQuery query(SequenceDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "Sequence Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);

    bResult = query.exec();
    if(bResult == false)
    {
        SequenceDBObj.close();
        qDebug() << "Sequence Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        SequenceDBObj.close();
        return bResult;
    }

    ((SequenceElement*)_obj)->SequenceID = query.value("ID").toInt();
    ((SequenceElement*)_obj)->SequenceName = query.value("SequenceName").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((SequenceElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((SequenceElement*)_obj)->OperatorID = query.value("OperatorID").toInt();
    QString tmpStr = query.value("JSONSplice").toString();
    _Utility->StringJsonToMap(tmpStr, &((SequenceElement*)_obj)->SpliceList);

    ((SequenceElement*)_obj)->NoOfSplice = ((SequenceElement*)_obj)->SpliceList.size();

    SequenceDBObj.close();
    return bResult;
}

bool DBSequenceTable::DeleteEntireTable()
{
    QSqlQuery query(SequenceDBObj);
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

    SequenceDBObj.close();
    return bResult;
}

bool DBSequenceTable::DeleteOneRecordFromTable(int ID, QString Name)
{
    QSqlQuery query(SequenceDBObj);
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
    SequenceDBObj.close();
    return bResult;
}

bool DBSequenceTable::UpdateRecordIntoTable(void *_obj)
{
    if(_obj == NULL)
        return false;
    UtilityClass* _Utility = UtilityClass::Instance();
    QSqlQuery query(SequenceDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR1:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::UPDATE_ONE_RECORD]);
    query.addBindValue(((SequenceElement*)_obj)->SequenceName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((SequenceElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((SequenceElement*)_obj)->OperatorID);
    query.addBindValue(((SequenceElement*)_obj)->SpliceList.size());
    QString tmpStr;
    _Utility->MapJsonToString(&((SequenceElement*)_obj)->SpliceList, tmpStr);
    query.addBindValue(tmpStr);
    query.addBindValue(((SequenceElement*)_obj)->SequenceID);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "Harness Table SQL ERROR:"<< query.lastError();
    }
    SequenceDBObj.close();
    return bResult;
}

bool DBSequenceTable::QueryOnlyUseName(QString Name, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(SequenceDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, SequenceName FROM Sequence WHERE SequenceName = ?");
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("SequenceName").toString());
    }
    else
    {
        qDebug() << "Sequence Table SQL ERROR:"<< query.lastError();
    }

    SequenceDBObj.close();
    return bResult;
}

bool DBSequenceTable::QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(SequenceDBObj);
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
                           query.value("SequenceName").toString());
    }
    else
    {
        qDebug() << "Sequence Table SQL ERROR:"<< query.lastError();
    }

    SequenceDBObj.close();
    return bResult;
}

bool DBSequenceTable::QueryUseNameAndTime(QString Name, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(SequenceDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, SequenceName FROM Sequence "
                  "WHERE SequenceName = ? AND CreatedDate >= ?"
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
                           query.value("SequenceName").toString());
    }
    else
    {
        qDebug() << "Sequence Table SQL ERROR:"<< query.lastError();
    }

    SequenceDBObj.close();
    return bResult;
}
