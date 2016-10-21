#include "databasetest.h"
#include "Modules/UtilityClass.h"
#include "DataBase/Sqlit3Class.h"
#include <QMap>
#include <QDebug>
#include "Interface/definition.h"
#include "Modules/UtilityClass.h"
DataBaseTest::DataBaseTest()
{

}

void DataBaseTest::TestInsertOneRecordIntoWireTable()
{
    SQLITCLASS *_SQLITCLASS = SQLITCLASS::Instance();
    struct WireElementStructure tmpWire;
    tmpWire.WireName = "TESTWIRE";
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
    _SQLITCLASS->InsertRecordIntoWireTable(&tmpWire);
}

void DataBaseTest::TestInsertOneRecordIntoPresetTable()
{
    SQLITCLASS *_SQLITCLASS = SQLITCLASS::Instance();
    UtilityClass* _UtilityClass = UtilityClass::Instance();
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
    tmpSplice.AdvanceSetting.ShrinkTube.ShrinkTubeIndex = 0;
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

    _SQLITCLASS->InsertRecordIntoPresetTable(&tmpSplice);
}

void DataBaseTest::TestInsertOneRecordIntoPartTable()
{
    SQLITCLASS *_SQLITCLASS = SQLITCLASS::Instance();
    UtilityClass* _UtilityClass = UtilityClass::Instance();

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

    _SQLITCLASS->InsertRecordIntoPartTable(&tmpPart);
}

void DataBaseTest::TestInsertOneRecordIntoWorkOrderTable()
{
    SQLITCLASS *_SQLITCLASS = SQLITCLASS::Instance();
    UtilityClass* _UtilityClass = UtilityClass::Instance();

    struct WorkOrder tmpWorkOrder;
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

    _SQLITCLASS->InsertRecordIntoWorkOrderTable(&tmpWorkOrder);
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
    SQLITCLASS *_SQLITCLASS = SQLITCLASS::Instance();
    QMap<int, QString> tmpMap;
    _SQLITCLASS->QueryEntireWireTable(&tmpMap);
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
    SQLITCLASS *_SQLITCLASS = SQLITCLASS::Instance();
    QMap<int, QString> tmpMap;
    _SQLITCLASS->QueryEntirePresetTable(&tmpMap);
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
    SQLITCLASS *_SQLITCLASS = SQLITCLASS::Instance();
    QMap<int, QString> tmpMap;
    _SQLITCLASS->QueryEntirePartTable(&tmpMap);
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
    SQLITCLASS *_SQLITCLASS = SQLITCLASS::Instance();
    QMap<int, QString> tmpMap;
    _SQLITCLASS->QueryEntireWorkOrderTable(&tmpMap);
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
    SQLITCLASS *_SQLITCLASS = SQLITCLASS::Instance();
    WireElementStructure tmpWire;
    _SQLITCLASS->QueryOneWireTable(2,"TESTWIRE", &tmpWire);
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
