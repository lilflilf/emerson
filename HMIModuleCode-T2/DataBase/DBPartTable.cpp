#include "DBPartTable.h"
#include "Modules/UtilityClass.h"
#include "Interface/PartElement.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonParseError>
#include <QFile>

DBPartTable* DBPartTable::_instance = NULL;
QString DBPartTable::PartDBFile   = "Part.db";
QString DBPartTable::DatabaseDir = "c:\\BransonData\\Library\\";
const QString SQLSentence[] = {
    "CREATE TABLE Part ("                       /*0 Create Part Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "PartName VARCHAR UNIQUE, "
    "CreatedDate VARCHAR, OperatorID INT, "
    /* PartTypeSetting */
    "ProcessMode ENUM,"
    "TotalWorkstation INT, MaxSplicesPerWorkstation INT, "
    "Rows INT, Columns INT, MaxSplicesPerZone INT, "
    "NoOfSplice INT, JSONSplice VARCHAR)",

    "INSERT INTO Part ("                        /*1 Insert record into Part Table*/
    "PartName, CreatedDate, OperatorID, "
    "ProcessMode, TotalWorkstation, MaxSplicesPerWorkstation, "
    "Rows, Columns, MaxSplicesPerZone, NoOfSplice, JSONSplice) "
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",

    "SELECT ID, PartName FROM Part",            /*2 Query Entire Part Table */

    "SELECT * FROM Part WHERE ID = ? AND PartName = ?",
                                                /*3 Query One Record From Part Table */
    "SELECT * FROM Part WHERE ID = ?",          /*4 Query One Record Only Use ID */

    "DELETE FROM Part",                         /*5 Delete Entire Part Table*/

    "DELETE FROM Part WHERE ID = ? AND PartName = ?",
                                                /*6 Delete One Record from Part Table*/

    "UPDATE Part SET PartName = ?, CreatedDate = ?, OperatorID = ?, "
    "ProcessMode = ?, TotalWorkstation = ?, MaxSplicesPerWorkstation = ?, "
    "Rows = ?, Columns = ?, MaxSplicesPerZone = ?, NoOfSplice = ?, JSONSplice = ? "
    "WHERE ID = ?",                             /*7 Update One Record to Part Table*/

};

DBPartTable* DBPartTable::Instance()
{
    if(_instance == 0){
        _instance = new DBPartTable();
    }
    return _instance;
}

DBPartTable::DBPartTable()
{
    spliceTable = DBPresetTable::Instance();
    PartDBObj = QSqlDatabase::addDatabase("QSQLITE", "PartDBObjConnect");
    PartDBObj.setDatabaseName(DatabaseDir + PartDBFile);
    if(PartDBObj.open())
    {
        if(!PartDBObj.tables().contains("Part")) {
            CreateNewTable();
//            InsertTestDataIntoTable();
        }
    }
    PartDBObj.close();
}

void DBPartTable::InsertTestDataIntoTable()
{
    struct PartElement tmpPart;
    for (int i = 0; i < 7; i++)
    {
        if ( i == 0)
            tmpPart.PartName = "32117-SHA-0001-00(INSTHARNESSS)";
        if ( i == 1)
            tmpPart.PartName = "32200-SGA-2000-01(CABINHARNESS)";
        if ( i == 2)
            tmpPart.PartName = "32751-TAA-A190-03(FRDOORHARNESS)";
        if ( i == 3)
            tmpPart.PartName = "P5VH006Y0";
        if ( i == 4)
            tmpPart.PartName = "P5VH006P0";
        if ( i == 5)
            tmpPart.PartName = "P5VH006Z0";
        else
            tmpPart.PartName = QString("P5VH006Z0 + %1").arg(i);

        tmpPart.CreatedDate = QDateTime::currentDateTime().toTime_t();
        tmpPart.OperatorID = 2;
        tmpPart.PartTypeSetting.ProcessMode = BASIC;
        tmpPart.PartTypeSetting.WorkStations.TotalWorkstation = 20;
        tmpPart.PartTypeSetting.WorkStations.MaxSplicesPerWorkstation = 30;
        tmpPart.PartTypeSetting.BoardLayout.Rows = 4;
        tmpPart.PartTypeSetting.BoardLayout.Columns = 4;
        tmpPart.PartTypeSetting.BoardLayout.MaxSplicesPerZone = 10;

        struct PARTATTRIBUTE PartAttribute;
        PartAttribute.SpliceName = "WangYIBIN";
        PartAttribute.CurrentBoardLayoutZone = 1;
        PartAttribute.CurrentWorkstation = 2;
        tmpPart.SpliceList.insert(0,PartAttribute);
        PartAttribute.SpliceName = "JWang";
        PartAttribute.CurrentBoardLayoutZone = 2;
        PartAttribute.CurrentWorkstation = 3;
        tmpPart.SpliceList.insert(1,PartAttribute);
        PartAttribute.SpliceName = "JW";
        PartAttribute.CurrentBoardLayoutZone = 3;
        PartAttribute.CurrentWorkstation = 4;
        tmpPart.SpliceList.insert(2,PartAttribute);
        tmpPart.NoOfSplice = tmpPart.SpliceList.size();

        InsertRecordIntoTable(&tmpPart);
    }
}

DBPartTable::~DBPartTable()
{
    PartDBObj.close();
}

bool DBPartTable::CreateNewTable()
{
    QSqlQuery query(PartDBObj);
    bool bResult = PartDBObj.open();

    bResult = query.exec(SQLSentence[CREATE]);   //run SQL

    if(bResult == false)
        qDebug() << "SQL ERROR:"<< query.lastError();

    PartDBObj.close();

    return bResult;
}

int DBPartTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    int iResult = -1;
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

    query.prepare(SQLSentence[INSERT]);

    query.addBindValue(((PartElement*)_obj)->PartName);
    QDateTime TimeLabel = QDateTime::currentDateTime();
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
    _Utility->MapJsonToString(&((PartElement*)_obj)->SpliceList,tmpJson);
    query.addBindValue(tmpJson);

    bResult = query.exec();
    if (bResult == false)   //run SQL
        qDebug() << "SQL ERROR InsertRecordIntoTable:"<< query.lastError();
    else
        iResult = query.lastInsertId().toInt(&bResult);
    if(bResult == false)
        iResult = -1;
    PartDBObj.close();
    return iResult;
}

bool DBPartTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(PartDBObj);
    bool bResult = PartDBObj.open();
    if(bResult == false)
        return bResult;

    bResult = query.exec(SQLSentence[QUERY_ENTIRE_TABLE]);
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

    query.prepare(SQLSentence[QUERY_ONE_RECORD]);
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
            query.value("MaxSplicesPerZone").toInt();
    QString tmpStr = query.value("JSONSplice").toString();
    _Utility->StringJsonToMap(tmpStr, &((PartElement*)_obj)->SpliceList);

    ((PartElement*)_obj)->NoOfSplice = ((PartElement*)_obj)->SpliceList.size();

    PartDBObj.close();
    return bResult;
}

bool DBPartTable::QueryOneRecordFromTable(int ID, void *_obj)
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

    query.prepare(SQLSentence[QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);

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
            query.value("MaxSplicesPerZone").toInt();
    QString tmpStr = query.value("JSONSplice").toString();
    _Utility->StringJsonToMap(tmpStr, &((PartElement*)_obj)->SpliceList);

    ((PartElement*)_obj)->NoOfSplice = ((PartElement*)_obj)->SpliceList.size();

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

    bResult = query.exec(SQLSentence[DELETE_ENTIRE_TABLE]);
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

    query.prepare(SQLSentence[DELETE_ONE_RECORD]);
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

    query.prepare(SQLSentence[UPDATE_ONE_RECORD]);
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
    query.addBindValue(((PartElement*)_obj)->SpliceList.size());
    QString tmpStr;
    _Utility->MapJsonToString(&((PartElement*)_obj)->SpliceList, tmpStr);
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

bool DBPartTable::QueryUseNameAndTime(QString Name, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(PartDBObj);
    bool bResult = PartDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, PartName FROM Part "
                  "WHERE PartName = ? AND CreatedDate >= ?"
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
                           query.value("PartName").toString());
    }
    else
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    PartDBObj.close();
    return bResult;
}

bool DBPartTable::exportData(int partId, QString fileUrl)
{
    QString queryStr;
    QString lineValue = "";
    QSqlQuery query(PartDBObj);
    QString spliceData;
    bool bResult = PartDBObj.open();
    bool ok;
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
        PartDBObj.close();
    }
    return bResult;
}

int DBPartTable::importData(QString value, QMap<int, QString> spliceIdMap)
{
    QString lineData;
    QStringList lineList;
    bool ok;
    int ret;

    lineData = value;
    lineList = lineData.split(",");
    if (lineList.size() >= 11) {
        PartElement myPart;
        myPart.PartName = lineList[1];
        myPart.CreatedDate = QDateTime::fromString(lineList[2],"yyyy/MM/dd hh:mm:ss").toTime_t();
        myPart.OperatorID = QString(lineList[3]).toInt(&ok,10);
        myPart.PartTypeSetting.ProcessMode = (PROCESSMODE)QString(lineList[4]).toInt(&ok,10);
        myPart.PartTypeSetting.WorkStations.TotalWorkstation = QString(lineList[5]).toInt(&ok,10);
        myPart.PartTypeSetting.WorkStations.MaxSplicesPerWorkstation = QString(lineList[6]).toInt(&ok,10);
        myPart.PartTypeSetting.BoardLayout.Rows = QString(lineList[7]).toInt(&ok,10);
        myPart.PartTypeSetting.BoardLayout.Columns = QString(lineList[8]).toInt(&ok,10);
        myPart.PartTypeSetting.BoardLayout.MaxSplicesPerZone = QString(lineList[9]).toInt(&ok,10);
        QMap<int ,struct PARTATTRIBUTE> tempMap;

        int i = 0;
        QMap<int,QString>::iterator it; //遍历map
        for ( it = spliceIdMap.begin(); it != spliceIdMap.end(); ++it ) {
            struct PARTATTRIBUTE temp;
            temp.SpliceID = it.key();
            temp.SpliceName = it.value();
            tempMap.insert(i,temp);
            i++;
        }
        myPart.SpliceList = tempMap;
        myPart.NoOfSplice = myPart.SpliceList.size();

        ret = InsertRecordIntoTable(&myPart);
        while (ret == -1) {
            qDebug() << "part";
            QMap<int ,QString> tempMap;
            QueryOnlyUseName(myPart.PartName, &tempMap);
            if (tempMap.size() > 0) {
                myPart.PartName = myPart.PartName + "(1)";
                ret = InsertRecordIntoTable(&myPart);
            }
            else if (tempMap.size() == 0)
                return -1;
        }
    }
    return ret;
}
