#ifndef SYSCONFIGURATION_H
#define SYSCONFIGURATION_H
#include <QString>
#include <QObject>
#include "definition.h"

#define MaxWireEntries 20

#define PORT_DISABLE              0   //Value represents Port Disable
#define PASSWORDCOUNT             3   //Does not include Administrator
#define PASSCOUNT                 3

//File System Flags, 3 groups of 8 bits (Most not used)
//First Flag in each group is Include Support Files in operation
#define FSFCopyMask           0xFF
#define FSFCopyIncSupFiles    0x01
#define FSFMoveMask           0xFF00
#define FSFMoveIncSupFiles    0x100
#define FSFDeleteMask         0xFF0000
#define FSFDeleteIncSupFiles  0x10000        //Not checked: Automatic
#define FSFDeleteOnlySupFiles 0x20000

//The default will be to Delete or Move the support files but not Copy them
#define FSFDefaultSet  (FSFMoveIncSupFiles | FSFDeleteIncSupFiles)& (~FSFCopyIncSupFiles);

#define Minmm2EnergyMult          25
#define Defmm2EnergyMult0         88
#define Defmm2EnergyMult1         96.8
#define Defmm2EnergyMult2         106.48
#define Maxmm2EnergyMult          200
#define Minmm2EnergyOffset        0
#define Defmm2EnergyOffset0       17
#define Defmm2EnergyOffset1       18.7
#define Defmm2EnergyOffset2       20.57
#define Maxmm2EnergyOffset        200
#define Minmm2WidthAreaRatio      0.5
#define Defmm2WidthAreaRatio0     1.25
#define Defmm2WidthAreaRatio1     1.25
#define Defmm2WidthAreaRatio2     1.25
#define Maxmm2WidthAreaRatio      2
#define Minmm2PressOffset         10
#define Defmm2PressOffset0        11
#define Defmm2PressOffset1        11
#define Defmm2PressOffset2        12.1
#define Maxmm2PressOffset         50
#define Minmm2PressMult           0.5
#define Defmm2PressMult0          1.8
#define Defmm2PressMult1          1.8
#define Defmm2PressMult2          1.98
#define Maxmm2PressMult           2
#define Minmm2AmplitudeOffset     5
#define Defmm2AmplitudeOffset0    18
#define Defmm2AmplitudeOffset1    19.8
#define Defmm2AmplitudeOffset2    21.78
#define Maxmm2AmplitudeOffset     50
#define Minmm2AmplitudeMult       0.5
#define Defmm2AmplitudeMult0      2.4
#define Defmm2AmplitudeMult1      2.64
#define Defmm2AmplitudeMult2      2.9
#define Maxmm2AmplitudeMult       5
#define MinRange1                 0
#define MaxRange1                 6.99
#define MinRange2                 7
#define MaxRange2                 14.99
#define MinRange3                 15
#define MaxRange3                 40

#define AdminUsername        QObject::tr("ADMIN")
#define TechUsername         QObject::tr("TECH")
#define QCtlUsername         QObject::tr("QCTL")

#define ShrinkTubeMinTemp             200
#define ShrinkTubeMaxTemp             600
#define ShrinkTubeMinTime             0
#define ShrinkTubeMaxTime             99.9
#define ShrinkTubeDefTemp1            260
#define ShrinkTubeDefTime1            9
#define ShrinkTubeDefTemp2            260
#define ShrinkTubeDefTime2            10
#define ShrinkTubeDefTemp3            260
#define ShrinkTubeDefTime3            11
#define ShrinkTubeDefTemp4            260
#define ShrinkTubeDefTime4            14
#define ShrinkTubeDefTemp5            260
#define ShrinkTubeDefTime5            15
#define ShrinkTubeDefTemp6            260
#define ShrinkTubeDefTime6            18
#define ShrinkTubeDefTemp7            260
#define ShrinkTubeDefTime7            20
#define ShrinkTubeDefTemp8            260
#define ShrinkTubeDefTime8            26
#define ShrinkTubeDefTemp9            260
#define ShrinkTubeDefTime9            28
#define ShrinkTubeDefTemp10           260
#define ShrinkTubeDefTime10           30

#define ADMINOPWrequired     0x04

#define SoftLimitDefaultSampleSize 5
#define SoftLimitSigmaDefault      3
#define SoftLimitEnabledFlag    0x200
#define DefAutoGetNextDelay       3   //3/10 Second

#define BRANSON_LASTWELD_FILE  "BransonLastWeld.bin" //Array DataCell() is stored in this file

enum SCREEN_MODE{
    No_SCREEN = 0,
    CreateNew_SCREEN,
    Operate_SCREEN,
    Test_SCREEN,
};

// Used to set the correct Language Version for the Software
enum LangSupport{
    NO_Lang = 0,
    ENGLISH_lang,
    FRENCH_Lang,
    GERMAN_Lang,
    HUNGARIAN_Lang,
    PORTUGUESE_Lang,
    SPANISH_Lang,
    TURKISH_Lang,
    ITALIAN_Lang,
    CHINESE_Lang,
    JAPANESE_Lang,
    KOREAN_Lang,
    END_Lang            //Add above this
};

enum PRESSUREUNIT{
    ToPSI,
    ToBar,
    TokPa,
};

enum WeldSetFormula{
    WeldFormulaAmtechStandard,
    WeldFormulaAmtechXL,
    WeldFormulaCustom,
};

//Structure for the Amtech.Bin (Software Settings File)
struct BRANSON_INI_STRUCT
{
    enum LangSupport Lang_Support;
    int Horn_Calibrate;
    int AutoPreburst;
    bool AutoGetNext;
    int SonicGenWatts;
    bool ToolCoverIgnore;
    enum PRESSUREUNIT Pressure2Unit;
    bool Mm2Awg;
    float PWWidth2Height;       //Not used anywhere?
    int MinAmplitude;
    int MinPressure;
    int GotoRunScreen;         //Not used, open for re-use
    int NoToolCover4SU;
    enum WeldSetFormula WeldFormula;
    int RunCount;              //  Number to Run to Qualify the Splice
    enum TEACH_MODE_TYPE Teach_Mode;
    int TunePoint;
    int FrequencyOffset;
};

// Structure for reading the settings.inf file if one exists
struct M20_SETTINGS
{
    // Stores bitfields for several options listed below
    int UnsignedWeldData;
    // Unsigned WeldtoEnergy  :1   Energy, Height, and Time are mutually exclusive options
    // Unsigned WeldToHeight  :1   Program will only accept last one
    // Unsigned WeldToTime    :1
    // Unsigned AfterBurst    :1
    // Unsigned Setup_allowed :1
    int AfterBurstDelay;
    int AfterBurstDuration;
    int EnergyWindowPL;
    int PreBurstIndex;
};

struct QUALITY_DATA_FILE
{
    M20_SETTINGS mod10a_settings;
    int cust_qual_range[WIDTH_ADJ];
};


// Structure fo the Hard/Soft Limit Ranges
enum VALUETYPE
{
    Sigam,
    Percent,
};

struct HARD_SOFT_DATA
{
    enum VALUETYPE TypeHS;       //Value is either 0 = Sigma OR 1 = Percent
    int ValueHS;                 //Value Depends on the Type Either 1-9 Sigma Or 1%-99%
};

//Range Markers for the Hard/Soft Usl/Lsl limits
enum HARD_SOFT_MARKER
{
    TIME_USL,
    TIME_LSL,
    POWER_USL,
    POWER_LSL,
    PREHEIGHT_USL,
    PREHEIGHT_LSL,
    HEIGHT_USL,
    HEIGHT_LSL,
    END_SL,
};

struct HARD_SOFT_SETTINGS
{
    HARD_SOFT_DATA HARD_LIMIT[END_SL];
    HARD_SOFT_DATA SOFT_LIMIT[END_SL];
};

struct IAComElement
{
    long COMport;          //Stores the value of the Comm Port
    int BaudRate;          //Stores the setting for the Baud Rate of the comm port
};

enum ActuatorType{
    ACT2020,
    ACTXL,
    ACTTERMINATOR,
    ACTMOD9,
    ACTMOD10,
    ACTMOD10HD,
    ACTULTRA20,
    ACTULTRA40,
    ACTST40,
    ACTGUN40,
    ACTMTS20,
    ACT2032,
    ACTAUTOTERMINATOR,
    ACTNEWSPLICER,
};

struct PasswordEntry
{
    QString Identifier;
    QString Password;
};

enum FormulaRange
{
    EnergyR1,
    EnergyR2,
    EnergyR3,
    WidthR1,
    WidthR2,
    WidthR3,
    PressureR1,
    PressureR2,
    PressureR3,
    AmplitudeR1,
    AmplitudeR2,
    AmplitudeR3,
    FormulaRangSize,
};

struct CalcWeldSettings4BuildStruct
{
    float Multplier;
    float Offset;
    float MinRange;
    float MaxRange;
};

enum WeldDefaultSettingIndex
{
    WDSIABDelay,
    WDSIABDuration,
    WDSISqueezeTime,
    WDSIHoldTime,
    WDSIPreBurst,
    WDSI_SIZE,
};

enum ShrnkTubeIndex
{
    STIunder = -2,   //Marker
    STInone,         //Indicates no shrink tube
    STIR1,           //Raychem shrink tube type 1
    STIR2,
    STIR3,
    STIR4,
    STIR5,
    STIR6,
    STIR7,
    STIR8,
    STIR9,
    STIR10,
    STI_SIZE,         //Marker
};

struct ShrinkTubeData
{
    QString Name;
    int temp;
    float Time;
};

enum SoftLimitsIndex
{
    SLIUpperControlLimit = 0,    //Based on the screen view of the data
    SLILowerControlLimit = 1,
    SLIControlLimitSize = 2,
    SLITime = 0,
    SLIPower = 1,
    SLIPreHeight = 2,
    SLIHeight = 3,
    SLI_Size = 4,
};

enum CoolingMode{
   ENERGYMODE = -1,
   OFF = 0
};

enum PWSDefinitions{
    PWSNotDefined,           //Button will not show in menu (CNTRL+Y shows button)
    PWSAdministrator,        //Administrator at least is required.
};

enum ACTUATORMODE{
    ANTISIDESPLICEOFF = -1,
    ANTISIDESPLICE = 0,
    WIDTHPLUS2,
    WIDTHPLUS25PERCENT,
    DOUBLEHITMODE,
    USESTARTHANDLE,
};

//A single structure and a single file for the status data
class Status_Data
{
public:
    int RevCode;
    QString CreatedDate;
    QString OperatorName;
    BRANSON_INI_STRUCT Soft_Settings;
    QUALITY_DATA_FILE Cust_Data;
    HARD_SOFT_SETTINGS HSDATA;     //Not used, held for backwords compatibility
    IAComElement ComInfo;
    enum ActuatorType MachineType;
    QString MachineDate;
    bool KeepDailyHistory;
    enum PWSDefinitions PasswordStatus;
    PasswordEntry PasswordData[PASSWORDCOUNT];
    long AdminOptions;        //Flag field
    long PWPermissions;       //Flag field
    CalcWeldSettings4BuildStruct WeldSettings4Build[FormulaRangSize];
    int WeldSettingsDefault4Build[WDSI_SIZE];  //100's of Secs
    int WeldSettingDefaultWeldMode;
    int WeldSettingDefaultTrigPress;
    bool AutoStartLastPart;
    bool NRGtoHeightMode;      //Mode 3 not on all machines
    bool TubeShrinkMode;       //Tube shrinker not on all machines
    ShrinkTubeData ShrinkTubeDefaults[STI_SIZE];
    int RemoteRecallport;
    long SoftLimitsModeFlags;
    int SoftLimitSampleSize;
    int SoftLimit[SLIControlLimitSize][SLI_Size];
    bool QualityLimitsModeFlags;
    long FileSystemFlags;
    long AutoGetNextDelay;
    long NetworkingEnabled;
    QString CurrentWrkStaID;
    QString CentralComputerID;
    enum ACTUATORMODE ActuatorMode;
    int AntisideSpliceTime;
    int CurrentCoolingDur;
    int CurrentCoolingDel;
    enum CoolingMode CurrentCoolingMode;
    int CurrentCoolingTooling;
    int LockonAlarm;
    int RunMode;
    int Machineflags[4];

    long CycleCount;
    long MaintenanceLimits[8];
    long CurrentMaintenanceLimits[8];
    int TubeShrinkerport;
    bool HistoryGraphData;
    bool RemoteGraphData;
    enum SCREEN_MODE StartScreen;
    bool EnableModularFlag;
    PasswordEntry ModularPassword[PASSCOUNT];
    int PowerGraphSampleRatio;
    long GraphDataLen;
    int CutoffMode;
    bool LockKeyFlag;
    bool FootPedalFlag;
public:
    Status_Data operator=(const Status_Data &StatusDataObj) const;
};


#endif // SYSCONFIGURATION_H
