#ifndef M2010_H
#define M2010_H

#include <iostream>
#include <string>
#include <sstream>
#include "stdio.h"
#include "stdlib.h"
#include "M10definitions.h"
#include "UtilityDefine.h"
#include "Interface/SysConfiguration.h"
using namespace std;

enum MACHINE_TYPE{
    None,
    Welder,
    WireSplicer,
};

struct ActuatorInfo{
    int CurrentActuatorType;
    int CurrentActuatorMode;
    int CurrentAntisideSpliceTime;
};

struct M20_run{
    bool Sequence_Done;        // Current Sequence is complete
    bool Pre_Hght_Error;       // Preheight error mode in progress
    bool Alarm_found;          // Alarm mode
    bool Save_Data;            // Allows data to be saved (automatically)
    bool Auto_Set_Mode;        // Autoset mode, limits not enforced
    bool BarcodeFlash;         // Bar code answer in progress (not implemented)
    bool SafetyFailed;         // Safety failure detected in progress
    int Sequence_Line;         // Currently running splice of a sequence
    int Part_Count;            // Current part count of splice
    QString Run_Splice;         // Filename of current splice
    string Seq_File_Name;
    bool Select_Part_file;
    bool Select_Seq_file;
    bool Load_From_Lib;        // Part File Loaded from Library
    bool Initial_Startup;      // Used only when the program first starts
    QString Run_Splice_Stat;    // File Name for Stat's for the current Part File
    bool GotoRun;
    bool E_Stop_Signal;        // Flag used when the User hits the E-Stop Button.
    bool Horn_Close;
    bool Gather_Close;
    bool Anvil_Clamped;
    bool Aux3On;
    bool Aux4On;
    bool Aux5On;
    bool CoolingOn;
    bool ToolingCoolingOn;
};

struct M20Build{
    bool Create_Part;         // New Splice file being created
    bool Create_Seq;          // New Sequence file being created
    string EditPartName;      // Variable to temporarily store the Part Names for Splices & Sequences
    string EditFileName;      //Variable to temporarily store the File Names for Splices & Sequences
    bool Edit_a_Splice;       //Variable to distinguish between editing a splice and starting from scratch in Unload_event()
    bool Edit_a_Seq;          //Variable used when editing a Sequence
    bool Edit_Seq_Run_Pos;
    bool Edit_Seq_Run_Qty;
    int Edit_Seq_Value;       //Variable to store the Run Quantity or Run Position from the Input Box
    bool KeyBoard_Vis;        //to tell if the Amtech Keyboard is on
};

#define WELDMMODEMASK      0x03
#define AMPSTEPMASK        0xE000
#define ENERGYSTEPMASK     0x8000
#define TIMESTEPMASK       0x4000
#define POWERSTEPMASK      0x2000

enum PRESET_TEACHSETTING{
    GLOBALS,
    SPECIAL,
};

struct BitFlag{
    bool SETUPdata;
    bool PRESETdata;
    bool WELDdata;
    bool PowerGraphData;
    bool HeightGraphData;
    bool SNdata;
    bool IOdata;
    bool SonicHitsData;
    bool PressureData;
    bool IOSWITCHdata;
    bool WELDDOWNLOADPARAMETERdata;
    bool WELDDOWNLOADdata;
    bool HeightData;
    bool WIDTHdata;
    bool MEMORYdata;
    bool POWERrating;
    bool STARTsignal;
    bool SEQUENCEtable;
    bool HORNamplitude;
    bool SYSTEMid;
    bool MAINTENANCEcounters;
    int AVAILABLE;
    bool IAFOUNDGOOD;
    bool TIMEOUTERROR;
    bool BADCHECKSUM;
    bool PresetTable;
    bool WireData;
    bool FootPadelDATA;
    bool ControllerVersionData;
    bool ControllerSerialNumData;
    bool ControllerPartNumData;
    bool CalibrationDone;
    bool HostReadyData;
    bool CalHeightMaxGaugeData;
    bool ActuatorVersionData;
    bool ActuatorSerialNumData;
    bool ActuatorPartNumData;
    bool ActuatorType;
    bool CutterResponseData;
    bool ReliabilityModeData;
    bool CoolingTypeData;
    bool LockOnAlarmData;
    bool MachineFlagsData;
    bool TunePointData;
    bool FreqOffsetData;
    bool PNData;
};

enum Last_made{
    None_Made,
    Splice_Made,
    Sequence_Made,
};

struct M10PartRevThree{
    int RevCode;              //Amtech Revision Code for possible future use
    QString PartNo;           //Customer's Part Number
    //    string FileName;         //Keep file name here to update
    int FlagField;
    //    string CustRev;           //Customer Rev Code NOT USED ,for future use
    int Amplitude2;           //
    int EnergyToStep;         //
    long Area;                   //Area of part in mm*mm/100
    long PartsCnt;                //Accummulated total
    //  long RevDate;                 //Date of last rev, seconds from Jan 1, 1980
    int TimeToStep;           ////
    int PowerToStep;          ////
    int Energy;               //Energy in joules
    int Width;                //Width in mm/100
    int Pressure;             //Pressure in PSI
    int Amplitude;            //Amplitude in microns
    Qual Time;                    //Time limits in seconds/100
    Qual Power;                  //Power limits in percent
    Qual Preheight;               //Pre weld height limits in mm/100
    Qual Height;                  //Post weld height limits in mm/100
    Qual Force;                   //Force limits in Newtons
    int NoOfWires;            //Number of wires in this splice  
    RecommendedData RecData;       //Recommended Data
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
};

struct M10PartRevTwo{
    int RevCode;              //Amtech Revision Code for possible future use
    QString PartNo;          //Customer's Part Number
    //    string FileName;         //Keep file name here to update
    int FlagField;
    //    string CustRev;           //Customer Rev Code NOT USED ,for future use
    int Amplitude2;           //
    int EnergyToStep;         //
    long Area;                   //Area of part in mm*mm/100
    long PartsCnt;                //Accummulated total
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
    Qual Force;                   //Force limits in Newtons
    int NoOfWires;            //Number of wires in this splice
    RecommendedData RecData;       //Recommended Data
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
};



struct PresetTeachModeSettings{
    int PresetTeachModeSetting;
    int TeachModequal_Window[ENERGY_ADJ];
    int StandardRunQuantity;
    int AutoRunQuantity;
    int SigmaRunQuantity;
};

//This structure will replace all previous sequence structures
struct SequenceDataStruct{
    string sSeqName;
    int iListCount;                 //This is a convenience
    string* sPartName;
    int iPartCount[];               //This will be 1 for at least a while
};

enum EDITTASKS{
    EDITTASKnone,
    EDITTASKedit,
    EDITTASKabort,
    EDITTASKaddPart,
    EDITTASKremovePart,
};

struct SEQUENCE_ENTRY_DATA{            //Variable used for temporialy holding the Current selected Splice for entry into
    string PartName;                    //A sequence catalog
    string FileName;
    int RunQuanity;
    int Position;
    EDITTASKS task;
};



struct ErrMsgStruct{
    string ErrType;
    string ErrItem;
};

class M2010
{
public:
    ActuatorInfo TempActuatorInfo;
    MACHINE_TYPE Machine;
    int Shim2MAx;
    int Shim1Val;
    int Shim2Val;
    long LanguageNumber;
    long LanguageIndexer;
    bool WeldDone;

    M20_run M10Run;
    M20Build M10Build;

    long MaintenceCounter;
    long MaintenceDueCounter;
    int AdjHeight;
    int AbsHeight;
    int ACV;
    int ACTap;
    int ACmax;
    int ACmin;

    bool IAready;
    bool PresetChanged;
    M10Part TempPreset;
    bool SaveAsFlag;
    bool UseTempStsFile;

    SCREEN_MODE Prog_Mode;
    SCREEN_MODE Child_Mode;
    // made for usage in Auto Teach mode
    SCREEN_MODE PreviousScreen_Prog_mode;
    SCREEN_MODE InputBox_Mode;

    bool SpliceAssyVis;
//    CommandButton CurrentTextBox;

    BitFlag ReceiveFlags;
    BitFlag SendFlags;

    string Run_Option;

    long PortNum;           //Stores the value of the Comm Port
    int BaudRate;       //Stores the setting for the Baud Rate of the comm port
    bool CableFound;

    bool CommError;
    int LineVoltage;    //Stores the Line Voltage

    int AcTapMax;
    int AcTapMin;

    unsigned char ArrayOfBytes[];
    string RunFilePart;

    bool BaseColorFlag;
    bool BandOneFlag;
    bool BandTwoFlag;
    bool BandThreeFlag;

    int SpliceFileCount, SequenceFileCount;
    string *sPARTFILES;
    string *sPARTNAMES;
    string *sSEQFILES;
    string *sSEQNAMES;

    M10Part Splice;

    PresetTeachModeSettings PresetTeachSettings;

    string WireName[MAX_WIRE_ELEMENTS];
    bool StartFromNew;

    Sequence_StructrevTwo EditSequencerevTwo;
    Sequence_StructrevTwo Seq_FilerevTwo;

    Sequence_Struct EditSequence;
    Sequence_Struct Seq_File;

    SequenceDataStruct SequenceData;

    SEQUENCE_ENTRY_DATA SequenceEntryData;

    M10Part OriginalSplice;
    string OldPrtName;
private:
    void MakeDefaultSplice(M10Part SpliceName);
public:
    void LoadSequenceData(string sSeqName, bool bFailedLoad, bool bIgnoreParts = false);
    void GetLastRunRecord();
    void PutLastRunRecord(int TypeMade, QString PartName);
    void MakeNormalSplice(M10Part ThisSplice);
    int DecPtrCircular(int ptr, int ptrMAX);
    int IncPtrCircular(int ptr, int ptrMAX);
    void ConvertPowerGraphData(QStringList SourceGraphDataList, QList<int> *DestList);
    void ConvertHeightGraphData(QStringList SourceGraphDataList, QList<int> *DestList);
    QString ParseSerialNumber(QString SerialCode);
    string GetResString(long StringNo);
    void NumberOnly(int KeyAscii);
    void load_splice_file();
    void SpliceData2IA();
    void UpdateIAfields();
    void ReZeroSpliceData();
    void UpdateSpliceData();
    void UpdateThisSplice(M10Part ThisSplice);
    void SendNWmsgStruct(ErrMsgStruct MsgStruct[]);
    void SendNWmsg(string sErrPart, string sErr);
    void LoadSpliceFile(QString sPartDescription, M10Part PartDest);
    void SaveSpliceFile(bool bUpdateRun = true, bool SaveOriginalSplice = false);
    int MakeIntEven(int DataIn, bool RoundDown = false);
    void UpdateRevCode(string sFilePath, M10Part PartDest, int PrtRevCode);
    int GetTeachModeRunCount();
    void CopyPartRevThree(M10PartRevThree PartDestRevThree, M10Part PartDest);
    void CopyPartRevTwo(M10PartRevTwo PartDestRevTwo, M10Part PartDest);

public:
    static M2010* Instance();
protected:
    M2010();
private:
    static M2010* _instance;
public:
    ~M2010(){} //do-nothing destructor
};

#endif // M2010_H
