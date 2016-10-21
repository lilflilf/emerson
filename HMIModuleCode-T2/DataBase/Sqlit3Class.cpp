#include "Sqlit3Class.h"
#include "sqlsentence.h"
#include "Modules/UtilityClass.h"
#include <QDebug>

SQLITCLASS* SQLITCLASS::_instance = 0;
QString SQLITCLASS::DatabaseDir  = "c:\\BransonData\\Library\\";
QString SQLITCLASS::WorkOrderFile = "WorkOrder.db";
QString SQLITCLASS::PartDBFile   = "Part.db";
QString SQLITCLASS::SpliceDBFile = "Splice.db";
QString SQLITCLASS::WireDBFile   = "Wire.db";
#define SQLCREATEWIRETABLE ;

SQLITCLASS* SQLITCLASS::Instance()
{
    if(_instance == 0){
        _instance = new SQLITCLASS();
    }
    return _instance;
}

SQLITCLASS::SQLITCLASS()
{
    WorkOrderDBObj = QSqlDatabase::addDatabase("QSQLITE", "WorkOrderDBObjConnect");
    WorkOrderDBObj.setDatabaseName(DatabaseDir + WorkOrderFile);
    if(WorkOrderDBObj.open())
    {
        if(!WorkOrderDBObj.tables().contains("WorkOrder"))
            SQL_Execute(&WorkOrderDBObj, SQLSentence[CREATEWORKORDERTABLE]);
    }
    WorkOrderDBObj.close();

    PartDBObj = QSqlDatabase::addDatabase("QSQLITE", "PartDBObjConnect");
    PartDBObj.setDatabaseName(DatabaseDir + PartDBFile);
    if(PartDBObj.open())
    {
        if(!PartDBObj.tables().contains("Part"))
            SQL_Execute(&PartDBObj, SQLSentence[CREATEPARTTABLE]);
    }
    PartDBObj.close();

    SpliceDBObj = QSqlDatabase::addDatabase("QSQLITE","SpliceDBObjConnect");
    SpliceDBObj.setDatabaseName(DatabaseDir + SpliceDBFile);
    if(SpliceDBObj.open())
    {
        if(!SpliceDBObj.tables().contains("Preset"))
            SQL_Execute(&SpliceDBObj, SQLSentence[CREATESPLICETABLE]);
    }
    SpliceDBObj.close();

    WireDBObj   = QSqlDatabase::addDatabase("QSQLITE","WireDBObjConnect");
    WireDBObj.setDatabaseName(DatabaseDir + WireDBFile);
    if(WireDBObj.open())
    {
        if(!WireDBObj.tables().contains("Wire"))
            SQL_Execute(&WireDBObj, SQLSentence[CREATEWIRETABLE]);
    }
    WireDBObj.close();
}

SQLITCLASS::~SQLITCLASS()
{
    WorkOrderDBObj.close();
    PartDBObj.close();
    SpliceDBObj.close();
    WireDBObj.close();
}

bool SQLITCLASS::SQL_Execute(QSqlDatabase *_DBObject, QString SQL_Sentence)
{
    qDebug() << "SQL_Execute" << SQL_Sentence;

    QSqlQuery query(*_DBObject);
    bool bResult = _DBObject->open();
    if(bResult == false)
        return bResult;

    if (query.exec(SQL_Sentence))   //run SQL
        bResult = true;
    else
    {
        bResult = false;
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    _DBObject->close();

    return bResult;
}

bool SQLITCLASS::InsertRecordIntoWireTable(WireElementStructure* _WireElement)
{
     QSqlQuery query(WireDBObj);
     bool bResult = WireDBObj.open();
     if(bResult == false)
     {
         qDebug() << "SQL ERROR:"<< query.lastError();
         return bResult;
     }

     query.prepare(SQLSentence[INSERTWIRETABLE]);
     query.addBindValue(_WireElement->WireName);
     query.addBindValue(_WireElement->CreatedDate);
     query.addBindValue(_WireElement->OperatorID);
     query.addBindValue(_WireElement->Color);
     query.addBindValue(_WireElement->Stripe.TypeOfStripe);
     query.addBindValue(_WireElement->Stripe.Color);
     query.addBindValue(_WireElement->Gauge);
     query.addBindValue(_WireElement->TypeOfWire);
     query.addBindValue(_WireElement->Side);
     query.addBindValue(_WireElement->VerticalSide);
     query.addBindValue(_WireElement->Position);
     QSqlQuery query;

     query.prepare("INSERT INTO Wire (WireName, CreatedDate, OperatorID, Color,"
                   "StripeTye, StripeColor, Gauge, MetalType, HorizontalLocation,"
                   "VerticalLocation, VerticalPosition)"
                   "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
     query.addBindValue("JerryWang");
     query.addBindValue("20161019");
     query.addBindValue("JW");
     query.addBindValue("GREEN");
     query.addBindValue(0);
     query.addBindValue("YELLOW");
     query.addBindValue(50);
     query.addBindValue(0);
     query.addBindValue(0);
     query.addBindValue(1);
     query.addBindValue(0);
     //query.value()

     if (query.exec())   //run SQL
         bResult = true;
     else
     {
         bResult = false;
         qDebug() << "SQL ERROR:"<< query.lastError();
     }

     WireDBObj.close();

     return bResult;
 }

bool SQLITCLASS::InsertRecordIntoPresetTable(PresetElement *_PresetElement)
{
    QSqlQuery query(SpliceDBObj);
    bool bResult = SpliceDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }

    UtilityClass *_Utility = UtilityClass::Instance();

    query.prepare(SQLSentence[INSERTSPLICETABLE]);
    query.addBindValue(_PresetElement->SpliceName);
    query.addBindValue(_PresetElement->CreatedDate);
    query.addBindValue(_PresetElement->OperatorID);
    query.addBindValue(_PresetElement->CrossSection);
    query.addBindValue(_PresetElement->PresetPicNamePath);
    query.addBindValue(_PresetElement->Verified);

    query.addBindValue(_PresetElement->WeldSetting.Energy);
    query.addBindValue(_PresetElement->WeldSetting.Amplitude);
    query.addBindValue(_PresetElement->WeldSetting.Width);
    query.addBindValue(_PresetElement->WeldSetting.Pressure);
    query.addBindValue(_PresetElement->WeldSetting.TrigPres);

    query.addBindValue(_PresetElement->QualitySetting.Time.Plus);
    query.addBindValue(_PresetElement->QualitySetting.Time.Minus);
    query.addBindValue(_PresetElement->QualitySetting.Power.Plus);
    query.addBindValue(_PresetElement->QualitySetting.Power.Minus);
    query.addBindValue(_PresetElement->QualitySetting.Preheight.Plus);
    query.addBindValue(_PresetElement->QualitySetting.Preheight.Minus);
    query.addBindValue(_PresetElement->QualitySetting.Height.Plus);
    query.addBindValue(_PresetElement->QualitySetting.Height.Minus);
    query.addBindValue(_PresetElement->QualitySetting.Force.Plus);
    query.addBindValue(_PresetElement->QualitySetting.Force.Minus);

    query.addBindValue(_PresetElement->AdvanceSetting.WeldMode);
    query.addBindValue(_PresetElement->AdvanceSetting.StepWeld.StepWeldMode);
    query.addBindValue(_PresetElement->AdvanceSetting.StepWeld.EnergyToStep);
    query.addBindValue(_PresetElement->AdvanceSetting.StepWeld.TimeToStep);
    query.addBindValue(_PresetElement->AdvanceSetting.StepWeld.PowerToStep);
    query.addBindValue(_PresetElement->AdvanceSetting.StepWeld.Amplitude2);
    query.addBindValue(_PresetElement->AdvanceSetting.PreBurst);
    query.addBindValue(_PresetElement->AdvanceSetting.HoldTime);
    query.addBindValue(_PresetElement->AdvanceSetting.SqzTime);
    query.addBindValue(_PresetElement->AdvanceSetting.ABDelay);
    query.addBindValue(_PresetElement->AdvanceSetting.ABDur);
    query.addBindValue(_PresetElement->AdvanceSetting.CutOff);
    query.addBindValue(_PresetElement->AdvanceSetting.AntiSide);
    query.addBindValue(_PresetElement->AdvanceSetting.MeasuredWidth);
    query.addBindValue(_PresetElement->AdvanceSetting.MeasuredHeight);
    query.addBindValue(_PresetElement->AdvanceSetting.ShrinkTube.ShrinkOption);
    query.addBindValue(_PresetElement->AdvanceSetting.ShrinkTube.ShrinkTubeIndex);
    query.addBindValue(_PresetElement->AdvanceSetting.ShrinkTube.ShrinkTime);
    query.addBindValue(_PresetElement->AdvanceSetting.ShrinkTube.ShrinkTemperature);

    query.addBindValue(_PresetElement->TestSetting.Qutanty);
    query.addBindValue(_PresetElement->TestSetting.StopCount);
    query.addBindValue(_PresetElement->TestSetting.TestMode);
    query.addBindValue(_PresetElement->TestSetting.TeachModeSetting.TeachModeType);
    for(int i = 0; i< 18; i++)
    {
        query.addBindValue(_PresetElement->TestSetting.
                            TeachModeSetting.TeachModequal_Window[i]);
    }
    query.addBindValue(_PresetElement->TestSetting.TestingDone);

    query.addBindValue(_PresetElement->NoOfWires);

    QString tmpJson;
    _Utility->MapJsonToString(&_PresetElement->WireIndex,tmpJson);
    query.addBindValue(tmpJson);

    if (query.exec())   //run SQL
        bResult = true;
    else
    {
        bResult = false;
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    SpliceDBObj.close();

    return bResult;
}

bool SQLITCLASS::InsertRecordIntoPartTable(PartElement *_PartElement)
{
    QSqlQuery query(PartDBObj);
    bool bResult = PartDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }

    UtilityClass *_Utility = UtilityClass::Instance();

    query.prepare(SQLSentence[INSERTPARTTABLE]);

    query.addBindValue(_PartElement->PartName);
    query.addBindValue(_PartElement->CreatedDate);
    query.addBindValue(_PartElement->OperatorID);
    query.addBindValue(_PartElement->PartTypeSetting.ProcessMode);
    query.addBindValue(_PartElement->PartTypeSetting.WorkStations.
                       TotalWorkstation);
    query.addBindValue(_PartElement->PartTypeSetting.WorkStations.
                       MaxSplicesPerWorkstation);
    query.addBindValue(_PartElement->PartTypeSetting.BoardLayout.Rows);
    query.addBindValue(_PartElement->PartTypeSetting.BoardLayout.
                       Columns);
    query.addBindValue(_PartElement->PartTypeSetting.BoardLayout.
                       MaxSplicesPerZone);
    query.addBindValue(_PartElement->NoOfSplice);

    QString tmpJson;
    _Utility->MapJsonToString(&_PartElement->SpliceIndex,tmpJson);
    query.addBindValue(tmpJson);

    if (query.exec())   //run SQL
        bResult = true;
    else
    {
        bResult = false;
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    PartDBObj.close();

}

bool SQLITCLASS::InsertRecordIntoWorkOrderTable(WorkOrder *_WorkOrder)
{
    QSqlQuery query(WorkOrderDBObj);
    bool bResult = WorkOrderDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }

    UtilityClass *_Utility = UtilityClass::Instance();

    query.prepare(SQLSentence[INSERTWORKORDERTABLE]);

    query.addBindValue(_WorkOrder->WorkOrderName);
    query.addBindValue(_WorkOrder->CreatedDate);
    query.addBindValue(_WorkOrder->OperatorID);
    query.addBindValue(_WorkOrder->NoOfPart);
    query.addBindValue(_WorkOrder->Quantity);
    query.addBindValue(_WorkOrder->CurrentPartCount);
    query.addBindValue(_WorkOrder->CurrentSplice.SpliceID);
    query.addBindValue(_WorkOrder->CurrentSplice.SpliceName);
    query.addBindValue(_WorkOrder->WorkOrderDone);

    QString tmpJson;
    _Utility->MapJsonToString(&_WorkOrder->PartIndex, tmpJson);
    query.addBindValue(tmpJson);

    _Utility->MapJsonToString(&_WorkOrder->MissSpliceList, tmpJson);
    query.addBindValue(tmpJson);

    if (query.exec())   //run SQL
        bResult = true;
    else
    {
        bResult = false;
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    WorkOrderDBObj.close();
}

bool SQLITCLASS::QueryEntireWireTable(QMap<int, QString>* _Index)
{
    QSqlQuery query(WireDBObj);
    bool bResult = WireDBObj.open();
    if(bResult == false)
        return bResult;

    if (query.exec(SQLSentence[QUERYENTIREWIRETABLE]))
    {
        while(query.next())
        {
            _Index->insert(query.value("ID").toInt(),
                           query.value("WireName").toString());
        }
        bResult = true;
    }
    else
    {
        bResult = false;
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    WireDBObj.close();

    return bResult;
}

bool SQLITCLASS::QueryEntirePresetTable(QMap<int, QString> *_Index)
{
    QSqlQuery query(SpliceDBObj);
    bool bResult = SpliceDBObj.open();
    if(bResult == false)
        return bResult;

    if (query.exec(SQLSentence[QUERYENTIRESPLICETABLE]))
    {
        while(query.next())
        {
            _Index->insert(query.value("ID").toInt(),
                           query.value("SpliceName").toString());
        }
        bResult = true;
    }
    else
    {
        bResult = false;
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    SpliceDBObj.close();

    return bResult;
}

bool SQLITCLASS::QueryEntirePartTable(QMap<int, QString> *_Index)
{
    QSqlQuery query(PartDBObj);
    bool bResult = PartDBObj.open();
    if(bResult == false)
        return bResult;

    if (query.exec(SQLSentence[QUERYENTIREPARTTABLE]))
    {
        while(query.next())
        {
            _Index->insert(query.value("ID").toInt(),
                           query.value("PartName").toString());
        }
        bResult = true;
    }
    else
    {
        bResult = false;
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    PartDBObj.close();

    return bResult;
}

bool SQLITCLASS::QueryEntireWorkOrderTable(QMap<int, QString> *_Index)
{
    QSqlQuery query(WorkOrderDBObj);
    bool bResult = WorkOrderDBObj.open();
    if(bResult == false)
        return bResult;

    if (query.exec(SQLSentence[QUERYENTIREWORKORDERTABLE]))
    {
        while(query.next())
        {
            _Index->insert(query.value("ID").toInt(),
                           query.value("WorkOrderName").toString());
        }
        bResult = true;
    }
    else
    {
        bResult = false;
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    WorkOrderDBObj.close();

    return bResult;
}

bool SQLITCLASS::QueryOneWireTable(int ID, QString Name, WireElementStructure *_WireElement)
{
    QSqlQuery query(WireDBObj);
    bool bResult = WireDBObj.open();
    if(bResult == false)
        return bResult;

//    if (query.exec(SQLSentence[QUERYENTIREWIRETABLE]))
    query.prepare("SELECT * FROM Wire WHERE ID = ? AND WireName = ?");
    query.addBindValue(ID);
    query.addBindValue(Name);

    if (query.exec())   //run SQL
    {
        while(query.next())
        {
            _WireElement->WireID = query.value("ID").toInt();
            _WireElement->WireName = query.value("WireName").toString();
            _WireElement->CreatedDate = query.value("CreatedDate").toString();
            _WireElement->OperatorID = query.value("OperatorID").toString();
            _WireElement->Color = query.value("Color").toString();
            _WireElement->Stripe.Color = query.value("StripeColor").toString();
            _WireElement->Stripe.TypeOfStripe = (enum StripeType)query.value("StripeTye").toInt();
            _WireElement->Gauge = query.value("Gauge").toInt();
            _WireElement->TypeOfWire = (enum MetalType)query.value("MetalType").toInt();
            _WireElement->Side = (enum HorizontalLocation)query.value("HorizontalLocation").toInt();
            _WireElement->VerticalSide = (enum VerticalLocation)query.value("VerticalLocation").toInt();
            _WireElement->Position = (enum VerticalPosition)query.value("VerticalPosition").toInt();
        }
        bResult = true;
    }
    else
    {
        bResult = false;
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    WireDBObj.close();

    return bResult;
}
