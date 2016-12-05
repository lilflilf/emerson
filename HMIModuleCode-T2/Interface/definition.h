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

class WireElement
{
public:
    QString WireName;
    int     WireID;
    unsigned int CreatedDate;
    int OperatorID;

    QString Color;
    struct STRIPE Stripe;
    int Gauge;               //Area of Wire in mm*mm/100
    int GaugeAWG;
    enum MetalType TypeOfWire;
    enum HorizontalLocation Side;
    enum VerticalLocation VerticalSide;
    enum VerticalPosition Position;
public:
    WireElement()
    {
        WireName.clear();
        WireID = -1;
        CreatedDate = 0;
        OperatorID = -1;
        Color = "pink";
        Stripe.Color = "pink";
        Stripe.TypeOfStripe = Horizontal;
        Gauge = 10;
        GaugeAWG = 37;
        TypeOfWire = Copper;
        Side = Right;
        VerticalSide = Basic;
        Position = Middle;
    }
    WireElement operator=(const WireElement &WireObject)
    {
        if(this == &WireObject)
            return *this;
        this->WireName = WireObject.WireName;
        this->WireID = WireObject.WireID;
        this->CreatedDate = WireObject.CreatedDate;
        this->OperatorID = WireObject.OperatorID;
        this->Color = WireObject.Color;
        this->Stripe.Color = WireObject.Stripe.Color;
        this->Stripe.TypeOfStripe = WireObject.Stripe.TypeOfStripe;
        this->Gauge = WireObject.Gauge;
        this->GaugeAWG = WireObject.GaugeAWG;
        this->TypeOfWire = WireObject.TypeOfWire;
        this->Side = WireObject.Side;
        this->VerticalSide = WireObject.VerticalSide;
        this->Position = WireObject.Position;
        return *this;
    }
    bool operator==(const WireElement &WireObject)
    {
        bool bResult = false;
//        if(this->WireName != WireObject.WireName)
//            return bResult;
//        if(this->WireID != WireObject.WireID)
//            return bResult;
//        if(this->CreatedDate != WireObject.CreatedDate)
//            return bResult;
        if(this->OperatorID != WireObject.OperatorID)
            return bResult;
        if(this->Color != WireObject.Color)
            return bResult;
        if(this->Stripe.Color != WireObject.Stripe.Color)
            return bResult;
        if(this->Stripe.TypeOfStripe != WireObject.Stripe.TypeOfStripe)
            return bResult;
        if(this->Gauge != WireObject.Gauge)
            return bResult;
        if(this->GaugeAWG != WireObject.GaugeAWG)
            return bResult;
        if(this->TypeOfWire != WireObject.TypeOfWire)
            return bResult;
        if(this->Side != WireObject.Side)
            return bResult;
        if(this->VerticalSide != WireObject.VerticalSide)
            return bResult;
        if(this->Position != WireObject.Position)
            return bResult;
        bResult = true;
        return bResult;
    }
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

    struct WELDSETTING WeldSettings;
    unsigned int HashCode;
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

        WeldSettings.BasicSetting.Energy = -1;
        WeldSettings.BasicSetting.Amplitude = -1;
        WeldSettings.BasicSetting.Pressure = -1;
        WeldSettings.BasicSetting.TrigPres = -1;
        WeldSettings.BasicSetting.Width = -1;
        WeldSettings.QualitySetting.Time.Minus = 0;
        WeldSettings.QualitySetting.Time.Plus = 1000;               //Seconds * 200
        WeldSettings.QualitySetting.Power.Minus = 0;
        WeldSettings.QualitySetting.Power.Plus = 4800;
        WeldSettings.QualitySetting.Preheight.Minus = 0;
        WeldSettings.QualitySetting.Preheight.Plus = 1500;               //mm * 100
        WeldSettings.QualitySetting.Height.Minus = 0;
        WeldSettings.QualitySetting.Height.Plus = 1500;
        WeldSettings.AdvanceSetting.ABDelay = 0;
        WeldSettings.AdvanceSetting.ABDur = 0;
        WeldSettings.AdvanceSetting.AntiSide = false;
        WeldSettings.AdvanceSetting.CutOff = false;
        WeldSettings.AdvanceSetting.HoldTime = 0;
        WeldSettings.AdvanceSetting.MeasuredHeight = 0;
        WeldSettings.AdvanceSetting.MeasuredWidth = 0;
        WeldSettings.AdvanceSetting.PreBurst = 0;
        WeldSettings.AdvanceSetting.SqzTime = 0;
        WeldSettings.AdvanceSetting.WeldMode = ENERGY;
        WeldSettings.AdvanceSetting.StepWeld.StepWeldMode = STEPDISABLE;
        WeldSettings.AdvanceSetting.StepWeld.Amplitude2 = -1;
        WeldSettings.AdvanceSetting.StepWeld.EnergyToStep = -1;
        WeldSettings.AdvanceSetting.StepWeld.PowerToStep = -1;
        WeldSettings.AdvanceSetting.StepWeld.TimeToStep = -1;
        WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption = false;
        WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature = -1;
        WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime = -1;
        WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID = -1;
        HashCode = qHashBits(&WeldSettings, sizeof(WeldSettings), 0);
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
    PresetElement operator=(const PresetElement &PresetObject)
    {
        if(this == &PresetObject)
            return *this;
        this->RevCode = PresetObject.RevCode;
        this->SpliceID = PresetObject.SpliceID;
        this->SpliceName = PresetObject.SpliceName;
        this->CreatedDate = PresetObject.CreatedDate;
        this->OperatorID = PresetObject.OperatorID;

        this->CrossSection = PresetObject.CrossSection;
        this->PresetPicNamePath = PresetObject.PresetPicNamePath;
        this->Verified = PresetObject.Verified;

        this->WeldSettings.BasicSetting.Energy =
                PresetObject.WeldSettings.BasicSetting.Energy;
        this->WeldSettings.BasicSetting.Amplitude = PresetObject.WeldSettings.BasicSetting.Amplitude;
        this->WeldSettings.BasicSetting.Pressure = PresetObject.WeldSettings.BasicSetting.Pressure;
        this->WeldSettings.BasicSetting.TrigPres = PresetObject.WeldSettings.BasicSetting.TrigPres;
        this->WeldSettings.BasicSetting.Width = PresetObject.WeldSettings.BasicSetting.Width;
        this->WeldSettings.QualitySetting.Time.Minus =
                PresetObject.WeldSettings.QualitySetting.Time.Minus;
        this->WeldSettings.QualitySetting.Time.Plus =
                PresetObject.WeldSettings.QualitySetting.Time.Plus;
        this->WeldSettings.QualitySetting.Power.Minus =
                PresetObject.WeldSettings.QualitySetting.Power.Minus;
        this->WeldSettings.QualitySetting.Power.Plus =
                PresetObject.WeldSettings.QualitySetting.Power.Plus;
        this->WeldSettings.QualitySetting.Preheight.Minus =
                PresetObject.WeldSettings.QualitySetting.Preheight.Minus;
        this->WeldSettings.QualitySetting.Preheight.Plus =
                PresetObject.WeldSettings.QualitySetting.Preheight.Plus;
        this->WeldSettings.QualitySetting.Height.Minus =
                PresetObject.WeldSettings.QualitySetting.Height.Minus;
        this->WeldSettings.QualitySetting.Height.Plus =
                PresetObject.WeldSettings.QualitySetting.Height.Plus;
        this->WeldSettings.AdvanceSetting.ABDelay =
                PresetObject.WeldSettings.AdvanceSetting.ABDelay;
        this->WeldSettings.AdvanceSetting.ABDur =
                PresetObject.WeldSettings.AdvanceSetting.ABDur;
        this->WeldSettings.AdvanceSetting.AntiSide =
                PresetObject.WeldSettings.AdvanceSetting.AntiSide;
        this->WeldSettings.AdvanceSetting.CutOff =
                PresetObject.WeldSettings.AdvanceSetting.CutOff;
        this->WeldSettings.AdvanceSetting.HoldTime =
                PresetObject.WeldSettings.AdvanceSetting.HoldTime;
        this->WeldSettings.AdvanceSetting.MeasuredHeight =
                PresetObject.WeldSettings.AdvanceSetting.MeasuredHeight;
        this->WeldSettings.AdvanceSetting.MeasuredWidth =
                PresetObject.WeldSettings.AdvanceSetting.MeasuredWidth;
        this->WeldSettings.AdvanceSetting.PreBurst =
                PresetObject.WeldSettings.AdvanceSetting.PreBurst;
        this->WeldSettings.AdvanceSetting.SqzTime =
                PresetObject.WeldSettings.AdvanceSetting.SqzTime;
        this->WeldSettings.AdvanceSetting.WeldMode =
                PresetObject.WeldSettings.AdvanceSetting.WeldMode;
        this->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode
                = PresetObject.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode;
        this->WeldSettings.AdvanceSetting.StepWeld.Amplitude2
                = PresetObject.WeldSettings.AdvanceSetting.StepWeld.Amplitude2;
        this->WeldSettings.AdvanceSetting.StepWeld.EnergyToStep
                = PresetObject.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep;
        this->WeldSettings.AdvanceSetting.StepWeld.PowerToStep
                = PresetObject.WeldSettings.AdvanceSetting.StepWeld.PowerToStep;
        this->WeldSettings.AdvanceSetting.StepWeld.TimeToStep
                = PresetObject.WeldSettings.AdvanceSetting.StepWeld.TimeToStep;
        this->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption
                = PresetObject.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption;
        this->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature
                = PresetObject.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature;
        this->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime
                = PresetObject.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime;
        this->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID
                = PresetObject.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID;
        this->HashCode = PresetObject.HashCode;
        QMap<int,QString>::const_iterator i
                = PresetObject.WireIndex.constBegin();
        while(i != PresetObject.WireIndex.constEnd())
        {
            this->WireIndex.insert(i.key(),i.value());
            ++i;
        }
        this->NoOfWires = this->WireIndex.size();
        this->TestSetting.Qutanty = PresetObject.TestSetting.Qutanty;
        this->TestSetting.StopCount = PresetObject.TestSetting.StopCount;
        this->TestSetting.TestMode = PresetObject.TestSetting.TestMode;
        this->TestSetting.TeachModeSetting.TeachModeType
                = PresetObject.TestSetting.TeachModeSetting.TeachModeType;
        for (int i = TIME_PLRG; i<= HEIGHT_CONFRG_MS; i++)
        {
            this->TestSetting.TeachModeSetting.TeachModequal_Window[i]
                    = PresetObject.TestSetting.TeachModeSetting.TeachModequal_Window[i];
        }
        this->TestSetting.TestingDone = PresetObject.TestSetting.TestingDone;
        return *this;
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
    unsigned int SpliceHash;
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
