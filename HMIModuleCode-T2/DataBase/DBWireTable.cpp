#include "DBWireTable.h"
#include <QDebug>
#include "Interface/WireElement.h"

DBWireTable* DBWireTable::_instance = NULL;
QString DBWireTable::WireDBFile   = "Wire.db";
QString DBWireTable::DatabaseDir = "c:\\BransonData\\Library\\";

const QString SQLSentence[] = {
    "CREATE TABLE Wire ("                   /*0 Create Wire Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "WireName VARCHAR, "
    "CreatedDate VARCHAR, OperatorID INT, Color VARCHAR, "
    "StripeType INT, StripeColor VARCHAR, Gauge INT, "
    "MetalType INT, HorizontalLocation INT, VerticalLocation INT, "
    "VerticalPosition INT)",

    "INSERT INTO Wire ("                    /*1 Insert record into Wire Table*/
    "WireName, CreatedDate, OperatorID, Color, "
    "StripeType, StripeColor, Gauge, MetalType, "
    "HorizontalLocation, VerticalLocation, VerticalPosition)"
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",

    "SELECT ID, WireName FROM Wire",        /*2 Query Entire Wire Table */

    "SELECT * FROM Wire WHERE ID = ? AND WireName = ?",
                                            /*3 Query One Record From Splice Table */
    "DELETE FROM Wire",                     /*4 Delete Entire Wire Table*/
    "DELETE FROM Wire WHERE ID = ? AND WireName = ?",
                                            /*5 Delete One Record from Wire Table*/
    "UPDATE Wire Set WireName = ?, CreatedDate = ?, OperatorID = ?, "
    "Color = ?, StripeType = ?, StripeColor = ?, Gauge = ?, MetalType = ?, "
    "HorizontalLocation = ?, VerticalLocation = ?, VerticalPosition = ? "
    "WHERE ID = ?",                         /*6 Update One Record to Wire Table*/
};

DBWireTable* DBWireTable::Instance()
{
    if(_instance == 0){
        _instance = new DBWireTable();
    }
    return _instance;
}

DBWireTable::DBWireTable()
{
    WireDBObj   = QSqlDatabase::addDatabase("QSQLITE","WireDBObjConnect");
    WireDBObj.setDatabaseName(DatabaseDir + WireDBFile);
    if(WireDBObj.open())
    {
        if(!WireDBObj.tables().contains("Wire"))
            CreateNewTable();
    }
    WireDBObj.close();
}

DBWireTable::~DBWireTable()
{
    WireDBObj.close();
}

bool DBWireTable::CreateNewTable()
{
    QSqlQuery query(WireDBObj);
    bool bResult = WireDBObj.open();

    bResult = query.exec(SQLSentence[CREATE_WIRE_TABLE]);   //run SQL

    if(bResult == false)
        qDebug() << "SQL ERROR:"<< query.lastError();

    WireDBObj.close();

    return bResult;
}

int DBWireTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    int iResult = -1;
    if(_obj == NULL)
        return false;

    QSqlQuery query(WireDBObj);
    bResult = WireDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[INSERT_WIRE_TABLE]);
    query.addBindValue(((WireElement*)_obj)->WireName);
    QDateTime TimeLabel = QDateTime::currentDateTime();
    qDebug()<<"Time: "<<TimeLabel.toString("yyyy/MM/dd hh:mm:ss");
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((WireElement*)_obj)->OperatorID);
    query.addBindValue(((WireElement*)_obj)->Color);
    query.addBindValue(((WireElement*)_obj)->Stripe.TypeOfStripe);
    query.addBindValue(((WireElement*)_obj)->Stripe.Color);
    query.addBindValue(((WireElement*)_obj)->Gauge);
    query.addBindValue(((WireElement*)_obj)->TypeOfWire);
    query.addBindValue(((WireElement*)_obj)->Side);
    query.addBindValue(((WireElement*)_obj)->VerticalSide);
    query.addBindValue(((WireElement*)_obj)->Position);

    bResult = query.exec();   //run SQL
    if(bResult == false)
        qDebug() << "SQL ERROR:"<< query.lastError();
    else
        iResult = query.lastInsertId().toInt(&bResult);
    if(bResult == false)
        iResult = -1;
    WireDBObj.close();
    return iResult;
}

bool DBWireTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WireDBObj);
    bool bResult = WireDBObj.open();
    if(bResult == false)
        return bResult;

    bResult = query.exec(SQLSentence[QUERY_ENTIRE_WIRE_TABLE]);
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("WireName").toString());
    }
    else
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    WireDBObj.close();
    return bResult;
}

bool DBWireTable::QueryOneRecordFromTable(int ID, QString Name, void *_obj)
{
    if(_obj == NULL)
        return false;
    QSqlQuery query(WireDBObj);
    bool bResult = WireDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        WireDBObj.close();
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        WireDBObj.close();
        return bResult;
    }

    ((WireElement*)_obj)->WireID = query.value("ID").toInt();
    ((WireElement*)_obj)->WireName = query.value("WireName").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((WireElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((WireElement*)_obj)->OperatorID = query.value("OperatorID").toInt();
    ((WireElement*)_obj)->Color = query.value("Color").toString();
    ((WireElement*)_obj)->Stripe.Color = query.value("StripeColor").toString();
    ((WireElement*)_obj)->Stripe.TypeOfStripe = (enum StripeType)query.value("StripeType").toInt();
    ((WireElement*)_obj)->Gauge = query.value("Gauge").toInt();
    ((WireElement*)_obj)->TypeOfWire = (enum MetalType)query.value("MetalType").toInt();
    ((WireElement*)_obj)->Side = (enum HorizontalLocation)query.value("HorizontalLocation").toInt();
    ((WireElement*)_obj)->VerticalSide = (enum VerticalLocation)query.value("VerticalLocation").toInt();
    ((WireElement*)_obj)->Position = (enum VerticalPosition)query.value("VerticalPosition").toInt();

    bResult = true;
    WireDBObj.close();

    return bResult;
}

bool DBWireTable::DeleteEntireTable()
{
    QSqlQuery query(WireDBObj);
    bool bResult = WireDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }
    bResult = query.exec(SQLSentence[DELETE_ENTIRE_WIRE_TABLE]);
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }
    WireDBObj.close();
    return bResult;
}

bool DBWireTable::DeleteOneRecordFromTable(int ID, QString Name)
{
    QSqlQuery query(WireDBObj);
    bool bResult = WireDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[DELETE_ONE_RECORD_WIRE_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }
    WireDBObj.close();
    return bResult;
}

bool DBWireTable::UpdateRecordIntoTable(void *_obj)
{
    if(_obj == NULL)
        return false;
    QSqlQuery query(WireDBObj);
    bool bResult = WireDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[UPDATE_ONE_RECORD_WIRE_TABLE]);
    query.addBindValue(((WireElement*)_obj)->WireName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((WireElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((WireElement*)_obj)->OperatorID);
    query.addBindValue(((WireElement*)_obj)->Color);
    query.addBindValue(((WireElement*)_obj)->Stripe.TypeOfStripe);
    query.addBindValue(((WireElement*)_obj)->Stripe.Color);
    query.addBindValue(((WireElement*)_obj)->Gauge);
    query.addBindValue(((WireElement*)_obj)->TypeOfWire);
    query.addBindValue(((WireElement*)_obj)->Side);
    query.addBindValue(((WireElement*)_obj)->VerticalSide);
    query.addBindValue(((WireElement*)_obj)->Position);
    query.addBindValue(((WireElement*)_obj)->WireID);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }
    WireDBObj.close();
    return bResult;
}

bool DBWireTable::QueryOnlyUseName(QString Name, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WireDBObj);
    bool bResult = WireDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, WireName FROM Wire WHERE WireName = ?");
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("WireName").toString());
    }
    else
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    WireDBObj.close();
    return bResult;
}

bool DBWireTable::QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WireDBObj);
    bool bResult = WireDBObj.open();
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
                           query.value("WireName").toString());
    }
    else
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    WireDBObj.close();
    return bResult;
}
