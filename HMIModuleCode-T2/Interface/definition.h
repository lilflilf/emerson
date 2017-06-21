#ifndef DEFINITION_H
#define DEFINITION_H
#include <QString>
#include <QMap>
#include <QHash>

struct BRANSONDATA
{
    QString Maximum;
    QString Minimum;
    QString Current;
};

struct VersionList{
    QString SoftwareVersion;
    QString ControllerVersion;
    QString ActuatorVersion;
};

class STRIPE
{
public:
    enum StripeType{
        Horizontal,
        Slash,
        Vertical,
        None,
    };
    enum StripeType TypeOfStripe;
    QString Color;
};

//Splice Structure
struct Qual
{
   int Plus;
   int Minus;
};

struct STEPWELD
{
public:
    enum STEPWELDMODE
    {
        STEPENERGY,
        STEPTIME,
        STEPPOWER,
        STEPDISABLE,
    };
    enum STEPWELDMODE StepWeldMode;
    int EnergyToStep;         //
    int TimeToStep;           //
    int PowerToStep;          //
    int Amplitude2;           //If the step weld is disabled, the Amplitude2 is always 0
};

struct SHRINKTUBE
{
    //Added 30 June 2000 to accommodate the Raychem tube shrinker data
    bool ShrinkOption;
    QString ShrinkTubeID;     //Raychem tube index (0 for None,1,2,3,3A,Other)
    int ShrinkTime;           //Secs * 10
    int ShrinkTemperature;    //In Centigrade degrees
    bool ShrinkMutex;         // Insulution Mutex lock

};

struct BASICWELDSETTING
{
    int Energy;               //Energy in joules
    int Amplitude;            //Amplitude in microns

    int Width;                //Width in mm/100
    int Pressure;             //Pressure in PSI
    int TrigPres;             //PSI * 10
};

struct QUALITYWINDONSETTING
{
    Qual Time;                //Time limits in seconds/100
    Qual Power;               //Power limits in percent
    Qual Preheight;           //Pre weld height limits in mm/100
    Qual Height;              //Post weld height limits in mm/100
    Qual Force;               //Force limits in Newtons
};

class Cutter
{
public:
    bool CutOff;           //CutterOption
    int CutOffSpliceTime;
    bool Cutter4TimeAlarm;
    bool Cutter4PowerAlarm;
    bool Cutter4PreHeightAlarm;
    bool Cutter4HeightAlarm;
};

struct AntiSide
{
    bool AntiSideMode;
    int AntiSideSpliceTime;
};

struct Offset
{
    int DisplayWidth;
    int MeasuredWidth;
    int DisplayHeight;
    int MeasuredHeight;
};

class ADVANCESETTING
{
public:
    enum WELDMODE
    {
        ENERGY,
        TIME,
        HEIGHT,
        ENERGYWITHHEIGHT,
    };
    WELDMODE WeldMode;   //Used for Weld Mode 0:energy,1:height,2:time
    STEPWELD StepWeld;

    int PreBurst;             //Secs * 1000
    int HoldTime;             //Secs * 100
    int SqzTime;              //Secs * 100
    //For splice ABDelay always is zero
    int ABDelay;              //Secs * 100
    int ABDur;                //Secs * 100

    Cutter CutOffOption;
    AntiSide AntiSideOption;
    Offset OffsetOption;

    SHRINKTUBE ShrinkTube;
};



// Quality Range Variables Created (set), defined under InitializeData
enum QUAL_RANGE_MARKER{
    TIME_PLRG_STD = 0,
    TIME_MSRG_STD,
    POWER_PLRG_STD,
    POWER_MSRG_STD,
    PRE_HGT_PLRG_STD,
    PRE_HGT_MSRG_STD,
    HEIGHT_PLRG_STD,
    HEIGHT_MSRG_STD,
    FORCE_PLRG_STD,
    FORCE_MSRG_STD,

    TIME_PLRG_AUTO,
    TIME_MSRG_AUTO,
    POWER_PLRG_AUTO,
    POWER_MSRG_AUTO,
    PRE_HGT_PLRG_AUTO,
    PRE_HGT_MSRG_AUTO,
    HEIGHT_PLRG_AUTO,
    HEIGHT_MSRG_AUTO,
    FORCE_PLRG_AUTO,
    FORCE_MSRG_AUTO,

    TIME_CONFRG_PL,
    POWER_CONFRG_PL,
    PRE_HGT_CONFRG_PL,
    HEIGHT_CONFRG_PL,
    TIME_CONFRG_MS,
    POWER_CONFRG_MS,
    PRE_HGT_CONFRG_MS,
    HEIGHT_CONFRG_MS,
    ENERGY_ADJ,
    PRESSURE_ADJ,
    AMPLITUDE_ADJ,
    WIDTH_ADJ,
    QUAL_RANGES
};

class TEACHMODESETTING
{
public:
    enum TEACH_MODE_TYPE
    {
        STANDARD,
        AUTO,
        SIGMA,
        UNDEFINED,
    };
    enum TEACH_MODE_TYPE TeachModeType;
    int TeachModequal_Window[ENERGY_ADJ];
    int StandardRunQuantity;
    int AutoRunQuantity;
    int SigmaRunQuantity;
};

class TESTSETTING
{
public:
    enum TESTMODE
    {
        UNCONSTRAINED,
        CONSTRAINED,
    };
    int BatchSize;             //Accummulated total
    int StopCount;
    TESTMODE TestMode;
    TEACHMODESETTING TeachModeSetting;
    bool TestingDone;
};

struct WELDSETTING
{
    struct BASICWELDSETTING BasicSetting;
    struct QUALITYWINDONSETTING QualitySetting;
    ADVANCESETTING AdvanceSetting;
};

//Part Structure
enum PROCESSMODE
{
    BASIC,
    ADVANCE,
};

struct WORKSTATIONS
{
    int TotalWorkstation;
    int MaxSplicesPerWorkstation;
};

struct BOARDLAYOUT
{
    int Rows;
    int Columns;
    int MaxSplicesPerZone;
};

struct HARNESSTYPE
{
    enum PROCESSMODE ProcessMode;
    struct WORKSTATIONS WorkStations;
    struct BOARDLAYOUT BoardLayout;
};

struct HARNESSATTRIBUTE
{
    int SpliceID;
    QString SpliceName;
    int CurrentWorkstation;
    int CurrentBoardLayoutZone;

};

struct SEQUENCEATTRIBUTE
{
    int SpliceID;
    QString SpliceName;
    int Quantity;
};

//Work Order Structure
struct PartIndex
{
    int PartID;
    QString PartName;
    unsigned int PartHash;
};

enum ALARMTYPE
{
    NONEALARM = -1,
    TIMEALARM,
    PEAKPOWERALARM,
    PREHEIGHTALARM,
    HEIGHTALARM,
    OVERLOADALARM,
    MOTORERROR,
    HEIGHTENCODERERROR,
    SAFETYERROR,
    VOL24ERROR,
    CUTERROR,
    IDCHIPERROR,
    RAMERROR,
    E_STOP,
    HORN80PERCENTCOUNTALARM,
    ANVIL80PERCENTCOUNTALARM,
    GATHER80PERCENTCOUNTALARM,
    GUIDE80PERCENTCOUNTALARM,
    HORN80PERCENTENERGYALARM,
    ANVIL80PERCENTENERGYALARM,
    GATHER80PERCENTENERGYALARM,
    GUIDE80PERCENTENERGYALARM,

    HORN100PERCENTCOUNTALARM,
    ANVIL100PERCENTCOUNTALARM,
    GATHER100PERCENTCOUNTALARM,
    GUIDE100PERCENTCOUNTALARM,
    HORN100PERCENTENERGYALARM,
    ANVIL100PERCENTENERGYALARM,
    GATHER100PERCENTENERGYALARM,
    GUIDE100PERCENTENERGYALARM,

};

struct WorkOrderIndex
{
    int WorkOrderID;
    QString WorkOrderName;
};

struct HarnessIndex
{
    int HarnessID;
    QString HarnessName;
};

struct SequenceIndex
{
    int SequenceID;
    QString SequenceName;
};

struct WELDRESULT
{
    int ActualEnergy;
    int ActualTPressure;
    int ActualPressure;
    int ActualAmplitude;
    int ActualAmplitude2;
    int ActualWidth;
    int ActualTime;
    int ActualPeakPower;
    int ActualPreheight;
    int ActualPostheight;
    unsigned int ActualAlarmflags;
};

enum QUALITYTYPE
{
    QUALITYTIME,
    QUALITYPOWER,
    QUALITYPREHEIGHT,
    QUALITYPOSTHEIGHT,
};

#endif // DEFINITION_H
