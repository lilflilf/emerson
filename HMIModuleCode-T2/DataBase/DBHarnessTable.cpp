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
    spliceTable = DBPresetTable::Instance();
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

void DBHarnessTable::InsertTestDataIntoTable()
{
    struct HarnessElement tmpHarness;
    for (int i = 0; i < 7; i++)
    {
        if ( i == 0)
            tmpHarness.HarnessName = "32117-SHA-0001-00(INSTHARNESSS)";
        if ( i == 1)
            tmpHarness.HarnessName = "32200-SGA-2000-01(CABINHARNESS)";
        if ( i == 2)
            tmpHarness.HarnessName = "32751-TAA-A190-03(FRDOORHARNESS)";
        if ( i == 3)
            tmpHarness.HarnessName = "P5VH006Y0";
        if ( i == 4)
            tmpHarness.HarnessName = "P5VH006P0";
        if ( i == 5)
            tmpHarness.HarnessName = "P5VH006Z0";
        else
            tmpHarness.HarnessName = QString("P5VH006Z0 + %1").arg(i);

        tmpHarness.CreatedDate = QDateTime::currentDateTime().toTime_t();
        tmpHarness.OperatorID = 2;
        tmpHarness.HarnessTypeSetting.ProcessMode = BASIC;
        tmpHarness.HarnessTypeSetting.WorkStations.TotalWorkstation = 20;
        tmpHarness.HarnessTypeSetting.WorkStations.MaxSplicesPerWorkstation = 30;
        tmpHarness.HarnessTypeSetting.BoardLayout.Rows = 4;
        tmpHarness.HarnessTypeSetting.BoardLayout.Columns = 4;
        tmpHarness.HarnessTypeSetting.BoardLayout.MaxSplicesPerZone = 10;

        struct HARNESSATTRIBUTE HarnessAttribute;
        HarnessAttribute.SpliceName = "WangYIBIN";
        HarnessAttribute.CurrentBoardLayoutZone = 1;
        HarnessAttribute.CurrentWorkstation = 2;
        tmpHarness.SpliceList.insert(0,HarnessAttribute);
        HarnessAttribute.SpliceName = "JWang";
        HarnessAttribute.CurrentBoardLayoutZone = 2;
        HarnessAttribute.CurrentWorkstation = 3;
        tmpHarness.SpliceList.insert(1,HarnessAttribute);
        HarnessAttribute.SpliceName = "JW";
        HarnessAttribute.CurrentBoardLayoutZone = 3;
        HarnessAttribute.CurrentWorkstation = 4;
        tmpHarness.SpliceList.insert(2,HarnessAttribute);
        tmpHarness.NoOfSplice = tmpHarness.SpliceList.size();

        InsertRecordIntoTable(&tmpHarness);
    }
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

bool DBHarnessTable::exportData(int partId, QString fileUrl)
{
    QString queryStr;
    QString lineValue = "";
    QSqlQuery query(HarnessDBObj);
    QString spliceData;
    bool bResult = OpenDBObject();
//    bool ok;
    QString tempWireData;
    QString fileSource;
    if(bResult == true)
    {
        queryStr = QString("SELECT * FROM Part WHERE ID == '%1'").arg(partId);
        query.prepare(queryStr);
        bResult = query.exec();
        if (bResult) {
            bResult = query.next();
            if(bResult) {
                for (int i = 0;i < 12;i++)
                {
                    if (i == 11)
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
                                        tempWireData = spliceTable->GetExportString(((QString)strList.at(0)).toInt());
                                        spliceData.append(tempWireData + "|");
                                    }
                                }
                            }
                        }
                        lineValue.append(spliceData + ",");
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
                    out << "PartData" << '\n' << lineValue;
                    csvFile.close();
                }
            }
        }
        HarnessDBObj.close();
    }
    return bResult;
}

int DBHarnessTable::importData(QString value, QMap<int, QString> spliceIdMap)
{
    QString lineData;
    QStringList lineList;
    bool ok;
    int ret = -1;

    lineData = value;
    lineList = lineData.split(",");
    if (lineList.size() >= 11) {
        HarnessElement myHarness;
        myHarness.HarnessName = lineList[1];
        myHarness.CreatedDate = QDateTime::fromString(lineList[2],"yyyy/MM/dd hh:mm:ss").toTime_t();
        myHarness.OperatorID = QString(lineList[3]).toInt(&ok,10);
        myHarness.HarnessTypeSetting.ProcessMode = (PROCESSMODE)QString(lineList[4]).toInt(&ok,10);
        myHarness.HarnessTypeSetting.WorkStations.TotalWorkstation = QString(lineList[5]).toInt(&ok,10);
        myHarness.HarnessTypeSetting.WorkStations.MaxSplicesPerWorkstation = QString(lineList[6]).toInt(&ok,10);
        myHarness.HarnessTypeSetting.BoardLayout.Rows = QString(lineList[7]).toInt(&ok,10);
        myHarness.HarnessTypeSetting.BoardLayout.Columns = QString(lineList[8]).toInt(&ok,10);
        myHarness.HarnessTypeSetting.BoardLayout.MaxSplicesPerZone = QString(lineList[9]).toInt(&ok,10);
        QMap<int ,struct HARNESSATTRIBUTE> tempMap;

        int i = 0;
        QMap<int,QString>::iterator it; //遍历map
        for ( it = spliceIdMap.begin(); it != spliceIdMap.end(); ++it ) {
            struct HARNESSATTRIBUTE temp;
            temp.SpliceID = it.key();
            temp.SpliceName = it.value();
            tempMap.insert(i,temp);
            i++;
        }
        myHarness.SpliceList = tempMap;
        myHarness.NoOfSplice = myHarness.SpliceList.size();

        ret = InsertRecordIntoTable(&myHarness);
        while (ret == -1) {
            qDebug() << "harness";
            QMap<int ,QString> tempMap;
            QueryOnlyUseName(myHarness.HarnessName, &tempMap);
            if (tempMap.size() > 0) {
                myHarness.HarnessName = myHarness.HarnessName + "(1)";
                ret = InsertRecordIntoTable(&myHarness);
            }
            else if (tempMap.size() == 0)
                return -1;
        }
    }
    return ret;
}

QString DBHarnessTable::GetExportString(int partId)
{
    QString tempSpliceData;
    QString spliceData;
    QString queryStr;
    QString lineValue = "";
    QSqlQuery query(HarnessDBObj);
    bool bResult = OpenDBObject();
    if(bResult == true)
    {
        queryStr = QString("SELECT * FROM Part WHERE ID == '%1'").arg(partId);
        query.prepare(queryStr);
        bResult = query.exec();
        if (bResult) {
            bResult = query.next();
            if(bResult) {
                for (int i = 0;i < 12;i++)
                {
                    if (i == 11)
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
                                        tempSpliceData = spliceTable->GetExportString(((QString)strList.at(0)).toInt());
                                        spliceData.append(tempSpliceData + "|");
                                    }
                                }
                            }
                        }
                        lineValue.append(spliceData + "@");
                    }
                    else
                        lineValue.append(query.value(i).toString() + "@");
                }

            }
        }
        HarnessDBObj.close();
    }
    return lineValue;
}
