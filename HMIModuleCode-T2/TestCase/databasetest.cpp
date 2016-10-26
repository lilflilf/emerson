#include "databasetest.h"
#include "Modules/UtilityClass.h"
#include "DataBase/DBWireTable.h"
#include "DataBase/DBPresetTable.h"
#include "DataBase/DBPartTable.h"
#include "DataBase/DBWorkOrderTable.h"
#include <QMap>
#include <QDebug>
#include "Interface/definition.h"
#include "Modules/UtilityClass.h"
DataBaseTest::DataBaseTest()
{

}

void DataBaseTest::TestInsertOneRecordIntoWireTable()
{
    SQLITCLASS *_SQLITCLASS = DBWireTable::Instance();
    struct WireElement tmpWire;
    tmpWire.WireName = "TESTWire";
    tmpWire.CreatedDate = "20161020";
    tmpWire.OperatorID = "JW";
    tmpWire.Color = "GREEN";
    tmpWire.Stripe.TypeOfStripe = Slash;
    tmpWire.Stripe.Color = "RED";
    tmpWire.Gauge = 100;
    tmpWire.TypeOfWire = Copper;
    tmpWire.Side = Right;
    tmpWire.VerticalSide = Basic;
    tmpWire.Position = Middle;
    _SQLITCLASS->InsertRecordIntoTable(&tmpWire);
}

void DataBaseTest::TestInsertOneRecordIntoPresetTable()
{
    SQLITCLASS *_SQLITCLASS = DBPresetTable::Instance();
    QMap<int, QString> TestMap;
    TestMap.insert(0, "WANG");
    TestMap.insert(1,"Mr.Li");
    TestMap.insert(2, "Zhang");
    struct PresetElement tmpSplice;
    tmpSplice.SpliceName = "TESTSplice";
    tmpSplice.CreatedDate = "20161020";
    tmpSplice.OperatorID = "JW";
    tmpSplice.CrossSection = 100;
    tmpSplice.PresetPicNamePath = "C:\\";
    tmpSplice.Verified = false;
    tmpSplice.WeldSetting.Energy = 155;
    tmpSplice.WeldSetting.Amplitude = 55;
    tmpSplice.WeldSetting.Width = 800;
    tmpSplice.WeldSetting.Pressure = 80;
    tmpSplice.WeldSetting.TrigPres = 50;
    tmpSplice.QualitySetting.Time.Plus = 500;
    tmpSplice.QualitySetting.Time.Minus = 0;
    tmpSplice.QualitySetting.Power.Plus = 3960;
    tmpSplice.QualitySetting.Power.Minus = 0;
    tmpSplice.QualitySetting.Preheight.Plus = 1500;
    tmpSplice.QualitySetting.Preheight.Minus = 0;
    tmpSplice.QualitySetting.Height.Plus = 1500;
    tmpSplice.QualitySetting.Height.Minus = 0;
    tmpSplice.QualitySetting.Force.Plus = 55;
    tmpSplice.QualitySetting.Force.Minus = 0;
    tmpSplice.AdvanceSetting.WeldMode = ENERGY;
    tmpSplice.AdvanceSetting.StepWeld.StepWeldMode = STEPDISABLE;
    tmpSplice.AdvanceSetting.StepWeld.EnergyToStep = 55;
    tmpSplice.AdvanceSetting.StepWeld.TimeToStep = 1;
    tmpSplice.AdvanceSetting.StepWeld.PowerToStep = 500;
    tmpSplice.AdvanceSetting.StepWeld.Amplitude2 = 22;
    tmpSplice.AdvanceSetting.PreBurst = 1000;
    tmpSplice.AdvanceSetting.HoldTime = 100;
    tmpSplice.AdvanceSetting.SqzTime = 200;
    tmpSplice.AdvanceSetting.ABDelay = 300;
    tmpSplice.AdvanceSetting.ABDur = 400;
    tmpSplice.AdvanceSetting.CutOff = false;
    tmpSplice.AdvanceSetting.AntiSide = true;
    tmpSplice.AdvanceSetting.MeasuredWidth = 100;
    tmpSplice.AdvanceSetting.MeasuredHeight = 100;
    tmpSplice.AdvanceSetting.ShrinkTube.ShrinkOption = false;
    tmpSplice.AdvanceSetting.ShrinkTube.ShrinkTubeID = 0;
    tmpSplice.AdvanceSetting.ShrinkTube.ShrinkTime = 10;
    tmpSplice.AdvanceSetting.ShrinkTube.ShrinkTemperature = 260;
    tmpSplice.TestSetting.Qutanty = 55;
    tmpSplice.TestSetting.StopCount = 20;
    tmpSplice.TestSetting.TestMode = UNCONSTRAINED;
    tmpSplice.TestSetting.TeachModeSetting.TeachModeType = UNDEFINED;
    for(int i=0;i< 18;i++)
        tmpSplice.TestSetting.TeachModeSetting.TeachModequal_Window[i] = 40;
    tmpSplice.TestSetting.TestingDone = true;
    QMap<int, QString>::const_iterator i = TestMap.constBegin();
    while (i != TestMap.constEnd()) {
        tmpSplice.WireIndex.insert(i.key(),i.value());
        ++i;
    }
    tmpSplice.NoOfWires = tmpSplice.WireIndex.size();

    _SQLITCLASS->InsertRecordIntoTable(&tmpSplice);
}

void DataBaseTest::TestInsertOneRecordIntoPartTable()
{
    SQLITCLASS *_SQLITCLASS = DBPartTable::Instance();

    struct PartElement tmpPart;
    tmpPart.PartName = "TESTPart";
    tmpPart.CreatedDate = "20161020";
    tmpPart.OperatorID = "JW";
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
    tmpPart.SpliceIndex.insert(0,PartAttribute);
    PartAttribute.SpliceName = "JWang";
    PartAttribute.CurrentBoardLayoutZone = 2;
    PartAttribute.CurrentWorkstation = 3;
    tmpPart.SpliceIndex.insert(1,PartAttribute);
    PartAttribute.SpliceName = "JW";
    PartAttribute.CurrentBoardLayoutZone = 3;
    PartAttribute.CurrentWorkstation = 4;
    tmpPart.SpliceIndex.insert(2,PartAttribute);
    tmpPart.NoOfSplice = tmpPart.SpliceIndex.size();

    _SQLITCLASS->InsertRecordIntoTable(&tmpPart);
}

void DataBaseTest::TestInsertOneRecordIntoWorkOrderTable()
{
    SQLITCLASS *_SQLITCLASS = DBWorkOrderTable::Instance();

    struct WorkOrderElement tmpWorkOrder;
    tmpWorkOrder.WorkOrderName = "TESTWorkOrder";
    tmpWorkOrder.CreatedDate = "20161020";
    tmpWorkOrder.OperatorID = "JW";
    tmpWorkOrder.PartIndex.insert(1,"PartName");
    tmpWorkOrder.NoOfPart = tmpWorkOrder.PartIndex.size();

    tmpWorkOrder.Quantity = 50;
    tmpWorkOrder.CurrentPartCount = 30;

    tmpWorkOrder.MissSpliceList.insert(0, "MissSplice1");
    tmpWorkOrder.MissSpliceList.insert(1, "MissSplice2");
    tmpWorkOrder.MissSpliceList.insert(2, "MissSplice3");

    tmpWorkOrder.CurrentSplice.SpliceID = 5;
    tmpWorkOrder.CurrentSplice.SpliceName = "TestSplice";

    tmpWorkOrder.WorkOrderDone = false;

    _SQLITCLASS->InsertRecordIntoTable(&tmpWorkOrder);
}

void DataBaseTest::TestMapJsonToString()
{
    UtilityClass *_Utility = UtilityClass::Instance();
    struct PARTATTRIBUTE tmpPart;
    tmpPart.SpliceName = "WangYIBIN";
    tmpPart.CurrentBoardLayoutZone = 1;
    tmpPart.CurrentWorkstation = 2;
    QMap<int, struct PARTATTRIBUTE> tmpMap;
    tmpMap.insert(0, tmpPart);
    tmpPart.SpliceName = "JWANG";
    tmpPart.CurrentBoardLayoutZone = 2;
    tmpPart.CurrentWorkstation = 3;
    tmpMap.insert(1, tmpPart);
    tmpPart.SpliceName = "JW";
    tmpPart.CurrentBoardLayoutZone = 3;
    tmpPart.CurrentWorkstation = 4;
    tmpMap.insert(2, tmpPart);
    _Utility->MapJsonToString(&tmpMap,TestStr);
    qDebug()<<"TestMapJsonToString: " << TestStr;
}

void DataBaseTest::TestStringJsonToMap()
{
    UtilityClass *_Utility = UtilityClass::Instance();
    QMap<int, struct PARTATTRIBUTE> tmpMap;
    _Utility->StringJsonToMap(TestStr,&tmpMap);
    QMap<int, struct PARTATTRIBUTE>::const_iterator i = tmpMap.constBegin();
    while(i != tmpMap.constEnd())
    {
        qDebug()<<"Key: "<<i.key();
        qDebug()<<"SpliceName: "<<i.value().SpliceName;
        qDebug()<<"Workstation: "<<i.value().CurrentWorkstation;
        qDebug()<<"BoradLayout: "<<i.value().CurrentBoardLayoutZone;
        ++i;
    }
}

void DataBaseTest::TestQueryEntireWireTable()
{
    SQLITCLASS *_SQLITCLASS = DBWireTable::Instance();
    QMap<int, QString> tmpMap;
    _SQLITCLASS->QueryEntireTable(&tmpMap);
    QMap<int, QString>::ConstIterator i = tmpMap.constBegin();
    while(i != tmpMap.constEnd())
    {
        qDebug()<<"Wire ID: "<<i.key();
        qDebug()<<"Wire Name: "<<i.value();
        ++i;
    }
}

void DataBaseTest::TestQueryEntireSpliceTable()
{
    SQLITCLASS *_SQLITCLASS = DBPresetTable::Instance();
    QMap<int, QString> tmpMap;
    _SQLITCLASS->QueryEntireTable(&tmpMap);
    QMap<int, QString>::ConstIterator i = tmpMap.constBegin();
    while(i != tmpMap.constEnd())
    {
        qDebug()<<"Preset ID: "<<i.key();
        qDebug()<<"Preset Name: "<<i.value();
        ++i;
    }
}

void DataBaseTest::TestQueryEntirePartTable()
{
    SQLITCLASS *_SQLITCLASS = DBPartTable::Instance();
    QMap<int, QString> tmpMap;
    _SQLITCLASS->QueryEntireTable(&tmpMap);
    QMap<int, QString>::ConstIterator i = tmpMap.constBegin();
    while(i != tmpMap.constEnd())
    {
        qDebug()<<"Part ID: "<<i.key();
        qDebug()<<"Part Name: "<<i.value();
        ++i;
    }
}

void DataBaseTest::TestQueryEntireWorkOrderTable()
{
    SQLITCLASS *_SQLITCLASS = DBWorkOrderTable::Instance();
    QMap<int, QString> tmpMap;
    _SQLITCLASS->QueryEntireTable(&tmpMap);
    QMap<int, QString>::ConstIterator i = tmpMap.constBegin();
    while(i != tmpMap.constEnd())
    {
        qDebug()<<"WorkOrder ID: "<<i.key();
        qDebug()<<"WorkOrder Name: "<<i.value();
        ++i;
    }
}

void DataBaseTest::TestQueryOneWireTable()
{
    SQLITCLASS *_SQLITCLASS = DBWireTable::Instance();
    WireElement tmpWire;
    if(_SQLITCLASS->QueryOneRecordFromTable(1,"TESTWIRE", &tmpWire))
    {
        qDebug()<<"WireID: "<<tmpWire.WireID;
        qDebug()<<"WireName: "<<tmpWire.WireName;
        qDebug()<<"CreatedDate: "<<tmpWire.CreatedDate;
        qDebug()<<"OperatorID: "<<tmpWire.OperatorID;
        qDebug()<<"Color: "<<tmpWire.Color;
        qDebug()<<"StripType: "<<tmpWire.Stripe.TypeOfStripe;
        qDebug()<<"StripColor: "<<tmpWire.Stripe.Color;
        qDebug()<<"Gauge: "<<tmpWire.Gauge;
        qDebug()<<"MetalType: "<<tmpWire.TypeOfWire;
        qDebug()<<"HorizotalLocation: "<<tmpWire.Side;
        qDebug()<<"VerticalLocation: "<<tmpWire.VerticalSide;
        qDebug()<<"VerticalPosition: "<<tmpWire.Position;
    }

}

void DataBaseTest::TestDeleteEntireWireTable()
{
    SQLITCLASS *_SQLITCLASS = DBWireTable::Instance();
    if(_SQLITCLASS->DeleteEntireTable())
        qDebug()<<"Delete Wire Table Sucessful.";
    else
        qDebug()<<"Delete Wire Table Unsucessful.";

}

void DataBaseTest::TestDeleteEntirePresetTable()
{
    SQLITCLASS *_SQLITCLASS = DBPresetTable::Instance();
    if(_SQLITCLASS->DeleteEntireTable())
        qDebug()<<"Delete Splice Table Sucessful.";
    else
        qDebug()<<"Delete Splice Table Unsucessful.";
}

void DataBaseTest::TestDeleteEntirePartTable()
{
    SQLITCLASS *_SQLITCLASS = DBPartTable::Instance();
    if(_SQLITCLASS->DeleteEntireTable())
        qDebug()<<"Delete Part Table Sucessful.";
    else
        qDebug()<<"Delete Part Table Unsucessful.";
}

void DataBaseTest::TestDeleteEntireWorkOrderTable()
{
    SQLITCLASS *_SQLITCLASS = DBWorkOrderTable::Instance();
    if(_SQLITCLASS->DeleteEntireTable())
        qDebug()<<"Delete WorkOrder Table Sucessful.";
    else
        qDebug()<<"Delete WorkOrder Table Unsucessful.";
}

void DataBaseTest::TestDeleteOneWireTable()
{
    SQLITCLASS *_SQLITCLASS = DBWireTable::Instance();
    if(_SQLITCLASS->DeleteOneRecordFromTable(3, "TESTWIRE"))
        qDebug()<<"Delete Wire Table Sucessful.";
    else
        qDebug()<<"Delete Wire Table Unsucessful.";
}

void DataBaseTest::TestDeleteOnePresetTable()
{
    SQLITCLASS *_SQLITCLASS = DBPresetTable::Instance();
    if(_SQLITCLASS->DeleteOneRecordFromTable(2, "TESTSplice"))
        qDebug()<<"Delete Splice Table Sucessful.";
    else
        qDebug()<<"Delete Splice Table Unsucessful.";
}

void DataBaseTest::TestDeleteOnePartTable()
{
    SQLITCLASS *_SQLITCLASS = DBPartTable::Instance();
    if(_SQLITCLASS->DeleteOneRecordFromTable(2, "TESTPart"))
        qDebug()<<"Delete Part Table Sucessful.";
    else
        qDebug()<<"Delete Part Table Unsucessful.";
}

void DataBaseTest::TestDeleteOneWorkOrderTable()
{
    SQLITCLASS *_SQLITCLASS = DBWorkOrderTable::Instance();
    if(_SQLITCLASS->DeleteOneRecordFromTable(2, "TESTWorkOrder"))
        qDebug()<<"Delete WorkOrder Table Sucessful.";
    else
        qDebug()<<"Delete WorkOrder Table Unsucessful.";
}

void DataBaseTest::TestUpdateOneRecordIntoWireTable()
{
    SQLITCLASS *_SQLITCLASS = DBWireTable::Instance();
    struct WireElement tmpWire;
    tmpWire.WireID = 4;
    tmpWire.WireName = "TESTWIRE";
    tmpWire.CreatedDate = "20161024";
    tmpWire.OperatorID = "JW";
    tmpWire.Color = "GREEN";
    tmpWire.Stripe.TypeOfStripe = Slash;
    tmpWire.Stripe.Color = "RED";
    tmpWire.Gauge = 100;
    tmpWire.TypeOfWire = Copper;
    tmpWire.Side = Right;
    tmpWire.VerticalSide = Basic;
    tmpWire.Position = Middle;
    _SQLITCLASS->UpdateRecordIntoTable(&tmpWire);
}

void DataBaseTest::TestUpdateOneRecordIntoPresetTable()
{
    SQLITCLASS *_SQLITCLASS = DBPresetTable::Instance();
    QMap<int, QString> TestMap;
    TestMap.insert(0, "WANG");
    TestMap.insert(1,"Mr.Li");
    TestMap.insert(2, "Zhang");
    struct PresetElement tmpSplice;
    tmpSplice.SpliceID = 3;
    tmpSplice.SpliceName = "TESTSPLICE";
    tmpSplice.CreatedDate = "20161020";
    tmpSplice.OperatorID = "JW";
    tmpSplice.CrossSection = 100;
    tmpSplice.PresetPicNamePath = "C:\\";
    tmpSplice.Verified = false;
    tmpSplice.WeldSetting.Energy = 155;
    tmpSplice.WeldSetting.Amplitude = 55;
    tmpSplice.WeldSetting.Width = 800;
    tmpSplice.WeldSetting.Pressure = 80;
    tmpSplice.WeldSetting.TrigPres = 50;
    tmpSplice.QualitySetting.Time.Plus = 500;
    tmpSplice.QualitySetting.Time.Minus = 0;
    tmpSplice.QualitySetting.Power.Plus = 3960;
    tmpSplice.QualitySetting.Power.Minus = 0;
    tmpSplice.QualitySetting.Preheight.Plus = 1500;
    tmpSplice.QualitySetting.Preheight.Minus = 0;
    tmpSplice.QualitySetting.Height.Plus = 1500;
    tmpSplice.QualitySetting.Height.Minus = 0;
    tmpSplice.QualitySetting.Force.Plus = 55;
    tmpSplice.QualitySetting.Force.Minus = 0;
    tmpSplice.AdvanceSetting.WeldMode = ENERGY;
    tmpSplice.AdvanceSetting.StepWeld.StepWeldMode = STEPDISABLE;
    tmpSplice.AdvanceSetting.StepWeld.EnergyToStep = 55;
    tmpSplice.AdvanceSetting.StepWeld.TimeToStep = 1;
    tmpSplice.AdvanceSetting.StepWeld.PowerToStep = 500;
    tmpSplice.AdvanceSetting.StepWeld.Amplitude2 = 22;
    tmpSplice.AdvanceSetting.PreBurst = 1000;
    tmpSplice.AdvanceSetting.HoldTime = 100;
    tmpSplice.AdvanceSetting.SqzTime = 200;
    tmpSplice.AdvanceSetting.ABDelay = 300;
    tmpSplice.AdvanceSetting.ABDur = 400;
    tmpSplice.AdvanceSetting.CutOff = false;
    tmpSplice.AdvanceSetting.AntiSide = true;
    tmpSplice.AdvanceSetting.MeasuredWidth = 100;
    tmpSplice.AdvanceSetting.MeasuredHeight = 100;
    tmpSplice.AdvanceSetting.ShrinkTube.ShrinkOption = false;
    tmpSplice.AdvanceSetting.ShrinkTube.ShrinkTubeID = 0;
    tmpSplice.AdvanceSetting.ShrinkTube.ShrinkTime = 10;
    tmpSplice.AdvanceSetting.ShrinkTube.ShrinkTemperature = 260;
    tmpSplice.TestSetting.Qutanty = 55;
    tmpSplice.TestSetting.StopCount = 20;
    tmpSplice.TestSetting.TestMode = UNCONSTRAINED;
    tmpSplice.TestSetting.TeachModeSetting.TeachModeType = UNDEFINED;
    for(int i=0;i< 18;i++)
        tmpSplice.TestSetting.TeachModeSetting.TeachModequal_Window[i] = 40;
    tmpSplice.TestSetting.TestingDone = true;
    QMap<int, QString>::const_iterator i = TestMap.constBegin();
    while (i != TestMap.constEnd()) {
        tmpSplice.WireIndex.insert(i.key(),i.value());
        ++i;
    }
    tmpSplice.NoOfWires = tmpSplice.WireIndex.size();

    _SQLITCLASS->UpdateRecordIntoTable(&tmpSplice);
}

void DataBaseTest::TestUpdateOneRecordIntoPartTable()
{
    SQLITCLASS *_SQLITCLASS = DBPartTable::Instance();
    struct PartElement tmpPart;
    tmpPart.PartID = 3;
    tmpPart.PartName = "TESTPART";
    tmpPart.CreatedDate = "20161020";
    tmpPart.OperatorID = "JW";
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
    tmpPart.SpliceIndex.insert(0,PartAttribute);
    PartAttribute.SpliceName = "JWang";
    PartAttribute.CurrentBoardLayoutZone = 2;
    PartAttribute.CurrentWorkstation = 3;
    tmpPart.SpliceIndex.insert(1,PartAttribute);
    PartAttribute.SpliceName = "JW";
    PartAttribute.CurrentBoardLayoutZone = 3;
    PartAttribute.CurrentWorkstation = 4;
    tmpPart.SpliceIndex.insert(2,PartAttribute);
    tmpPart.NoOfSplice = tmpPart.SpliceIndex.size();

    _SQLITCLASS->UpdateRecordIntoTable(&tmpPart);
}

void DataBaseTest::TestUpdateOneRecordIntoWorkOrderTable()
{
    SQLITCLASS *_SQLITCLASS = DBWorkOrderTable::Instance();

    struct WorkOrderElement tmpWorkOrder;
    tmpWorkOrder.WorkOrderID = 3;
    tmpWorkOrder.WorkOrderName = "TESTWORKORDER";
    tmpWorkOrder.CreatedDate = "20161020";
    tmpWorkOrder.OperatorID = "JW";
    tmpWorkOrder.PartIndex.insert(1,"PartName");
    tmpWorkOrder.NoOfPart = tmpWorkOrder.PartIndex.size();

    tmpWorkOrder.Quantity = 50;
    tmpWorkOrder.CurrentPartCount = 30;

    tmpWorkOrder.MissSpliceList.insert(0, "MissSplice1");
    tmpWorkOrder.MissSpliceList.insert(1, "MissSplice2");
    tmpWorkOrder.MissSpliceList.insert(2, "MissSplice3");

    tmpWorkOrder.CurrentSplice.SpliceID = 5;
    tmpWorkOrder.CurrentSplice.SpliceName = "TESTSPLICE";

    tmpWorkOrder.WorkOrderDone = false;

    _SQLITCLASS->UpdateRecordIntoTable(&tmpWorkOrder);
}
