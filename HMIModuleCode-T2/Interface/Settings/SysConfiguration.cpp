#include "SysConfiguration.h"
Status_Data Status_Data::operator=(const Status_Data &StatusDataObj) const
{
    Status_Data Obj;
    Obj.RevCode = StatusDataObj.RevCode;
    Obj.CreatedDate = StatusDataObj.CreatedDate;
    Obj.OperatorName = StatusDataObj.OperatorName;

    Obj.Soft_Settings.Lang_Support = StatusDataObj.Soft_Settings.Lang_Support;
    Obj.Soft_Settings.Horn_Calibrate = StatusDataObj.Soft_Settings.Horn_Calibrate;
    Obj.Soft_Settings.AutoPreburst = StatusDataObj.Soft_Settings.AutoPreburst;
//    Obj.Soft_Settings.AutoGetNext = StatusDataObj.Soft_Settings.AutoGetNext;
    Obj.Soft_Settings.SonicGenWatts = StatusDataObj.Soft_Settings.SonicGenWatts;
    Obj.Soft_Settings.ToolCoverIgnore = StatusDataObj.Soft_Settings.ToolCoverIgnore;
    Obj.Soft_Settings.Pressure2Unit = StatusDataObj.Soft_Settings.Pressure2Unit;
    Obj.Soft_Settings.Mm2Awg = StatusDataObj.Soft_Settings.Mm2Awg;
    Obj.Soft_Settings.PWWidth2Height = StatusDataObj.Soft_Settings.PWWidth2Height;
    Obj.Soft_Settings.MinAmplitude = StatusDataObj.Soft_Settings.MinAmplitude;
    Obj.Soft_Settings.MinPressure = StatusDataObj.Soft_Settings.MinPressure;
//    Obj.Soft_Settings.GotoRunScreen = StatusDataObj.Soft_Settings.GotoRunScreen;
//    Obj.Soft_Settings.NoToolCover4SU = StatusDataObj.Soft_Settings.NoToolCover4SU;
    Obj.Soft_Settings.WeldFormula = StatusDataObj.Soft_Settings.WeldFormula;
    Obj.Soft_Settings.RunCount = StatusDataObj.Soft_Settings.RunCount;
    Obj.Soft_Settings.Teach_Mode = StatusDataObj.Soft_Settings.Teach_Mode;
    Obj.Soft_Settings.TunePoint = StatusDataObj.Soft_Settings.TunePoint;
    Obj.Soft_Settings.FrequencyOffset = StatusDataObj.Soft_Settings.FrequencyOffset;

    Obj.Cust_Data.mod10a_settings.UnsignedWeldData =
            StatusDataObj.Cust_Data.mod10a_settings.UnsignedWeldData;
    Obj.Cust_Data.mod10a_settings.AfterBurstDelay =
            StatusDataObj.Cust_Data.mod10a_settings.AfterBurstDelay;
    Obj.Cust_Data.mod10a_settings.AfterBurstDuration =
            StatusDataObj.Cust_Data.mod10a_settings.AfterBurstDuration;
    Obj.Cust_Data.mod10a_settings.EnergyWindowPL =
            StatusDataObj.Cust_Data.mod10a_settings.EnergyWindowPL;
    Obj.Cust_Data.mod10a_settings.PreBurstIndex =
            StatusDataObj.Cust_Data.mod10a_settings.PreBurstIndex;
    for(int i = 0; i < WIDTH_ADJ; i++)
        Obj.Cust_Data.cust_qual_range[i] = StatusDataObj.Cust_Data.cust_qual_range[i];

    for(int i = 0; i< END_SL; i++)
    {
        Obj.HSDATA.HARD_LIMIT[i].TypeHS =
                StatusDataObj.HSDATA.HARD_LIMIT[i].TypeHS;
        Obj.HSDATA.HARD_LIMIT[i].ValueHS =
                StatusDataObj.HSDATA.HARD_LIMIT[i].ValueHS;
        Obj.HSDATA.SOFT_LIMIT[i].TypeHS =
                StatusDataObj.HSDATA.SOFT_LIMIT[i].TypeHS;
        Obj.HSDATA.SOFT_LIMIT[i].ValueHS =
                StatusDataObj.HSDATA.SOFT_LIMIT[i].ValueHS;
    }


    Obj.ComInfo.BaudRate = StatusDataObj.ComInfo.BaudRate;
    Obj.ComInfo.COMport = StatusDataObj.ComInfo.COMport;
    Obj.MachineType = StatusDataObj.MachineType;
    Obj.MachineDate = StatusDataObj.MachineDate;
    Obj.KeepDailyHistory = StatusDataObj.KeepDailyHistory;

    for (int i = 0; i< PERMISSIONLEVEL; i++)
    {
        Obj.PasswordData[i].Identifier = StatusDataObj.PasswordData[i].Identifier;
        Obj.PasswordData[i].Password = StatusDataObj.PasswordData[i].Password;
        Obj.PasswordData[i].PWPermissions = StatusDataObj.PasswordData[i].PWPermissions;
    }

    for (int i = 0; i< FormulaRangSize; i++)
    {
        Obj.WeldSettings4Build[i].MaxRange = StatusDataObj.WeldSettings4Build[i].MaxRange;
        Obj.WeldSettings4Build[i].MinRange = StatusDataObj.WeldSettings4Build[i].MinRange;
        Obj.WeldSettings4Build[i].Multplier = StatusDataObj.WeldSettings4Build[i].Multplier;
        Obj.WeldSettings4Build[i].Offset = StatusDataObj.WeldSettings4Build[i].Offset;
    }

//    for (int i = 0; i< WDSI_SIZE; i++)
//        Obj.WeldSettingsDefault4Build[i] = StatusDataObj.WeldSettingsDefault4Build[i];
//    Obj.WeldSettingDefaultWeldMode = StatusDataObj.WeldSettingDefaultWeldMode;
//    Obj.WeldSettingDefaultTrigPress = StatusDataObj.WeldSettingDefaultTrigPress;
//    Obj.AutoStartLastPart = StatusDataObj.AutoStartLastPart;
    Obj.NRGtoHeightMode = StatusDataObj.NRGtoHeightMode;
    Obj.TubeShrinkMode = StatusDataObj.TubeShrinkMode;
    ShrinkTubeData ShrinkTubeDefaults[STI_SIZE];
    for(int i = 0; i < STI_SIZE; i++)
    {
        Obj.ShrinkTubeDefaults[i].Name = StatusDataObj.ShrinkTubeDefaults[i].Name;
        Obj.ShrinkTubeDefaults[i].temp = StatusDataObj.ShrinkTubeDefaults[i].temp;
        Obj.ShrinkTubeDefaults[i].Time = StatusDataObj.ShrinkTubeDefaults[i].Time;
    }

    Obj.RemoteRecallport = StatusDataObj.RemoteRecallport;
    Obj.SoftLimitsModeFlags = StatusDataObj.SoftLimitsModeFlags;
    Obj.SoftLimitSampleSize = StatusDataObj.SoftLimitSampleSize;
    for(int i = 0; i < SLIControlLimitSize; i++)
        for(int j = 0; j < SLI_Size; j++)
            Obj.SoftLimit[i][j] = StatusDataObj.SoftLimit[i][j];

//    Obj.QualityLimitsModeFlags = StatusDataObj.QualityLimitsModeFlags;
    Obj.FileSystemFlags = StatusDataObj.FileSystemFlags;
    Obj.AutoGetNextDelay = StatusDataObj.AutoGetNextDelay;
    Obj.NetworkingEnabled = StatusDataObj.NetworkingEnabled;
    Obj.CurrentWrkStaID = StatusDataObj.CurrentWrkStaID;
    Obj.CentralComputerID = StatusDataObj.CentralComputerID;
    Obj.ActuatorMode = StatusDataObj.ActuatorMode;
    Obj.AntisideSpliceTime = StatusDataObj.AntisideSpliceTime;
    Obj.CurrentCoolingDur = StatusDataObj.CurrentCoolingDur;
    Obj.CurrentCoolingDel = StatusDataObj.CurrentCoolingDel;
    Obj.CurrentCoolingMode = StatusDataObj.CurrentCoolingMode;
    Obj.CurrentCoolingTooling = StatusDataObj.CurrentCoolingTooling;
    Obj.LockonAlarm = StatusDataObj.LockonAlarm;
    Obj.RunMode = StatusDataObj.RunMode;
    for(int i = 0; i< 4; i++)
        Obj.Machineflags.Word[i] = StatusDataObj.Machineflags.Word[i];

    Obj.CycleCount = StatusDataObj.CycleCount;
    for(int i = 0; i< 8; i++)
    {
        Obj.MaintenanceLimits[i] = StatusDataObj.MaintenanceLimits[i];
        Obj.CurrentMaintenanceLimits[i] = StatusDataObj.CurrentMaintenanceLimits[i];
    }
    Obj.TubeShrinkerport = StatusDataObj.TubeShrinkerport;
    Obj.HistoryGraphData = StatusDataObj.HistoryGraphData;
    Obj.RemoteGraphData = StatusDataObj.RemoteGraphData;
    Obj.StartScreen = StatusDataObj.StartScreen;
    Obj.EnableModularFlag = StatusDataObj.EnableModularFlag;
    PasswordEntry ModularPassword[PASSCOUNT];
    for(int i = 0; i< PASSCOUNT; i++)
    {
        Obj.ModularPassword[i].Identifier = StatusDataObj.ModularPassword[i].Identifier;
        Obj.ModularPassword[i].Password = StatusDataObj.ModularPassword[i].Password;
    }

    Obj.PowerGraphSampleRatio = StatusDataObj.PowerGraphSampleRatio;
    Obj.GraphDataLen = StatusDataObj.GraphDataLen;
    Obj.CutoffMode = StatusDataObj.CutoffMode;
    Obj.LockKeyFlag = StatusDataObj.LockKeyFlag;
    Obj.FootPedalFlag = StatusDataObj.FootPedalFlag;
    return Obj;
}


