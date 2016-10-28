#ifndef DEFINITION_H
#define DEFINITION_H
#include <QString>
#include <QMap>
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

enum TEACHMODETYPE
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

struct TEACHMODESETTING
{
    enum TEACHMODETYPE TeachModeType;
    //TeachModeAdvanceSetting
    int TeachModequal_Window[18];
};

struct TESTSETTING
{
    int Qutanty;             //Accummulated total
    int StopCount;
    enum TESTMODE TestMode;
    struct TEACHMODESETTING TeachModeSetting;
    bool TestingDone;
};

struct PresetElement
{
    int RevCode;              //Amtech Revision Code for possible future use
    int SpliceID;
    QString SpliceName;       //Customer's Part Number
    unsigned int CreatedDate;       //Date of last rev, seconds from Jan 1, 1980
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

//    RecommendedData RecData;  //Recommended Data

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

struct PartElement
{
    int RevCode;
    int PartID;
    QString PartName;
    unsigned int CreatedDate;
    int OperatorID;
    struct PARTTYPE PartTypeSetting;

    int NoOfSplice;
    //#define SEQ_MAX_SPLICES  250
    QMap<int, struct PARTATTRIBUTE> SpliceIndex;

};

//Work Order Structure
struct SpliceIndex
{
    int SpliceID;
    QString SpliceName;
};

struct WorkOrderElement
{
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
};

enum PASSWORDCONTROL
{
    ADMINISTRATOR,
    TECHNICIAN,
    QUALITYCONTROL,
    OPEN,
};

//default has two records in user log.
struct OperatorElement
{
    int RevCode;
    int OperatorID;
    QString OperatorName;
    int WhoCreatedNewID;
    unsigned int CreatedDate;
    QString Password;
    enum PASSWORDCONTROL PermissionLevel;
};

//
struct AlarmInfo
{
    int RevCode;
    int AlarmID;
    QString AlarmMsg;
    QString CreatedDate;
    int AlarmType;
    int WeldResultID;
    int OperaterID;

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

//struct WeldResultInfo
//{
//    int RevCode = 0;
//    int WeldResultID;
//    QString OperatorName;
//    QString CreatedDate;
//    struct WorkOrderIndex CurrentWorkOrder;
//    struct PartIndex CurrentPart;
//    struct SpliceIndex CurrentSplice;
//    int WeldCount;//just for the test mode
//    int PartCount;//just for the operate mode
//    struct WELDRESULT ActualResult;

//    enum SAMPLERATIO SampleRatio;

//    int NoOfSamples;
//    QMap<int, QString> PowerGraph;
//    QMap<int, QString> PostHeightGraph;
//};


typedef struct _weldResultInfo
{
    int RevCode;
    int WeldResultID;
    QString OperatorName;
    QString CreatedDate;
    struct WorkOrderIndex CurrentWorkOrder;
    struct PartIndex CurrentPart;
    struct SpliceIndex CurrentSplice;
    int WeldCount;//just for the test mode
    int PartCount;//just for the operate mode
    struct WELDRESULT ActualResult;
    enum SAMPLERATIO SampleRatio;
    int NoOfSamples;
    QMap<int, QString> PowerGraph;
    QMap<int, QString> PostHeightGraph;
public:
    _weldResultInfo()
    {
        RevCode = 0;
        WeldResultID = 0;
        OperatorName = "";
        CreatedDate = "";
    }
    _weldResultInfo& operator=(const _weldResultInfo info)
    {
        RevCode = info.RevCode;
        WeldResultID = info.WeldResultID;
        OperatorName = info.OperatorName;
        CreatedDate = info.CreatedDate;
        return *this;
    }
} WeldResultInfo;

#endif // DEFINITION_H