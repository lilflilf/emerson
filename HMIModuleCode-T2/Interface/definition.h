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

//Wire Structure
enum MetalType{
    Copper,
    Aluminum,
};

enum HorizontalLocation{
    Left,
    Right
};

enum VerticalLocation{
    Basic,
    Advance,
};

enum VerticalPosition{
    Top,
    Middle,
    Bottom,
};

enum StripeType{
    Horizontal,
    Slash,
    OneVertical,
    TwoVertical,
};

struct STRIPE
{
    enum StripeType TypeOfStripe;
    QString Color;
};

//Splice Structure
struct Qual
{
   int Plus;
   int Minus;
};

enum WELDMODE
{
    ENERGY,
    TIME,
    HEIGHT,
    ENERGYWITHHEIGHT,
};

enum STEPWELDMODE
{
    STEPENERGY,
    STEPTIME,
    STEPPOWER,
    STEPDISABLE,
};

struct STEPWELD
{
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
    int ShrinkTubeID;     //Raychem tube index (0 for None,1,2,3,3A,Other)
    int ShrinkTime;           //Secs * 10
    int ShrinkTemperature;    //In Centigrade degrees

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

struct ADVANCESETTING
{
    enum WELDMODE WeldMode;   //Used for Weld Mode 0:energy,1:height,2:time
    struct STEPWELD StepWeld;

    int PreBurst;             //Secs * 1000
    int HoldTime;             //Secs * 100
    int SqzTime;              //Secs * 100
    //For splice ABDelay always is zero
    int ABDelay;              //Secs * 100
    int ABDur;                //Secs * 100

    bool CutOff;           //CutterOption
    int CutOffSpliceTime;
    bool AntiSide;
    int AntiSideSpliceTime;

    int MeasuredWidth;
    int MeasuredHeight;

    struct SHRINKTUBE ShrinkTube;
};

enum TEACH_MODE_TYPE
{
    STANDARD,
    AUTO,
    SIGMA,
    UNDEFINED,
};

enum TESTMODE
{
    UNCONSTRAINED,
    CONSTRAINED,
    TEACHMODE,
};

// Quality Range Variables Created (set), defined under InitializeData
enum QUAL_RANGE_MARKER{
    TIME_PLRG = 0,
    TIME_MSRG,
    POWER_PLRG,
    POWER_MSRG,
    PRE_HGT_PLRG,
    PRE_HGT_MSRG,
    HEIGHT_PLRG,
    HEIGHT_MSRG,
    FORCE_PLRG,
    FORCE_MSRG,
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

struct TEACHMODESETTING
{
    enum TEACH_MODE_TYPE TeachModeType;
    //TeachModeAdvanceSetting
    int TeachModequal_Window[ENERGY_ADJ];
};

struct TESTSETTING
{
    int Qutanty;             //Accummulated total
    int StopCount;
    enum TESTMODE TestMode;
    struct TEACHMODESETTING TeachModeSetting;
    bool TestingDone;
};

struct WELDSETTING
{
    struct BASICWELDSETTING BasicSetting;
    struct QUALITYWINDONSETTING QualitySetting;
    struct ADVANCESETTING AdvanceSetting;
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

struct PARTTYPE
{
    enum PROCESSMODE ProcessMode;
    struct WORKSTATIONS WorkStations;
    struct BOARDLAYOUT BoardLayout;
};

struct PARTATTRIBUTE
{
    QString SpliceName;
    int CurrentWorkstation;
    int CurrentBoardLayoutZone;

};

//Work Order Structure
struct SpliceIndex
{
    int SpliceID;
    QString SpliceName;
    unsigned int SpliceHash;
};

enum PASSWORDCONTROL
{
    SUPERUSER,
    ADMINISTRATOR,
    TECHNICIAN,
    QUALITYCONTROL,
    OPEN,
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
    E_STOP,
};

class AlarmElement
{
public:
    int RevCode;
    int AlarmID;
    QString AlarmMsg;
    unsigned int CreatedDate;
    enum ALARMTYPE AlarmType;
    int WeldResultID;
    int OperatorID;
public:
    AlarmElement()
    {
        RevCode = -1;
        AlarmID = -1;
        AlarmMsg.clear();
        CreatedDate = 0;
        AlarmType = NONEALARM;
        WeldResultID = -1;
        OperatorID = -1;
    }
    ~AlarmElement(){}
    AlarmElement operator=(const AlarmElement &AlarmObject) const
    {
        AlarmElement Obj;
        Obj.RevCode = AlarmObject.RevCode;
        Obj.AlarmID = AlarmObject.AlarmID;
        Obj.AlarmMsg = AlarmObject.AlarmMsg;
        Obj.CreatedDate = AlarmObject.CreatedDate;
        Obj.AlarmType = AlarmObject.AlarmType;
        Obj.WeldResultID = AlarmObject.WeldResultID;
        Obj.OperatorID = AlarmObject.OperatorID;
        return Obj;
    }

};

struct WorkOrderIndex
{
    int WorkOrderID;
    QString WorkOrderName;
};

struct PartIndex
{
    int PartID;
    QString PartName;
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

enum SAMPLERATIO
{
    SampleWith1ms,
    SampleWith5ms,
    SampleWith10ms,
    SampleWith20ms,
};

class WeldResultElement
{
public:
    int RevCode;
    int WeldResultID;
    QString TableName;
    QString OperatorName;
    unsigned int CreatedDate;
    struct WorkOrderIndex CurrentWorkOrder;
    struct PartIndex CurrentPart;
    struct SpliceIndex CurrentSplice;
    int WeldCount;//just for the test mode
    int PartCount;//just for the operate mode
    int CrossSection;
    struct WELDRESULT ActualResult;
    enum SAMPLERATIO SampleRatio;
    int NoOfSamples;
    QMap<int, QString> PowerGraph;
    QMap<int, QString> PostHeightGraph;
public:
    WeldResultElement()
    {
        RevCode = -1;
        WeldResultID = -1;
        TableName.clear();
        OperatorName.clear();
        CreatedDate = 0;
        CurrentWorkOrder.WorkOrderID = -1;
        CurrentWorkOrder.WorkOrderName.clear();
        CurrentPart.PartID = -1;
        CurrentPart.PartName.clear();
        CurrentSplice.SpliceID = -1;
        CurrentSplice.SpliceName.clear();
        WeldCount = -1;
        PartCount = -1;
        ActualResult.ActualAlarmflags = -1;
        ActualResult.ActualAmplitude = -1;
        ActualResult.ActualAmplitude2 = -1;
        ActualResult.ActualEnergy = -1;
        ActualResult.ActualPeakPower = -1;
        ActualResult.ActualPostheight = -1;
        ActualResult.ActualPreheight = -1;
        ActualResult.ActualPressure = -1;
        ActualResult.ActualTime = -1;
        ActualResult.ActualTPressure = -1;
        ActualResult.ActualWidth = -1;
        SampleRatio = SampleWith1ms;
        PowerGraph.clear();
        PostHeightGraph.clear();
        NoOfSamples = PowerGraph.size();
    }
    ~WeldResultElement()
    {
        PowerGraph.clear();
        PostHeightGraph.clear();
    }
    WeldResultElement operator=(const WeldResultElement &WeldResultObject) const
    {
        WeldResultElement Obj;
        Obj.RevCode = WeldResultObject.RevCode;
        Obj.WeldResultID = WeldResultObject.WeldResultID;
        Obj.OperatorName = WeldResultObject.OperatorName;
        Obj.CreatedDate = WeldResultObject.CreatedDate;
        Obj.CurrentWorkOrder.WorkOrderID = WeldResultObject.CurrentWorkOrder.WorkOrderID;
        Obj.CurrentWorkOrder.WorkOrderName
                = WeldResultObject.CurrentWorkOrder.WorkOrderName;
        Obj.CurrentPart.PartID = WeldResultObject.CurrentPart.PartID;
        Obj.CurrentPart.PartName = WeldResultObject.CurrentPart.PartName;
        Obj.CurrentSplice.SpliceID = WeldResultObject.CurrentSplice.SpliceID;
        Obj.CurrentSplice.SpliceName = WeldResultObject.CurrentSplice.SpliceName;
        Obj.WeldCount = WeldResultObject.WeldCount;
        Obj.PartCount = WeldResultObject.PartCount;
        Obj.ActualResult.ActualAlarmflags
                = WeldResultObject.ActualResult.ActualAlarmflags;
        Obj.ActualResult.ActualAmplitude = WeldResultObject.ActualResult.ActualAmplitude;
        Obj.ActualResult.ActualAmplitude2 = WeldResultObject.ActualResult.ActualAmplitude2;
        Obj.ActualResult.ActualEnergy = WeldResultObject.ActualResult.ActualEnergy;
        Obj.ActualResult.ActualPeakPower = WeldResultObject.ActualResult.ActualPeakPower;
        Obj.ActualResult.ActualPostheight = WeldResultObject.ActualResult.ActualPostheight;
        Obj.ActualResult.ActualPreheight = WeldResultObject.ActualResult.ActualPreheight;
        Obj.ActualResult.ActualPressure = WeldResultObject.ActualResult.ActualPressure;
        Obj.ActualResult.ActualTime = WeldResultObject.ActualResult.ActualTime;
        Obj.ActualResult.ActualTPressure = WeldResultObject.ActualResult.ActualTPressure;
        Obj.ActualResult.ActualWidth = WeldResultObject.ActualResult.ActualWidth;
        Obj.SampleRatio = WeldResultObject.SampleRatio;

        QMap<int, QString>::const_iterator i = WeldResultObject.PowerGraph.constBegin();
        while(i != WeldResultObject.PowerGraph.constEnd())
        {
            Obj.PowerGraph.insert(i.key(),i.value());
            ++i;
        }
        i = WeldResultObject.PostHeightGraph.constBegin();
        while(i != WeldResultObject.PostHeightGraph.constEnd())
        {
            Obj.PostHeightGraph.insert(i.key(),i.value());
            ++i;
        }
        Obj.NoOfSamples = PowerGraph.size();
        return Obj;
    }
};

#endif // DEFINITION_H
