#include "M10INI.h"
#include "Password.h"
#include "M2010.h"
#include "Interface/Interface.h"
#include "Interface/SysConfiguration.h"
#include "UtilityClass.h"
#include "typedef.h"
#include <QDir>
#include <QFile>
#include <QDataStream>
#include <windows.h>
#include <QObject>
#include <QDateTime>
#include <QSettings>
#include <QDebug>
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
//    InterfaceClass* _Interface = InterfaceClass::Instance();
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
                _DataStruct->WeldSettings4Build[i].Multplier = (float)Defmm2EnergyMult1;
                _DataStruct->WeldSettings4Build[i].Offset = (float)Defmm2EnergyOffset1;
            break;
            case 2:
                _DataStruct->WeldSettings4Build[i].Multplier = (float)Defmm2EnergyMult2;
                _DataStruct->WeldSettings4Build[i].Offset = (float)Defmm2EnergyOffset2;
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
                _DataStruct->WeldSettings4Build[i].Multplier = (float)Defmm2PressMult0;
                _DataStruct->WeldSettings4Build[i].Offset = Defmm2PressOffset0;
            break;
            case 7:
                _DataStruct->WeldSettings4Build[i].Multplier = (float)Defmm2PressMult1;
                _DataStruct->WeldSettings4Build[i].Offset = Defmm2PressOffset1;
            break;
            case 8:
                _DataStruct->WeldSettings4Build[i].Multplier = (float)Defmm2PressMult2;
                _DataStruct->WeldSettings4Build[i].Offset = (float)Defmm2PressOffset2;
            break;
            case 9:
                _DataStruct->WeldSettings4Build[i].Multplier = (float)Defmm2AmplitudeMult0;
                _DataStruct->WeldSettings4Build[i].Offset = Defmm2AmplitudeOffset0;
            break;
            case 10:
                _DataStruct->WeldSettings4Build[i].Multplier = (float)Defmm2AmplitudeMult1;
                _DataStruct->WeldSettings4Build[i].Offset = (float)Defmm2AmplitudeOffset1;
            break;
            case 11:
                _DataStruct->WeldSettings4Build[i].Multplier = (float)Defmm2AmplitudeMult2;
                _DataStruct->WeldSettings4Build[i].Offset = (float)Defmm2AmplitudeOffset2;
            break;
        };
    }
    _DataStruct->WeldSettings4Build[0].MinRange = MinRange1;
    _DataStruct->WeldSettings4Build[0].MaxRange = (float)MaxRange1;
    _DataStruct->WeldSettings4Build[1].MinRange = MinRange2;
    _DataStruct->WeldSettings4Build[1].MaxRange = (float)MaxRange2;
    _DataStruct->WeldSettings4Build[2].MinRange = MinRange3;
    _DataStruct->WeldSettings4Build[2].MaxRange = MaxRange3;
}

void M10INI::SetDefaultPassword(Status_Data* _DataStruct)
{
    _DataStruct->EnableModularFlag = false;
    _DataStruct->PasswordData[0].Identifier = QObject::tr("Physical Key");
    _DataStruct->PasswordData[0].Password.clear();
    _DataStruct->PasswordData[0].PWPermissions = 0xFFFFFFFF;
    _DataStruct->PasswordData[1].Identifier = QObject::tr("Level 1");
    _DataStruct->PasswordData[1].Password.clear();
    _DataStruct->PasswordData[1].PWPermissions = 0;
    _DataStruct->PasswordData[2].Identifier = QObject::tr("Level 2");
    _DataStruct->PasswordData[2].Password.clear();
    _DataStruct->PasswordData[2].PWPermissions = 0;
    _DataStruct->PasswordData[3].Identifier = QObject::tr("Level 3");
    _DataStruct->PasswordData[3].Password.clear();
    _DataStruct->PasswordData[3].PWPermissions = 0;
    _DataStruct->PasswordData[4].Identifier = QObject::tr("Level 4");
    _DataStruct->PasswordData[4].Password.clear();
    _DataStruct->PasswordData[4].PWPermissions = 0;
    _DataStruct->ModularPassword[0].Identifier = QObject::tr("ENABLEKSK");
    _DataStruct->ModularPassword[0].Password = QObject::tr("ENKSK01");
    _DataStruct->ModularPassword[1].Identifier = QObject::tr("DISABLEKSK");
    _DataStruct->ModularPassword[1].Password = QObject::tr("DSKSK01");
    _DataStruct->ModularPassword[2].Identifier = QObject::tr("ENABLEKSK2D");
    _DataStruct->ModularPassword[2].Password = QObject::tr("ENKSK2D");
}

void M10INI::SetAWGToMMTable(Status_Data* _DataStruct)
{
    QString sPathName = ConfigFilesPath + AWG2MM_TABLE_FILE;
    QSettings settings(sPathName, QSettings::IniFormat);
    settings.beginGroup("AWG2AreaTable");
    for(int i = 0; i< 40; i++)
    {
        _DataStruct->AWGToAreaTable.insert(i + 1,
            settings.value(QString::number(i+1,10) + "AWG").value<int>());
//        qDebug()<<"i: "<<(i+1)<<QString::number(i+1,10) + "AWG"
//                << settings.value(QString::number(i+1,10) + "AWG").value<int>();
    }

    settings.endGroup();
}

void M10INI::Init_AWGToMMTable()
{
    QString sPathName = ConfigFilesPath + AWG2MM_TABLE_FILE;

    //Check if file exists, if not, create it.
    QDir dir;
    if (dir.exists(sPathName) == false)
    {
        QSettings settings(sPathName, QSettings::IniFormat);
        settings.beginGroup("AWG2AreaTable");
        settings.setValue("1AWG", "4241");
        settings.setValue("2AWG", "3363");
        settings.setValue("3AWG", "2665");
        settings.setValue("4AWG", "2115");
        settings.setValue("5AWG", "1677");
        settings.setValue("6AWG", "1330");
        settings.setValue("7AWG", "1055");
        settings.setValue("8AWG", "837");
        settings.setValue("9AWG", "663");
        settings.setValue("10AWG", "526");
        settings.setValue("11AWG", "417");
        settings.setValue("12AWG", "331");
        settings.setValue("13AWG", "262");
        settings.setValue("14AWG", "208");
        settings.setValue("15AWG", "165");
        settings.setValue("16AWG", "131");
        settings.setValue("17AWG", "104");
        settings.setValue("18AWG", "82");
        settings.setValue("19AWG", "65");
        settings.setValue("20AWG", "52");
        settings.setValue("21AWG", "41");
        settings.setValue("22AWG", "33");
        settings.setValue("23AWG", "26");
        settings.setValue("24AWG", "20");
        settings.setValue("25AWG", "16");
        settings.setValue("26AWG", "13");
        settings.setValue("27AWG", "10");
        settings.setValue("28AWG", "8");
        settings.setValue("29AWG", "7");
        settings.setValue("30AWG", "5");
        settings.setValue("31AWG", "4");
        settings.setValue("32AWG", "3");
        settings.setValue("33AWG", "2");
        settings.setValue("34AWG", "2");
        settings.setValue("35AWG", "1");
        settings.setValue("36AWG", "1");
        settings.setValue("37AWG", "1");
        settings.endGroup();
    }
}

void M10INI::SetShrinkTubeDefaults(Status_Data* _DataStruct)
{
    //This function will set the shrink tube values to default values for the very 1st time.
    struct ShrinkTubeData tmpShrinkTube;
    for (int i = STIR1;  i <= STIR11; i++)
    {
        tmpShrinkTube.Name = QString::number(i + 1);
        _DataStruct->ShrinkTubeDefaults.insert(i, tmpShrinkTube);
    }
    _DataStruct->ShrinkTubeDefaults[STIR1].temp = ShrinkTubeDefTemp1;
    _DataStruct->ShrinkTubeDefaults[STIR1].Time = ShrinkTubeDefTime1;
    _DataStruct->ShrinkTubeDefaults[STIR2].temp = ShrinkTubeDefTemp2;
    _DataStruct->ShrinkTubeDefaults[STIR2].Time = ShrinkTubeDefTime2;
    _DataStruct->ShrinkTubeDefaults[STIR3].temp = ShrinkTubeDefTemp3;
    _DataStruct->ShrinkTubeDefaults[STIR3].Time = ShrinkTubeDefTime3;
    _DataStruct->ShrinkTubeDefaults[STIR4].temp = ShrinkTubeDefTemp4;
    _DataStruct->ShrinkTubeDefaults[STIR4].Time = ShrinkTubeDefTime4;
    _DataStruct->ShrinkTubeDefaults[STIR5].temp = ShrinkTubeDefTemp5;
    _DataStruct->ShrinkTubeDefaults[STIR5].Time = ShrinkTubeDefTime5;
    _DataStruct->ShrinkTubeDefaults[STIR6].temp = ShrinkTubeDefTemp6;
    _DataStruct->ShrinkTubeDefaults[STIR6].Time = ShrinkTubeDefTime6;
    _DataStruct->ShrinkTubeDefaults[STIR7].temp = ShrinkTubeDefTemp7;
    _DataStruct->ShrinkTubeDefaults[STIR7].Time = ShrinkTubeDefTime7;
    _DataStruct->ShrinkTubeDefaults[STIR8].temp = ShrinkTubeDefTemp8;
    _DataStruct->ShrinkTubeDefaults[STIR8].Time = ShrinkTubeDefTime8;
    _DataStruct->ShrinkTubeDefaults[STIR9].temp = ShrinkTubeDefTemp9;
    _DataStruct->ShrinkTubeDefaults[STIR9].Time = ShrinkTubeDefTime9;
    _DataStruct->ShrinkTubeDefaults[STIR10].temp = ShrinkTubeDefTemp10;
    _DataStruct->ShrinkTubeDefaults[STIR10].Time = ShrinkTubeDefTime10;
    _DataStruct->ShrinkTubeDefaults[STIR11].temp = ShrinkTubeDefTemp1;
    _DataStruct->ShrinkTubeDefaults[STIR11].Time = ShrinkTubeDefTime1;

    //Make Remote recall port disable by default for special
    _DataStruct->ShrinkTubeComInfo.COMport = 1;
    _DataStruct->ShrinkTubeComInfo.BaudRate = 9600;
}

void M10INI::SetSoftLimitDefaults(Status_Data* _DataStruct, bool EnableSoftLimits)
{
    _DataStruct->SoftLimitsModeFlags = (1 | 4 | 16 | 64); //Set to off with sigma
    _DataStruct->SoftLimitSampleSize = SoftLimitDefaultSampleSize;
    for(int i = SLITime; i <= SLIHeight; i++)
    {
        _DataStruct->SoftLimit[SLIUpperControlLimit][i] = SoftLimitSigmaDefault;
        _DataStruct->SoftLimit[SLILowerControlLimit][i] = SoftLimitSigmaDefault;
    }
    if (EnableSoftLimits == true)
        _DataStruct->SoftLimitsModeFlags =
                (_DataStruct->SoftLimitsModeFlags | SoftLimitEnabledFlag);
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
    _Interface->DefaultStatusData.RevCode = INVALID;
    _Interface->DefaultStatusData.CreatedDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    _Interface->DefaultStatusData.StartScreen = CreateNew_SCREEN;
    _Interface->DefaultStatusData.Soft_Settings.Lang_Support = ENGLISH_lang;
    _Interface->DefaultStatusData.Soft_Settings.Horn_Calibrate = MAXAMPLITUDE;
    _Interface->DefaultStatusData.Soft_Settings.AutoPreburst = 0;
//    _Interface->StatusData.Soft_Settings.AutoGetNext = true;
    _Interface->DefaultStatusData.Soft_Settings.SonicGenWatts = 4000; // newsplicer 4000w, others we can set 3300w
    _Interface->DefaultStatusData.Soft_Settings.ToolCoverIgnore  = true;
//    _Interface->StatusData.Soft_Settings.NoToolCover4SU = true;
    _Interface->DefaultStatusData.Soft_Settings.Pressure2Unit =
            BRANSON_INI_STRUCT::ToPSI;
    _Interface->DefaultStatusData.Soft_Settings.Square2Unit =
            BRANSON_INI_STRUCT::ToSqrMM;
    _Interface->DefaultStatusData.Soft_Settings.Length2Unit =
            BRANSON_INI_STRUCT::ToMM;
    _Interface->DefaultStatusData.Soft_Settings.PWWidth2Height = 0;
    _Interface->DefaultStatusData.Soft_Settings.MinAmplitude = MINAMPLITUDE;
    _Interface->DefaultStatusData.Soft_Settings.MinPressure = MINWELDPRESSURE;
    _Interface->DefaultStatusData.Soft_Settings.WeldFormula = WeldFormulaAmtechStandard;
    _Interface->DefaultStatusData.Soft_Settings.RunCount = 10;
    _Interface->DefaultStatusData.Soft_Settings.Teach_Mode = TEACHMODESETTING::SIGMA;
    _Interface->DefaultStatusData.Soft_Settings.TunePoint = 19950;
    _Interface->DefaultStatusData.Soft_Settings.FrequencyOffset = 0;

    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[TIME_PLRG_STD] = 40;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[TIME_MSRG_STD] = 40;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[POWER_PLRG_STD] = 25;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[POWER_MSRG_STD] = 25;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[PRE_HGT_PLRG_STD] = 15;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[PRE_HGT_MSRG_STD] = 15;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[HEIGHT_PLRG_STD] = 10;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[HEIGHT_MSRG_STD] = 10;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[FORCE_PLRG_STD] = 5;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[FORCE_MSRG_STD] = 10;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[TIME_PLRG_AUTO] = 40;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[TIME_MSRG_AUTO] = 40;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[POWER_PLRG_AUTO] = 25;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[POWER_MSRG_AUTO] = 25;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[PRE_HGT_PLRG_AUTO] = 15;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[PRE_HGT_MSRG_AUTO] = 15;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[HEIGHT_PLRG_AUTO] = 10;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[HEIGHT_MSRG_AUTO] = 10;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[FORCE_PLRG_AUTO] = 5;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[FORCE_MSRG_AUTO] = 10;
    for(int i = TIME_CONFRG_PL; i <= HEIGHT_CONFRG_MS; i++)
    {
        _Interface->DefaultStatusData.Cust_Data.cust_qual_range[i] = 4;
    }
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[ENERGY_ADJ] = 280;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[PRESSURE_ADJ] = 30;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[AMPLITUDE_ADJ] = 26;
    _Interface->DefaultStatusData.Cust_Data.cust_qual_range[WIDTH_ADJ] = 625;
    _Interface->DefaultStatusData.Cust_Data.PresetTeachModeSetting = QUALITY_DATA_FILE::GLOBALS;
    _Interface->DefaultStatusData.Cust_Data.StandardRunQuantity = 15;
    _Interface->DefaultStatusData.Cust_Data.AutoRunQuantity = 15;
    _Interface->DefaultStatusData.Cust_Data.SigmaRunQuantity = 15;
    //Now store the new file data

    _Interface->DefaultStatusData.ComInfo.COMport = 1;
    _Interface->DefaultStatusData.ComInfo.BaudRate = 115200;
    _Interface->DefaultStatusData.MachineType = ACTNEWSPLICER; //Need To Fix
    _Interface->DefaultStatusData.MachineDate = "";
    _Interface->DefaultStatusData.Machineflags.Word[0] = 0;
    _Interface->DefaultStatusData.KeepDailyHistory = true;
    _Interface->DefaultStatusData.HistoryGraphData = true;
    _Interface->DefaultStatusData.GraphSampleRatio = WeldResultElement::SampleWith1ms;

    _Interface->DefaultStatusData.LockonAlarm = 0;
    _Interface->DefaultStatusData.RunMode.Word = 0;
//    _Interface->StatusData.AdminOptions = 0x00;
//    _Interface->StatusData.WeldSettingDefaultWeldMode = 0;
//    _Interface->StatusData.WeldSettingDefaultTrigPress = -1;
//    _Interface->StatusData.AutoStartLastPart = false;
//    _Interface->StatusData.NRGtoHeightMode = false;
    _Interface->DefaultStatusData.ShrinkTubeModeEnable = false;
    _Interface->DefaultStatusData.FileSystemFlags = FSFDefaultSet;
    _Interface->DefaultStatusData.AutoGetNextDelay = DefAutoGetNextDelay;
    _Interface->DefaultStatusData.NetworkingEnabled = false;
    _Interface->DefaultStatusData.RemoteDataLogging = false;
    _Interface->DefaultStatusData.ServerPort = 4000;
    _Interface->DefaultStatusData.ModularProductionEnabled = false;

    _Interface->DefaultStatusData.CurrentWrkStaID = "";
    _Interface->DefaultStatusData.CentralComputerID = "";
    _Interface->DefaultStatusData.CurrentCoolingDel = 0;
    _Interface->DefaultStatusData.CurrentCoolingDur = 100;
    _Interface->DefaultStatusData.CurrentCoolingMode = Status_Data::ENERGYMODE;
    _Interface->DefaultStatusData.CurrentCoolingTooling = true;
    _Interface->DefaultStatusData.CycleCount = 0;

    _Interface->DefaultStatusData.RemoteGraphData = false;
//    _Interface->StatusData.AntisideSpliceTime = DEFAULTUNLOADTIME; //Default Unload time should be 1.5s

    for(int i = 0; i<= 7; i++)
    {
        _Interface->DefaultStatusData.Maintenance80PercentAlarm[i] = false;
        _Interface->DefaultStatusData.Maintenance100PercentLock[i] = false;
    }
    _Interface->DefaultStatusData.MaintenanceCountLimits[0] = 400000;
    _Interface->DefaultStatusData.MaintenanceCountLimits[1] = 400000;
    _Interface->DefaultStatusData.MaintenanceCountLimits[2] = 400000;
    _Interface->DefaultStatusData.MaintenanceCountLimits[3] = 400000;

    _Interface->DefaultStatusData.MaintenanceEnergyLimits[0] = 200000;
    _Interface->DefaultStatusData.MaintenanceEnergyLimits[1] = 200000;
    _Interface->DefaultStatusData.MaintenanceEnergyLimits[2] = 200000;
    _Interface->DefaultStatusData.MaintenanceEnergyLimits[3] = 200000;

    _Interface->DefaultStatusData.CurrentCountMaintenanceLimits[0] = 105009;
    _Interface->DefaultStatusData.CurrentCountMaintenanceLimits[1] = 15001;
    _Interface->DefaultStatusData.CurrentCountMaintenanceLimits[2] = 25111;
    _Interface->DefaultStatusData.CurrentCountMaintenanceLimits[3] = 35222;
    _Interface->DefaultStatusData.CurrentCountMaintenanceLimits[4] = 53098086;

    _Interface->DefaultStatusData.CurrentEnergyMaintenanceLimits[0] = 100000;
    _Interface->DefaultStatusData.CurrentEnergyMaintenanceLimits[1] = 100000;
    _Interface->DefaultStatusData.CurrentEnergyMaintenanceLimits[2] = 100000;
    _Interface->DefaultStatusData.CurrentEnergyMaintenanceLimits[3] = 100000;

    QDateTime tmp = QDateTime::fromString("10/20/2016","MM/dd/yyyy");
    _Interface->DefaultStatusData.MaintenanceDateStarted[0] = tmp.toTime_t();
    tmp = QDateTime::fromString("01/20/2015", "MM/dd/yyyy");
    _Interface->DefaultStatusData.MaintenanceDateStarted[1] = tmp.toTime_t();
    tmp = QDateTime::fromString("10/02/2013", "MM/dd/yyyy");
    _Interface->DefaultStatusData.MaintenanceDateStarted[2] = tmp.toTime_t();
    tmp = QDateTime::fromString("08/10/2014", "MM/dd/yyyy");
    _Interface->DefaultStatusData.MaintenanceDateStarted[3] = tmp.toTime_t();
    tmp = QDateTime::fromString("08/10/2014", "MM/dd/yyyy");
    _Interface->DefaultStatusData.MaintenanceDateStarted[4] = tmp.toTime_t();
    tmp = QDateTime::fromString("05/05/2002", "MM/dd/yyyy");
    _Interface->DefaultStatusData.MaintenanceDateStarted[5] = tmp.toTime_t();

    _Interface->DefaultStatusData.ActuatorVersion.clear();
    _Interface->DefaultStatusData.ActuatorPartNumber.clear();
    _Interface->DefaultStatusData.ActuatorSerialNumber.clear();
    _Interface->DefaultStatusData.ActuatorModuleNumber.clear();

    QString str = _Interface->CurrentVersions.ActuatorVersion;

    SetDefaultWeldFormula(&_Interface->DefaultStatusData);
    SetDefaultPassword(&_Interface->DefaultStatusData);
    SetShrinkTubeDefaults(&_Interface->DefaultStatusData);
    SetSoftLimitDefaults(&_Interface->DefaultStatusData);
    SetAWGToMMTable(&_Interface->DefaultStatusData);
}

void M10INI::Get_INI_File()
{
    //Check for presence of Branson.bin file if not present will create.
    QString FileName;
//    Password *_Password = Password::Instance();
    M2010    *_M2010    = M2010::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    UtilityClass *_Utility = UtilityClass::Instance();

    QDir dir;
    FileName = ConfigFilesPath + BRANSON_INI_FILE;
    Init_StatusData();
    if (_Interface->StatusData.ReadStatusDataFromQSetting() == true)
    {
//        bErasePasswords can only be done in the debug mode (Can't be set to true
//        by program)
//        if (_Password->bErasePasswords == true)
//        {
////            cMsgBox GetResString(826)
//            BransonMessageBox tmpMsgBox;
//            tmpMsgBox.MsgPrompt = (QObject::tr("ErasePasswords = TRUE"));
//            tmpMsgBox.MsgTitle  = (QObject::tr("Information"));
//            tmpMsgBox.TipsMode = Information;
//            tmpMsgBox.func_ptr = NULL;
//            _Interface->cMsgBox(&tmpMsgBox);
//            ClearPasswordData();
//        }
    }else
    {
        _Interface->StatusData = _Interface->DefaultStatusData;
        _Interface->StatusData.WriteStatusDataToQSetting();
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
     _Utility->Maxpower = (float)(1.2 * _Interface->StatusData.Soft_Settings.SonicGenWatts);
}

void M10INI::Save_StatusData(bool WithUpdate)
{
//    Saves temp data into data and stores the file
    InterfaceClass* _Interface = InterfaceClass::Instance();
//    UtilityClass* _Utility = UtilityClass::Instance();
    M2010    *_M2010    = M2010::Instance();

    if (WithUpdate == true)
        _Interface->StatusData = _Interface->tempStatusData;
    else
        _Interface->tempStatusData = _Interface->StatusData;

    bool bResult = true;
//    bool bResult = _Utility->WriteToBinaryFile(&_Interface->StatusData,
//                                   (ConfigFilesPath + BRANSON_INI_FILE));
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

void M10INI::CheckBransonFolder()
{
    //the routine checks if the required folders exist in the C drive of
    //the system.If not exist it would be created
    ConfigFilesPath = "c:\\BransonData\\etc\\";
    QDir objDriveSystem;
    if (objDriveSystem.exists("c:\\BransonData\\") == false)
    {
        objDriveSystem.mkdir("c:\\BransonData\\"); //Creates a new directory or folder.
        objDriveSystem.mkdir("c:\\BransonData\\Library\\");
        objDriveSystem.mkdir("c:\\BransonData\\Modular Production\\");
        objDriveSystem.mkdir("c:\\BransonData\\History\\");
//        objDriveSystem.mkdir("c:\\BransonData\\ToolChangeImage\\");
        objDriveSystem.mkdir("c:\\BransonData\\History\\Graph\\");
    }else{
        if (objDriveSystem.exists("c:\\BransonData\\History\\") == false)
           objDriveSystem.mkdir("c:\\BransonData\\History\\");
        else
        {
            if(objDriveSystem.exists("c:\\BransonData\\History\\Graph") == false)
                objDriveSystem.mkdir("c:\\BransonData\\History\\Graph\\");
        }

        if (objDriveSystem.exists("c:\\BransonData\\Library\\") == false)
           objDriveSystem.mkdir("c:\\BransonData\\Library\\");
        else
        {
            if(objDriveSystem.exists("c:\\BransonData\\Library\\SpliceImage\\") == false)
                objDriveSystem.mkdir("c:\\BransonData\\Library\\SpliceImage\\");
        }
        if (objDriveSystem.exists("c:\\BransonData\\Modular Production\\") == false)
            objDriveSystem.mkdir("c:\\BransonData\\Modular Production\\");
        else
        {
            if(objDriveSystem.exists("c:\\BransonData\\Modular Production\\SpliceImage\\") == false)
                objDriveSystem.mkdir("c:\\BransonData\\Modular Production\\SpliceImage\\");
        }
//        if(objDriveSystem.exists("c:\\BransonData\\ToolChangeImage\\") == false)
//            objDriveSystem.mkdir("c:\\BransonData\\ToolChangeImage\\");

    }

    QString FilePathQSTR = ConfigFilesPath;
    if (objDriveSystem.exists(FilePathQSTR) == false)
    {
        objDriveSystem.mkdir(FilePathQSTR);
        size_t size = ConfigFilesPath.length();
        wchar_t *buffer = new wchar_t[size + 1];
        MultiByteToWideChar(CP_ACP,0,ConfigFilesPath.toStdString().c_str(),size,buffer,size * sizeof(wchar_t));
        buffer[size] = 0; //to figure out the '\0' at the end of  array.
        SetFileAttributes(buffer,FILE_ATTRIBUTE_HIDDEN);
        delete []buffer;
    }
    QString strFilePath = "C:\\Users\\jerryw.wang\\AppData\\Local\\Temp\\";
    if(objDriveSystem.exists(strFilePath))
    {
        objDriveSystem.setPath(strFilePath);
        objDriveSystem.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        objDriveSystem.setSorting(QDir::Size | QDir::Reversed);
        QStringList filters;
        filters << "*.tmp";
        objDriveSystem.setNameFilters(filters);// to filter the specific file "*.tmp"
        QFileInfoList list = objDriveSystem.entryInfoList();
        if(list.size() > 0)
        {
            int i = 0;
            do{
                QFileInfo fileInfo = list.at(i);
                fileInfo.dir().remove(fileInfo.fileName());
                i++;
            }while(i < list.size());
        }
    }
}
