#include "M10INI.h"
#include "Password.h"
#include "M2010.h"
#include "Interface/Interface.h"
#include "Interface/Settings/SysConfiguration.h"
#include "UtilityClass.h"
#include <QDir>
#include <QFile>
#include <QDataStream>
#include <windows.h>
#include <QObject>
#include <QDateTime>
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

//string M10INI::MakeNWErrorPath(string CenComp)
//{
//    string tmpStr; //= "\\" & trim(CenComp) & "\A0MsgCtr\";
//    return tmpStr;
//}

//string M10INI::MakeNWLocSeqPath(string WrkSta)
//{
//    string tmpStr; //"c:\AmtData\" & Trim(WrkSta) & "\"
//    return tmpStr;
//}

//string M10INI::MakeNWSeqPath(string CenComp, string WrkSta)
//{
//    string tmpStr; //"\\" & Trim(CenComp) & "\AmtData\" & Trim(WrkSta) & "\"
//    return tmpStr;
//}

//string M10INI::MakeNWPartPath(string CenComp)
//{
//    string tmpStr; //= "\\" & Trim(CenComp) & "\AmtData\" & StoragePaths.sComputerName & "\"
//    return tmpStr;
//}

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

//void M10INI::GenerateSLFlagGroup(long Flaggroup, int Index)
//{

//}

void M10INI::Save_LastWeldGraph()
{

}

void M10INI::SetDefaultWeldFormula(Status_Data* _DataStruct)
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    //This function will set the weld seeting formulas to default values for the very 1st time.
    //Original Packard formula:
    //   Energy = 111 * area
    //   Amplitude = .023 + .00233 * area
    //   Pressure = 23.1 + 1.22 * area
    //   Width = 1.256 * sqrt(area)

    for (int i = 0; i <= FormulaRangSize; i++)
    {
        switch (i)
        {
            case 0:
                _DataStruct->WeldSettings4Build[i].Multplier = Defmm2EnergyMult0;
                _DataStruct->WeldSettings4Build[i].Offset = Defmm2EnergyOffset0;
            break;
            case 1:
                _DataStruct->WeldSettings4Build[i].Multplier = Defmm2EnergyMult1;
                _DataStruct->WeldSettings4Build[i].Offset = Defmm2EnergyOffset1;
            break;
            case 2:
                _DataStruct->WeldSettings4Build[i].Multplier = Defmm2EnergyMult2;
                _DataStruct->WeldSettings4Build[i].Offset = Defmm2EnergyOffset2;
            break;
            case 3:
                _DataStruct->WeldSettings4Build[i].Multplier = Defmm2WidthAreaRatio0;
                _DataStruct->WeldSettings4Build[i].Offset = 0;            //Not used
            break;
            case 4:
                _DataStruct->WeldSettings4Build[i].Multplier = Defmm2WidthAreaRatio1;
                _DataStruct->WeldSettings4Build[i].Offset = 0;            //Not used
            break;
            case 5:
                _DataStruct->WeldSettings4Build[i].Multplier = Defmm2WidthAreaRatio2;
                _DataStruct->WeldSettings4Build[i].Offset = 0;            //Not used
            break;
            case 6:
                _DataStruct->WeldSettings4Build[i].Multplier = Defmm2PressMult0;
                _DataStruct->WeldSettings4Build[i].Offset = Defmm2PressOffset0;
            break;
            case 7:
                _DataStruct->WeldSettings4Build[i].Multplier = Defmm2PressMult1;
                _DataStruct->WeldSettings4Build[i].Offset = Defmm2PressOffset1;
            break;
            case 8:
                _DataStruct->WeldSettings4Build[i].Multplier = Defmm2PressMult2;
                _DataStruct->WeldSettings4Build[i].Offset = Defmm2PressOffset2;
            break;
            case 9:
                _DataStruct->WeldSettings4Build[i].Multplier = Defmm2AmplitudeMult0;
                _DataStruct->WeldSettings4Build[i].Offset = Defmm2AmplitudeOffset0;
            break;
            case 10:
                _DataStruct->WeldSettings4Build[i].Multplier = Defmm2AmplitudeMult1;
                _DataStruct->WeldSettings4Build[i].Offset = Defmm2AmplitudeOffset1;
            break;
            case 11:
                _DataStruct->WeldSettings4Build[i].Multplier = Defmm2AmplitudeMult2;
                _DataStruct->WeldSettings4Build[i].Offset = Defmm2AmplitudeOffset2;
            break;
        };
    }
    _DataStruct->WeldSettings4Build[0].MinRange = MinRange1;
    _DataStruct->WeldSettings4Build[0].MaxRange = MaxRange1;
    _DataStruct->WeldSettings4Build[1].MinRange = MinRange2;
    _DataStruct->WeldSettings4Build[1].MaxRange = MaxRange2;
    _DataStruct->WeldSettings4Build[2].MinRange = MinRange3;
    _DataStruct->WeldSettings4Build[2].MaxRange = MaxRange3;
}

void M10INI::SetDefaultPassword()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.EnableModularFlag = false;
    _Interface->StatusData.PasswordData[0].Identifier = QObject::tr("Switch Key");
    _Interface->StatusData.PasswordData[0].Password.clear();
    _Interface->StatusData.PasswordData[0].PWPermissions = 0xFFFFFFFF;
    _Interface->StatusData.PasswordData[1].Identifier = QObject::tr("Level 1");
    _Interface->StatusData.PasswordData[1].Password.clear();
    _Interface->StatusData.PasswordData[1].PWPermissions = 0;
    _Interface->StatusData.PasswordData[2].Identifier = QObject::tr("Level 2");
    _Interface->StatusData.PasswordData[2].Password.clear();
    _Interface->StatusData.PasswordData[2].PWPermissions = 0;
    _Interface->StatusData.PasswordData[3].Identifier = QObject::tr("Level 3");
    _Interface->StatusData.PasswordData[3].Password.clear();
    _Interface->StatusData.PasswordData[3].PWPermissions = 0;
    _Interface->StatusData.PasswordData[4].Identifier = QObject::tr("Level 4");
    _Interface->StatusData.PasswordData[4].Password.clear();
    _Interface->StatusData.PasswordData[4].PWPermissions = 0;
    _Interface->StatusData.ModularPassword[0].Identifier = QObject::tr("ENABLEKSK");
    _Interface->StatusData.ModularPassword[0].Password = QObject::tr("ENKSK01");
    _Interface->StatusData.ModularPassword[1].Identifier = QObject::tr("DISABLEKSK");
    _Interface->StatusData.ModularPassword[1].Password = QObject::tr("DSKSK01");
    _Interface->StatusData.ModularPassword[2].Identifier = QObject::tr("ENABLEKSK2D");
    _Interface->StatusData.ModularPassword[2].Password = QObject::tr("ENKSK2D");
}

void M10INI::SetShrinkTubeDefaults()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    //This function will set the shrink tube values to default values for the very 1st time.
    for (int i = STIR1;  i <= STIR10; i++)
        _Interface->StatusData.ShrinkTubeDefaults[i].Name = QString::number(i+1);

    _Interface->StatusData.ShrinkTubeDefaults[STIR1].temp = ShrinkTubeDefTemp1;
    _Interface->StatusData.ShrinkTubeDefaults[STIR1].Time = ShrinkTubeDefTime1;
    _Interface->StatusData.ShrinkTubeDefaults[STIR2].temp = ShrinkTubeDefTemp2;
    _Interface->StatusData.ShrinkTubeDefaults[STIR2].Time = ShrinkTubeDefTime2;
    _Interface->StatusData.ShrinkTubeDefaults[STIR3].temp = ShrinkTubeDefTemp3;
    _Interface->StatusData.ShrinkTubeDefaults[STIR3].Time = ShrinkTubeDefTime3;
    _Interface->StatusData.ShrinkTubeDefaults[STIR4].temp = ShrinkTubeDefTemp4;
    _Interface->StatusData.ShrinkTubeDefaults[STIR4].Time = ShrinkTubeDefTime4;
    _Interface->StatusData.ShrinkTubeDefaults[STIR5].temp = ShrinkTubeDefTemp5;
    _Interface->StatusData.ShrinkTubeDefaults[STIR5].Time = ShrinkTubeDefTime5;
    _Interface->StatusData.ShrinkTubeDefaults[STIR6].temp = ShrinkTubeDefTemp6;
    _Interface->StatusData.ShrinkTubeDefaults[STIR6].Time = ShrinkTubeDefTime6;
    _Interface->StatusData.ShrinkTubeDefaults[STIR7].temp = ShrinkTubeDefTemp7;
    _Interface->StatusData.ShrinkTubeDefaults[STIR7].Time = ShrinkTubeDefTime7;
    _Interface->StatusData.ShrinkTubeDefaults[STIR8].temp = ShrinkTubeDefTemp8;
    _Interface->StatusData.ShrinkTubeDefaults[STIR8].Time = ShrinkTubeDefTime8;
    _Interface->StatusData.ShrinkTubeDefaults[STIR9].temp = ShrinkTubeDefTemp9;
    _Interface->StatusData.ShrinkTubeDefaults[STIR9].Time = ShrinkTubeDefTime9;
    _Interface->StatusData.ShrinkTubeDefaults[STIR10].temp = ShrinkTubeDefTemp10;
    _Interface->StatusData.ShrinkTubeDefaults[STIR10].Time = ShrinkTubeDefTime10;

    //Make Remote recall port disable by default for special
    _Interface->StatusData.TubeShrinkerport = PORT_DISABLE;
    _Interface->StatusData.RemoteRecallport = PORT_DISABLE;
}

void M10INI::SetSoftLimitDefaults(bool EnableSoftLimits)
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.SoftLimitsModeFlags = (1 | 4 | 16 | 64); //Set to off with sigma
    _Interface->StatusData.SoftLimitSampleSize = SoftLimitDefaultSampleSize;
    for(int i = SLITime; i <= SLIHeight; i++)
    {
        _Interface->StatusData.SoftLimit[SLIUpperControlLimit][i] = SoftLimitSigmaDefault;
        _Interface->StatusData.SoftLimit[SLILowerControlLimit][i] = SoftLimitSigmaDefault;
    }
    if (EnableSoftLimits == true)
        _Interface->StatusData.SoftLimitsModeFlags =
                (_Interface->StatusData.SoftLimitsModeFlags | SoftLimitEnabledFlag);
}

void M10INI::ClearPasswordData()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.PasswordData[0].Identifier = QObject::tr("Switch Key");
    _Interface->StatusData.PasswordData[0].Password.clear();
    _Interface->StatusData.PasswordData[0].PWPermissions = 0xFFFFFFFF;
    _Interface->StatusData.PasswordData[1].Identifier = QObject::tr("Level 1");
    _Interface->StatusData.PasswordData[1].Password.clear();
    _Interface->StatusData.PasswordData[1].PWPermissions = 0;
    _Interface->StatusData.PasswordData[2].Identifier = QObject::tr("Level 2");
    _Interface->StatusData.PasswordData[2].Password.clear();
    _Interface->StatusData.PasswordData[2].PWPermissions = 0;
    _Interface->StatusData.PasswordData[3].Identifier = QObject::tr("Level 3");
    _Interface->StatusData.PasswordData[3].Password.clear();
    _Interface->StatusData.PasswordData[3].PWPermissions = 0;
    _Interface->StatusData.PasswordData[4].Identifier = QObject::tr("Level 4");
    _Interface->StatusData.PasswordData[4].Password.clear();
    _Interface->StatusData.PasswordData[4].PWPermissions = 0;
}

void M10INI::Init_StatusData()
{
    InterfaceClass *_Interface = InterfaceClass::Instance();
    _Interface->StatusData.RevCode = -1;
    _Interface->StatusData.CreatedDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    _Interface->StatusData.StartScreen = CreateNew_SCREEN;
    _Interface->StatusData.Soft_Settings.Lang_Support = ENGLISH_lang;
    _Interface->StatusData.Soft_Settings.Horn_Calibrate = MAXAMPLITUDE;
    _Interface->StatusData.Soft_Settings.AutoPreburst = 0;
//    _Interface->StatusData.Soft_Settings.AutoGetNext = true;
    _Interface->StatusData.Soft_Settings.SonicGenWatts = 4000; // newsplicer 4000w, others we can set 3300w
    _Interface->StatusData.Soft_Settings.ToolCoverIgnore  = true;
//    _Interface->StatusData.Soft_Settings.NoToolCover4SU = true;
    _Interface->StatusData.Soft_Settings.Pressure2Unit = ToPSI;
    _Interface->StatusData.Soft_Settings.Mm2Awg = false;
    _Interface->StatusData.Soft_Settings.PWWidth2Height = 0;
    _Interface->StatusData.Soft_Settings.MinAmplitude = MINAMPLITUDE;
    _Interface->StatusData.Soft_Settings.MinPressure = MINWELDPRESSURE;
    _Interface->StatusData.Soft_Settings.WeldFormula = WeldFormulaAmtechStandard;
    _Interface->StatusData.Soft_Settings.RunCount = 10;
    _Interface->StatusData.Soft_Settings.Teach_Mode = SIGMA;
    _Interface->StatusData.Soft_Settings.TunePoint = 40;
    _Interface->StatusData.Soft_Settings.FrequencyOffset = 50;

    _Interface->StatusData.Cust_Data.mod10a_settings.UnsignedWeldData = 4097;
    _Interface->StatusData.Cust_Data.mod10a_settings.AfterBurstDelay = 10;
    _Interface->StatusData.Cust_Data.mod10a_settings.AfterBurstDuration = 20;
    _Interface->StatusData.Cust_Data.mod10a_settings.EnergyWindowPL = 50;
    _Interface->StatusData.Cust_Data.mod10a_settings.PreBurstIndex = 0;
    _Interface->StatusData.Cust_Data.cust_qual_range[TIME_PLRG] = 40;
    _Interface->StatusData.Cust_Data.cust_qual_range[TIME_MSRG] = 40;
    _Interface->StatusData.Cust_Data.cust_qual_range[POWER_PLRG] = 25;
    _Interface->StatusData.Cust_Data.cust_qual_range[POWER_MSRG] = 25;
    _Interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_PLRG] = 15;
    _Interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_MSRG] = 15;
    _Interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_PLRG] = 10;
    _Interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_MSRG] = 10;
    _Interface->StatusData.Cust_Data.cust_qual_range[FORCE_PLRG] = 5;
    _Interface->StatusData.Cust_Data.cust_qual_range[FORCE_MSRG] = 10;
    for(int i = TIME_CONFRG_PL; i <= HEIGHT_CONFRG_MS; i++)
    {
        _Interface->StatusData.Cust_Data.cust_qual_range[i] = 4;
    }
    _Interface->StatusData.Cust_Data.cust_qual_range[ENERGY_ADJ] = 280;
    _Interface->StatusData.Cust_Data.cust_qual_range[PRESSURE_ADJ] = 30;
    _Interface->StatusData.Cust_Data.cust_qual_range[AMPLITUDE_ADJ] = 26;
    _Interface->StatusData.Cust_Data.cust_qual_range[WIDTH_ADJ] = 625;
    //Now store the new file data

    for(int i = TIME_USL; i<= HEIGHT_LSL; i++)
    {
        _Interface->StatusData.HSDATA.HARD_LIMIT[i].TypeHS = Sigam;
        _Interface->StatusData.HSDATA.HARD_LIMIT[i].ValueHS = 4;
        _Interface->StatusData.HSDATA.SOFT_LIMIT[i].TypeHS = Percent;
        _Interface->StatusData.HSDATA.SOFT_LIMIT[i].ValueHS = 30;
    }
    _Interface->StatusData.ComInfo.COMport = 1;
    _Interface->StatusData.ComInfo.BaudRate = 1152;
    _Interface->StatusData.MachineType = ACTNEWSPLICER; //Need To Fix
    _Interface->StatusData.MachineDate = "";
    _Interface->StatusData.Machineflags.Word[0] = 0;
    _Interface->StatusData.KeepDailyHistory = true;

    _Interface->StatusData.LockonAlarm = 0;
    _Interface->StatusData.RunMode.Word = 0;
//    _Interface->StatusData.AdminOptions = 0x00;
//    _Interface->StatusData.WeldSettingDefaultWeldMode = 0;
//    _Interface->StatusData.WeldSettingDefaultTrigPress = -1;
//    _Interface->StatusData.AutoStartLastPart = false;
//    _Interface->StatusData.NRGtoHeightMode = false;
    _Interface->StatusData.ShrinkTubeMode = false;
    _Interface->StatusData.FileSystemFlags = FSFDefaultSet;
    _Interface->StatusData.AutoGetNextDelay = DefAutoGetNextDelay;
    _Interface->StatusData.NetworkingEnabled = false;
    _Interface->StatusData.CurrentWrkStaID = "";
    _Interface->StatusData.CentralComputerID = "";
    _Interface->StatusData.CurrentCoolingDel = 0;
    _Interface->StatusData.CurrentCoolingDur = 100;
    _Interface->StatusData.CurrentCoolingMode = ENERGYMODE;
    _Interface->StatusData.CycleCount = 0;
    _Interface->StatusData.HistoryGraphData = true;
    _Interface->StatusData.RemoteGraphData = false;
//    _Interface->StatusData.AntisideSpliceTime = DEFAULTUNLOADTIME; //Default Unload time should be 1.5s

    for(int i = 0; i<= 7; i++)
    {
        _Interface->StatusData.MaintenanceLimits[i] = 0;
        _Interface->StatusData.CurrentMaintenanceLimits[i] = 0;
    }

    SetDefaultWeldFormula(&_Interface->StatusData);
    SetDefaultPassword();
    SetShrinkTubeDefaults();
    SetSoftLimitDefaults();
}

void M10INI::Get_INI_File()
{
    //Check for presence of Branson.bin file if not present will create.
    QString FileName;
    Password *_Password = Password::Instance();
    M2010    *_M2010    = M2010::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    UtilityClass *_Utility = UtilityClass::Instance();

    QDir dir;
    FileName = ConfigFilesPath + BRANSON_INI_FILE;
    if (_Utility->ReadFromBinaryFile(FileName,&_Interface->StatusData) == true)
    {
//        bErasePasswords can only be done in the debug mode (Can't be set to true
//        by program)
        if (_Password->bErasePasswords == true)
        {
//            cMsgBox GetResString(826)
            BransonMessageBox tmpMsgBox;
            tmpMsgBox.MsgPrompt = (QObject::tr("ErasePasswords = TRUE"));
            tmpMsgBox.MsgTitle  = (QObject::tr("Information"));
            tmpMsgBox.TipsMode = Information;
            tmpMsgBox.func_ptr = NULL;
            _Interface->cMsgBox(&tmpMsgBox);
            ClearPasswordData();
        }
    }else
    {
        Init_StatusData();
    }

    FileName = ConfigFilesPath + BRANSON_LASTWELD_FILE;
    if (dir.exists(FileName) == true)
    {
        if (DataCell == NULL)
        {
            DataCell = new int[_Interface->StatusData.GraphDataLen];
        }else
        {
            delete []DataCell;
            DataCell = new int[_Interface->StatusData.GraphDataLen];
        }
        if(_Utility->ReadFromBinaryFile(FileName,DataCell)== true)
        {
            PowerDataReady = true;
            if (_Password->bErasePasswords == true)
            {
    //          cMsgBox GetResString(826)
                BransonMessageBox tmpMsgBox;
                tmpMsgBox.MsgPrompt = (QObject::tr("ErasePasswords = TRUE"));
                tmpMsgBox.MsgTitle = (QObject::tr("Information"));
                tmpMsgBox.TipsMode = Information;
                tmpMsgBox.func_ptr = NULL;
                _Interface->cMsgBox(&tmpMsgBox);
                ClearPasswordData();
            }
            else
                PowerDataReady = false;
        }
    }
    switch (_Interface->StatusData.MachineType)
    {
        case ACTULTRA20:
        case ACTULTRA40:
        case ACTMTS20:
        case ACTGUN40:
            _M2010->Machine = Welder;
        break;
        default:
            _M2010->Machine = WireSplicer;
        break;
    };
     _Interface->tempStatusData = _Interface->StatusData;
     SetStoragePaths(); //Required for networking applications

     //This data is usually initialized from the control input
     _Utility->Maxpower = int(1.2 * _Interface->StatusData.Soft_Settings.SonicGenWatts);
}

void M10INI::Save_StatusData(bool WithUpdate)
{
//    Saves temp data into data and stores the file
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    M2010    *_M2010    = M2010::Instance();

    if (WithUpdate == true)
        _Interface->StatusData = _Interface->tempStatusData;
    else
        _Interface->tempStatusData = _Interface->StatusData;

    bool bResult = _Utility->WriteToBinaryFile(&_Interface->StatusData,
                                   (ConfigFilesPath + BRANSON_INI_FILE));
    if (bResult == true)
    {

        switch(_Interface->StatusData.MachineType)
        {
        case ACTULTRA20:
        case ACTULTRA40:
        case ACTMTS20:
        case ACTGUN40:
              _M2010->Machine = Welder;
        break;
        default:
              _M2010->Machine = WireSplicer;
        break;
        }

    }
}
