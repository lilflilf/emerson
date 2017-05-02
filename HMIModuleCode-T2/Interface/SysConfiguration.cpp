#include "SysConfiguration.h"
#include "Modules/M10INI.h"
#include "Modules/UtilityClass.h"
#include <QDir>
#include <QSettings>
#include <QDebug>
Status_Data::Status_Data()
{

}

Status_Data &Status_Data::operator= (const Status_Data &StatusDataObj)
{
    if(this == &StatusDataObj)
        return *this;
    this->RevCode = StatusDataObj.RevCode;
    this->CreatedDate = StatusDataObj.CreatedDate;
    this->OperatorName = StatusDataObj.OperatorName;
    this->AWGToAreaTable.clear();
    QMap<int, int>::const_iterator i = StatusDataObj.AWGToAreaTable.constBegin();
    while(i != StatusDataObj.AWGToAreaTable.constEnd())
    {
        this->AWGToAreaTable.insert(i.key(),i.value());
        ++i;
    }

    this->Soft_Settings.Lang_Support = StatusDataObj.Soft_Settings.Lang_Support;
    this->Soft_Settings.Horn_Calibrate = StatusDataObj.Soft_Settings.Horn_Calibrate;
    this->Soft_Settings.AutoPreburst = StatusDataObj.Soft_Settings.AutoPreburst;
//    Obj.Soft_Settings.AutoGetNext = StatusDataObj.Soft_Settings.AutoGetNext;
    this->Soft_Settings.SonicGenWatts = StatusDataObj.Soft_Settings.SonicGenWatts;
    this->Soft_Settings.ToolCoverIgnore = StatusDataObj.Soft_Settings.ToolCoverIgnore;
    this->Soft_Settings.Pressure2Unit = StatusDataObj.Soft_Settings.Pressure2Unit;
    this->Soft_Settings.Mm2Awg = StatusDataObj.Soft_Settings.Mm2Awg;
    this->Soft_Settings.PWWidth2Height = StatusDataObj.Soft_Settings.PWWidth2Height;
    this->Soft_Settings.MinAmplitude = StatusDataObj.Soft_Settings.MinAmplitude;
    this->Soft_Settings.MinPressure = StatusDataObj.Soft_Settings.MinPressure;
//    Obj.Soft_Settings.GotoRunScreen = StatusDataObj.Soft_Settings.GotoRunScreen;
//    Obj.Soft_Settings.NoToolCover4SU = StatusDataObj.Soft_Settings.NoToolCover4SU;
    this->Soft_Settings.WeldFormula = StatusDataObj.Soft_Settings.WeldFormula;
    this->Soft_Settings.RunCount = StatusDataObj.Soft_Settings.RunCount;
    this->Soft_Settings.Teach_Mode = StatusDataObj.Soft_Settings.Teach_Mode;
    this->Soft_Settings.TunePoint = StatusDataObj.Soft_Settings.TunePoint;
    this->Soft_Settings.FrequencyOffset = StatusDataObj.Soft_Settings.FrequencyOffset;

    for(int i = 0; i < WIDTH_ADJ; i++)
        this->Cust_Data.cust_qual_range[i] = StatusDataObj.Cust_Data.cust_qual_range[i];
    this->Cust_Data.PresetTeachModeSetting = StatusDataObj.Cust_Data.PresetTeachModeSetting;
    this->Cust_Data.StandardRunQuantity = StatusDataObj.Cust_Data.StandardRunQuantity;
    this->Cust_Data.AutoRunQuantity = StatusDataObj.Cust_Data.AutoRunQuantity;
    this->Cust_Data.SigmaRunQuantity = StatusDataObj.Cust_Data.SigmaRunQuantity;

    this->ComInfo.BaudRate = StatusDataObj.ComInfo.BaudRate;
    this->ComInfo.COMport = StatusDataObj.ComInfo.COMport;
    this->MachineType = StatusDataObj.MachineType;
    this->MachineDate = StatusDataObj.MachineDate;
    this->KeepDailyHistory = StatusDataObj.KeepDailyHistory;

    for (int i = 0; i< PERMISSIONLEVEL; i++)
    {
        this->PasswordData[i].Identifier = StatusDataObj.PasswordData[i].Identifier;
        this->PasswordData[i].Password = StatusDataObj.PasswordData[i].Password;
        this->PasswordData[i].PWPermissions = StatusDataObj.PasswordData[i].PWPermissions;
    }
    this->CurrentFunIndex.clear();
    for(int i = 0; i < CurrentFunIndex.size(); i++)
    {
        this->CurrentFunIndex.insert(i, StatusDataObj.CurrentFunIndex.at(i));
    }

    for (int i = 0; i< FormulaRangSize; i++)
    {
        this->WeldSettings4Build[i].MaxRange = StatusDataObj.WeldSettings4Build[i].MaxRange;
        this->WeldSettings4Build[i].MinRange = StatusDataObj.WeldSettings4Build[i].MinRange;
        this->WeldSettings4Build[i].Multplier = StatusDataObj.WeldSettings4Build[i].Multplier;
        this->WeldSettings4Build[i].Offset = StatusDataObj.WeldSettings4Build[i].Offset;
    }

//    for (int i = 0; i< WDSI_SIZE; i++)
//        this->WeldSettingsDefault4Build[i] = StatusDataObj.WeldSettingsDefault4Build[i];
//    Obj.WeldSettingDefaultWeldMode = StatusDataObj.WeldSettingDefaultWeldMode;
//    Obj.WeldSettingDefaultTrigPress = StatusDataObj.WeldSettingDefaultTrigPress;
//    Obj.AutoStartLastPart = StatusDataObj.AutoStartLastPart;
//    Obj.NRGtoHeightMode = StatusDataObj.NRGtoHeightMode;
    this->ShrinkTubeMode = StatusDataObj.ShrinkTubeMode;
    ShrinkTubeData tmpShrinkTube;
    this->ShrinkTubeDefaults.clear();
    for(int i = 0; i < StatusDataObj.ShrinkTubeDefaults.size(); i++)
    {
        tmpShrinkTube.Name = StatusDataObj.ShrinkTubeDefaults[i].Name;
        tmpShrinkTube.temp = StatusDataObj.ShrinkTubeDefaults[i].temp;
        tmpShrinkTube.Time = StatusDataObj.ShrinkTubeDefaults[i].Time;
        this->ShrinkTubeDefaults.insert(i, tmpShrinkTube);
    }

    this->RemoteRecallport = StatusDataObj.RemoteRecallport;
    this->SoftLimitsModeFlags = StatusDataObj.SoftLimitsModeFlags;
    this->SoftLimitSampleSize = StatusDataObj.SoftLimitSampleSize;
    for(int i = 0; i < SLIControlLimitSize; i++)
        for(int j = 0; j < SLI_Size; j++)
            this->SoftLimit[i][j] = StatusDataObj.SoftLimit[i][j];

//    Obj.QualityLimitsModeFlags = StatusDataObj.QualityLimitsModeFlags;
    this->FileSystemFlags = StatusDataObj.FileSystemFlags;
    this->AutoGetNextDelay = StatusDataObj.AutoGetNextDelay;
    this->NetworkingEnabled = StatusDataObj.NetworkingEnabled;
    this->RemoteDataLogging = StatusDataObj.RemoteDataLogging;
    this->CurrentWrkStaID = StatusDataObj.CurrentWrkStaID;
    this->CentralComputerID = StatusDataObj.CentralComputerID;
    this->ActuatorMode = StatusDataObj.ActuatorMode;
    this->AntisideSpliceTime = StatusDataObj.AntisideSpliceTime;
    this->CurrentCoolingDur = StatusDataObj.CurrentCoolingDur;
    this->CurrentCoolingDel = StatusDataObj.CurrentCoolingDel;
    this->CurrentCoolingMode = StatusDataObj.CurrentCoolingMode;
    this->CurrentCoolingTooling = StatusDataObj.CurrentCoolingTooling;
    this->LockonAlarm = StatusDataObj.LockonAlarm;
    this->RunMode.Word = StatusDataObj.RunMode.Word;
    for(int i = 0; i< 4; i++)
        this->Machineflags.Word[i] = StatusDataObj.Machineflags.Word[i];

    this->CycleCount = StatusDataObj.CycleCount;
    for(int i = 0; i< 8; i++)
    {
        this->MaintenanceCountLimits[i] = StatusDataObj.MaintenanceCountLimits[i];
        this->MaintenanceEnergyLimits[i] = StatusDataObj.MaintenanceEnergyLimits[i];
        this->CurrentCountMaintenanceLimits[i] = StatusDataObj.CurrentCountMaintenanceLimits[i];
        this->CurrentEnergyMaintenanceLimits[i] = StatusDataObj.CurrentEnergyMaintenanceLimits[i];
        this->MaintenanceDateStarted[i] = StatusDataObj.MaintenanceDateStarted[i];
        this->Maintenance80PercentAlarm[i] = StatusDataObj.Maintenance80PercentAlarm[i];
        this->Maintenance100PercentLock[i] = StatusDataObj.Maintenance100PercentLock[i];
    }
    this->ShrinkTubeComInfo.COMport = StatusDataObj.ShrinkTubeComInfo.COMport;
    this->ShrinkTubeComInfo.BaudRate = StatusDataObj.ShrinkTubeComInfo.BaudRate;
    this->HistoryGraphData = StatusDataObj.HistoryGraphData;
    this->RemoteGraphData = StatusDataObj.RemoteGraphData;
    this->StartScreen = StatusDataObj.StartScreen;
    this->EnableModularFlag = StatusDataObj.EnableModularFlag;
    for(int i = 0; i< PASSCOUNT; i++)
    {
        this->ModularPassword[i].Identifier = StatusDataObj.ModularPassword[i].Identifier;
        this->ModularPassword[i].Password = StatusDataObj.ModularPassword[i].Password;
    }

    this->GraphSampleRatio = StatusDataObj.GraphSampleRatio;
    this->GraphDataLen = StatusDataObj.GraphDataLen;
    this->CutoffMode = StatusDataObj.CutoffMode;
    this->LockKeyFlag = StatusDataObj.LockKeyFlag;
    this->FootPedalFlag = StatusDataObj.FootPedalFlag;
    this->ServerPort = StatusDataObj.ServerPort;
    this->ModularProductionEnabled = StatusDataObj.ModularProductionEnabled;

    this->ActuatorModuleNumber = StatusDataObj.ActuatorModuleNumber;
    this->ActuatorPartNumber = StatusDataObj.ActuatorPartNumber;
    this->ActuatorSerialNumber = StatusDataObj.ActuatorSerialNumber;
    this->ActuatorVersion = StatusDataObj.ActuatorVersion;
    this->carTemplate.clear();
    QMap<int, QString>::const_iterator it;
    for ( it = StatusDataObj.carTemplate.begin(); it != StatusDataObj.carTemplate.end(); ++it )
    {
        this->carTemplate.insert(it.key(),it.value());
    }
    this->ReliablityMode = StatusDataObj.ReliablityMode;
    this->PhysicalKeyMode = StatusDataObj.PhysicalKeyMode;
    return *this;
}

bool Status_Data::ReadStatusDataFromQSetting()
{
    QDir dir;
    QString str = "";
    M10INI* _M10INI = M10INI::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString FileName = _M10INI->ConfigFilesPath + BRANSON_INI_FILE;
    if (dir.exists(FileName) == false)
        return false;

    QSettings settings(FileName, QSettings::IniFormat);
    settings.beginGroup("BransonInitial");
    RevCode = settings.value("RevCode").value<int>();
    CreatedDate = settings.value("CreatedDate").value<QString>();
    OperatorName = settings.value("OperatorName").value<QString>();

    settings.beginGroup("Soft_Settings");
    int i_tmp = settings.value("Lang_Support").value<int>();
    Soft_Settings.Lang_Support = (enum LangSupport)i_tmp;
    Soft_Settings.Horn_Calibrate = settings.value("Horn_Calibrate").value<int>();
    Soft_Settings.AutoPreburst = settings.value("AutoPreburst").value<int>();
    Soft_Settings.SonicGenWatts = settings.value("SonicGenWatts").value<int>();
    Soft_Settings.ToolCoverIgnore = settings.value("ToolCoverIgnore").value<bool>();
    i_tmp = settings.value("Pressure2Unit").value<int>();
    Soft_Settings.Pressure2Unit = (enum PRESSUREUNIT)i_tmp;
    Soft_Settings.Mm2Awg = settings.value("Mm2Awg").value<bool>();
    Soft_Settings.PWWidth2Height = settings.value("PWWidth2Height").value<float>();
    Soft_Settings.MinAmplitude = settings.value("MinAmplitude").value<int>();
    Soft_Settings.MinPressure = settings.value("MinPressure").value<int>();
    i_tmp = settings.value("WeldFormula").value<int>();
    Soft_Settings.WeldFormula = (enum WeldSetFormula)i_tmp;
    Soft_Settings.RunCount = settings.value("RunCount").value<int>();
    i_tmp = settings.value("Teach_Mode").value<int>();
    Soft_Settings.Teach_Mode = (TEACHMODESETTING::TEACH_MODE_TYPE)i_tmp;
    Soft_Settings.TunePoint = settings.value("TunePoint").value<int>();
    Soft_Settings.FrequencyOffset = settings.value("FrequencyOffset").value<int>();
    settings.endGroup();

    settings.beginGroup("Cust_Data");
    for(int i = 0; i < WIDTH_ADJ; i++)
    {
        str = QString("cust_qual_range%1").arg(QString::number(i,10));
        Cust_Data.cust_qual_range[i] = settings.value(str).value<int>();
    }
    Cust_Data.PresetTeachModeSetting = (QUALITY_DATA_FILE::PRESET_TEACHSETTING)settings.value("PresetTeachModeSetting").value<int>();
    Cust_Data.StandardRunQuantity = settings.value("StandardRunQuantity").value<int>();
    Cust_Data.AutoRunQuantity = settings.value("AutoRunQuantity").value<int>();
    Cust_Data.SigmaRunQuantity = settings.value("SigmaRunQuantity").value<int>();
    settings.endGroup();

    settings.beginGroup("ComInfo");
    ComInfo.BaudRate = settings.value("BaudRate").value<int>();
    ComInfo.COMport = settings.value("COMport").value<unsigned int>();
    settings.endGroup();
    i_tmp = settings.value("MachineType").value<int>();
    MachineType = (enum ActuatorType)i_tmp;
    MachineDate = settings.value("MachineDate").value<QString>();
    KeepDailyHistory = settings.value("KeepDailyHistory").value<bool>();

    for (int i = 0; i< PERMISSIONLEVEL; i++)
    {
        str = QString("PasswordData%1.Identifier").arg(QString::number(i, 10));
        PasswordData[i].Identifier = settings.value(str).value<QString>();
        str = QString("PasswordData%1.Password").arg(QString::number(i, 10));
        PasswordData[i].Password = settings.value(str).value<QString>();
        str = QString("PasswordData%1.PWPermissions").arg(QString::number(i, 10));
        PasswordData[i].PWPermissions = settings.value(str).value<unsigned int>();
    }


    str = settings.value("CurrentFunIndex").value<QString>();
    _Utility->StringJsonToList(str, &CurrentFunIndex);

    for (int i = 0; i< FormulaRangSize; i++)
    {
        str = QString("WeldSettings4Build%1.MaxRange").arg(QString::number(i, 10));
        WeldSettings4Build[i].MaxRange = settings.value(str).value<float>();
        str = QString("WeldSettings4Build%1.MinRange").arg(QString::number(i, 10));
        WeldSettings4Build[i].MinRange = settings.value(str).value<float>();
        str = QString("WeldSettings4Build%1.Multplier").arg(QString::number(i, 10));
        WeldSettings4Build[i].Multplier = settings.value(str).value<float>();
        str = QString("WeldSettings4Build%1.Offset").arg(QString::number(i, 10));
        WeldSettings4Build[i].Offset = settings.value(str).value<float>();
    }

    str = settings.value("ShrinkTubeDefault").value<QString>();
    _Utility->StringJsonToList(str, &ShrinkTubeDefaults);

    RemoteRecallport = settings.value("RemoteRecallport").value<int>();
    SoftLimitsModeFlags = settings.value("SoftLimitsModeFlags").value<unsigned int>();
    SoftLimitSampleSize = settings.value("SoftLimitSampleSize").value<int>();

    for(int i = 0; i < SLIControlLimitSize; i++)
    {
        for(int j = 0; j < SLI_Size; j++)
        {
            str = QString("SoftLimit%1%2").arg(QString::number(i, 10),QString::number(j,10));
            SoftLimit[i][j] = settings.value(str).value<int>();
        }
    }

    FileSystemFlags = settings.value("FileSystemFlags").value<long>();
    AutoGetNextDelay = settings.value("AutoGetNextDelay").value<long>();
    NetworkingEnabled = settings.value("NetworkingEnabled").value<bool>();
    RemoteDataLogging = settings.value("RemoteDataLogging").value<bool>();
    CurrentWrkStaID = settings.value("CurrentWrkStaID").value<QString>();
    CentralComputerID = settings.value("CentralComputerID").value<QString>();
    i_tmp = settings.value("ActuatorMode").value<int>();
    ActuatorMode = (enum ACTUATORMODE)i_tmp;
    AntisideSpliceTime = settings.value("AntisideSpliceTime").value<int>();
    CurrentCoolingDur = settings.value("CurrentCoolingDur").value<int>();
    CurrentCoolingDel = settings.value("CurrentCoolingDel").value<int>();
    i_tmp = settings.value("CurrentCoolingMode").value<int>();
    CurrentCoolingMode = (enum CoolingMode)i_tmp;
    CurrentCoolingTooling = settings.value("CurrentCoolingTooling").value<int>();
    LockonAlarm = settings.value("LockonAlarm").value<int>();
    RunMode.Word = settings.value("RunMode.Word").value<unsigned short>();

    for(int i = 0; i< 4; i++)
    {
        str = QString("Machineflags.Word%1").arg(QString::number(i, 10));
        Machineflags.Word[i] = settings.value(str).value<unsigned short>();
    }

    CycleCount = settings.value("CycleCount").value<long>();

    for(int i = 0; i< 8; i++)
    {
        str = QString("MaintenanceCountLimits%1").arg(QString::number(i, 10));
        MaintenanceCountLimits[i] = settings.value(str).value<long>();
        str = QString("MaintenanceEnergyLimits%1").arg(QString::number(i, 10));
        MaintenanceEnergyLimits[i] = settings.value(str).value<long>();
        str = QString("CurrentCountMaintenanceLimits%1").arg(QString::number(i, 10));
        CurrentCountMaintenanceLimits[i] = settings.value(str).value<long>();
        str = QString("CurrentEnergyMaintenanceLimits%1").arg(QString::number(i, 10));
        CurrentEnergyMaintenanceLimits[i] = settings.value(str).value<long>();
        str = QString("MaintenanceDateStarted%1").arg(QString::number(i, 10));
        MaintenanceDateStarted[i] = settings.value(str).value<unsigned int>();
        str = QString("Maintenance80PercentAlarm%1").arg(QString::number(i, 10));
        Maintenance80PercentAlarm[i] = settings.value(str).value<bool>();
        str = QString("Maintenance100PercentLock%1").arg(QString::number(i, 10));
        Maintenance100PercentLock[i] = settings.value(str).value<bool>();
    }

    settings.beginGroup("ShrinkTubeComInfo");
    ShrinkTubeComInfo.BaudRate = settings.value("ShrinkTubeBaudRate").value<int>();
    ShrinkTubeComInfo.COMport = settings.value("ShrinkTubeCOMPort").value<unsigned int>();
    settings.endGroup();

    HistoryGraphData = settings.value("HistoryGraphData").value<bool>();
    RemoteGraphData = settings.value("RemoteGraphData").value<bool>();
    i_tmp = settings.value("StartScreen").value<int>();
    StartScreen = (enum SCREEN_MODE)i_tmp;
    EnableModularFlag = settings.value("EnableModularFlag").value<bool>();

    for(int i = 0; i< PASSCOUNT; i++)
    {
        str = QString("ModularPassword%1.Identifier").arg(QString::number(i, 10));
        ModularPassword[i].Identifier = settings.value(str).value<QString>();
        str = QString("ModularPassword%1.Password").arg(QString::number(i, 10));
        ModularPassword[i].Password = settings.value(str).value<QString>();
    }

    i_tmp = settings.value("GraphSampleRatio").value<int>();
    GraphSampleRatio = (WeldResultElement::SAMPLERATIO)i_tmp;
    GraphDataLen = settings.value("GraphDataLen").value<long>();
    CutoffMode = settings.value("CutoffMode").value<int>();
    LockKeyFlag = settings.value("LockKeyFlag").value<bool>();
    FootPedalFlag = settings.value("FootPedalFlag").value<bool>();
    ServerPort = settings.value("ServerPort").value<int>();
    ModularProductionEnabled = settings.value("ModularProductionEnabled").value<bool>();

    ActuatorModuleNumber = settings.value("ActuatorModuleNumber").value<QString>();
    ActuatorPartNumber = settings.value("ActuatorPartNumber").value<QString>();
    ActuatorSerialNumber = settings.value("ActuatorSerialNumber").value<QString>();
    ActuatorVersion = settings.value("ActuatorVersion").value<QString>();

    str = settings.value("carTemplate").value<QString>();
    _Utility->StringJsonToMap(str, &carTemplate);

    settings.endGroup();
    return true;

}

void Status_Data::WriteStatusDataToQSetting()
{
    QString str; //BransonInitial
    M10INI* _M10INI = M10INI::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString FileName = _M10INI->ConfigFilesPath + BRANSON_INI_FILE;
    QSettings settings(FileName, QSettings::IniFormat);
    settings.beginGroup("BransonInitial");
    settings.setValue("RevCode", RevCode);
    settings.setValue("CreatedDate", CreatedDate);
    settings.setValue("OperatorName", OperatorName);

    settings.beginGroup("Soft_Settings");
    settings.setValue("Lang_Support", Soft_Settings.Lang_Support);
    settings.setValue("Horn_Calibrate", Soft_Settings.Horn_Calibrate);
    settings.setValue("AutoPreburst", Soft_Settings.AutoPreburst);
    settings.setValue("SonicGenWatts", Soft_Settings.SonicGenWatts);
    settings.setValue("ToolCoverIgnore", Soft_Settings.ToolCoverIgnore);
    settings.setValue("Pressure2Unit", Soft_Settings.Pressure2Unit);
    settings.setValue("Mm2Awg", Soft_Settings.Mm2Awg);
    settings.setValue("PWWidth2Height", Soft_Settings.PWWidth2Height);
    settings.setValue("MinAmplitude", Soft_Settings.MinAmplitude);
    settings.setValue("MinPressure", Soft_Settings.MinPressure);
    settings.setValue("WeldFormula", Soft_Settings.WeldFormula);
    settings.setValue("RunCount", Soft_Settings.RunCount);
    settings.setValue("Teach_Mode", Soft_Settings.Teach_Mode);
    settings.setValue("TunePoint", Soft_Settings.TunePoint);
    settings.setValue("FrequencyOffset", Soft_Settings.FrequencyOffset);
    settings.endGroup();

    settings.beginGroup("Cust_Data");
    for(int i = 0; i < WIDTH_ADJ; i++)
    {
        str = QString("cust_qual_range%1").arg(QString::number(i,10));
        settings.setValue(str,Cust_Data.cust_qual_range[i]);
    }
    settings.setValue("PresetTeachModeSetting", Cust_Data.PresetTeachModeSetting);
    settings.setValue("StandardRunQuantity", Cust_Data.StandardRunQuantity);
    settings.setValue("AutoRunQuantity", Cust_Data.AutoRunQuantity);
    settings.setValue("SigmaRunQuantity", Cust_Data.SigmaRunQuantity);
    settings.endGroup();

    settings.beginGroup("ComInfo");
    settings.setValue("BaudRate", ComInfo.BaudRate);
    settings.setValue("COMport", ComInfo.COMport);
    settings.endGroup();
    settings.setValue("MachineType", MachineType);
    settings.setValue("MachineDate", MachineDate);
    settings.setValue("KeepDailyHistory", KeepDailyHistory);

    for (int i = 0; i< PERMISSIONLEVEL; i++)
    {
        str = QString("PasswordData%1.Identifier").arg(QString::number(i, 10));
        settings.setValue(str, PasswordData[i].Identifier);
        str = QString("PasswordData%1.Password").arg(QString::number(i, 10));
        settings.setValue(str, PasswordData[i].Password);
        str = QString("PasswordData%1.PWPermissions").arg(QString::number(i, 10));
        settings.setValue(str, PasswordData[i].PWPermissions);
    }

    QString Str;
    _Utility->ListJsonToString(&CurrentFunIndex, Str);
    settings.setValue("CurrentFunIndex", Str);

    for (int i = 0; i< FormulaRangSize; i++)
    {
        str = QString("WeldSettings4Build%1.MaxRange").arg(QString::number(i, 10));
        settings.setValue(str, WeldSettings4Build[i].MaxRange);
        str = QString("WeldSettings4Build%1.MinRange").arg(QString::number(i, 10));
        settings.setValue(str, WeldSettings4Build[i].MinRange);
        str = QString("WeldSettings4Build%1.Multplier").arg(QString::number(i, 10));
        settings.setValue(str, WeldSettings4Build[i].Multplier);
        str = QString("WeldSettings4Build%1.Offset").arg(QString::number(i, 10));
        settings.setValue(str, WeldSettings4Build[i].Offset);
    }

    _Utility->ListJsonToString(&ShrinkTubeDefaults, str);
    settings.setValue("ShrinkTubeDefault", str);

    settings.setValue("RemoteRecallport", RemoteRecallport);
    settings.setValue("SoftLimitsModeFlags", SoftLimitsModeFlags);
    settings.setValue("SoftLimitSampleSize", SoftLimitSampleSize);

    for(int i = 0; i < SLIControlLimitSize; i++)
    {
        for(int j = 0; j < SLI_Size; j++)
        {
            str = QString("SoftLimit%1%2").arg(QString::number(i, 10),QString::number(j,10));
            settings.setValue(str, SoftLimit[i][j]);
        }
    }

    settings.setValue("FileSystemFlags", FileSystemFlags);
    settings.setValue("AutoGetNextDelay", AutoGetNextDelay);
    settings.setValue("NetworkingEnabled", NetworkingEnabled);
    settings.setValue("RemoteDataLogging", RemoteDataLogging);
    settings.setValue("CurrentWrkStaID", CurrentWrkStaID);
    settings.setValue("CentralComputerID", CentralComputerID);
    settings.setValue("ActuatorMode", ActuatorMode);
    settings.setValue("AntisideSpliceTime", AntisideSpliceTime);
    settings.setValue("CurrentCoolingDur", CurrentCoolingDur);
    settings.setValue("CurrentCoolingDel", CurrentCoolingDel);
    settings.setValue("CurrentCoolingMode", CurrentCoolingMode);
    settings.setValue("CurrentCoolingTooling", CurrentCoolingTooling);
    settings.setValue("LockonAlarm", LockonAlarm);
    settings.setValue("RunMode.Word", RunMode.Word);

    for(int i = 0; i< 4; i++)
    {
        str = QString("Machineflags.Word%1").arg(QString::number(i, 10));
        settings.setValue(str, Machineflags.Word[i]);
    }

    settings.setValue("CycleCount", CycleCount);

    for(int i = 0; i< 8; i++)
    {
        str = QString("MaintenanceCountLimits%1").arg(QString::number(i, 10));
        settings.setValue(str, MaintenanceCountLimits[i]);
        str = QString("MaintenanceEnergyLimits%1").arg(QString::number(i, 10));
        settings.setValue(str, MaintenanceEnergyLimits[i]);
        str = QString("CurrentCountMaintenanceLimits%1").arg(QString::number(i, 10));
        settings.setValue(str, CurrentCountMaintenanceLimits[i]);
        str = QString("CurrentEnergyMaintenanceLimits%1").arg(QString::number(i, 10));
        settings.setValue(str, CurrentEnergyMaintenanceLimits[i]);
        str = QString("MaintenanceDateStarted%1").arg(QString::number(i, 10));
        settings.setValue(str, MaintenanceDateStarted[i]);
        str = QString("Maintenance80PercentAlarm%1").arg(QString::number(i, 10));
        settings.setValue(str, Maintenance80PercentAlarm[i]);
        str = QString("Maintenance100PercentLock%1").arg(QString::number(i, 10));
        settings.setValue(str, Maintenance100PercentLock[i]);
    }


    settings.beginGroup("ShrinkTubeComInfo");
    settings.setValue("ShrinkTubeBaudRate", ShrinkTubeComInfo.BaudRate);
    settings.setValue("ShrinkTubeCOMPort", ShrinkTubeComInfo.COMport);
    settings.endGroup();

    settings.setValue("HistoryGraphData", HistoryGraphData);
    settings.setValue("RemoteGraphData", RemoteGraphData);
    settings.setValue("StartScreen", StartScreen);
    settings.setValue("EnableModularFlag", EnableModularFlag);

    for(int i = 0; i< PASSCOUNT; i++)
    {
        str = QString("ModularPassword%1.Identifier").arg(QString::number(i, 10));
        settings.setValue(str, ModularPassword[i].Identifier);
        str = QString("ModularPassword%1.Password").arg(QString::number(i, 10));
        settings.setValue(str, ModularPassword[i].Password);
    }

    settings.setValue("GraphSampleRatio", GraphSampleRatio);
    settings.setValue("GraphDataLen", GraphDataLen);
    settings.setValue("CutoffMode", CutoffMode);
    settings.setValue("LockKeyFlag", LockKeyFlag);
    settings.setValue("FootPedalFlag", FootPedalFlag);
    settings.setValue("ServerPort", ServerPort);
    settings.setValue("ModularProductionEnabled", ModularProductionEnabled);

    settings.setValue("ActuatorModuleNumber", ActuatorModuleNumber);
    settings.setValue("ActuatorPartNumber", ActuatorPartNumber);
    settings.setValue("ActuatorSerialNumber", ActuatorSerialNumber);
    settings.setValue("ActuatorVersion", ActuatorVersion);

    _Utility->MapJsonToString(&carTemplate, str);
    settings.setValue("carTemplate", str);

    settings.endGroup();
}
