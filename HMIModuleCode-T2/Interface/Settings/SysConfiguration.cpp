#include "SysConfiguration.h"
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

    this->Cust_Data.mod10a_settings.UnsignedWeldData =
            StatusDataObj.Cust_Data.mod10a_settings.UnsignedWeldData;
    this->Cust_Data.mod10a_settings.AfterBurstDelay =
            StatusDataObj.Cust_Data.mod10a_settings.AfterBurstDelay;
    this->Cust_Data.mod10a_settings.AfterBurstDuration =
            StatusDataObj.Cust_Data.mod10a_settings.AfterBurstDuration;
    this->Cust_Data.mod10a_settings.EnergyWindowPL =
            StatusDataObj.Cust_Data.mod10a_settings.EnergyWindowPL;
    this->Cust_Data.mod10a_settings.PreBurstIndex =
            StatusDataObj.Cust_Data.mod10a_settings.PreBurstIndex;
    for(int i = 0; i < WIDTH_ADJ; i++)
        this->Cust_Data.cust_qual_range[i] = StatusDataObj.Cust_Data.cust_qual_range[i];

    for(int i = 0; i< END_SL; i++)
    {
        this->HSDATA.HARD_LIMIT[i].TypeHS =
                StatusDataObj.HSDATA.HARD_LIMIT[i].TypeHS;
        this->HSDATA.HARD_LIMIT[i].ValueHS =
                StatusDataObj.HSDATA.HARD_LIMIT[i].ValueHS;
        this->HSDATA.SOFT_LIMIT[i].TypeHS =
                StatusDataObj.HSDATA.SOFT_LIMIT[i].TypeHS;
        this->HSDATA.SOFT_LIMIT[i].ValueHS =
                StatusDataObj.HSDATA.SOFT_LIMIT[i].ValueHS;
    }


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
//        Obj.WeldSettingsDefault4Build[i] = StatusDataObj.WeldSettingsDefault4Build[i];
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
    this->RunMode = StatusDataObj.RunMode;
    for(int i = 0; i< 4; i++)
        this->Machineflags.Word[i] = StatusDataObj.Machineflags.Word[i];

    this->CycleCount = StatusDataObj.CycleCount;
    for(int i = 0; i< 8; i++)
    {
        this->MaintenanceLimits[i] = StatusDataObj.MaintenanceLimits[i];
        this->CurrentMaintenanceLimits[i] = StatusDataObj.CurrentMaintenanceLimits[i];
        this->MaintenanceDateStarted[i] = StatusDataObj.MaintenanceDateStarted[i];
    }
    this->TubeShrinkerport = StatusDataObj.TubeShrinkerport;
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

    return *this;
}


