#ifndef M102IA_H
#define M102IA_H
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include "m10definitions.h"
#include <QObject>
using namespace std;

#define IAPRESET0  0x8000

enum AuxSubCommand{
    DO_AUX1_OFF = 1,        //0x01
    DO_AUX1_ON,             //0x02
    DO_CLOSE_CLAMP,         //0x03
    DO_OPEN_CLAMP,          //0x04
    DO_CLOSE_SAFETY,        //0x05
    DO_OPEN_SAFETY,         //0x06
    DO_COOLING_ON,          //0x07
    DO_COOLING_OFF,         //0x08
    DO_AUX3_ON,             //0x09
    DO_AUX3_OFF,            //0x0A
    DO_AUX4_ON,             //0x0B
    DO_AUX4_OFF,            //0x0C
    DO_SONICS_ON,           //0x0D
    DO_SONICS_FULL,         //0x0E
    DO_SONICS_OFF,          //0x0F
    DO_AUX5_ON,             //0x10
    DO_AUX5_OFF,            //0x11
};

enum ACTIONMODE{
    No_Axn,
    Delete_Axn,
    DeleteApp_Axn,
    CopyTo_Axn,
    CopyFrom_Axn,
    MoveTo_Axn,
    MoveFrom_Axn,
};

//Data from the IA is sent via Intel hex strings
struct INTELhexRECORD{
   int Count;                 //     First byte
   unsigned short Address;              //     2 bytes, big endian address
   unsigned char RecordType;            //     1 byte
   char ByteData[32];          //     0 to 32 bytes as data
   char CheckSum;              //     Last byte
};

struct QualWindow{
   int min;
   int max;
};

// Data as it is returned from the IA (IA, not IA98)
struct WELDSETTINGS{
   int ModeFlags;
   int Energy;
   int Width;
   int WeldPressure;
   int TriggerPressure;
   int Amplitude;
   int SqueezeTime;
   QualWindow Time;
   QualWindow Power;
   QualWindow Preheight;
   QualWindow Height;
   int PartCounter;
   int StopCount;
   int HoldTime;
   int ABDelay;
   int ABDuration;
   int Amplitude2;           // Amplitude2 used for Amp Stepping
   QString PartName;
   int EnergyToStep;         // Energy Step used for Amp Stepping
   int TimeToStep;           // Time Step used for Amp Stepping
   int PowerToStep;          // Power Step used for Amp Stepping
};

struct WELDdata{
   QString Reserved;          // Internal Data
   int Energy;               // Energy in Joules
   int Width;                // Width in 1/100mm's
   int Time;                 // Time in 5 millisecond counts
   QString PeakPowerPer;
   int Power;                // Peak power in Watts
   int Preheight;            // Last Preheight that sonics fired
   int Amplitude;            // Amplitude in microns
   int Height;               // Height after weld - Post Height in 1/100mm's
   int Amplitude2;           // Value of Amp 2 received from Controller
   int PPHeight;             // Pre Height before sonics fired
   int Pressure;             // Weld Pressure, Uses Transducer if IN
   int TPressure;            // Weld Trigger Pressure.
   long Alarmflags;          // To store errors
   QString PowerGraph;
   QString HeightGraph;
};


struct IOinfo{
   unsigned long IO;                  // Inputs / Outputs  bitflag structure shown above
   long IO2;                 // VELEZ040811
   int AdjHeight;            // Height with zero and pressure adjustments
   int AbsHeight;            // Height encoder reading, no adjustments
   int ACV;                  // AC Line Voltage
   int ACTap;                // AC transformer tap setting
   int ACmax;                // AC tap + 15%
   int ACmin;                // Ac tap - 15%
};

//Data from the FootPedal
struct LASTIOSWITCHS{
   QString ByteData[2];
   int WordData;
   long IO;
   long IO2;                 // VELEZ040811
};

#define M10_WIDTH_TOL 10  // .01mm per count

struct SpliceFileData{
    int Energy;
    int Width;
    int Pressure;
    int Amplitude;
    Qual Time;
    Qual Power;
    Qual Preheight;
    Qual Height;
    Qual Force;
};

// Mode flag bits used in IAsetupStructure.ModeFlags
#define WMFweld2Hgt       0x01       //     Weld to Height
#define WMFweld2Tme       0x02       //     Weld to Time
#define WMFulAlarms       0x04       //     Unlatch Alarms
#define WMFulOvrLd        0x08       //     Unlatch Overload Alarms
#define WMFprnwld         0x100      //     Print after weld
#define WMFprnLine        0x200      //     Print line data (only)
#define WMFprnAlrms       0x400      //     Print after alarms (only)

// IA header record identification
enum IASig{
    IASigEmpty,             //0x00
    IASigSetup,             //0x01
    IASigPresetTable,       //0x02
    IASigWeld,              //0x03
    IASigPower,             //0x04
    IASigSerialNumber,      //0x05
    IASigIO,                //0x06
    IASigSonicHits,         //0x07
    IASigPressure,          //0x08
    IASigIOswitch,          //0x09
    IASigAbortEnable,       //0x0A   Abort button in case of double hit
    IASigHistoryPar,        //0x0B   Weld Down Loaded Parameter Data
    IASigMemory,            //0x0C
    IASigHeight,            //0x0D
    IASigWidth,             //0x0E
    IASigPWRrating,         //0x0F   Power Rating
    IASigSequenceTable,     //0x10
    IASigHornAmplitude,     //0x11
    IASigSystemID,          //0x12
    IASigMaintCount,        //0x13   Maintence counter
    IASigPresetData,        //0x14   IA98 added signature, Data for a single preset
    IASigMachineFlags,
    IASigRunMode,           //0x16
    IASigActuator,          //0x17
    IASigWidthZero,         //0x18
    IASigHeightZero,        //0x19
    IAsigCooling,           //0x1A
    IASigDataLockOnAlarm,   //0x1B
    IASigDataMaintCntr,     //0x1C
    IASigDataCycleCntr,     //0x1D
    IASigCommError,         //0x1E
    IASigControllerVer,     //0x1F
    IASigReadPower,         //0x20
    IASigDATADOUBLECLICK,   //0x21
    IASigDownSpeed,         //0x22
    IASigHeightCal,         //0x23
    IASigHostReadyStatus,   //0x24
    IASigMaximumGauge,      //0x25
    IASigTunePoint,         //0x26
    IASigCutoff,            //0x27
    IASigFrequencyOffset,   //0x28
    IASigActuatorVer,       //0x29
    IASigActuatorPartNum,   //0x2A
    IASigActuatorSerialNum, //0x2B
    IASigResetReady,        //0x2C
    IASigHeightGraph,       //0x2D
    IASigReliablityMode,    //0x2E
    IASigPhysicalKeyMode,   //0x2F
    IASigEnd,               //Identifies end of Enum
    IASigMax = IASigEnd - 1,     //Used by functions to test for limit
};

//#define IA98System 1
// IA command list
// Edited 6 Feb 2001 to include IA98 Commands (Odd numbered items)
enum IACommands{

#ifdef IA98System
   IAComSendPreset            = 7,
   IAComSavePreset            = 9,
   IAComClearPresets          = 13,
   IAComSetIA98System         = 17,
#endif

    IAComSetM10Mode            = 2,
    IAComSendSerialNumber      = 4,
    IAComSendSetup             = 6,
    IAComSendPresetTable       = 8,    //Sends names and numbers in IA98
    IAComSendWeldData          = 10,
    IAComSendPowerGraph        = 12,
    IAComSetACtap              = 14,
    IAComSendIOdata            = 16,
    IAComHornOpen              = 18,
    IAComHornClose             = 20,
    IAComAux1Open              = 22,
    IAComAux1Close             = 24,
    IAComSetGenPWR             = 26,
    IAComCoolAirOn             = 28,
    IAComCoolAirOff            = 30,
    IAComSigLightOn            = 32,
    IAComSigLightOff           = 34,
    IAComSigLightBlink         = 36,
    IAComSendSonicHits         = 38,
    IAComSendPressure          = 40,
    IAComSetRunMode            = 42,
    IAComSetPressure           = 44,
    IAComSetAmplitude          = 46,
    IAComSetPreburst           = 48,
    IAComHeightZero            = 50,
    IAComSendMemory            = 52,
    IAComSendHeights           = 54,
    IAComSendWidths            = 56,
    IAComSendPWRrating         = 58,
    IAComClrM10mode            = 60,
    IAComClrAlarms             = 62,
    IAComHostReady             = 64,
    IAComSetCoolTime           = 66,
    IAComCalHeight             = 68,
    IAComRecallPreset          = 70,
    IAComSendSequenceTable     = 72,
    IAComRunSequence           = 74,
    IAComSetBaudRate           = 76,
    IAComSetWidth              = 78,
    IAComAuxMotion             = 80,
    IAComSendHornAmplitude     = 82,
    IAComSendSystemID          = 84,
    IAComSendMaintCounters     = 86,
    IAComSetMainDueCounter     = 88,
    IAComRstMaintCounter       = 90,
    IAComCalWidth              = 92,
    IAComSetTunePoint          = 93,
    IAComGetTunePoint          = 94,
    IAComSetMachineFlags       = 96,  //0x60
    IAComGetMachineFlags       = 97,  //0x61
    IAComSetRunModeNew         = 98,  //0x62
    IAComGetRunModeNew         = 99,  //0x63
    IAComSetActuator           = 100, //0x64
    IAComgetActuator           = 101, //0x65
    IAComSetWidthZero          = 102, //0x66
    IAComGetWidthZero          = 103, //0x67
    IAComSetHeightZero         = 104, //0x68
    IAComGetHeightZero         = 105, //0x69
    IAComSetCooling            = 106, //0x6A
    IAComGetCooling            = 107, //0x6B
    IAComSetGenPower           = 108, //0x6C
    IACOMWeldAbort             = 109, //0x6D
    // Reserved                = 109, //0x6D,
    IAComSetLockonAlarm        = 110, //0x6E
    IAComGetLockonAlarm        = 111, //0x6F
    IAComClearBBR              = 112, //0x70
    IAComSystemRestart         = 113, //0x71
    IAComSetMotor              = 114,
    IAComSetHornCalibAmplitude = 118,
    IAComGetMaintCntr          = 119, //0x77
    IAComClearMaintCntr        = 120, //0x78
    IAComGetCycleCntr          = 121, //0x79
    IAComClearCycleCntr        = 122, //0x7A
    IAComGetControllerVer      = 123, //0x7B
    IAComBeep                  = 124, //0x7C
    IAComReadPower             = 125, //0x7D
    IADownSpeedofHorn          = 126, //0x7E
    IAAmpStepParameters        = 127, //0x7F
    IAComSetMaximumGauge       = 128, //0x80
    IAComGetMaximumGauge       = 129, //0x81
    IAComSetCutoff             = 130, //0x82
    IAComGetCutoff             = 131, //0x83
    IAComSetFrequencyOffset    = 132, //0x84
    IAComGetFrequencyOffset    = 133, //0x85
    IAComGetActuatorVer        = 134, //0x86
    IAComGetActuatorPartNum    = 135, //0x87
    IAComGetActuatorSerialNum  = 136, //0x88
    IAComSendHeightGraph       = 137, //0x89
    IAComLim,
    IAComEnd                   = IAComLim - 1,
};

struct GraphData
{
    QStringList GraphDataList;
    int         TotalFrame;
    int         CurrentIndex;
};

class M102IA : public QObject
{
    Q_OBJECT
private:
    INTELhexRECORD hexRecord;
public:
    int CalibHeight;
    int OpenChkHeight;
    double RawHeight;
    int DownSpeed;
    int CalibHeightMaxGauge;
    bool EnableAbortButton1;

    GraphData RawPowerDataGraph;
    GraphData RawHeightDataGraph;

    ACTIONMODE ActDone;

    //Variable Flag if an Error is found
    bool ErrorFound;

    int IACommandError;


    // IAsetup is used to tranfer setup data back and forth to the IA
    WELDSETTINGS IAsetup;
    // IAactual receives weld data from  IA
    WELDdata IAactual;


    int PWRpoints;

    //String Variable to hold IA Serial #
    QString SerialNoData;                //not used now
    int HeightCalResult;
    QString ContollerVersion;            //To store controller's software version no.
    QString ActuatorVersion;
    QString ActuatorPartNum;
    QString ActuatorSerialNum;

    IOinfo IOstatus;
    IOinfo LastIOstatus;

    LASTIOSWITCHS LastIOSwitchData;

    int HEIGHTbuffer[3];
    //HEIGHTbuffer[0] = Real Height (Adjusted for zero and pressure)
    //HEIGHTbuffer[1] = Absolute Height (Raw read of encoder)
    //HEIGHTbuffer[2] = Relative Height (Raw read minus zero position)

    int WIDTHbuffer[2];
    //WIDTHbuffer[0] = Relative width (Raw read minus zero position) - ACTUAL WIDTH
    //WIDTHbuffer[1] = Absolute width (Raw read of encoder)

    int PressureRead;
    QString SonicHitsStrData[4];
    QString SonicHitsData;

    long MaintenanceCounter;
    long MaintenanceDueCounter;
    double EnergyAccumulator;
    double EnergyMaintenanceDue;
    int ADPower;

    QString IAdataSignature;

    //Records as they come in
    QString HexLine;
    QString IAstructure;

    QString OutStructure;
private:
    void PackHexRecord();
    void SetHighByte(int ByteNo, unsigned short Data);
    void SetLowByte(int ByteNo, unsigned short Data);
    void LittleEndianWord(int HighByte, unsigned short Data);

public:
    void Generate_Beep(int BeepTime = 100);
    void HexLineCheck(QString HexLineData, bool &HexLineFlag);
    void HexLineBufferCheck(QString InputLine);

    char MakeHexNibble(int InNumber);
    QString MakeHexByte(unsigned char InNumber);
    QString MakeHexWord(int InNumber);
    void IACommand(IACommands CommandNumber, int SimNo = 0);
    void SendIACommand(IACommands CommandNumber, int CommandData);
    int MakeHexNibbleNumber(char HexNibble);
    int MakeHexByteNumber(QString HexByte);
    int MakeHexWordNumber(QString HexWord);
    long MakeHexWordNumberLong(QString HexWord);
    void MakeMemoryString(string InputHexString, string &OutputHexString);
    void GetCstringFromHex(string InputString,string &OutputString, int Start, int CharCount);
    long GetLongValue(QString InputString,int Ref);
    int ParseHexStructure(QString HexString, int tmpDataSignature);
    bool SetIAWidth(int WidthSet = -1, bool SettingCheck = true);
    void CheckIAControl();
    void SendCommandData(int CommandData);
    bool SendCommandSetRunMode(int CommandData);
    void SendPresetToIA(int PresetNo);
    bool WaitForResponseAfterSent(int TimeOut = 3000, bool *CheckResponseFlag = NULL);
signals:
    void WeldCycleSignal(bool &_status);
    void AlarmStatusSignal(bool &_status);
    void HeightGraphSignal(bool &_status);
    void PowerGraphSignal(bool &_status);
    void PhysicalKeySignal(bool & _status);
public:
    static M102IA* Instance();
protected:
    M102IA(QObject *parent = 0);
private:
    static M102IA* _instance;
public:
    ~M102IA(){} //do-nothing destructor
};

#endif // M102IA_H
