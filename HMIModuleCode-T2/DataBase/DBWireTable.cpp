#include "DBWireTable.h"
#include <QDebug>

DBWireTable* DBWireTable::_instance = NULL;
QString DBWireTable::WireDBFile   = "Wire.db";
QString DBWireTable::DatabaseDir = "c:\\BransonData\\Library\\";
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

bool DBWireTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
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
    query.addBindValue(((WireElementStructure*)_obj)->WireName);
    query.addBindValue(((WireElementStructure*)_obj)->CreatedDate);
    query.addBindValue(((WireElementStructure*)_obj)->OperatorID);
    query.addBindValue(((WireElementStructure*)_obj)->Color);
    query.addBindValue(((WireElementStructure*)_obj)->Stripe.TypeOfStripe);
    query.addBindValue(((WireElementStructure*)_obj)->Stripe.Color);
    query.addBindValue(((WireElementStructure*)_obj)->Gauge);
    query.addBindValue(((WireElementStructure*)_obj)->TypeOfWire);
    query.addBindValue(((WireElementStructure*)_obj)->Side);
    query.addBindValue(((WireElementStructure*)_obj)->VerticalSide);
    query.addBindValue(((WireElementStructure*)_obj)->Position);

    bResult = query.exec();   //run SQL
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }
    WireDBObj.close();
    return bResult;
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

    ((WireElementStructure*)_obj)->WireID = query.value("ID").toInt();
    ((WireElementStructure*)_obj)->WireName = query.value("WireName").toString();
    ((WireElementStructure*)_obj)->CreatedDate = query.value("CreatedDate").toString();
    ((WireElementStructure*)_obj)->OperatorID = query.value("OperatorID").toString();
    ((WireElementStructure*)_obj)->Color = query.value("Color").toString();
    ((WireElementStructure*)_obj)->Stripe.Color = query.value("StripeColor").toString();
    ((WireElementStructure*)_obj)->Stripe.TypeOfStripe = (enum StripeType)query.value("StripeType").toInt();
    ((WireElementStructure*)_obj)->Gauge = query.value("Gauge").toInt();
    ((WireElementStructure*)_obj)->TypeOfWire = (enum MetalType)query.value("MetalType").toInt();
    ((WireElementStructure*)_obj)->Side = (enum HorizontalLocation)query.value("HorizontalLocation").toInt();
    ((WireElementStructure*)_obj)->VerticalSide = (enum VerticalLocation)query.value("VerticalLocation").toInt();
    ((WireElementStructure*)_obj)->Position = (enum VerticalPosition)query.value("VerticalPosition").toInt();

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
    query.addBindValue(((WireElementStructure*)_obj)->WireName);
    query.addBindValue(((WireElementStructure*)_obj)->CreatedDate);
    query.addBindValue(((WireElementStructure*)_obj)->OperatorID);
    query.addBindValue(((WireElementStructure*)_obj)->Color);
    query.addBindValue(((WireElementStructure*)_obj)->Stripe.TypeOfStripe);
    query.addBindValue(((WireElementStructure*)_obj)->Stripe.Color);
    query.addBindValue(((WireElementStructure*)_obj)->Gauge);
    query.addBindValue(((WireElementStructure*)_obj)->TypeOfWire);
    query.addBindValue(((WireElementStructure*)_obj)->Side);
    query.addBindValue(((WireElementStructure*)_obj)->VerticalSide);
    query.addBindValue(((WireElementStructure*)_obj)->Position);
    query.addBindValue(((WireElementStructure*)_obj)->WireID);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }
    WireDBObj.close();
    return bResult;
}
