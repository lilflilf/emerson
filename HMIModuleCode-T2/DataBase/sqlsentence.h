#ifndef SQLSENTENCE_H
#define SQLSENTENCE_H
#include <QString>
enum{
    CREATEWIRETABLE,
    INSERTWIRETABLE,
    CREATESPLICETABLE,
    INSERTSPLICETABLE,
    CREATEPARTTABLE,
    INSERTPARTTABLE,
    CREATEWORKORDERTABLE,
    INSERTWORKORDERTABLE,
    QUERYENTIREWIRETABLE,
    QUERYENTIRESPLICETABLE,
    QUERYENTIREPARTTABLE,
    QUERYENTIREWORKORDERTABLE,

};

QString SQLSentence[] = {
    "CREATE TABLE Wire ("                 /*0 Create Wire Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "WireName VARCHAR UNIQUE, "
    "CreatedDate VARCHAR, OperatorID VARCHAR,Color VARCHAR,"
    "StripeType INT, StripeColor VARCHAR, Gauge INT,"
    "MetalType INT, HorizontalLocation INT, VerticalLocation INT,"
    "VerticalPosition INT)",

    "INSERT INTO Wire ("                   /*1 Insert record into Wire Table*/
    "WireName, CreatedDate, OperatorID, Color, "
    "StripeType, StripeColor, Gauge, MetalType, "
    "HorizontalLocation, VerticalLocation, VerticalPosition)"
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",


    "CREATE TABLE Preset ("               /*2 Create Preset Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "SpliceName VARCHAR UNIQUE, "
    "CreatedDate VARCHAR, OperatorID VARCHAR, CrossSection INT, "
    "PresetPicPath VARCHAR, Verified BOOLEAN,"                  /* 7 items */

    /*WeldSetting*/                                             /* 5 items */
    "Energy INT, Amplitude INT, Width INT, Pressure INT, TrigPres INT, "

    /*QualityWindowSetting*/
    "TimePlus INT, TimeMinus INT, PowerPlus INT, PowerMinus INT, "
    "PreheightPlus INT, PreheightMinus INT, HeightPlus INT, HeightMinus INT, "
    "ForcePlus INT, ForceMinus INT, "                           /* 10 items */

    /*AdvanceSetting*/                                          /* 15 items */
    "WeldMode INT, StepWeldMode INT, EnergyToStep INT, TimeToStep INT, "
    "PowerToStep INT, Amplitude2 INT, PreBurst INT, HoldTime INT, "
    "SqueezeTime INT, AfterBurstDelay INT, AfterBurstDuring INT, "
    "CutOff BOOLEAN, AntiSide BOOLEAN, MeasuredWidth INT, MeasuredHeight INT, "

    /*Shrink Tube Setting*/
    "ShrinkOption BOOLEAN, ShrinkTubeID INT, ShrinkTime INT, "
    "ShrinkTemperature INT, "                                   /*4 items */

    /*Testing*/
    "Qutanty INT, StopCount INT, TestMode INT, TEACHMODETYPE ENUM, "
    "TimePLRG INT, TimeMSRG INT, PowerPLRG INT, PowerMSRG INT, "
    "PreHeightPLRG INT, PreHeightMSRG INT, HeightPLRG INT, HeightMSRG INT, "
    "ForcePLRG INT, ForceMSRG INT, TimeConfigPL INT, TimeConfigMS INT, "
    "PowerConfigPL INT, PowerConfigMS INT, PreHeightConfigPL INT, PreHeightConfigMS INT, "
    "HeightConfigPL INT, HeightCOnfigMS INT, TestingDone BOOLEAN, "                /* 23 items */

    "NoOfWires INT, "
    /*JSON Structure WireID, WireName*/
    "JSONWire VARCHAR)",                 /*2 items */


    "INSERT INTO Preset ("                   /*3 Insert record into Preset Table*/
    "SpliceName, CreatedDate, OperatorID, CrossSection, PresetPicPath, Verified, "

    /*WeldSetting*/
    "Energy, Amplitude, Width, Pressure, TrigPres, "

    /*QualityWindowSetting*/
    "TimePlus, TimeMinus, PowerPlus, PowerMinus, PreheightPlus, PreheightMinus, "
    "HeightPlus, HeightMinus, ForcePlus, ForceMinus, "

    /*AdvanceSetting*/
    "WeldMode, StepWeldMode, EnergyToStep, TimeToStep, PowerToStep, Amplitude2, "
    "PreBurst, HoldTime, SqueezeTime, AfterBurstDelay, AfterBurstDuring, CutOff, "
    "AntiSide, MeasuredWidth, MeasuredHeight, "

    /*Shrink Tube Setting*/
    "ShrinkOption, ShrinkTubeID, ShrinkTime, ShrinkTemperature, "

    /*Testing*/
    "Qutanty, StopCount, TestMode, TEACHMODETYPE, TimePLRG, TimeMSRG, "
    "PowerPLRG, PowerMSRG, PreHeightPLRG, PreHeightMSRG, HeightPLRG, HeightMSRG, "
    "ForcePLRG, ForceMSRG, TimeConfigPL, TimeConfigMS, PowerConfigPL, PowerConfigMS, "
    "PreHeightConfigPL, PreHeightConfigMS, HeightConfigPL, HeightCOnfigMS, TestingDone, "

    /*JSON Structure WireID, WireName*/
    "NoOfWires, JSONWire) "
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",

    "CREATE TABLE Part ("                 /*4 Create Part Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "PartName VARCHAR UNIQUE, "
    "CreatedDate VARCHAR, OperatorID VARCHAR, "
    /* PartTypeSetting */
    "ProcessMode ENUM,"
    "TotalWorkstation INT, MaxSplicesPerWorkstation INT, "
    "Rows INT, Columns INT, MaxSplicesPerZone INT, "
    "NoOfSplice INT, JSONSplice VARCHAR)",

    "INSERT INTO Part ("                   /*5 Insert record into Part Table*/
    "PartName, CreatedDate, OperatorID, "
    "ProcessMode, TotalWorkstation, MaxSplicesPerWorkstation, "
    "Rows, Columns, MaxSplicesPerZone, NoOfSplice, JSONSplice) "
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",

    "CREATE TABLE WorkOrder ("                 /*6 Create WorkOrder Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "WorkOrderName VARCHAR UNIQUE, "
    "CreatedDate VARCHAR, OperatorID VARCHAR, "
    "NoOfPart INT, Quantity INT, CurrentPartCount INT, "
    "CurrentSpliceID INT, CurrentSpliceName VARCHAR, WorkOrderDone INT, "
    "JSONPartIndex VARCHAR, JSONMissSpliceList VARCHAR)",

    "INSERT INTO WorkOrder ("                   /*7 Insert record into Part Table*/
    "WorkOrderName, CreatedDate, OperatorID, "
    "NoOfPart, Quantity, CurrentPartCount, "
    "CurrentSpliceID, CurrentSpliceName, WorkOrderDone, "
    "JSONPartIndex, JSONMissSpliceList) "
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",

    "SELECT ID, WireName FROM Wire",           /*8 Query Entire Wire Table */
    "SELECT ID, SpliceName FROM Preset",       /*9 Query Entire Preset Table */
    "SELECT ID, PartName FROM Part",           /*10 Query Entire Part Table */
    "SELECT ID, WorkOrderName FROM WorkOrder", /*11 Query Entire WorkOrder Table */


};


#endif // SQLSENTENCE_H
