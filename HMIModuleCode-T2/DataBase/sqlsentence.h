#ifndef SQLSENTENCE_H
#define SQLSENTENCE_H
#include <QString>
enum{
    CREATE_WIRE_TABLE = 0,
    INSERT_WIRE_TABLE = 1,
    CREATE_SPLICE_TABLE = 2,
    INSERT_SPLICE_TABLE = 3,
    CREATE_PART_TABLE = 4,
    INSERT_PART_TABLE = 5,
    CREATE_WORKORDER_TABLE = 6,
    INSERT_WORKORDER_TABLE = 7,
    QUERY_ENTIRE_WIRE_TABLE = 8,
    QUERY_ENTIRE_SPLICE_TABLE = 9,
    QUERY_ENTIRE_PART_TABLE = 10,
    QUERY_ENTIRE_WORKORDER_TABLE = 11,
    QUERY_ONE_RECORD_WIRE_TABLE = 12,
    QUERY_ONE_RECORD_SPLICE_TABLE = 13,
    QUERY_ONE_RECORD_PART_TABLE = 14,
    QUERY_ONE_RECORD_WORKORDER_TABLE = 15,
    DELETE_ENTIRE_WIRE_TABLE = 16,
    DELETE_ENTIRE_SPLICE_TABLE = 17,
    DELETE_ENTIRE_PART_TABLE = 18,
    DELETE_ENTIRE_WORKORDER_TABLE = 19,
    DELETE_ONE_RECORD_WIRE_TABLE = 20,
    DELETE_ONE_RECORD_SPLICE_TABLE = 21,
    DELETE_ONE_RECORD_PART_TABLE = 22,
    DELETE_ONE_RECORD_WORKORDER_TABLE = 23,
    UPDATE_ONE_RECORD_WIRE_TABLE = 24,
    UPDATE_ONE_RECORD_SPLICE_TABLE = 25,
    UPDATE_ONE_RECORD_PART_TABLE = 26,
    UPDATE_ONE_RECORD_WORKORDER_TABLE = 27,

};

const QString SQLSentence[] = {
    "CREATE TABLE Wire ("                   /*0 Create Wire Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "WireName VARCHAR UNIQUE, "
    "CreatedDate VARCHAR, OperatorID INT, Color VARCHAR, "
    "StripeType INT, StripeColor VARCHAR, Gauge INT, "
    "MetalType INT, HorizontalLocation INT, VerticalLocation INT, "
    "VerticalPosition INT)",

    "INSERT INTO Wire ("                    /*1 Insert record into Wire Table*/
    "WireName, CreatedDate, OperatorID, Color, "
    "StripeType, StripeColor, Gauge, MetalType, "
    "HorizontalLocation, VerticalLocation, VerticalPosition)"
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",


    "CREATE TABLE Preset ("                 /*2 Create Preset Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "SpliceName VARCHAR UNIQUE, "
    "CreatedDate VARCHAR, OperatorID INT, CrossSection INT, "
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


    "INSERT INTO Preset ("                      /*3 Insert record into Preset Table*/
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

    "CREATE TABLE Part ("                       /*4 Create Part Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "PartName VARCHAR UNIQUE, "
    "CreatedDate VARCHAR, OperatorID INT, "
    /* PartTypeSetting */
    "ProcessMode ENUM,"
    "TotalWorkstation INT, MaxSplicesPerWorkstation INT, "
    "Rows INT, Columns INT, MaxSplicesPerZone INT, "
    "NoOfSplice INT, JSONSplice VARCHAR)",

    "INSERT INTO Part ("                        /*5 Insert record into Part Table*/
    "PartName, CreatedDate, OperatorID, "
    "ProcessMode, TotalWorkstation, MaxSplicesPerWorkstation, "
    "Rows, Columns, MaxSplicesPerZone, NoOfSplice, JSONSplice) "
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",

    "CREATE TABLE WorkOrder ("                  /*6 Create WorkOrder Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "WorkOrderName VARCHAR UNIQUE, "
    "CreatedDate VARCHAR, OperatorID INT, "
    "NoOfPart INT, Quantity INT, CurrentPartCount INT, "
    "CurrentSpliceID INT, CurrentSpliceName VARCHAR, WorkOrderDone INT, "
    "JSONPartIndex VARCHAR, JSONMissSpliceList VARCHAR)",

    "INSERT INTO WorkOrder ("                   /*7 Insert record into Part Table*/
    "WorkOrderName, CreatedDate, OperatorID, "
    "NoOfPart, Quantity, CurrentPartCount, "
    "CurrentSpliceID, CurrentSpliceName, WorkOrderDone, "
    "JSONPartIndex, JSONMissSpliceList) "
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",

    "SELECT ID, WireName FROM Wire",            /*8 Query Entire Wire Table */
    "SELECT ID, SpliceName FROM Preset",        /*9 Query Entire Preset Table */
    "SELECT ID, PartName FROM Part",            /*10 Query Entire Part Table */
    "SELECT ID, WorkOrderName FROM WorkOrder",  /*11 Query Entire WorkOrder Table */

                                                /*12 Query One Record From Wire Table */
    "SELECT * FROM Wire WHERE ID = ? AND WireName = ?",
                                                /*13 Query One Record From Splice Table */
    "SELECT * FROM Preset WHERE ID = ? AND SpliceName = ?",
                                                /*14 Query One Record From Part Table */
    "SELECT * FROM Part WHERE ID = ? AND PartName = ?",
                                                /*15 Query One Record From WorkOrder Table */
    "SELECT * FROM WorkOrder WHERE ID = ? AND WorkOrderName = ?",

    "DELETE FROM Wire",                          /*16 Delete Entire Wire Table*/
    "DELETE FROM Preset",                        /*17 Delete Entire Splice Table*/
    "DELETE FROM Part",                          /*18 Delete Entire Part Table*/
    "DELETE FROM WorkOrder",                     /*19 Delete Entire WorkOrder Table*/
    "DELETE FROM Wire WHERE ID = ? AND WireName = ?",
                                                 /*20 Delete One Record from Wire Table*/
    "DELETE FROM Preset WHERE ID = ? AND SpliceName = ?",
                                                 /*21 Delete One Record from Splice Table*/
    "DELETE FROM Part WHERE ID = ? AND PartName = ?",
                                                 /*22 Delete One Record from Part Table*/
    "DELETE FROM WorkOrder WHERE ID = ? AND WorkOrderName = ?",
                                                 /*23 Delete One Record from WorkOrder Table*/
    "UPDATE Wire Set WireName = ?, CreatedDate = ?, OperatorID = ?, "
    "Color = ?, StripeType = ?, StripeColor = ?, Gauge = ?, MetalType = ?, "
    "HorizontalLocation = ?, VerticalLocation = ?, VerticalPosition = ? "
    "WHERE ID = ?",                              /*24 Update One Record to Wire Table*/

    "UPDATE Preset Set SpliceName = ?, CreatedDate = ?, OperatorID = ?, "
    "CrossSection = ?, PresetPicPath = ?, Verified = ?, " /* item 6 */
    "Energy = ?, Amplitude = ?, Width = ?, Pressure = ?, TrigPres= ?, " /* item 5 */

    "TimePlus = ?, TimeMinus = ?, PowerPlus = ?, PowerMinus = ?, "    /* item 10 */
    "PreheightPlus = ?, PreheightMinus= ?, HeightPlus = ?, HeightMinus = ?, "
    "ForcePlus = ?, ForceMinus = ?, "

    "WeldMode = ?, StepWeldMode = ?, EnergyToStep = ?, TimeToStep = ?, PowerToStep = ?, "
    "Amplitude2 = ?, PreBurst = ?, HoldTime = ?, SqueezeTime = ?, AfterBurstDelay = ?, "
    "AfterBurstDuring = ?, CutOff = ?, AntiSide = ?, MeasuredWidth = ?, MeasuredHeight = ?, "  /* item 15 */

    "ShrinkOption = ?, ShrinkTubeID = ?, ShrinkTime = ?, ShrinkTemperature = ?, "

    "Qutanty = ?, StopCount = ?, TestMode = ?, TEACHMODETYPE = ?, "
    "TimePLRG = ?, TimeMSRG = ?, PowerPLRG = ?, PowerMSRG = ?, "
    "PreHeightPLRG = ?, PreHeightMSRG = ?, HeightPLRG = ?, HeightMSRG = ?, "
    "ForcePLRG = ?, ForceMSRG = ?, TimeConfigPL = ?, TimeConfigMS = ?, "
    "PowerConfigPL = ?, PowerConfigMS = ?, PreHeightConfigPL = ?, PreHeightConfigMS = ?, "
    "HeightConfigPL = ?, HeightCOnfigMS = ?, TestingDone = ?, "

    "NoOfWires = ?, JSONWire = ? "
    "WHERE ID = ?",                                  /*25 Update One Record to Splice Table*/

    "UPDATE Part SET PartName = ?, CreatedDate = ?, OperatorID = ?, "
    "ProcessMode = ?, TotalWorkstation = ?, MaxSplicesPerWorkstation = ?, "
    "Rows = ?, Columns = ?, MaxSplicesPerZone = ?, NoOfSplice = ?, JSONSplice = ? "
    "WHERE ID = ?",                                  /*26 Update One Record to Part Table*/

    "UPDATE WorkOrder SET WorkOrderName = ?, CreatedDate = ?, OperatorID = ?, "
    "NoOfPart = ?, Quantity = ?, CurrentPartCount = ?, "
    "CurrentSpliceID = ?, CurrentSpliceName = ?, WorkOrderDone = ?, "
    "JSONPartIndex = ?, JSONMissSpliceList = ?"
    "WHERE ID = ?",                                  /*27 Update One Record to WorkOrder Table*/

};


#endif // SQLSENTENCE_H
