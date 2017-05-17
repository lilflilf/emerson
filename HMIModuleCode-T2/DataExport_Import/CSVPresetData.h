#ifndef CSVPRESETDATA_H
#define CSVPRESETDATA_H
#include "DataClass.h"

class CSVPresetData //: public DataClass
{
public:
    enum PresetItem{
        SpliceID = 0, SpliceName = 1, CreatedDate = 2,
        OperatorID = 3, CrossSection = 4, PresetPicPath = 5,
        Verified = 6,                  /* 7 items */
        /*WeldSetting*/                /* 5 items */
        Energy = 7, Amplitude = 8, Width = 9, Pressure = 10, TrigPres = 11,
        /*QualityWindowSetting*/       /* 10 items */
        TimePlus = 12, TimeMinus = 13, PowerPlus = 14, PowerMinus = 15,
        PreheightPlus = 16, PreheightMinus = 17, HeightPlus = 18, HeightMinus = 19,
        ForcePlus = 20, ForceMinus = 21,
        /*AdvanceSetting*/             /* 23 items */
        WeldMode = 22, StepWeldMode = 23, EnergyToStep = 24, TimeToStep = 25,
        PowerToStep = 26, Amplitude2 = 27, PreBurst = 28, HoldTime = 29,
        SqueezeTime = 30, AfterBurstDelay = 31, AfterBurstDuring = 32,
        CutOff = 33, CutOffSpliceTime = 34, CutOffHeightAlarm = 35,
        CutOffPowerAlarm = 36, CutOffPreHeightAlarm = 37, CutOffTimeAlarm = 38,
        AntiSide = 39, AntiSideSpliceTime = 40, MeasuredWidth = 41,
        MeasuredHeight = 42, DisplayWidth = 43, DisplayHeight = 44,
        /*Shrink Tube Setting*/        /*5 items */
        ShrinkOption = 45, ShrinkTubeID = 46, ShrinkTime = 47,
        ShrinkTemperature = 48, ShrinkMutex = 49,
        HashCode = 50,                 /*1 items */
        /*Testing*/                    /* 36 items */
        BatchSize = 51, StopCount = 52, TestMode = 53, TEACHMODETYPE = 54,
        TimePLRG_STD = 55, TimeMSRG_STD = 56, PowerPLRG_STD = 57,
        PowerMSRG_STD = 58, PreHeightPLRG_STD = 59, PreHeightMSRG_STD = 60,
        HeightPLRG_STD = 61, HeightMSRG_STD = 62, ForcePLRG_STD = 63,
        ForceMSRG_STD = 64,

        TimePLRG_AUTO = 65, TimeMSRG_AUTO = 66, PowerPLRG_AUTO = 67,
        PowerMSRG_AUTO = 68, PreHeightPLRG_AUTO = 69, PreHeightMSRG_AUTO = 70,
        HeightPLRG_AUTO = 71, HeightMSRG_AUTO = 72, ForcePLRG_AUTO = 73,
        ForceMSRG_AUTO = 74,

        TimeConfigPL = 75, TimeConfigMS = 76, PowerConfigPL = 77,
        PowerConfigMS = 78, PreHeightConfigPL = 79, PreHeightConfigMS = 80,
        HeightConfigPL = 81, HeightConfigMS = 82, StandardQuantity = 83,
        AutoQuantity = 84, SigmaQuantity = 85, TestingDone = 86,

        NoOfWires = 87,
        /*JSON Structure WireID, WireName*/
        JSONWire = 88,                /*2 items */
        PresetEnd = 89
    };
public:
    virtual bool ExportData(int ID, QString fileUrl);
    virtual QString GetExportString(int ID);
//    virtual int ImportData(QString StrValue);
    virtual int ImportData(QString StrValue, QMap<int, QString> WireIDMap);
public:
    static CSVPresetData* Instance();
protected:
    CSVPresetData();
private:
    static CSVPresetData* _instance;
public:
    ~CSVPresetData();
};

#endif // CSVDATACLASS_H
