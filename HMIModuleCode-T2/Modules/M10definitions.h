#ifndef M10DEFINITIONS_H
#define M10DEFINITIONS_H
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include <QString>
#include <QObject>
#include "UtilityDefine.h"
#include "Interface/Definition.h"
using namespace std;
//enum TubeShrinkermessages{
//    TubeShrinker_comError = -1,
//    TubeShrinker_nak,
//    TubeShrinker_ack,
//    TubeShrinker_timedOut,
//    TubeShrinker_UnknownMessage,
//};

enum TEACH_MODE_TYPE{
    Undefined,
    Standard,
    Auto,
    Sigma,
};

enum M10EXIT_ACTION{
    ShutdownM10exit,
    WindowsM10exit,
};

enum OPERATOR_SCREEN_WELD_INDICATOR{
    Low,
    Pass,
    High,
};

//enum MENUCLICKOPTION{
//    CreateSpliceScreen = 2,
//    CreateSeqScreen = 4,
//    EditScreen = 6,
//    SavePresetScreen = 8,
//    SavePresetAsScreen = 10,
//    FileManagerScreen = 12,
//    OperatorScreen = 14,
//    NewPresetScreen = 16,
//    NewSeqScreen = 18,
//    SetupScreen = 20,
//    TeachScreen = 22,
//    ConfigScreen = 24,
//    MaintScreen = 26,
//    AdminScreen = 28,
//    GraphScreen = 30,
//    StatScreen = 32,
//    ErrLogScreen = 34,
//    HistoryScreen = 36,
//    AboutScreen = 38,
//};

enum PWSDefinitions{
    PWSNotDefined,           //Button will not show in menu (CNTRL+Y shows button)
    PWSAdministrator,        //Administrator at least is required.
};

enum SpotDataNames{
    SDNEnergy,
    SDNWidth,
    SDNWeldPressure,
    SDNAmplitude,
    SDNTimeMax,
    SDNTimeMin,
    SDNPowerMax,
    SDNPowerMin,
    SDNPreHeightMax,
    SDNPreHeightMin,
    SDNHeightMax,
    SDNHeightMin,
    SDNTriggerPressure,
    SDNABdelay,
    SDNABduration,
    SDNPartCounter,
    SDNStopCounter,
    SDNSqueezeTime,
    SDNHoldTime,
    SDNModeFlags,        //--Not Used by Jim's Program !
    SDNHeightCal,        //--Calibrated Height
    SDNWidthCal,         //--Calibrated width Something new to Jim's Eprom's starting with the XL. Version 20.21
    SDNPreBurst,
    SDNCorrWidth,        //--Adjusted Width
    SDNCorrHeight,       //--Adjusted Height
    SDNWeldMode,         //--Weld Mode - Energy, Time, Height
    SDNAmplitude2,       //--Indexes for Amplitude Stepping
    SDNEnergy2Step,
    SDNTime2Step,
    SDNPower2Step,

    SDNEndFlag,
};

enum ActualIndexer{      //Indexes for Labels on Setup Screen
    AINEnergy = 1,
    AINTriggerPressure,
    AINWeldPressure,
    AINAmplitude,
    AINWidth,
    AINTime,
    AINPower,
    AINPreHeight,
    AINHeight,
    AINAmplitude2,        //Index for Actual value of Amplitude2
    //AINEndFlag

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

enum SCREEN_MODE{
    No_SCREEN = 0,
    Splash_SCREEN,           //For Initial Splash Screen
    About_SCREEN,            //About Software Form Dialog Screen
    Main_SCREEN,             //Main Menu Screen
    Error_SCREEN,            //Dialog Errors Screen
    Auto_Settings_SCREEN,    //Dialog Screen for Quality Settings used in Automatic Setup Mode
    Setup_SCREEN,            //When user changes Splice Data on the Run Screen
    IA_SCREEN,               //IA Settings Screen with Width and Height Corrections
    Jog_SCREEN,              //Maintence Screen the with the I/O Board shown.
    Run_SCREEN,              //Main Run Screen with File/Run/Actual Columns
    Graph_SCREEN,            //Weld Graph Dialog
    Stats_SCREEN,            //Stat's Screen for Time, Power, Pre-Height, Height
    Library_SCREEN,          //Create Screen (Part File Library)
    InputBox_SCREEN,         //Used when brought up by Library or Password Screen, KeyBoard Screen is a child of this Form
    Build_SCREEN,            //Build Screen were all splices are made
    Password_SCREEN,         //Password Screen Form
    Comm_SCREEN,             //Comport & BaudRate Screen under the Menu Screen
    Maintenance_SCREEN,      //Maintenance Log used to make a Log Entry
    Catalog_SCREEN,          //Catalog Screen used on Menu Screen & Next Button on the Run Screen
    Equip_SCREEN,            //Equipment Check Screen
    Keyboard_SCREEN,         //Keyboard Screen, brings up the AmTech Keyboard
    Login_SCREEN,            //Login Form, used for Password Validation
    Message_SCREEN,          //Message screen used mostly for E-Stop Warning
    Splice_Assy_SCREEN,      //Used for Splice Assembly Image Form during Run Mode
    Splice_Wiz_SCREEN,       //Splice Wizard called from the Library Screen.
    Splice_History_SCREEN,   //Splice History Screen"
    Advanced_SCREEN,
    Invalid_SCREEN,
    Operator_SCREEN,         //The first screen
    FileManager_SCREEN,      // New file manager
    PartsLoader_SCREEN,      // used when user wants to load one of existing sequence files
    EditWireChart_SCREEN,    //pops up on edit wire screen
    EditWire_SCREEN,
    EditSpliceSequence_SCREEN,
    Configuration_SCREEN,    //New Configuration Screen
    ShrinkMode_SCREEN,       //Shrink Mode
    SoftLimits_SCREEN,       //Soft Limits
    Administrator_SCREEN,    //Admin screen
    rename_SCREEN,           //rename Aux
    ErrorsLog_SCREEN,
    SavePreset_SCREEN,
    //New Added
    CreateNew_SCREEN,
    WorkOrderLibrary_SCREEN
};



//#define LISTVIEWTOP        108
//#define LISTVIEWLEFT       12
//#define LISTVIEWHEIGHT     541
//#define LISTVIEWWIDTH      973

#define Min_RunCount_Auto_Teach       15
#define Min_RunCount_Standard_Teach   1
#define Min_RunCount_Sigma_Teach      1
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

//Constant used to depict the latest Revision Code
#define DEFINEDREVCODE       0x04

#define AdminUsername        QObject::tr("ADMIN")
#define TechUsername         QObject::tr("TECH")

#define AVERSION_NUM_FILE "VersionNum.txt"
#define TESTVERSION       QObject::tr("-T5")
#define DESCRIPTION       QObject::tr("TEST VERSION")

//Administrator option flags
#define ADMINOButton         0x01
#define ADMINOShutdown       0x02
#define ADMINOPWrequired     0x04
#define ADMINOShowMaintData  0x08
#define ADMINOQualifiedOnly  0x10

enum M20_ERROR_TYPE{
    Non_ERR,
    EnergyERR,
    WidthERR,
    PressureERR,
    AmplitudeERR,
    TimeERR,
    PowerERR,
    PreHgtERR,
    HeightERR,
    ForceERR,
    OverloadERR,
    End_ERRORS_TYPE,
    UnspecifiedERR,
};

struct RecommendedData{
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

#define MAX_WIRE_ELEMENTS 20

struct M10Part{
    int RevCode;              //Amtech Revision Code for possible future use
    QString PartNo;          //Customer's Part Number
    //    string FileName;         //Keep file name here to update
    int FlagField;
    //    string CustRev;           //Customer Rev Code NOT USED ,for future use
    int Amplitude2;           //
    int EnergyToStep;         //
    long Area;                   //Area of part in mm*mm/100
    long PartsCnt;               //Accummulated total
    //  long RevDate;                 //Date of last rev, seconds from Jan 1, 1980
    int TimeToStep;           ////
    int PowerToStep;          ////
    int Energy;               //Energy in joules
    int Width;                //Width in mm/100
    int Pressure;             //Pressure in PSI
    int Amplitude;            //Amplitude in microns
    Qual Time;                    //Time limits in seconds/100
    Qual Power;                   //Power limits in percent
    Qual Preheight;               //Pre weld height limits in mm/100
    Qual Height;                  //Post weld height limits in mm/100
    Qual Force;                  //Force limits in Newtons
    int NoOfWires;            //Number of wires in this splice
    WireElement WireEl[MAX_WIRE_ELEMENTS];  //Store data for individual wires
    RecommendedData RecData;          //Recommended Data
    int TrigPres;             //PSI * 10
    int SqzTime;              //Secs * 100
    int FlagWord;             //Used for Weld Mode 0:energy,1:height,2:time
    int StopCount;
    int HoldTime;             //Secs * 100
    int ABDelay;              //Secs * 100
    int ABDur;                //Secs * 100
    int PreBurst;             //Secs * 1000
    int WidthCorr;
    int HeightCorr;
    //Added 30 June 2000 to accommodate the Raychem tube shrinker data
    long ShrinkTubeIndex;         //Raychem tube index (0 for None,1,2,3,3A,Other)
    float ShrinkTime;
    int ShrinkTemperature;    //In Centigrade degrees
    int PreviousFileNumber;
    int PresetTeachModeSetting;
    int TeachModequal_Window[ENERGY_ADJ];
    int StandardRunQuantity;
    int AutoRunQuantity;
    int SigmaRunQuantity;
    string PresetPicName;
    bool Unqualitied;
};

enum SoftLimitsIndex{
    SLIUpperControlLimit = 0,    //Based on the screen view of the data
    SLILowerControlLimit = 1,
    SLITime = 0,
    SLIPower = 1,
    SLIPreHeight = 2,
    SLIHeight = 3,
    SLIEND = 4,
};

#define SWP_NOMOVE 0x02
#define SWP_NOSIZE 0x01

struct VersionList{
    string SoftVersion;
    string ControllerVersion;
};

#define Run_File_Name  "run_file.dat"

//The IA receive interrupt parses these characters out of the data
#define IAcomfunctionENQ  0x05         //IA returns "U" when it receives ENQ

enum ShrnkTubeIndex{
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
    STIover         //Marker
};
enum AuxNames{
    Aux1,
    Aux2,
    Aux3,
    Aux4,
    AuxEND,
};

#define SEQ_MAX_SPLICES   250  //To hold 250 splices in one sequence, 0 - 249 places
#define MAX_PARTS         1500

struct Sequence_record{
    string PartName;             //For storing the Splice Part name in the Sequence
    QString FileName;             //For storing the Splice filename in the sequence changed by achal
    int Quantity;                //Number of welds for each part in the Splice
};

struct Sequence_Struct{
    int RevCode;                   //Revision Date not used by Jim.
    QString SequenceName;           //For storing the Sequence Part Name, in C/C++ this was a char array var.
    string FileName;               //For storing the Sequence File Name, in C/C++ this was a char array var.
    int NoOfParts;                 //No of Splice Parts in the Sequence
    Sequence_record record[SEQ_MAX_SPLICES];    //Record of the individual Splice Files in the Sequence
};

struct Sequence_recordrevTwo{
    string PartName;               //For storing the Splice Part name in the Sequence
    QString FileName;               //For storing the Splice filename in the sequence changed by achal
    int Quantity;                  //Number of welds for each part in the Splice
};

struct Sequence_StructrevTwo{
    QString SequenceName;             //For storing the Sequence Part Name, in C/C++ this was a char array var.
    string FileName;                 //For storing the Sequence File Name, in C/C++ this was a char array var.
    int NoOfParts;                   //No of Splice Parts in the Sequence
    long Rev_Date;                   //Revision Date not used by Jim.
    Sequence_recordrevTwo record[SEQ_MAX_SPLICES];    //Record of the individual Splice Files in the Sequence
};

#endif // M10DEFINITIONS_H
