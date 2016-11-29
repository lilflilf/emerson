#ifndef DEFINITION_H
#define DEFINITION_H
#include <QString>
#include <QMap>

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

struct WireElement
{
    QString WireName;
    int     WireID;
    unsigned int CreatedDate;
    int OperatorID;

    QString Color;
    struct STRIPE Stripe;
    int Gauge;
    enum MetalType TypeOfWire;
    enum HorizontalLocation Side;
    enum VerticalLocation VerticalSide;
    enum VerticalPosition Position;
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

struct WELDSETTING
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
    bool AntiSide;

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

class PresetElement
{
public:
    int RevCode;              //Amtech Revision Code for possible future use
    int SpliceID;
    QString SpliceName;       //Customer's Part Number
    unsigned int CreatedDate; //Date of last rev, seconds from Jan 1, 1980
    int OperatorID;

    int CrossSection;         //Area of part in mm*mm/100
    QString PresetPicNamePath;
    bool Verified;

    struct WELDSETTING WeldSetting;
    struct QUALITYWINDONSETTING QualitySetting;
    struct ADVANCESETTING AdvanceSetting;

    int NoOfWires;            //Number of wires in this splice
    /*WireEl(1 To MAX_WIRE_ELEMENTS) As WireElement*/
    QMap<int,QString> WireIndex;   //Store data for individual wires

    struct TESTSETTING TestSetting;
public:
    PresetElement()
    {
        RevCode = -1;
        SpliceID = -1;
        SpliceName.clear();
        CreatedDate = 0;
        OperatorID = -1;

        CrossSection = -1;
        PresetPicNamePath.clear();
        Verified = false;

        WeldSetting.Energy = -1;
        WeldSetting.Amplitude = -1;
        WeldSetting.Pressure = -1;
        WeldSetting.TrigPres = -1;
        WeldSetting.Width = -1;
        QualitySetting.Time.Minus = 0;
        QualitySetting.Time.Plus = 1000;               //Seconds * 200
        QualitySetting.Power.Minus = 0;
        QualitySetting.Power.Plus = 4800;
        QualitySetting.Preheight.Minus = 0;
        QualitySetting.Preheight.Plus = 1500;               //mm * 100
        QualitySetting.Height.Minus = 0;
        QualitySetting.Height.Plus = 1500;
        AdvanceSetting.ABDelay = 0;
        AdvanceSetting.ABDur = 0;
        AdvanceSetting.AntiSide = false;
        AdvanceSetting.CutOff = false;
        AdvanceSetting.HoldTime = 0;
        AdvanceSetting.MeasuredHeight = 0;
        AdvanceSetting.MeasuredWidth = 0;
        AdvanceSetting.PreBurst = 0;
        AdvanceSetting.SqzTime = 0;
        AdvanceSetting.WeldMode = ENERGY;
        AdvanceSetting.StepWeld.StepWeldMode = STEPDISABLE;
        AdvanceSetting.StepWeld.Amplitude2 = -1;
        AdvanceSetting.StepWeld.EnergyToStep = -1;
        AdvanceSetting.StepWeld.PowerToStep = -1;
        AdvanceSetting.StepWeld.TimeToStep = -1;
        AdvanceSetting.ShrinkTube.ShrinkOption = false;
        AdvanceSetting.ShrinkTube.ShrinkTemperature = -1;
        AdvanceSetting.ShrinkTube.ShrinkTime = -1;
        AdvanceSetting.ShrinkTube.ShrinkTubeID = -1;
        WireIndex.clear();
        NoOfWires = WireIndex.size();
        TestSetting.Qutanty = -1;
        TestSetting.StopCount = -1;
        TestSetting.TestMode = UNCONSTRAINED;
        TestSetting.TeachModeSetting.TeachModeType = STANDARD;
        TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG] = 40;
        TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG] = 40;
        TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG] = 25;
        TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG] = 25;
        TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG] = 15;
        TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG] = 15;
        TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG] = 10;
        TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG] = 10;
        TestSetting.TeachModeSetting.TeachModequal_Window[FORCE_PLRG] = 5;
        TestSetting.TeachModeSetting.TeachModequal_Window[FORCE_MSRG] = 10;
        for (int i = TIME_CONFRG_PL; i<= HEIGHT_CONFRG_MS; i++)
        {
            TestSetting.TeachModeSetting.TeachModequal_Window[i] = 4;
        }
        TestSetting.TestingDone = false;
    }
    ~PresetElement()
    {
        WireIndex.clear();
        NoOfWires = WireIndex.size();
    }
    PresetElement operator=(const PresetElement &PresetObject) const
    {
        PresetElement Obj;
        Obj.RevCode = PresetObject.RevCode;
        Obj.SpliceID = PresetObject.SpliceID;
        Obj.SpliceName = PresetObject.SpliceName;
        Obj.CreatedDate = PresetObject.CreatedDate;
        Obj.OperatorID = PresetObject.OperatorID;

        Obj.CrossSection = PresetObject.CrossSection;
        Obj.PresetPicNamePath = PresetObject.PresetPicNamePath;
        Obj.Verified = PresetObject.Verified;

        Obj.WeldSetting.Energy = PresetObject.WeldSetting.Energy;
        Obj.WeldSetting.Amplitude = PresetObject.WeldSetting.Amplitude;
        Obj.WeldSetting.Pressure = PresetObject.WeldSetting.Pressure;
        Obj.WeldSetting.TrigPres = PresetObject.WeldSetting.TrigPres;
        Obj.WeldSetting.Width = PresetObject.WeldSetting.Width;
        Obj.QualitySetting.Time.Minus = PresetObject.QualitySetting.Time.Minus;
        Obj.QualitySetting.Time.Plus = PresetObject.QualitySetting.Time.Plus;
        Obj.QualitySetting.Power.Minus = PresetObject.QualitySetting.Power.Minus;
        Obj.QualitySetting.Power.Plus = PresetObject.QualitySetting.Power.Plus;
        Obj.QualitySetting.Preheight.Minus = PresetObject.QualitySetting.Preheight.Minus;
        Obj.QualitySetting.Preheight.Plus = PresetObject.QualitySetting.Preheight.Plus;
        Obj.QualitySetting.Height.Minus = PresetObject.QualitySetting.Height.Minus;
        Obj.QualitySetting.Height.Plus = PresetObject.QualitySetting.Height.Plus;
        Obj.AdvanceSetting.ABDelay = PresetObject.AdvanceSetting.ABDelay;
        Obj.AdvanceSetting.ABDur = PresetObject.AdvanceSetting.ABDur;
        Obj.AdvanceSetting.AntiSide = PresetObject.AdvanceSetting.AntiSide;
        Obj.AdvanceSetting.CutOff = PresetObject.AdvanceSetting.CutOff;
        Obj.AdvanceSetting.HoldTime = PresetObject.AdvanceSetting.HoldTime;
        Obj.AdvanceSetting.MeasuredHeight = PresetObject.AdvanceSetting.MeasuredHeight;
        Obj.AdvanceSetting.MeasuredWidth = PresetObject.AdvanceSetting.MeasuredWidth;
        Obj.AdvanceSetting.PreBurst = PresetObject.AdvanceSetting.PreBurst;
        Obj.AdvanceSetting.SqzTime = PresetObject.AdvanceSetting.SqzTime;
        Obj.AdvanceSetting.WeldMode = PresetObject.AdvanceSetting.WeldMode;
        Obj.AdvanceSetting.StepWeld.StepWeldMode
                = PresetObject.AdvanceSetting.StepWeld.StepWeldMode;
        Obj.AdvanceSetting.StepWeld.Amplitude2
                = PresetObject.AdvanceSetting.StepWeld.Amplitude2;
        Obj.AdvanceSetting.StepWeld.EnergyToStep
                = PresetObject.AdvanceSetting.StepWeld.EnergyToStep;
        Obj.AdvanceSetting.StepWeld.PowerToStep
                = PresetObject.AdvanceSetting.StepWeld.PowerToStep;
        Obj.AdvanceSetting.StepWeld.TimeToStep
                = PresetObject.AdvanceSetting.StepWeld.TimeToStep;
        Obj.AdvanceSetting.ShrinkTube.ShrinkOption
                = PresetObject.AdvanceSetting.ShrinkTube.ShrinkOption;
        Obj.AdvanceSetting.ShrinkTube.ShrinkTemperature
                = PresetObject.AdvanceSetting.ShrinkTube.ShrinkTemperature;
        Obj.AdvanceSetting.ShrinkTube.ShrinkTime
                = PresetObject.AdvanceSetting.ShrinkTube.ShrinkTime;
        Obj.AdvanceSetting.ShrinkTube.ShrinkTubeID
                = PresetObject.AdvanceSetting.ShrinkTube.ShrinkTubeID;
        QMap<int,QString>::const_iterator i
                = PresetObject.WireIndex.constBegin();
        while(i != PresetObject.WireIndex.constEnd())
        {
            Obj.WireIndex.insert(i.key(),i.value());
            ++i;
        }
        Obj.NoOfWires = Obj.WireIndex.size();
        Obj.TestSetting.Qutanty = PresetObject.TestSetting.Qutanty;
        Obj.TestSetting.StopCount = PresetObject.TestSetting.StopCount;
        Obj.TestSetting.TestMode = PresetObject.TestSetting.TestMode;
        Obj.TestSetting.TeachModeSetting.TeachModeType
                = PresetObject.TestSetting.TeachModeSetting.TeachModeType;
        for (int i = TIME_PLRG; i<= HEIGHT_CONFRG_MS; i++)
        {
            Obj.TestSetting.TeachModeSetting.TeachModequal_Window[i]
                    = PresetObject.TestSetting.TeachModeSetting.TeachModequal_Window[i];
        }
        Obj.TestSetting.TestingDone = PresetObject.TestSetting.TestingDone;
        return Obj;
    }

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

class PartElement
{
public:
    int RevCode;
    int PartID;
    QString PartName;
    unsigned int CreatedDate;
    int OperatorID;
    struct PARTTYPE PartTypeSetting;

    int NoOfSplice;
    //#define SEQ_MAX_SPLICES  250
    QMap<int, struct PARTATTRIBUTE> SpliceIndex;
public:
    PartElement()
    {
        RevCode = -1;
        PartID = -1;
        PartName.clear();
        CreatedDate = 0;
        OperatorID = -1;
        PartTypeSetting.BoardLayout.Columns = -1;
        PartTypeSetting.BoardLayout.Rows = -1;
        PartTypeSetting.BoardLayout.MaxSplicesPerZone = -1;
        PartTypeSetting.ProcessMode = BASIC;
        PartTypeSetting.WorkStations.MaxSplicesPerWorkstation = -1;
        PartTypeSetting.WorkStations.TotalWorkstation = -1;
        SpliceIndex.clear();
        NoOfSplice = SpliceIndex.size();
    }
    ~PartElement()
    {
        SpliceIndex.clear();
    }
    PartElement operator=(const PartElement &PartObject) const
    {
        PartElement Obj;
        Obj.RevCode = PartObject.RevCode;
        Obj.PartID = PartObject.PartID;
        Obj.PartName = PartObject.PartName;
        Obj.CreatedDate = PartObject.CreatedDate;
        Obj.OperatorID = PartObject.OperatorID;
        Obj.PartTypeSetting.BoardLayout.Columns =
                PartObject.PartTypeSetting.BoardLayout.Columns;
        Obj.PartTypeSetting.BoardLayout.Rows =
                PartObject.PartTypeSetting.BoardLayout.Rows;
        Obj.PartTypeSetting.BoardLayout.MaxSplicesPerZone
                = PartObject.PartTypeSetting.BoardLayout.MaxSplicesPerZone;
        Obj.PartTypeSetting.ProcessMode = PartObject.PartTypeSetting.ProcessMode;
        Obj.PartTypeSetting.WorkStations.MaxSplicesPerWorkstation
                = PartObject.PartTypeSetting.WorkStations.MaxSplicesPerWorkstation;
        Obj.PartTypeSetting.WorkStations.TotalWorkstation
                = PartObject.PartTypeSetting.WorkStations.TotalWorkstation;
        QMap<int, struct PARTATTRIBUTE>::const_iterator i
                = PartObject.SpliceIndex.constBegin();
        while(i != PartObject.SpliceIndex.constEnd())
        {
            Obj.SpliceIndex.insert(i.key(),i.value());
            ++i;
        }
        Obj.NoOfSplice = Obj.SpliceIndex.size();
        return Obj;
    }

};

//Work Order Structure
struct SpliceIndex
{
    int SpliceID;
    QString SpliceName;
};

class WorkOrderElement
{
public:
    int RevCode;
    int WorkOrderID;
    QString WorkOrderName;
    unsigned int CreatedDate;
    int OperatorID;
    int NoOfPart;
    QMap<int, QString> PartIndex;

    int Quantity;
    int CurrentPartCount;
    QMap<int, QString> MissSpliceList;
    struct SpliceIndex CurrentSplice;
    bool WorkOrderDone;
public:
    WorkOrderElement()
    {
        RevCode = -1;
        WorkOrderID = -1;
        WorkOrderName.clear();
        CreatedDate = 0;
        OperatorID = -1;
        PartIndex.clear();
        NoOfPart = PartIndex.size();
        Quantity = -1;
        CurrentPartCount = -1;
        MissSpliceList.clear();
        CurrentSplice.SpliceID = -1;
        CurrentSplice.SpliceName.clear();
        WorkOrderDone = true;
    }
    ~WorkOrderElement(){
        PartIndex.clear();
        MissSpliceList.clear();
    }
    WorkOrderElement operator=(const WorkOrderElement &WorkOrderObject) const
    {
        WorkOrderElement Obj;
        Obj.RevCode = WorkOrderObject.RevCode;
        Obj.WorkOrderID = WorkOrderObject.WorkOrderID;
        Obj.WorkOrderName = WorkOrderObject.WorkOrderName;
        Obj.CreatedDate = WorkOrderObject.CreatedDate;
        Obj.OperatorID = WorkOrderObject.OperatorID;
        QMap<int, QString>::const_iterator i = WorkOrderObject.PartIndex.constBegin();
        while(i != WorkOrderObject.PartIndex.constEnd())
        {
            Obj.PartIndex.insert(i.key(),i.value());
            ++i;
        }
        Obj.NoOfPart = Obj.PartIndex.size();
        Obj.Quantity = WorkOrderObject.Quantity;
        Obj.CurrentPartCount = WorkOrderObject.CurrentPartCount;
        i = WorkOrderObject.MissSpliceList.constBegin();
        while(i != WorkOrderObject.MissSpliceList.constEnd())
        {
            Obj.MissSpliceList.insert(i.key(),i.value());
            ++i;
        }
        Obj.CurrentSplice.SpliceID = WorkOrderObject.CurrentSplice.SpliceID;
        Obj.CurrentSplice.SpliceName = WorkOrderObject.CurrentSplice.SpliceName;
        Obj.WorkOrderDone = WorkOrderObject.WorkOrderDone;
        return Obj;
    }

};

enum PASSWORDCONTROL
{
    SUPERUSER,
    ADMINISTRATOR,
    TECHNICIAN,
    QUALITYCONTROL,
    OPEN,
};



//
class AlarmElement
{
public:
    int RevCode;
    int AlarmID;
    QString AlarmMsg;
    unsigned int CreatedDate;
    int AlarmType;
    int WeldResultID;
    int OperatorID;
public:
    AlarmElement()
    {
        RevCode = -1;
        AlarmID = -1;
        AlarmMsg.clear();
        CreatedDate = 0;
        AlarmType = -1;
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
    int ActualAlarmflags;
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
