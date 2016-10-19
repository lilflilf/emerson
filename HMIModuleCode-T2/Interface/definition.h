#ifndef DEFINITION_H
#define DEFINITION_H
#include <QString>
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
    QString CreateDate;

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

struct RecommendedData
{
   int Energy;
   int Width;
   int Pressure;
   int TrigPres;
   int Amplitude;
   Qual Time;
   Qual power;
   Qual Preheight;
   Qual Height;
   Qual Force;
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
    enum STEPWELDMODE StepWeld;
    int EnergyToStep;         //
    int TimeToStep;           //
    int PowerToStep;          //
    int Amplitude2;           //If the step weld is disabled, the Amplitude2 is always 0
};

struct SHRINKTUBE
{
    //Added 30 June 2000 to accommodate the Raychem tube shrinker data
    bool ShrinkOption;
    long ShrinkTubeIndex;     //Raychem tube index (0 for None,1,2,3,3A,Other)
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

    bool CutterOff;           //CutterOption
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
    Undefined,
};

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
    int TeachModequal_Window[ENERGY_ADJ];
};

struct TESTSETTING
{
    long Qutanty;             //Accummulated total
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
    QString CreateDate;       //Date of last rev, seconds from Jan 1, 1980
    QString OperatorID;

    int CrossSection;         //Area of part in mm*mm/100
    QString PresetPicNamePath;
    bool Verified;

    struct WELDSETTING WeldSetting;
    struct QUALITYWINDONSETTING QualitySetting;
    struct ADVANCESETTING AdvanceSetting;

    int NoOfWires;            //Number of wires in this splice
    /*WireEl(1 To MAX_WIRE_ELEMENTS) As WireElement*/
    QMap<int,QString> Wire;   //Store data for individual wires

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
    struct WORKSTATIONS;
    struct BOARDLAYOUT;
};

struct PARTATTRIBUTE
{
    int CurrentWorkstation;
    int CurrentBoardLayoutZone;
    QString SpliceName;
};

struct PartElement
{
    int RevCode;
    int PartID;
    QString PartName;
    QString CreateDate;
    QString OperatorID;
    struct PARTTYPE PartTypeSetting;

    int NoOfSplice;
    //#define SEQ_MAX_SPLICES  250
    QMap<int, struct PARTATTRIBUTE> Splice;

};

//Work Order Structure
struct SpliceIndex
{
    int SpliceID;
    QString SpliceName;
};

struct WorkOrder
{
    int RevCode;
    int WorkOrderID;
    QString WorkOrderName;
    QString CreateDate;
    QString OperatorID;
    int NoOfPart;
    QMap<int, QString> Part;

    int Quantity;
    int CurrentPartCount;
    QMap<int, QString> MissSpliceList;
    struct SpliceIndex CurrentSplice;
    bool WorkOrderDone;
};

#endif // DEFINITION_H
