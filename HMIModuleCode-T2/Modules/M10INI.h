#ifndef M10INI_H
#define M10INI_H

#include <iostream>
#include <string>
#include <sstream>
#include "stdio.h"
#include "stdlib.h"
#include "M10definitions.h"
#include "Interface/SysConfiguration.h"
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


struct IAcominfo{
    long COMport;          //Stores the value of the Comm Port
    int BaudRate;          //Stores the setting for the Baud Rate of the comm port
};

enum SampleRatio{
    Ratio_1ms = 0,
    Ratio_5ms = 1,
    Ratio_10ms = 2
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
   int SequenceError;
   int DoubleClick;
   int CoolingDur;
   int CoolingDel;
   int CoolingTooling;
   int CoolingMode;
   unsigned short Machineflags[4];
   int StartScreen;
   int CutoffMode;
};



#define BRANSON_INI_FILE        "Branson.ini" //StatusData is stored in this file

class M10INI
{
public:
    enum ShrinkTubeIndex
    {
        STIunder = -2, //Marker
        STInone,
        STIR1,
        STIR2,
        STIR3,
        STIR4,
        STIR5,
        STIR6,
        STIR7,
        STIR8,
        STIR9,
        STIR10,
        STIover
    };

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

    Maintenance_Configuration TempMaintConfig;
    System_Configuration TempSysConfig;
    StoragePathsType StoragePaths;
    QString ConfigFilesPath;
private:
    void InitNoNetworkStorage(StoragePathsType PathStruct);
    void SetSoftLimitDefaults(Status_Data* _DataStruct, bool EnableSoftLimits = false);
    void SetShrinkTubeDefaults(Status_Data* _DataStruct);
    void SetDefaultPassword(Status_Data* _DataStruct);
    void SetAWGToMMTable(Status_Data* _DataStruct);
    void ClearPasswordData();
public:
    void SetDefaultWeldFormula(Status_Data* _DataStruct);
    string MakeNWErrorPath(string CenComp);
    string MakeNWLocSeqPath(string WrkSta);
    string MakeNWSeqPath(string CenComp, string WrkSta);
    string MakeNWPartPath(string CenComp);
    void SetStoragePaths();
    void SetLanguageIndexer(long NewLanguage = 1);
    void GenerateSLFlagGroup(long Flaggroup, int Index);
    void Save_LastWeldGraph();
    void Get_INI_File();
    void Init_StatusData();
    void Save_StatusData(bool WithUpdate = true);
    void HelpFileLoader();
    void Init_AWGToMMTable();
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
