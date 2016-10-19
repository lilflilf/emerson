#ifndef M10INI_H
#define M10INI_H

#include <iostream>
#include <string>
#include <sstream>
#include "stdio.h"
#include "stdlib.h"
#include "M10definitions.h"
using namespace std;

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

#define WattsFactor               0.057;
#define DefAutoGetNextDelay       3   //3/10 Second

#define PORT_DISABLE              0   //Value represents Port Disable
#define PASSWORDCOUNT             2   //Does not include Administrator
#define PASSCOUNT                 4

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

// Structure for reading the settings.inf file if one exists
struct M20_SETTINGS{
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

struct QUALITY_DATA_FILE{
    struct M20_SETTINGS mod10a_settings;
    int cust_qual_range[WIDTH_ADJ];
};

#define MaxWireEntries  20

struct WIRE_ENTRY{
    int Wire_Area;
    string Wire_Ref_Ga;
};

struct BUILD_DATA{
    int No_of_Wires;
    WIRE_ENTRY WireEntries[MaxWireEntries];
};

//Range Markers for the Hard/Soft Usl/Lsl limits
enum HARD_SOFT_MARKER{
    TIME_USL,
    TIME_LSL,
    POWER_USL,
    POWER_LSL,
    PREHEIGHT_USL,
    PREHEIGHT_LSL,
    HEIGHT_USL,
    HEIGHT_LSL
};

enum WeldSetFormula{
    WeldFormulaAmtechStandard,
    WeldFormulaAmtechXL,
    WeldFormulaCustom,
};

enum WeldDefaultSettingIndex{
    WDSIABDelay,
    WDSIABDuration,
    WDSISqueezeTime,
    WDSIHoldTime,
    WDSIPreBurst,
};



enum FormulaRange{
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
};

enum PRESSUREUNIT{
    ToPSI,
    ToBar,
    TokPa,
};

// Structure fo the Hard/Soft Limit Ranges
struct HARD_SOFT_DATA{
    int TypeHS;       //Value is either 0 = Sigma OR 1 = Percent
    int ValueHS;      //Value Depends on the Type Either 1-9 Sigma Or 1%-99%
};

struct HARD_SOFT_SETTINGS{
    HARD_SOFT_DATA HARD_LIMIT[HEIGHT_LSL];
    HARD_SOFT_DATA SOFT_LIMIT[HEIGHT_LSL];
};

struct CalcWeldSettings4BuildStruct{
    float Multplier;
    float Offset;
    float MinRange;
    float MaxRange;
};

//Structure for the Amtech.Bin (Software Settings File)
struct AMTECH_INI_STRUCT{
    long Lang_Support;
    int Horn_Calibrate;
    int AutoPreburst;
    bool AutoGetNext;
    int SonicGenWatts;
    bool ToolCoverIgnore;
    int Pressure2Unit;
    float PWWidth2Height;       //Not used anywhere?
    int MinAmplitude;
    int MinPressure;
    int GotoRunScreen;        //Not used, open for re-use
    int NoToolCover4SU;
    long WeldFormula;
    int RunCount;            //  Number to Run to Qualify the Splice
    int Teach_Mode;
    int TunePoint;
    int FrequencyOffset;
};

struct PasswordEntry{
    QString Identifier;
    string Password;
};

//Each element of the soft limit check has two flags:
//Sigma or percent, absence of both flags means the element is off
//Low bit is the Sigma flag, high bit is the Percent flag
//Note that many routines will depend on the math relationship in comments
#define SoftLimitTimeFlags      0x03          //1 * 3 ((1 * 1) Or (1 * 2))
#define SoftLimitPowerFlags     0x0C          //4 * 3 ((4 * 1) Or (4 * 2))
#define SoftLimitPreHeightFlags 0x30          //16 * 3 ((16 * 1) Or (16 * 2))
#define SoftLimitHeightFlags    0xC0          //64 * 3 ((64 * 1) Or (64 * 2))
#define SoftLimitWeightFlag     0x100
#define SoftLimitEnabledFlag    0x200
#define SoftLimitAudibleFlag    0x400

#define SoftLimitDefaultSampleSize 5
#define SoftLimitSigmaMax          5
#define SoftLimitSigmaMin          1
#define SoftLimitSigmaDefault      3
#define SoftLimitPercentMax        90
#define SoftLimitPercentMin        10
#define SoftLimitPercentDefault    50

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

struct ShrinkTubeData{
    string Name;
    int temp;
    float Time;
};

struct IAcominfo{
    long COMport;          //Stores the value of the Comm Port
    int BaudRate;          //Stores the setting for the Baud Rate of the comm port
};

enum SampleRatio{
    Ratio_1ms = 0,
    Ratio_5ms = 1,
    Ratio_10ms = 2
};

//A single structure and a single file for the status data
struct Status_Data{
    AMTECH_INI_STRUCT Soft_Settings;
    BUILD_DATA Wire_Info;              //Wire information for building a weld or splice
    QUALITY_DATA_FILE Cust_Data;
    HARD_SOFT_SETTINGS HSDATA;         //Not used, held for backwords compatibility
    IAcominfo ComInfo;
    int MachineType;
    string MachineDate;
    bool KeepDailyHistory;
    long PasswordStatus;
    PasswordEntry PasswordData[PASSWORDCOUNT];
    long AdminOptions;                             //Flag field
    long PWPermissions;                            //Flag field
    CalcWeldSettings4BuildStruct WeldSettings4Build[AmplitudeR3];
    int WeldSettingsDefault4Build[WDSIPreBurst];   //100's of Secs
    int WeldSettingDefaultWeldMode;
    int WeldSettingDefaultTrigPress;
    bool AutoStartLastPart;
    bool NRGtoHeightMode;                           //Mode 3 not on all machines
    bool TubeShrinkMode;                            //Tube shrinker not on all machines
    ShrinkTubeData ShrinkTubeDefaults[STIover];
    // ShrinkTubeDefaults(0 To 9) As ShrinkTubeData
    int RemoteRecallport;
    long SoftLimitsModeFlags;
    int SoftLimitSampleSize;
    int SoftLimit[SLILowerControlLimit][SLIHeight];
    bool QualityLimitsModeFlags;
    long FileSystemFlags;
    long AutoGetNextDelay;
//Network items added 030220
    bool NetworkingEnabled;
    string CurrentWrkStaID;
    string CentralComputerID;
    //CutterMsgFlag  As Boolean
    int ActuatorMode;
    int AntisideSpliceTime;
    int CurrentCoolingDur;
    int CurrentCoolingDel;
    int CurrentCoolingMode;
    int LockonAlarm;
    int RunMode;
    int Machineflags[4];
    bool Mm2Awg;
    long CycleCount;
    long MaintenanceLimits[8];
    long currentMaintenanceLimits[8];
    int TubeShrinkerport;
    bool HistoryGraphData;
    bool RemoteGraphData;
    int StartScreen;
    bool EnableModularFlag;
    bool Enable2DBarcodeFlag;
    PasswordEntry ModularPassword[PASSCOUNT];
    int PowerGraphSampleRatio;
    long GraphDataLen;
    float CalHightMaximumGauge;
    int CutoffMode;
    bool LockKeyFlag;
    bool FootPedalFlag;
};

struct Comm_Settings{
   long ControllerComNum;
   long ShrinkTubeComNum;
   long RemoteRecallComNum;
};

struct Maintenance_Configuration{
   int GenPower;
   int Amplitude;
   int TunePoint;
   int FrequencyOffset;
};



struct StoragePathsType{
    string sComputerName;
    string sErrMsgDestination;
    string sLocalPartPath;
    string sLocalSeqPath;
    string sCentralPartPath;
    string sCentralSeqPath;
};

enum CoolingMode{
   ENERGYMODE = -1,
   OFF = 0
};

struct System_Configuration{
   bool WidthEncoder;
   bool HeightEncoder;
   bool PressureRead;
   bool bseek;
   int RunMode;
   bool DailyHistory;
   bool Pressure2bar;
   bool AutoGet;
   bool Mm2Awg;
   int LockAlarm;
   bool Shrink;
//   Cooling As Boolean
//   CoolingEnergy As Boolean
   int SequenceError;
   int DoubleClick;
   int CoolingDur;
   int CoolingDel;
   int CoolingMode;
   int Machineflags[4];
   int StartScreen;
   int CutoffMode;
};



#define AMTECH_INI_FILE        "Amtech.bin" //StatusData is stored in this file

#define BRANSON_LASTWELD_FILE  "BransonLastWeld.bin" //Array DataCell() is stored in this file



class M10INI
{
public:
    // Variables used to Calculate Max Power in the IA and for Plotting the Weld Graph
    int Pwr_Prefix_Data[7];
    // Variables to check if Weld Data came into the comm port!
    bool WelderCycleComplete;
    bool ValidWeldData;
    bool PowerDataReady;
    int GlobalSignature;
    int Power_to_Watts;
    int *DataCell;
    int WeldPoints;

    //Used by form Activate routines to load language related help files
    string strPrimativeHelpFile;
    string strMaintenanceHelpFile;
    string strMenuHelpFile;
    string strAdminHelpFile;
    string strOptionsHelpFile;
    string strWireInsulatorHelpFile;
    string strFileManagerHelpFile;


    int Width_Konst;

    // Variables used in determining Horn Amplitude from the IA.
    bool AutoPreburst;
    //A development marker
    long AMTECH_DEBUG_MARKER;   //Used for locations and debugging

    bool DoAutoStartLastPart;

    Status_Data StatusData;
    Status_Data tempStatusData;         //Used by routines before an OK or Save
    Maintenance_Configuration TempMaintConfig;
    System_Configuration TempSysConfig;
    StoragePathsType StoragePaths;
    QString ConfigFilesPath;
private:
    void InitNoNetworkStorage(StoragePathsType PathStruct);
public:
    string MakeNWErrorPath(string CenComp);
    string MakeNWLocSeqPath(string WrkSta);
    string MakeNWSeqPath(string CenComp, string WrkSta);
    string MakeNWPartPath(string CenComp);
    void SetStoragePaths();
    void SetLanguageIndexer(long NewLanguage = 1);
    void GenerateSLFlagGroup(long Flaggroup, int Index);
    void Save_StatusData(bool WithUpdate = true);
    void Save_LastWeldGraph();
    void Init_StatusData();
    void SetSoftLimitDefaults(bool EnableSoftLimits = false);
    void SetShrinkTubeDefaults(Status_Data DataStruct);
    void SetDefaultWeldFormula(Status_Data DataStruct);
    void SetDefaultPassword();
    void ClearPasswordData();
    void Get_INI_File();
    void HelpFileLoader();
public:
    static M10INI* Instance();
protected:
    M10INI();
private:
    static M10INI* _instance;
public:
    ~M10INI(){} //do-nothing destructor
};

#endif // M10INI_H
