#include "M10INI.h"
#include "Password.h"
#include "M2010.h"
#include "Interface/interface.h"
#include "UtilityClass.h"
#include <QDir>
#include <QFile>
#include <QDataStream>
#include <windows.h>
#include <QObject>
M10INI* M10INI::_instance = 0;
M10INI* M10INI::Instance()
{
    if(_instance == 0){
        _instance = new M10INI();
    }
    return _instance;
}

M10INI::M10INI()
{
    DataCell = 0;
}
/************************************************************/
/***********************FIXED********************************/
/************************************************************/
void M10INI::InitNoNetworkStorage(StoragePathsType PathStruct)
{
//    Previously used for Network Enabled version
//    Need To clean up.
    const int MAX_BUFFER_LEN = 33;
    wchar_t ThisComputerName[MAX_BUFFER_LEN];
    string NameStr;
    DWORD iNameLen = MAX_BUFFER_LEN;
    bool SuccessFlag;

    PathStruct.sComputerName = "";
//    While computer name is not required if not in network mode,
//    it is required to initialize the network mode when selected
    SuccessFlag = GetComputerName(ThisComputerName, &iNameLen);
    if (SuccessFlag == true)
    {
        char *Buffer = new char[MAX_BUFFER_LEN];
        WideCharToMultiByte(CP_OEMCP,0,ThisComputerName,-1,Buffer,MAX_BUFFER_LEN, NULL,FALSE);
        NameStr = Buffer;
        delete []Buffer;

        PathStruct.sComputerName = NameStr;
    }
//        Initialize to no network
        PathStruct.sErrMsgDestination = "";
        PathStruct.sLocalPartPath = "c:\\AmtData\\Apart\\";   //Always the same
        PathStruct.sLocalSeqPath = "c:\\AmtData\\Aseq\\";     //Could change for networking
        PathStruct.sCentralPartPath = "";
        PathStruct.sCentralSeqPath = "";
}

string M10INI::MakeNWErrorPath(string CenComp)
{
    string tmpStr; //= "\\" & trim(CenComp) & "\A0MsgCtr\";
    return tmpStr;
}

string M10INI::MakeNWLocSeqPath(string WrkSta)
{
    string tmpStr; //"c:\AmtData\" & Trim(WrkSta) & "\"
    return tmpStr;
}

string M10INI::MakeNWSeqPath(string CenComp, string WrkSta)
{
    string tmpStr; //"\\" & Trim(CenComp) & "\AmtData\" & Trim(WrkSta) & "\"
    return tmpStr;
}

string M10INI::MakeNWPartPath(string CenComp)
{
    string tmpStr; //= "\\" & Trim(CenComp) & "\AmtData\" & StoragePaths.sComputerName & "\"
    return tmpStr;
}

/************************************************************/
/**************************FIXED*****************************/
/************************************************************/
void M10INI::SetStoragePaths()
{
//    Previously used for Network Enabled version
//    Need To clean up.
//    With StoragePaths
    InitNoNetworkStorage(StoragePaths);
//    End With
}

/**************************************************************/
/*************************FIXED********************************/
/**************************************************************/
void M10INI::SetLanguageIndexer(long NewLanguage)
{
//    Setlanguage indexer into resource file, default is English
    M2010 *ptr_M2010 = M2010::Instance();
    ptr_M2010->LanguageNumber = NewLanguage;
    ptr_M2010->LanguageIndexer = 2000 * (ptr_M2010->LanguageNumber - 1);
}

void M10INI::GenerateSLFlagGroup(long Flaggroup, int Index)
{

}

void M10INI::Save_StatusData(bool WithUpdate)
{
    //Saves temp data into data and stores the file
    UtilityClass* ptr_Utility = UtilityClass::Instance();
    M2010* ptr_M2010 = M2010::Instance();
    if (WithUpdate == true)
        StatusData = tempStatusData;
    else
        tempStatusData = StatusData;

    ptr_Utility->WriteToBinaryFile(&StatusData, ConfigFilesPath + AMTECH_INI_FILE);

    switch (StatusData.MachineType)
    {
    case ACTULTRA20: ACTULTRA40: ACTMTS20: ACTGUN40:
        ptr_M2010->Machine = Welder;
        break;
    default:
        ptr_M2010->Machine = WireSplicer;
    }

}

void M10INI::Save_LastWeldGraph()
{

}

/******************************************************/
/************************FIXED*************************/
/******************************************************/
void M10INI::Init_StatusData()
{
    StatusData.StartScreen = Operator_SCREEN;

    StatusData.Soft_Settings.Lang_Support = ENGLISH_lang;
    StatusData.Soft_Settings.Horn_Calibrate = MAXAMPLITUDE;
    StatusData.Soft_Settings.AutoPreburst = 0;
    StatusData.Soft_Settings.AutoGetNext = false;
    StatusData.Soft_Settings.SonicGenWatts = 4000; // newsplicer 4000w, others we can set 3300w
    StatusData.Soft_Settings.ToolCoverIgnore  = true;
    StatusData.Soft_Settings.NoToolCover4SU = true;
    StatusData.Soft_Settings.Pressure2Unit = ToPSI;
    StatusData.Soft_Settings.PWWidth2Height = 0;
    StatusData.Soft_Settings.MinAmplitude = MINAMPLITUDE;
    StatusData.Soft_Settings.MinPressure = MINWELDPRESSURE;
    StatusData.Soft_Settings.WeldFormula = WeldFormulaAmtechStandard;
    StatusData.Soft_Settings.RunCount = 10;
    StatusData.Soft_Settings.Teach_Mode = Sigma;
    StatusData.Soft_Settings.TunePoint = 40;
    StatusData.Soft_Settings.FrequencyOffset = 50;

    StatusData.Cust_Data.mod10a_settings.UnsignedWeldData = 4097;
    StatusData.Cust_Data.mod10a_settings.AfterBurstDelay = 10;
    StatusData.Cust_Data.mod10a_settings.AfterBurstDuration = 20;
    StatusData.Cust_Data.mod10a_settings.EnergyWindowPL = 50;
    StatusData.Cust_Data.mod10a_settings.PreBurstIndex = 0;
    StatusData.Cust_Data.cust_qual_range[TIME_PLRG] = 40;
    StatusData.Cust_Data.cust_qual_range[TIME_MSRG] = 40;
    StatusData.Cust_Data.cust_qual_range[POWER_PLRG] = 25;
    StatusData.Cust_Data.cust_qual_range[POWER_MSRG] = 25;
    StatusData.Cust_Data.cust_qual_range[PRE_HGT_PLRG] = 15;
    StatusData.Cust_Data.cust_qual_range[PRE_HGT_MSRG] = 15;
    StatusData.Cust_Data.cust_qual_range[HEIGHT_PLRG] = 10;
    StatusData.Cust_Data.cust_qual_range[HEIGHT_MSRG] = 10;
    StatusData.Cust_Data.cust_qual_range[FORCE_PLRG] = 5;
    StatusData.Cust_Data.cust_qual_range[FORCE_MSRG] = 10;
    for(int i = TIME_CONFRG_PL; i <= HEIGHT_CONFRG_MS; i++)
    {
        StatusData.Cust_Data.cust_qual_range[i] = 4;
    }
    StatusData.Cust_Data.cust_qual_range[ENERGY_ADJ] = 280;
    StatusData.Cust_Data.cust_qual_range[PRESSURE_ADJ] = 30;
    StatusData.Cust_Data.cust_qual_range[AMPLITUDE_ADJ] = 26;
    StatusData.Cust_Data.cust_qual_range[WIDTH_ADJ] = 625;
    //Now store the new file data

    for(int i = TIME_USL; i<= HEIGHT_LSL; i++)
    {
        StatusData.HSDATA.HARD_LIMIT[i].TypeHS = 0;
        StatusData.HSDATA.HARD_LIMIT[i].ValueHS = 4;
        StatusData.HSDATA.SOFT_LIMIT[i].TypeHS = 1;
        StatusData.HSDATA.SOFT_LIMIT[i].ValueHS = 30;
    }

    StatusData.Wire_Info.No_of_Wires = 10;
    StatusData.Wire_Info.WireEntries[1].Wire_Area = 22;
    StatusData.Wire_Info.WireEntries[1].Wire_Ref_Ga = "24";
    StatusData.Wire_Info.WireEntries[2].Wire_Area = 35;
    StatusData.Wire_Info.WireEntries[2].Wire_Ref_Ga = "22";
    StatusData.Wire_Info.WireEntries[3].Wire_Area = 50;
    StatusData.Wire_Info.WireEntries[3].Wire_Ref_Ga = "20";
    StatusData.Wire_Info.WireEntries[4].Wire_Area = 75;
    StatusData.Wire_Info.WireEntries[4].Wire_Ref_Ga = "18";
    StatusData.Wire_Info.WireEntries[5].Wire_Area = 100;
    StatusData.Wire_Info.WireEntries[5].Wire_Ref_Ga = "16";
    StatusData.Wire_Info.WireEntries[6].Wire_Area = 200;
    StatusData.Wire_Info.WireEntries[6].Wire_Ref_Ga = "14";
    StatusData.Wire_Info.WireEntries[7].Wire_Area = 250;
    StatusData.Wire_Info.WireEntries[7].Wire_Ref_Ga = "";
    StatusData.Wire_Info.WireEntries[8].Wire_Area = 500;
    StatusData.Wire_Info.WireEntries[8].Wire_Ref_Ga = "10";
    StatusData.Wire_Info.WireEntries[9].Wire_Area = 800;
    StatusData.Wire_Info.WireEntries[9].Wire_Ref_Ga = "8";
    StatusData.Wire_Info.WireEntries[10].Wire_Area = 1000;
    StatusData.Wire_Info.WireEntries[10].Wire_Ref_Ga = "";
    StatusData.ComInfo.COMport = 2;
    StatusData.ComInfo.BaudRate = 1152;
    StatusData.MachineType = ACTULTRA20; //Need To Fix
    StatusData.MachineDate = "";
    StatusData.Machineflags[0] = 0;
    StatusData.KeepDailyHistory = false;
    StatusData.Mm2Awg = false;
    StatusData.LockonAlarm = 0;
    StatusData.RunMode = 0;
    StatusData.AdminOptions = 0x00;
    StatusData.WeldSettingDefaultWeldMode = 0;
    StatusData.WeldSettingDefaultTrigPress = -1;
    StatusData.AutoStartLastPart = false;
    StatusData.NRGtoHeightMode = false;
    StatusData.TubeShrinkMode = false;
    StatusData.FileSystemFlags = FSFDefaultSet;
    StatusData.AutoGetNextDelay = DefAutoGetNextDelay;
    StatusData.NetworkingEnabled = false;
    StatusData.CurrentWrkStaID = "";
    StatusData.CentralComputerID = "";
//    StatusData.CutterMSgFlag = false;      //VELEZ040817 Added for Lear Special
    StatusData.CurrentCoolingDel = 0;
    StatusData.CurrentCoolingDur = 100;
    StatusData.CurrentCoolingMode = ENERGYMODE;
    StatusData.CycleCount = 0;
    StatusData.HistoryGraphData = false;
    StatusData.RemoteGraphData = false;
    StatusData.AntisideSpliceTime = DEFAULTUNLOADTIME; //Default Unload time should be 1.5s
    StatusData.CalHightMaximumGauge = 600;

    for(int i = 0; i<= 7; i++)
    {
        StatusData.MaintenanceLimits[i] = 0;
        StatusData.currentMaintenanceLimits[i] = 0;
    }

    SetDefaultWeldFormula(StatusData);
    SetDefaultPassword();
//    ClearPasswordData();
    SetShrinkTubeDefaults(StatusData);
    SetSoftLimitDefaults();
}

/*******************************************************/
/***********************FIXED***************************/
/*******************************************************/
void M10INI::SetSoftLimitDefaults(bool EnableSoftLimits)
{
    StatusData.SoftLimitsModeFlags = (1 | 4 | 16 | 64); //Set to off with sigma
    StatusData.SoftLimitSampleSize = SoftLimitDefaultSampleSize;
    for(int i = SLITime; i <= SLIHeight; i++)
    {
        StatusData.SoftLimit[SLIUpperControlLimit][i] = SoftLimitSigmaDefault;
        StatusData.SoftLimit[SLILowerControlLimit][i] = SoftLimitSigmaDefault;
    }
    if (EnableSoftLimits == true)
        StatusData.SoftLimitsModeFlags = (StatusData.SoftLimitsModeFlags | SoftLimitEnabledFlag);
}

/***********************************************************/
/************************FIXED*******************************/
/***********************************************************/
void M10INI::SetShrinkTubeDefaults(Status_Data DataStruct)
{
//This function will set the shrink tube values to default values for the very 1st time.
    stringstream tmpStr;
    for (int i = STIR1;  i <= STIR10; i++)
    {
        tmpStr << (i + 1);
        tmpStr >>DataStruct.ShrinkTubeDefaults[i].Name;
    }

    DataStruct.ShrinkTubeDefaults[STIR1].temp = ShrinkTubeDefTemp1;
    DataStruct.ShrinkTubeDefaults[STIR1].Time = ShrinkTubeDefTime1;
    DataStruct.ShrinkTubeDefaults[STIR2].temp = ShrinkTubeDefTemp2;
    DataStruct.ShrinkTubeDefaults[STIR2].Time = ShrinkTubeDefTime2;
    DataStruct.ShrinkTubeDefaults[STIR3].temp = ShrinkTubeDefTemp3;
    DataStruct.ShrinkTubeDefaults[STIR3].Time = ShrinkTubeDefTime3;
    DataStruct.ShrinkTubeDefaults[STIR4].temp = ShrinkTubeDefTemp4;
    DataStruct.ShrinkTubeDefaults[STIR4].Time = ShrinkTubeDefTime4;
    DataStruct.ShrinkTubeDefaults[STIR5].temp = ShrinkTubeDefTemp5;
    DataStruct.ShrinkTubeDefaults[STIR5].Time = ShrinkTubeDefTime5;
    DataStruct.ShrinkTubeDefaults[STIR6].temp = ShrinkTubeDefTemp6;
    DataStruct.ShrinkTubeDefaults[STIR6].Time = ShrinkTubeDefTime6;
    DataStruct.ShrinkTubeDefaults[STIR7].temp = ShrinkTubeDefTemp7;
    DataStruct.ShrinkTubeDefaults[STIR7].Time = ShrinkTubeDefTime7;
    DataStruct.ShrinkTubeDefaults[STIR8].temp = ShrinkTubeDefTemp8;
    DataStruct.ShrinkTubeDefaults[STIR8].Time = ShrinkTubeDefTime8;
    DataStruct.ShrinkTubeDefaults[STIR9].temp = ShrinkTubeDefTemp9;
    DataStruct.ShrinkTubeDefaults[STIR9].Time = ShrinkTubeDefTime9;
    DataStruct.ShrinkTubeDefaults[STIR10].temp = ShrinkTubeDefTemp10;
    DataStruct.ShrinkTubeDefaults[STIR10].Time = ShrinkTubeDefTime10;

    //Make Remote recall port disable by default for special
    DataStruct.TubeShrinkerport = PORT_DISABLE;
    DataStruct.RemoteRecallport = PORT_DISABLE;
}

/********************************************************/
/***********************FIxed****************************/
/********************************************************/
void M10INI::SetDefaultWeldFormula(Status_Data DataStruct)
{
//This function will set the weld seeting formulas to default values for the very 1st time.
//Original Packard formula:
//   Energy = 111 * area
//   Amplitude = .023 + .00233 * area
//   Pressure = 23.1 + 1.22 * area
//   Width = 1.256 * sqrt(area)

    for (int i = 0; i <= 11; i++)
    {
        switch (i)
        {
            case 0:
                DataStruct.WeldSettings4Build[i].Multplier = Defmm2EnergyMult0;
                DataStruct.WeldSettings4Build[i].Offset = Defmm2EnergyOffset0;
            break;
            case 1:
                DataStruct.WeldSettings4Build[i].Multplier = Defmm2EnergyMult1;
                DataStruct.WeldSettings4Build[i].Offset = Defmm2EnergyOffset1;
            break;
            case 2:
                DataStruct.WeldSettings4Build[i].Multplier = Defmm2EnergyMult2;
                DataStruct.WeldSettings4Build[i].Offset = Defmm2EnergyOffset2;
            break;
            case 3:
                DataStruct.WeldSettings4Build[i].Multplier = Defmm2WidthAreaRatio0;
                DataStruct.WeldSettings4Build[i].Offset = 0;            //Not used
            break;
            case 4:
                DataStruct.WeldSettings4Build[i].Multplier = Defmm2WidthAreaRatio1;
                DataStruct.WeldSettings4Build[i].Offset = 0;            //Not used
            break;
            case 5:
                DataStruct.WeldSettings4Build[i].Multplier = Defmm2WidthAreaRatio2;
                DataStruct.WeldSettings4Build[i].Offset = 0;            //Not used
            break;
            case 6:
                DataStruct.WeldSettings4Build[i].Multplier = Defmm2PressMult0;
                DataStruct.WeldSettings4Build[i].Offset = Defmm2PressOffset0;
            break;
            case 7:
                DataStruct.WeldSettings4Build[i].Multplier = Defmm2PressMult1;
                DataStruct.WeldSettings4Build[i].Offset = Defmm2PressOffset1;
            break;
            case 8:
                DataStruct.WeldSettings4Build[i].Multplier = Defmm2PressMult2;
                DataStruct.WeldSettings4Build[i].Offset = Defmm2PressOffset2;
            break;
            case 9:
                DataStruct.WeldSettings4Build[i].Multplier = Defmm2AmplitudeMult0;
                DataStruct.WeldSettings4Build[i].Offset = Defmm2AmplitudeOffset0;
            break;
            case 10:
                DataStruct.WeldSettings4Build[i].Multplier = Defmm2AmplitudeMult1;
                DataStruct.WeldSettings4Build[i].Offset = Defmm2AmplitudeOffset1;
            break;
            case 11:
                DataStruct.WeldSettings4Build[i].Multplier = Defmm2AmplitudeMult2;
                DataStruct.WeldSettings4Build[i].Offset = Defmm2AmplitudeOffset2;
            break;
        };
    }
    DataStruct.WeldSettings4Build[0].MinRange = MinRange1;
    DataStruct.WeldSettings4Build[0].MaxRange = MaxRange1;
    DataStruct.WeldSettings4Build[1].MinRange = MinRange2;
    DataStruct.WeldSettings4Build[1].MaxRange = MaxRange2;
    DataStruct.WeldSettings4Build[2].MinRange = MinRange3;
    DataStruct.WeldSettings4Build[2].MaxRange = MaxRange3;
}

/*********************************************************/
/**********************FIXED******************************/
/*********************************************************/
void M10INI::SetDefaultPassword()
{
    StatusData.Enable2DBarcodeFlag = false;
    StatusData.EnableModularFlag = false;
    StatusData.PasswordStatus = PWSNotDefined;
    StatusData.PasswordData[0].Identifier = AdminUsername;
    StatusData.PasswordData[0].Password = "ADMIN";
    StatusData.PasswordData[1].Identifier = TechUsername;
    StatusData.PasswordData[1].Password = "USER";
    StatusData.ModularPassword[0].Identifier = "ENABLEKSK";
    StatusData.ModularPassword[0].Password = "ENKSK01";
    StatusData.ModularPassword[1].Identifier = "DISABLEKSK";
    StatusData.ModularPassword[1].Password = "DSKSK01";
    StatusData.ModularPassword[2].Identifier = "ENABLEKSK2D";
    StatusData.ModularPassword[2].Password = "ENKSK2D";
    StatusData.ModularPassword[3].Identifier = "DISABLEKSK2D";
    StatusData.ModularPassword[3].Password = "DSKSK2D";
    StatusData.PWPermissions = 0x22;
    StatusData.AdminOptions = (StatusData.AdminOptions | ADMINOPWrequired);
 }

/*********************************************************/
/**************************FIXED**************************/
/*********************************************************/
void M10INI::ClearPasswordData()
{
//Initialized password related structure.

    StatusData.PasswordStatus = PWSNotDefined;
    StatusData.PasswordData[0].Identifier = AdminUsername;
    StatusData.PasswordData[0].Password = "";
    StatusData.PasswordData[1].Identifier = TechUsername;
    StatusData.PasswordData[1].Password = "";
    StatusData.PWPermissions = 0x00;
}

/*********************************************************/
/**************************FIXED**************************/
/*********************************************************/
void M10INI::Get_INI_File()
{
    //Check for presence of Amtech.bin file if not present will create.
    QString FileName;
    Password *ptr_Password = Password::Instance();
    M2010    *ptr_M2010    = M2010::Instance();
    InterfaceClass *CInterface = InterfaceClass::Instance();
    UtilityClass *ptr_Utility = UtilityClass::Instance();
//    Const ConfigFilesPath = App.Path & "\etc"
//    Dim FolderName As String
//    FolderName = Dir(App.Path & "\etc", vbDirectory)
//    If FolderName = "" Then MkDir (App.Path & "\etc")
    QDir dir;
    FileName = ConfigFilesPath + AMTECH_INI_FILE;
    if (ptr_Utility->ReadFromBinaryFile(FileName,&StatusData) == true)
    {
//        bErasePasswords can only be done in the debug mode (Can't be set to true
//        by program)
        if (ptr_Password->bErasePasswords == true)
        {
//            cMsgBox GetResString(826)
            BransonMessageBox tmpMsgBox;
            tmpMsgBox.MsgPrompt = (QObject::tr("ErasePasswords = TRUE"));
            tmpMsgBox.MsgTitle  = (QObject::tr("Information"));
            tmpMsgBox.TipsMode = Information;
            tmpMsgBox.func_ptr = NULL;
            CInterface->cMsgBox(&tmpMsgBox);
            ClearPasswordData();
        }
    }else
    {
        Init_StatusData();
    }

    FileName = ConfigFilesPath + BRANSON_LASTWELD_FILE;
    if (DataCell == NULL)
    {
        DataCell = new int[StatusData.GraphDataLen];
    }else
    {
        delete []DataCell;
        DataCell = new int[StatusData.GraphDataLen];
    }
    if(ptr_Utility->ReadFromBinaryFile(FileName,DataCell)== true)
    {
        PowerDataReady = true;
        if (ptr_Password->bErasePasswords == true)
        {
//          cMsgBox GetResString(826)
            BransonMessageBox tmpMsgBox;
            tmpMsgBox.MsgPrompt = (QObject::tr("ErasePasswords = TRUE"));
            tmpMsgBox.MsgTitle = (QObject::tr("Information"));
            tmpMsgBox.TipsMode = Information;
            tmpMsgBox.func_ptr = NULL;
            CInterface->cMsgBox(&tmpMsgBox);
          ClearPasswordData();
        }

    else
      PowerDataReady = false;
    }
    switch (StatusData.MachineType)
    {
        case ACTULTRA20:
        case ACTULTRA40:
        case ACTMTS20:
        case ACTGUN40:
            ptr_M2010->Machine = Welder;
        break;
        default:
            ptr_M2010->Machine = WireSplicer;
        break;
    };
     tempStatusData = StatusData;
     if (StatusData.AutoStartLastPart == true)
         DoAutoStartLastPart = true;
     else
         DoAutoStartLastPart = false;

     SetStoragePaths(); //Required for networking applications

     //This data is usually initialized from the control input
     ptr_M2010->Maxpower = int(1.2 * StatusData.Soft_Settings.SonicGenWatts);
}
