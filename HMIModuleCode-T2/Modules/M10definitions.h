#ifndef M10DEFINITIONS_H
#define M10DEFINITIONS_H
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include <QString>
#include <QObject>
#include "UtilityDefine.h"
#include "Interface/WireElement.h"
using namespace std;
//enum TubeShrinkermessages{
//    TubeShrinker_comError = -1,
//    TubeShrinker_nak,
//    TubeShrinker_ack,
//    TubeShrinker_timedOut,
//    TubeShrinker_UnknownMessage,
//};


enum M10EXIT_ACTION{
    ShutdownM10exit,
    WindowsM10exit,
};

enum OPERATOR_SCREEN_WELD_INDICATOR{
    Low,
    Pass,
    High,
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

//Constant used to depict the latest Revision Code
#define DEFINEDREVCODE       0x04

#define AdminUsername        QObject::tr("ADMIN")
#define TechUsername         QObject::tr("TECH")

#define VERSION_NUM_FILE "VersionNum.ini"
#define AWG2MM_TABLE_FILE "AWG2AreaTable.ini"
#define TESTVERSION       "-T5"
#define DESCRIPTION       "TEST VERSION"

//Administrator option flags
#define ADMINOButton         0x01
#define ADMINOShutdown       0x02
#define ADMINOPWrequired     0x04
#define ADMINOShowMaintData  0x08
#define ADMINOQualifiedOnly  0x10

#define POWERFACTOR (3 * 0xFFFF / 4)

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

//#define HWND_TOPMOST   -1
//#define HWND_NOTOPMOST -2

//#define SWP_NOACTIVATE 0x10
//#define SWP_SHOWWINDOW 0x40

//#define SWP_NOMOVE 0x02
//#define SWP_NOSIZE 0x01
//#define FLAGS  (SWP_NOMOVE | SWP_NOSIZE)

//#define Run_File_Name  "run_file.dat"

//The IA receive interrupt parses these characters out of the data
#define IAcomfunctionENQ  0x05         //IA returns "U" when it receives ENQ

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
