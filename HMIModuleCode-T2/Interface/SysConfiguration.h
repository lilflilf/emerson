#ifndef SYSCONFIGURATION_H
#define SYSCONFIGURATION_H
#include <QString>
#include <QObject>
#include "Interface/Definition.h"
#include "Interface/WeldResultElement.h"

#define MaxWireEntries 20

#define PORT_DISABLE              0   //Value represents Port Disable
#define PASSWORDCOUNT             3   //Does not include Administrator
#define PASSCOUNT                 3
#define PERMISSIONLEVEL           5   // Switch Key, level1, level2, level3, level4,

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

#define ADMINNOButton        0x01
#define ADMINNOShutdown      0x02
#define ADMINOPWrequired     0x04
#define ADMINOShowMaintData  0x08
#define ADMINOQualifiedOnly  0x10

#define SoftLimitDefaultSampleSize 5
#define SoftLimitSigmaDefault      3
#define SoftLimitEnabledFlag    0x200
#define DefAutoGetNextDelay       3   //3/10 Second

#define MINSERVER_PORT_NUMBER     1
#define MAXSERVER_PORT_NUMBER     65535

#define BRANSON_LASTWELD_FILE  "BransonLastWeld.bin" //Array DataCell() is stored in this file

enum SCREEN_MODE{
    No_SCREEN = -1,
    CreateNew_SCREEN = 0,
    EditExisting_SCREEN,
    Operate_SCREEN,
    Test_SCREEN,
    TeachMode_SCREEN,
    Calibration_SCREEN,
    ToolChange_SCREEN,
    AdvancedMaintenance_SCREEN,
    MaintenanceCounter_SCREEN,
    MaintenanceLog_SCREEN,
    WorkOrderHistory_SCREEN,
    StatisticalTrend_SCREEN,
    ErrorAlarmLog_SCREEN,
    Library_SCREEN,
    VersionInformation_SCREEN,
    PermissionSetting_SCREEN,
    WeldDefaults_SCREEN,
    OperatorLibrary_SCREEN,
    DataCommunication_SCREEN,
    LockOnAlarm_SCREEN,
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
    int SonicGenWatts;
    bool ToolCoverIgnore;
    enum PRESSUREUNIT Pressure2Unit;
    bool Mm2Awg;
    bool Mm2Inch;
    float PWWidth2Height;       //Not used anywhere?
    int MinAmplitude;
    int MinPressure;
    enum WeldSetFormula WeldFormula;
    int RunCount;              //  Number to Run to Qualify the Splice
    TEACHMODESETTING::TEACH_MODE_TYPE Teach_Mode;
    int TunePoint;
    int FrequencyOffset;
};


class QUALITY_DATA_FILE
{
public:
    enum PRESET_TEACHSETTING{
        GLOBALS,
        SPECIAL,
    };

    int cust_qual_range[QUAL_RANGES];
    PRESET_TEACHSETTING PresetTeachModeSetting;
    int StandardRunQuantity;
    int AutoRunQuantity;
    int SigmaRunQuantity;
};

struct IAComElement
{
    int COMport;          //Stores the value of the Comm Port
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
    unsigned int PWPermissions;         //Flag field
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
    STIR11,
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

enum PWSDefinitions{
    PWSNotDefined,           //Button will not show in menu (CNTRL+Y shows button)
    PWSAdministrator,        //Administrator at least is required.
};

union MACHINEFLAGS	{	/* union MACHINEFLAGS MachineFlags */
    struct	{
        unsigned    Unused           :1;
        unsigned    ANVILRetractFunc :1;     /* Extract Gather for 2mm before Anvil only if this flag is set. */
        unsigned    BarcodeResponse  :1;      /* Send Barcode response only if this flag is set. */
        unsigned	NoSettingHdr	 :1;		/* Don't print header data on each page/change */
        unsigned	MntScanEaWld	 :1;		/* Maint. counters scanned after each weld or seq. */
        unsigned	Prnt2SerPort	 :1;		/* Print line data to serial port */
        unsigned	AirOn4Weld		 :1;		/* Air will not be turn off during weld */
        unsigned	PHgtSearchOn	 :1;		/* Pre-Height search mode used on MTS20; Note: Changed from PHgtSearchOff, Reversed logic to default to OFF KBoria 5/2010 */
        unsigned	PrnLegacyBrd	 :1;		/* Legacy PCB w/programmed strobe */
        unsigned	Seq2StrtOnErr	 :1;		/* Automatic reset to first on error */
        unsigned	SeqDblClk2Strt	 :1;		/* Double click to first instead of next */
        unsigned	SeqDblClkOff	 :1;		/* Double click to skip step */
        unsigned	SeekOff			 :1;
        /* Sequence and Double click reset options */
        unsigned	PrTransducerOff	 :1;		/* Standard condition now */
        unsigned	WdthEncoderOff	 :1;
        unsigned	HgtEncoderOff	 :1;		/* When these flags are set the device is missing */
    } Flag;
    unsigned short Word[4]; /* Room for 64 flags initialized to 0 (or?) */
};

union RUNMODE	{
    /*There is a big endian for struct bit field alignment for IAR */
    struct	{
        unsigned Unused :11;

        unsigned Mod10Mode          :1; /* Moved here into BBR from RAM */
        unsigned DefeatWeldAbort	:1;
        unsigned TeachModeOn		:1;
/* Set this flag to defeat the footpedal monitor during the weld cycle */
        unsigned SequenceRunning	:1;
        unsigned SequenceOn			:1;

    } ModeFlag;
    unsigned short Word;
};

//A single structure and a single file for the status data
class Status_Data
{
public:
    enum ACTUATORMODE{
        ANTISIDESPLICEOFF = -1,
        ANTISIDESPLICE = 0,
        WIDTHPLUS2,
        WIDTHPLUS25PERCENT,
        DOUBLEHITMODE,
        USESTARTHANDLE,
    };
    enum CoolingMode{
        ENERGYMODE = -1,
        OFF = 0,
        ON = 1,
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
public:
    int RevCode;
    QString CreatedDate;
    QString OperatorName;

    QMap<int, int> AWGToAreaTable;

    QUALITY_DATA_FILE Cust_Data;

    enum ActuatorType MachineType;
    QString MachineDate;
    IAComElement ComInfo;

    enum SCREEN_MODE StartScreen;
/*Setting->Premission Setting*/
    PasswordEntry PasswordData[PERMISSIONLEVEL];
    QList<int> CurrentFunIndex;
/*Weld Default*/
    union MACHINEFLAGS Machineflags;
    union RUNMODE RunMode;
    enum CoolingMode CurrentCoolingMode;
    bool CurrentCoolingTooling;
    int CurrentCoolingDur;
    int CurrentCoolingDel;
    BRANSON_INI_STRUCT Soft_Settings;
    bool KeepDailyHistory;
    bool HistoryGraphData;
    WeldResultElement::SAMPLERATIO GraphSampleRatio;

    CalcWeldSettings4BuildStruct WeldSettings4Build[FormulaRangSize];
//    int WeldSettingsDefault4Build[WDSI_SIZE];  //100's of Secs
//    int WeldSettingDefaultWeldMode;
//    int WeldSettingDefaultTrigPress;
//    bool AutoStartLastPart;
//    bool NRGtoHeightMode;      //Mode 3 not on all machines
/*Data Communication*/
    bool ShrinkTubeMode;       //Tube shrinker not on all machines
    QList<ShrinkTubeData> ShrinkTubeDefaults;
    IAComElement ShrinkTubeComInfo;

    bool NetworkingEnabled;
    bool RemoteDataLogging;
    bool RemoteGraphData;

    int ServerPort;
    bool ModularProductionEnabled;

    int RemoteRecallport;

    unsigned int SoftLimitsModeFlags;
    int SoftLimitSampleSize;
    int SoftLimit[SLIControlLimitSize][SLI_Size];
//    bool QualityLimitsModeFlags;
    int FileSystemFlags;
    int AutoGetNextDelay;

    QString CurrentWrkStaID;
    QString CentralComputerID;

    enum ACTUATORMODE ActuatorMode;
    QString ActuatorVersion;
    QString ActuatorPartNumber;
    QString ActuatorSerialNumber;
    QString ActuatorModuleNumber;
    QString PSPartNumber;
    QString PSSerialNumber;
    int AntisideSpliceTime;
    int LockonAlarm;
    int CycleCount;

    int CurrentCountMaintenanceLimits[8];
    double CurrentEnergyMaintenanceLimits[8];
    int MaintenanceCountLimits[8];
    double MaintenanceEnergyLimits[8];
    unsigned int MaintenanceDateStarted[8];
    bool Maintenance80PercentAlarm[8];
    bool Maintenance100PercentLock[8];

//    enum SCREEN_MODE StartScreen;
    bool EnableModularFlag;
    PasswordEntry ModularPassword[PASSCOUNT];

    int GraphDataLen;
    int CutoffMode;
    bool LockKeyFlag;
    bool FootPedalFlag;
    QMap<int, QString> carTemplate;
    int ReliablityMode;
    bool PhysicalKeyMode;
public:
    Status_Data();
    Status_Data &operator= (const Status_Data &StatusDataObj);
    bool ReadStatusDataFromQSetting();
    void WriteStatusDataToQSetting();
};


#endif // SYSCONFIGURATION_H
