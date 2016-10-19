#ifndef SQLSENTENCE_H
#define SQLSENTENCE_H
#include <QString>
enum{
    CREATEWIRETABLE,
    CREATESPLICETABLE,
    INSERTWIRETABLE,
};

QString SQLSentence[] = {
    "CREATE TABLE Wire ("
    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
    "WireName VARCHAR,"
    "CreatedDate VARCHAR,"
    "OperatorID VARCHAR,"
    "Color VARCHAR,"
    "StripeTye INT,"
    "StripeColor VARCHAR,"
    "Gauge INT,"
    "MetalType INT,"
    "HorizontalLocation INT,"
    "VerticalLocation INT,"
    "VerticalPosition INT)",

    "CREATE TABLE Preset ("               /*2 Create Preset Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
    "SpliceName VARCHAR,"
    "CreatedDate VARCHAR,"
    "OperatorID VARCHAR,"
    "CrossSection INT,"
    "PresetPicPath VARCHAR,"
    "Verified BOOLEAN,"

    /*WeldSetting*/
    "Energy INT,"
    "Amplitude INT,"
    "Width INT,"
    "Pressure INT,"
    "TrigPres INT,"

    /*QualityWindowSetting*/
    "TimePlus INT,"
    "TimeMinus INT,"
    "PowerPlus INT,"
    "PowerMinus INT,"
    "PreheightPlus INT,"
    "PreheightMinus INT,"
    "HeightPlus INT,"
    "HeightMinus INT,"
    "ForcePlus INT,"
    "ForceMinus INT,"

    /*AdvanceSetting*/
    "WeldMode INT,"
    "StepWeld INT,"
    "EnergyToStep INT,"
    "TimeToStep INT,"
    "PowerToStep INT,"
    "Amplitude2 INT,"
    "PreBurst INT,"
    "HoldTime INT,"
    "SqueezeTime INT,"
    "AfterBurstDelay INT,"
    "AfterBurstDuring INT,"
    "CutOff BOOLEAN,"
    "AntiSide BOOLEAN,"
    "MeasuredWidth INT,"
    "MeasuredHeight INT,"

    /*Shrink Tube Setting*/
    "ShrinkOption BOOLEAN,"
    "ShrinkTubeID INT,"
    "ShrinkTime INT,"
    "ShrinkTemperature INT,"

    /*Testing*/
    "Qutanty INT,"
    "StopCount INT,"
    "TestMode INT,"
    "TEACHMODETYPE ENUM,"
    "TimePLRG INT,"
    "TimeMSRG INT,"
    "PowerPLRG INT,"
    "PowerMSRG INT,"
    "PreHeightPLRG INT,"
    "PreHeightMSRG INT,"
    "HeightPLRG INT,"
    "HeightMSRG INT,"
    "ForcePLRG INT,"
    "ForceMSRG INT,"
    "TimeConfigPL INT,"
    "TimeConfigMS INT,"
    "PowerConfigPL INT,"
    "PowerConfigMS INT,"
    "PreHeightConfigPL INT,"
    "PreHeightConfigMS INT,"
    "HeightConfigPL INT,"
    "HeightCOnfigMS INT,"
    "TestingDone BOOLEAN,"

    "NoOfWires INT,"
    /*JSON Structure WireID, WireName*/
    "JSONWire VARCHAR)",

    "INSERT INTO Wire VALUES ("                  /*3 Insert Wire Table*/
    "'JerryWang',"
    "'20161019',"
    "'JW',"
    "'GREEN',"
    "0,"
    "'YELLOW',"
    "50,"
    "0,"
    "0,"
    "1,"
    "1)",


};


#endif // SQLSENTENCE_H
