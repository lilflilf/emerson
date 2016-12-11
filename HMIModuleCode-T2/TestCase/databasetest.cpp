#include "databasetest.h"
#include "Modules/UtilityClass.h"
#include "DataBase/DBWireTable.h"
#include "DataBase/DBPresetTable.h"
#include "DataBase/DBPartTable.h"
#include "DataBase/DBWorkOrderTable.h"
#include "DataBase/DBOperatorTable.h"
#include "DataBase/DBWeldResultTable.h"
#include <QMap>
#include <QDebug>
#include <QDateTime>
//#include "Interface/definition.h"
#include "Interface/WireElement.h"
#include "Interface/PresetElement.h"
#include "Interface/PartElement.h"
#include "Interface/WorkOrderElement.h"
#include "Interface/WeldResultElement.h"
#include "Interface/Settings/OperatorLibrary.h"
#include "Modules/UtilityClass.h"
DataBaseTest::DataBaseTest()
{

}

void DataBaseTest::TestInsertOneRecordIntoWireTable()
{
    SQLITCLASS *_SQLITCLASS = DBWireTable::Instance();
    struct WireElement tmpWire;
    tmpWire.WireName = "TESTWire1";
    QDateTime tmp = QDateTime::fromString("2016/10/24 00:00:00", "yyyy/MM/dd hh:mm:ss");
    tmpWire.CreatedDate = tmp.toTime_t();
    tmpWire.OperatorID = 2;
    tmpWire.Color = "GREEN";
    tmpWire.Stripe.TypeOfStripe = Slash;
    tmpWire.Stripe.Color = "RED";
    tmpWire.Gauge = 100;
    tmpWire.TypeOfWire = Copper;
    tmpWire.Side = Right;
    tmpWire.VerticalSide = Basic;
    tmpWire.Position = Middle;
    int i  = _SQLITCLASS->InsertRecordIntoTable(&tmpWire);
    qDebug()<< "Insert ID: "<<i;
}

void DataBaseTest::TestInsertOneRecordIntoPresetTable()
{
    SQLITCLASS *_SQLITCLASS = DBPresetTable::Instance();
    QMap<int, QString> TestMap;
    TestMap.insert(0, "WANG");
    TestMap.insert(1,"Mr.Li");
    TestMap.insert(2, "Zhang");
    struct PresetElement tmpSplice;
    tmpSplice.SpliceName = "TESTSplice4";
    QDateTime tmp = QDateTime::fromString("2016/10/20 00:00:00", "yyyy/MM/dd hh:mm:ss");
    tmpSplice.CreatedDate = tmp.toTime_t();
    tmpSplice.OperatorID = 2;
    tmpSplice.CrossSection = 100;
    tmpSplice.PresetPicNamePath = "C:\\";
    tmpSplice.Verified = false;
    tmpSplice.WeldSettings.BasicSetting.Energy = 155;
    tmpSplice.WeldSettings.BasicSetting.Amplitude = 55;
    tmpSplice.WeldSettings.BasicSetting.Width = 800;
    tmpSplice.WeldSettings.BasicSetting.Pressure = 80;
    tmpSplice.WeldSettings.BasicSetting.TrigPres = 50;
    tmpSplice.WeldSettings.QualitySetting.Time.Plus = 500;
    tmpSplice.WeldSettings.QualitySetting.Time.Minus = 0;
    tmpSplice.WeldSettings.QualitySetting.Power.Plus = 3960;
    tmpSplice.WeldSettings.QualitySetting.Power.Minus = 0;
    tmpSplice.WeldSettings.QualitySetting.Preheight.Plus = 1500;
    tmpSplice.WeldSettings.QualitySetting.Preheight.Minus = 0;
    tmpSplice.WeldSettings.QualitySetting.Height.Plus = 1500;
    tmpSplice.WeldSettings.QualitySetting.Height.Minus = 0;
    tmpSplice.WeldSettings.QualitySetting.Force.Plus = 55;
    tmpSplice.WeldSettings.QualitySetting.Force.Minus = 0;
    tmpSplice.WeldSettings.AdvanceSetting.WeldMode = ENERGY;
    tmpSplice.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode = STEPDISABLE;
    tmpSplice.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep = 55;
    tmpSplice.WeldSettings.AdvanceSetting.StepWeld.TimeToStep = 1;
    tmpSplice.WeldSettings.AdvanceSetting.StepWeld.PowerToStep = 500;
    tmpSplice.WeldSettings.AdvanceSetting.StepWeld.Amplitude2 = 22;
    tmpSplice.WeldSettings.AdvanceSetting.PreBurst = 1000;
    tmpSplice.WeldSettings.AdvanceSetting.HoldTime = 100;
    tmpSplice.WeldSettings.AdvanceSetting.SqzTime = 200;
    tmpSplice.WeldSettings.AdvanceSetting.ABDelay = 300;
    tmpSplice.WeldSettings.AdvanceSetting.ABDur = 400;
    tmpSplice.WeldSettings.AdvanceSetting.CutOff = false;
    tmpSplice.WeldSettings.AdvanceSetting.CutOffSpliceTime = -1;
    tmpSplice.WeldSettings.AdvanceSetting.AntiSide = true;
    tmpSplice.WeldSettings.AdvanceSetting.AntiSideSpliceTime = -1;
    tmpSplice.WeldSettings.AdvanceSetting.MeasuredWidth = 100;
    tmpSplice.WeldSettings.AdvanceSetting.MeasuredHeight = 100;
    tmpSplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption = false;
    tmpSplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID = 0;
    tmpSplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime = 10;
    tmpSplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature = 260;
    tmpSplice.TestSetting.Qutanty = 10;
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
    QDateTime tmp = QDateTime::fromString("2016/10/20 00:00:00", "yyyy/MM/dd hh:mm:ss");
    tmpPart.CreatedDate = tmp.toTime_t();
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

    _SQLITCLASS->InsertRecordIntoTable(&tmpPart);
}

void DataBaseTest::TestInsertOneRecordIntoWorkOrderTable()
{
    SQLITCLASS *_SQLITCLASS = DBWorkOrderTable::Instance();

    struct WorkOrderElement tmpWorkOrder;
    tmpWorkOrder.WorkOrderName = "TESTWorkOrder4";
    QDateTime tmp = QDateTime::fromString("2016/10/20 00:00:00", "yyyy/MM/dd hh:mm:ss");
    tmpWorkOrder.CreatedDate = tmp.toTime_t();
    tmpWorkOrder.OperatorID = 2;
    tmpWorkOrder.PartIndex.insert(1,"PartName");
    tmpWorkOrder.NoOfPart = tmpWorkOrder.PartIndex.size();

    tmpWorkOrder.Quantity = 10;
    tmpWorkOrder.CurrentPartCount = 30;

    tmpWorkOrder.MissSpliceList.insert(0, "MissSplice1");
    tmpWorkOrder.MissSpliceList.insert(1, "MissSplice2");
    tmpWorkOrder.MissSpliceList.insert(2, "MissSplice3");

    tmpWorkOrder.CurrentSplice.SpliceID = 5;
    tmpWorkOrder.CurrentSplice.SpliceName = "TestSplice";

    tmpWorkOrder.WorkOrderDone = false;

    _SQLITCLASS->InsertRecordIntoTable(&tmpWorkOrder);
}

void DataBaseTest::TestInsertOneRecordIntoOperatorTable()
{
    SQLITCLASS *_SQLITCLASS = DBOperatorTable::Instance();
    struct OperatorElement tmpOperator;
    tmpOperator.OperatorName = "TESTOperator";
    QDateTime tmp = QDateTime::fromString("2016/10/20 00:00:00", "yyyy/MM/dd hh:mm:ss");
    tmpOperator.CreatedDate = tmp.toTime_t();
    tmpOperator.WhoCreatedNewID = 2;
    tmpOperator.Password = "4567";
    tmpOperator.PermissionLevel = OPEN;

    _SQLITCLASS->InsertRecordIntoTable(&tmpOperator);
}

void DataBaseTest::TestInsertOneRecordIntoWeldResultTable()
{
    SQLITCLASS *_SQLITCLASS = DBWeldResultTable::Instance();
    struct WeldResultElement tmpWeldResult;
    tmpWeldResult.OperatorName = "TESTOperator";
    QDateTime tmp = QDateTime::currentDateTime();
    tmpWeldResult.CreatedDate = tmp.toTime_t();
    tmpWeldResult.CurrentWorkOrder.WorkOrderID = 1;
    tmpWeldResult.CurrentWorkOrder.WorkOrderName = "WorkOrderID";
    tmpWeldResult.CurrentPart.PartID = 1;
    tmpWeldResult.CurrentPart.PartName = "PartName";
    tmpWeldResult.CurrentSplice.SpliceID = 1;
    tmpWeldResult.CurrentSplice.SpliceName = "SpliceName";
    tmpWeldResult.WeldCount = 0;
    tmpWeldResult.PartCount = 0;
    tmpWeldResult.ActualResult.ActualAlarmflags = 0x55;
    tmpWeldResult.ActualResult.ActualAmplitude = 1;
    tmpWeldResult.ActualResult.ActualAmplitude2 = 2;
    tmpWeldResult.ActualResult.ActualEnergy = 3;
    tmpWeldResult.ActualResult.ActualPeakPower = 4;
    tmpWeldResult.ActualResult.ActualPostheight = 5;
    tmpWeldResult.ActualResult.ActualPreheight = 6;
    tmpWeldResult.ActualResult.ActualPressure = 7;
    tmpWeldResult.ActualResult.ActualTime = 8;
    tmpWeldResult.ActualResult.ActualTPressure = 9;
    tmpWeldResult.ActualResult.ActualWidth = 10;
    tmpWeldResult.SampleRatio = SampleWith1ms;
    tmpWeldResult.NoOfSamples = 2;
    tmpWeldResult.PowerGraph.insert(1, 500);
    tmpWeldResult.PowerGraph.insert(2, 1000);
    tmpWeldResult.PostHeightGraph.insert(1, 120);
    tmpWeldResult.PostHeightGraph.insert(2, 240);
    _SQLITCLASS->InsertRecordIntoTable(&tmpWeldResult);
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

void DataBaseTest::TestQueryEntireOpertorTable()
{
    SQLITCLASS *_SQLITCLASS = DBOperatorTable::Instance();
    QMap<int, QString> tmpMap;
    _SQLITCLASS->QueryEntireTable(&tmpMap);
    QMap<int, QString>::ConstIterator i = tmpMap.constBegin();
    while(i != tmpMap.constEnd())
    {
        qDebug()<<"Operator ID: "<<i.key();
        qDebug()<<"Operator Name: "<<i.value();
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
        QDateTime tmp = QDateTime::fromTime_t(tmpWire.CreatedDate);
        qDebug()<<"CreatedDate: "<<tmp.toString("yyyy/MM/dd hh:mm:ss");
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

void DataBaseTest::TestQueryOneOperatorTable()
{
    SQLITCLASS *_SQLITCLASS = DBOperatorTable::Instance();
    OperatorElement tmpOperator;
    if(_SQLITCLASS->QueryOneRecordFromTable(1,"TESTOperator", &tmpOperator))
    {
        qDebug()<<"OperatorID: "<<tmpOperator.OperatorID;
        qDebug()<<"OperatorName: "<<tmpOperator.OperatorName;
        QDateTime tmp = QDateTime::fromTime_t(tmpOperator.CreatedDate);
        qDebug()<<"CreatedDate: "<<tmp.toString("yyyy/MM/dd hh:mm:ss");
        qDebug()<<"WhoCreatedNewID: "<<tmpOperator.WhoCreatedNewID;
        qDebug()<<"Password: "<<tmpOperator.Password;
        qDebug()<<"PermissionLevel: "<<tmpOperator.PermissionLevel;
    }
}

void DataBaseTest::TestQueryOnlyUseFieldWeldResult()
{
    DBWeldResultTable *_SQLITCLASS = DBWeldResultTable::Instance();
    QMap<int, QString> tmpMap;
    _SQLITCLASS->QueryOnlyUseField("WorkOrderName", &tmpMap, true);
    QMap<int, QString>::ConstIterator i = tmpMap.constBegin();
    while(i != tmpMap.constEnd())
    {
        qDebug()<<"WorkResult ID: "<<i.key();
        qDebug()<<"WorkOrder Name: "<<i.value();
        ++i;
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

void DataBaseTest::TestDeleteEntireOperator()
{
    SQLITCLASS *_SQLITCLASS = DBOperatorTable::Instance();
    if(_SQLITCLASS->DeleteEntireTable())
        qDebug()<<"Delete Operator Table Sucessful.";
    else
        qDebug()<<"Delete Operator Table Unsucessful.";
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

void DataBaseTest::TestDeleteOneOperatorTable()
{
    SQLITCLASS *_SQLITCLASS = DBOperatorTable::Instance();
    if(_SQLITCLASS->DeleteOneRecordFromTable(2, "TESTOperator"))
        qDebug()<<"Delete Operator Table Sucessful.";
    else
        qDebug()<<"Delete Operator Table Unsucessful.";
}

void DataBaseTest::TestUpdateOneRecordIntoWireTable()
{
    SQLITCLASS *_SQLITCLASS = DBWireTable::Instance();
    struct WireElement tmpWire;
    tmpWire.WireID = 2;
    tmpWire.WireName = "TESTWire1";
    QDateTime tmp = QDateTime::fromString("10/23/2016 15:40:00", "yyyy/MM/dd hh:mm:ss");
    tmpWire.CreatedDate = tmp.toTime_t();
    tmpWire.OperatorID = 2;
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
    QDateTime tmp = QDateTime::fromString("2016/10/20 00:00:00", "yyyy/MM/dd hh:mm:ss");
    tmpSplice.CreatedDate = tmp.toTime_t();
    tmpSplice.OperatorID = 2;
    tmpSplice.CrossSection = 100;
    tmpSplice.PresetPicNamePath = "C:\\";
    tmpSplice.Verified = false;
    tmpSplice.WeldSettings.BasicSetting.Energy = 155;
    tmpSplice.WeldSettings.BasicSetting.Amplitude = 55;
    tmpSplice.WeldSettings.BasicSetting.Width = 800;
    tmpSplice.WeldSettings.BasicSetting.Pressure = 80;
    tmpSplice.WeldSettings.BasicSetting.TrigPres = 50;
    tmpSplice.WeldSettings.QualitySetting.Time.Plus = 500;
    tmpSplice.WeldSettings.QualitySetting.Time.Minus = 0;
    tmpSplice.WeldSettings.QualitySetting.Power.Plus = 3960;
    tmpSplice.WeldSettings.QualitySetting.Power.Minus = 0;
    tmpSplice.WeldSettings.QualitySetting.Preheight.Plus = 1500;
    tmpSplice.WeldSettings.QualitySetting.Preheight.Minus = 0;
    tmpSplice.WeldSettings.QualitySetting.Height.Plus = 1500;
    tmpSplice.WeldSettings.QualitySetting.Height.Minus = 0;
    tmpSplice.WeldSettings.QualitySetting.Force.Plus = 55;
    tmpSplice.WeldSettings.QualitySetting.Force.Minus = 0;
    tmpSplice.WeldSettings.AdvanceSetting.WeldMode = ENERGY;
    tmpSplice.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode = STEPDISABLE;
    tmpSplice.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep = 55;
    tmpSplice.WeldSettings.AdvanceSetting.StepWeld.TimeToStep = 1;
    tmpSplice.WeldSettings.AdvanceSetting.StepWeld.PowerToStep = 500;
    tmpSplice.WeldSettings.AdvanceSetting.StepWeld.Amplitude2 = 22;
    tmpSplice.WeldSettings.AdvanceSetting.PreBurst = 1000;
    tmpSplice.WeldSettings.AdvanceSetting.HoldTime = 100;
    tmpSplice.WeldSettings.AdvanceSetting.SqzTime = 200;
    tmpSplice.WeldSettings.AdvanceSetting.ABDelay = 300;
    tmpSplice.WeldSettings.AdvanceSetting.ABDur = 400;
    tmpSplice.WeldSettings.AdvanceSetting.CutOff = false;
    tmpSplice.WeldSettings.AdvanceSetting.CutOffSpliceTime = -1;
    tmpSplice.WeldSettings.AdvanceSetting.AntiSide = true;
    tmpSplice.WeldSettings.AdvanceSetting.AntiSideSpliceTime = -1;
    tmpSplice.WeldSettings.AdvanceSetting.MeasuredWidth = 100;
    tmpSplice.WeldSettings.AdvanceSetting.MeasuredHeight = 100;
    tmpSplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption = false;
    tmpSplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID = 0;
    tmpSplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime = 10;
    tmpSplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature = 260;
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
    QDateTime tmp = QDateTime::fromString("2016/10/20 00:00:00", "yyyy/MM/dd hh:mm:ss");
    tmpPart.CreatedDate = tmp.toTime_t();
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

    _SQLITCLASS->UpdateRecordIntoTable(&tmpPart);
}

void DataBaseTest::TestUpdateOneRecordIntoWorkOrderTable()
{
    SQLITCLASS *_SQLITCLASS = DBWorkOrderTable::Instance();

    struct WorkOrderElement tmpWorkOrder;
    tmpWorkOrder.WorkOrderID = 3;
    tmpWorkOrder.WorkOrderName = "TESTWORKORDER";
    QDateTime tmp = QDateTime::fromString("2016/10/20 00:00:00", "yyyy/MM/dd hh:mm:ss");
    tmpWorkOrder.CreatedDate = tmp.toTime_t();
    tmpWorkOrder.OperatorID = 2;
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

void DataBaseTest::TestUpdateOneRecordIntoOperatorTable()
{
    SQLITCLASS *_SQLITCLASS = DBOperatorTable::Instance();

    struct OperatorElement tmpOperator;
    tmpOperator.OperatorID = 3;
    tmpOperator.OperatorName = "TESTJW";
    QDateTime tmp = QDateTime::fromString("2016/10/26 00:00:00", "yyyy/MM/dd hh:mm:ss");
    tmpOperator.CreatedDate = tmp.toTime_t();
    tmpOperator.Password = "1234";
    tmpOperator.WhoCreatedNewID = 1;
    tmpOperator.PermissionLevel = ADMINISTRATOR;

    _SQLITCLASS->UpdateRecordIntoTable(&tmpOperator);
}

void DataBaseTest::TestQueryOnlyTimeWireTable()
{
    SQLITCLASS *_SQLITCLASS = DBWireTable::Instance();
    unsigned int currentDate = QDateTime::currentDateTime().toTime_t();
    QMap<int, QString> tmpMap;
    QDateTime TimeLabel = QDateTime::fromString("2015/10/20 00:00:00", "yyyy/MM/dd hh:mm:ss");
    _SQLITCLASS->QueryOnlyUseTime(TimeLabel.toTime_t(), currentDate, &tmpMap);
    QMap<int, QString>::ConstIterator i = tmpMap.constBegin();
    while(i != tmpMap.constEnd())
    {
        qDebug()<<"Wire ID: "<<i.key();
        qDebug()<<"Wire Name: "<<i.value();
        ++i;
    }
}

void DataBaseTest::TestQueryOnlyUseNameWireTable()
{

}
