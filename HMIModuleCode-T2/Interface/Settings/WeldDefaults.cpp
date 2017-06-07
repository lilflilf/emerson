#include "WeldDefaults.h"
#include "Interface/Interface.h"
#include "Interface/SysConfiguration.h"
#include "Modules/M10INI.h"
#include "Modules/M10definitions.h"
#include "Modules/UtilityClass.h"
#include "Modules/typedef.h"
#include "Modules/M102IA.h"
#include "Modules/M2010.h"
#include <QDebug>

WeldDefaults::WeldDefaults(QObject *parent) : QObject(parent)
{
}

void WeldDefaults::InitWeldSettings()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    M10INI* _M10INI = M10INI::Instance();
    if(_Interface->tempStatusData.WeldSettings4Build[0].Multplier <
            Minmm2EnergyMult)
    {
        _M10INI->SetDefaultWeldFormula(&_Interface->tempStatusData);
    }
    WeldSettingsInfo[SDNEnergy].MultRatio = 1;
    WeldSettingsInfo[SDNEnergy].MultMin = Minmm2EnergyMult;
    WeldSettingsInfo[SDNEnergy].MultMax = Maxmm2EnergyMult;
    WeldSettingsInfo[SDNEnergy].MultFormat = "%.2f";
    WeldSettingsInfo[SDNEnergy].OffsetRatio = 1;
    WeldSettingsInfo[SDNEnergy].OffsetMin = Minmm2EnergyOffset;
    WeldSettingsInfo[SDNEnergy].OffsetMax = Maxmm2EnergyOffset;
    WeldSettingsInfo[SDNEnergy].OffsetFormat = "%.2fJ";

    WeldSettingsInfo[SDNWidth].MultRatio = 100;
    WeldSettingsInfo[SDNWidth].MultMin = Minmm2WidthAreaRatio;
    WeldSettingsInfo[SDNWidth].MultMax = Maxmm2WidthAreaRatio;
    WeldSettingsInfo[SDNWidth].MultFormat = "%.2f";
    WeldSettingsInfo[SDNWidth].OffsetRatio = 1;
    WeldSettingsInfo[SDNWidth].OffsetMin = 0;
    WeldSettingsInfo[SDNWidth].OffsetMax = 0;
    WeldSettingsInfo[SDNWidth].OffsetFormat = "%dmm";

    WeldSettingsInfo[SDNWeldPressure].MultRatio = 100;
    WeldSettingsInfo[SDNWeldPressure].MultMin = Minmm2PressMult;
    WeldSettingsInfo[SDNWeldPressure].MultMax = Maxmm2PressMult;
    WeldSettingsInfo[SDNWeldPressure].MultFormat = "%.2f";
    WeldSettingsInfo[SDNWeldPressure].OffsetRatio = 10;
    WeldSettingsInfo[SDNWeldPressure].OffsetMin = Minmm2PressOffset;
    WeldSettingsInfo[SDNWeldPressure].OffsetMax = Maxmm2PressOffset;
    WeldSettingsInfo[SDNWeldPressure].OffsetFormat = "%.1fPSI";

    WeldSettingsInfo[SDNAmplitude].MultRatio = 10;
    WeldSettingsInfo[SDNAmplitude].MultMin = Minmm2AmplitudeMult;
    WeldSettingsInfo[SDNAmplitude].MultMax = Maxmm2AmplitudeMult;
    WeldSettingsInfo[SDNAmplitude].MultFormat = "%.2f";
    WeldSettingsInfo[SDNAmplitude].OffsetRatio = 1;
    WeldSettingsInfo[SDNAmplitude].OffsetMin = Minmm2AmplitudeOffset;
    WeldSettingsInfo[SDNAmplitude].OffsetMax = Maxmm2AmplitudeOffset;
    WeldSettingsInfo[SDNAmplitude].OffsetFormat = "%.2fμm";
}

void WeldDefaults::_Default()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    M10INI* _M10INI = M10INI::Instance();
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();

    _Interface->StatusData.Soft_Settings.Square2Unit =
            _Interface->DefaultStatusData.Soft_Settings.Square2Unit;
    _Interface->StatusData.Soft_Settings.Length2Unit =
            _Interface->DefaultStatusData.Soft_Settings.Length2Unit;
    _Interface->StatusData.Soft_Settings.Pressure2Unit =
            _Interface->DefaultStatusData.Soft_Settings.Pressure2Unit;

    _Utility->InitializeTextData();

    unsigned short Machineflags = _M10INI->TempSysConfig.Machineflags[0];
    _Interface->StatusData.Machineflags.Flag.WdthEncoderOff =
            _Interface->DefaultStatusData.Machineflags.Flag.WdthEncoderOff;
    if(_Interface->StatusData.Machineflags.Flag.WdthEncoderOff == ON)
        _M10INI->TempSysConfig.Machineflags[0] |= 0x4000;
    else
        _M10INI->TempSysConfig.Machineflags[0] &= ~0x4000;

    _Interface->StatusData.Machineflags.Flag.HgtEncoderOff =
            _Interface->DefaultStatusData.Machineflags.Flag.HgtEncoderOff;
    if(_Interface->StatusData.Machineflags.Flag.HgtEncoderOff == ON)
        _M10INI->TempSysConfig.Machineflags[0] |= 0x8000;
    else
        _M10INI->TempSysConfig.Machineflags[0] &= ~0x8000;

    _Interface->StatusData.Machineflags.Flag.SeekOff =
            _Interface->DefaultStatusData.Machineflags.Flag.SeekOff;
    if(_Interface->StatusData.Machineflags.Flag.SeekOff == ON)
        _M10INI->TempSysConfig.Machineflags[0] |= 0x1000;
    else
        _M10INI->TempSysConfig.Machineflags[0] &= ~0x1000;

    if(Machineflags != _M10INI->TempSysConfig.Machineflags[0])
    {
        _M2010->ReceiveFlags.MachineFlagsData = false;
        _M102IA->SendIACommand(IAComSetMachineFlags, 0);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.MachineFlagsData);
    }

    unsigned short RunMode = _M10INI->TempSysConfig.RunMode;
    _Interface->StatusData.RunMode.ModeFlag.DefeatWeldAbort =
            _Interface->DefaultStatusData.RunMode.ModeFlag.DefeatWeldAbort;
    if(_Interface->StatusData.RunMode.ModeFlag.DefeatWeldAbort == ON)
        _M10INI->TempSysConfig.RunMode &= ~0x1000;
    else
        _M10INI->TempSysConfig.RunMode |= 0x1000;
    if(RunMode != _M10INI->TempSysConfig.RunMode)
    {
        _M2010->ReceiveFlags.FootPadelDATA = false;
        _M102IA->SendIACommand(IAComSetRunModeNew, _M10INI->TempSysConfig.RunMode);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.FootPadelDATA);
    }

    unsigned short CoolingMode = _M10INI->TempSysConfig.CoolingMode;
    bool CoolingChange = false;
    _Interface->StatusData.CurrentCoolingMode =
            _Interface->DefaultStatusData.CurrentCoolingMode;
    if(CoolingMode != _Interface->StatusData.CurrentCoolingMode)
    {
        _M10INI->TempSysConfig.CoolingMode =
                _Interface->StatusData.CurrentCoolingMode;
        CoolingChange = true;
    }

    unsigned short CoolingTooling = _M10INI->TempSysConfig.CoolingTooling;
    _Interface->StatusData.CurrentCoolingTooling =
            _Interface->DefaultStatusData.CurrentCoolingTooling;
    if(CoolingTooling != (unsigned short)_Interface->StatusData.CurrentCoolingTooling)
    {
        _M10INI->TempSysConfig.CoolingTooling =
                (unsigned short)_Interface->StatusData.CurrentCoolingTooling;
        CoolingChange = true;
    }

    unsigned short CoolingDur = _M10INI->TempSysConfig.CoolingDur;
    _Interface->StatusData.CurrentCoolingDur =
            _Interface->DefaultStatusData.CurrentCoolingDur;
    if(CoolingDur != _Interface->StatusData.CurrentCoolingDur)
    {
        _M10INI->TempSysConfig.CoolingDur =
                _Interface->StatusData.CurrentCoolingDur;
        CoolingChange = true;
    }

    unsigned short CoolingDel = _M10INI->TempSysConfig.CoolingDel;
    _Interface->StatusData.CurrentCoolingDel =
            _Interface->DefaultStatusData.CurrentCoolingDel;
    if(CoolingDel != _Interface->StatusData.CurrentCoolingDel)
    {
        _M10INI->TempSysConfig.CoolingDel =
                _Interface->StatusData.CurrentCoolingDel;
        CoolingChange = true;
    }
    if(CoolingChange == true)
    {
        _M2010->ReceiveFlags.CoolingTypeData = false;
        _M102IA->SendIACommand(IAComSetCooling, 0);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.CoolingTypeData);
    }

    unsigned short LockonAlarm = _M10INI->TempSysConfig.LockAlarm;
    _Interface->StatusData.LockonAlarm = _Interface->DefaultStatusData.LockonAlarm;
    if(LockonAlarm != _Interface->StatusData.LockonAlarm)
    {
        _M10INI->TempSysConfig.LockAlarm = _Interface->StatusData.LockonAlarm;
        _M2010->ReceiveFlags.LockOnAlarmData = false;
        _M102IA->SendIACommand(IAComSetLockonAlarm, _M10INI->TempSysConfig.LockAlarm);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.LockOnAlarmData);
    }

    _Interface->StatusData.KeepDailyHistory =
            _Interface->DefaultStatusData.KeepDailyHistory;
    _Interface->StatusData.HistoryGraphData =
            _Interface->DefaultStatusData.HistoryGraphData;
    _Interface->StatusData.GraphSampleRatio =
            _Interface->DefaultStatusData.GraphSampleRatio;

    for(int i = EnergyR1; i < FormulaRangSize; i++)
    {
        _Interface->StatusData.WeldSettings4Build[i].MinRange =
                _Interface->DefaultStatusData.WeldSettings4Build[i].MinRange;
        _Interface->StatusData.WeldSettings4Build[i].MaxRange =
                _Interface->DefaultStatusData.WeldSettings4Build[i].MaxRange;
        _Interface->StatusData.WeldSettings4Build[i].Offset =
                _Interface->DefaultStatusData.WeldSettings4Build[i].Offset;
        _Interface->StatusData.WeldSettings4Build[i].Multplier =
                _Interface->DefaultStatusData.WeldSettings4Build[i].Multplier;

    }
    _Interface->StatusData.WriteStatusDataToQSetting();
}

bool WeldDefaults::_Recall()
{

    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    M10INI* _M10INI = M10INI::Instance();
    switch(_Interface->StatusData.Soft_Settings.Pressure2Unit)
    {
    case BRANSON_INI_STRUCT::ToPSI:
        CurrentWeldSettings.Pressure2Unit = BRANSON_INI_STRUCT::ToPSI;
        break;
    case BRANSON_INI_STRUCT::ToBar:
        CurrentWeldSettings.Pressure2Unit = BRANSON_INI_STRUCT::ToBar;
        break;
    case BRANSON_INI_STRUCT::TokPa:
        CurrentWeldSettings.Pressure2Unit = BRANSON_INI_STRUCT::TokPa;
        break;
    default:
        CurrentWeldSettings.Pressure2Unit = BRANSON_INI_STRUCT::ToPSI;
        break;
    }
    switch(_Interface->StatusData.Soft_Settings.Square2Unit)
    {
    case BRANSON_INI_STRUCT::ToSqrMM:
        CurrentWeldSettings.Square2Unit = BRANSON_INI_STRUCT::ToSqrMM;
        break;
    case BRANSON_INI_STRUCT::ToAWG:
        CurrentWeldSettings.Square2Unit = BRANSON_INI_STRUCT::ToAWG;
        break;
    default:
        CurrentWeldSettings.Square2Unit = BRANSON_INI_STRUCT::ToSqrMM;
        break;
    }
    switch(_Interface->StatusData.Soft_Settings.Length2Unit)
    {
    case BRANSON_INI_STRUCT::ToMM:
        CurrentWeldSettings.Length2Unit = BRANSON_INI_STRUCT::ToMM;
        break;
    case BRANSON_INI_STRUCT::ToINCH:
        CurrentWeldSettings.Length2Unit = BRANSON_INI_STRUCT::ToINCH;
        break;
    default:
        CurrentWeldSettings.Length2Unit = BRANSON_INI_STRUCT::ToMM;
        break;
    }

    _Utility->InitializeTextData();

    _M2010->ReceiveFlags.MachineFlagsData = false;
    _M102IA->IACommand(IAComGetMachineFlags);
    _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.MachineFlagsData);

    if(_M2010->ReceiveFlags.MachineFlagsData == true)
    {
        if((_M10INI->TempSysConfig.Machineflags[0] & 0x1000) == 0x1000)
            _Interface->StatusData.Machineflags.Flag.SeekOff = ON;
        else
            _Interface->StatusData.Machineflags.Flag.SeekOff = OFF;

        if((_M10INI->TempSysConfig.Machineflags[0] & 0x4000) == 0x4000)
            _Interface->StatusData.Machineflags.Flag.WdthEncoderOff = ON;
        else
            _Interface->StatusData.Machineflags.Flag.WdthEncoderOff = OFF;

        if((_M10INI->TempSysConfig.Machineflags[0] & 0x8000) == 0x8000)
            _Interface->StatusData.Machineflags.Flag.HgtEncoderOff = ON;
        else
            _Interface->StatusData.Machineflags.Flag.HgtEncoderOff = OFF;

    }
    if(_Interface->StatusData.Machineflags.Flag.WdthEncoderOff == OFF)
        CurrentWeldSettings.WidthEncoder = true;
    else
        CurrentWeldSettings.WidthEncoder = false;
    if(_Interface->StatusData.Machineflags.Flag.HgtEncoderOff == OFF)
        CurrentWeldSettings.HeightEncoder = true;
    else
        CurrentWeldSettings.HeightEncoder = false;
    if(_Interface->StatusData.Machineflags.Flag.SeekOff == OFF)
        CurrentWeldSettings.Seek = true;
    else
        CurrentWeldSettings.Seek = false;

    _M2010->ReceiveFlags.FootPadelDATA = false;
    _M102IA->IACommand(IAComGetRunModeNew);
    _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.FootPadelDATA);
    if(_M2010->ReceiveFlags.FootPadelDATA == true)
    {
        if((_M10INI->TempSysConfig.RunMode & 0x1000) == 0x1000)
            _Interface->StatusData.RunMode.ModeFlag.DefeatWeldAbort = OFF;
        else
            _Interface->StatusData.RunMode.ModeFlag.DefeatWeldAbort = ON;
    }
    if(_Interface->StatusData.RunMode.ModeFlag.DefeatWeldAbort == 1)
        CurrentWeldSettings.FootPedalAbort = true;
    else
        CurrentWeldSettings.FootPedalAbort = false;

    _M2010->ReceiveFlags.CoolingTypeData = false;
    _M102IA->IACommand(IAComGetCooling);
    _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.CoolingTypeData);
    if(_M2010->ReceiveFlags.CoolingTypeData == true)
    {
        _Interface->StatusData.CurrentCoolingMode =
                (Status_Data::CoolingMode)_M10INI->TempSysConfig.CoolingMode;
        _Interface->StatusData.CurrentCoolingTooling =
                _M10INI->TempSysConfig.CoolingTooling;
        _Interface->StatusData.CurrentCoolingDur =
                _M10INI->TempSysConfig.CoolingDur;
        _Interface->StatusData.CurrentCoolingDel =
                _M10INI->TempSysConfig.CoolingDel;
    }

    CurrentWeldSettings.CurrentCoolingMode =
            _Interface->StatusData.CurrentCoolingMode;
    CurrentWeldSettings.CoolingForTooling =
            _Interface->StatusData.CurrentCoolingTooling;

    CurrentWeldSettings.CurrentCoolingDur.Current =
            _Utility->FormatedDataToString(DINCoolDur, _Interface->StatusData.CurrentCoolingDur);
    CurrentWeldSettings.CurrentCoolingDur.Maximum =
            _Utility->FormatedDataToString(DINCoolDur, MAXCOOLDUR);
    CurrentWeldSettings.CurrentCoolingDur.Minimum =
            _Utility->FormatedDataToString(DINCoolDur, MINCOOLDUR);

    CurrentWeldSettings.CurrentCoolingDel.Current =
            _Utility->FormatedDataToString(DINCoolDel, _Interface->StatusData.CurrentCoolingDel);
    CurrentWeldSettings.CurrentCoolingDel.Maximum =
            _Utility->FormatedDataToString(DINCoolDel, MAXCOOLDEL);
    CurrentWeldSettings.CurrentCoolingDel.Minimum =
            _Utility->FormatedDataToString(DINCoolDel, MINCOOLDEL);

    _Interface->StatusData.KeepDailyHistory = true;
    CurrentWeldSettings.SampleRatio =
            _Interface->StatusData.GraphSampleRatio;

    float area = 0;
    float offset = 0;
    float multiplier = 0;
    QString str;
    for(int i = EnergyR1; i < FormulaRangSize; i++)
    {
        area = _Interface->StatusData.WeldSettings4Build[i].MinRange;
        str = _Utility->FormatedDataToString(DINFormulaArea,area);
        CurrentWeldSettings.WeldSettingFormula[i].Range.Current = str;
        switch (i)
        {
        case EnergyR1:
        case WidthR1:
        case PressureR1:
        case AmplitudeR1:
            str = _Utility->FormatedDataToString(DINFormulaArea,MINFORMULAAREA);
            CurrentWeldSettings.WeldSettingFormula[i].Range.Minimum = str;
            area = _Interface->StatusData.WeldSettings4Build[i].MaxRange;
            str = _Utility->FormatedDataToString(DINFormulaArea, (float)(area - 0.01));
            CurrentWeldSettings.WeldSettingFormula[i].Range.Maximum = str;
            break;
        case EnergyR2:
        case WidthR2:
        case PressureR2:
        case AmplitudeR2:
            area = _Interface->StatusData.WeldSettings4Build[i-1].MinRange;
            str = _Utility->FormatedDataToString(DINFormulaArea, (float)(area + 0.02));
            CurrentWeldSettings.WeldSettingFormula[i].Range.Minimum = str;
            area = _Interface->StatusData.WeldSettings4Build[i].MaxRange;
            str = _Utility->FormatedDataToString(DINFormulaArea, (float)(area - 0.01));
            CurrentWeldSettings.WeldSettingFormula[i].Range.Maximum = str;
            break;
        case EnergyR3:
        case WidthR3:
        case PressureR3:
        case AmplitudeR3:
            area = _Interface->StatusData.WeldSettings4Build[i-1].MinRange;
            str = _Utility->FormatedDataToString(DINFormulaArea, float(area + 0.02));
            CurrentWeldSettings.WeldSettingFormula[i].Range.Minimum = str;
            area = _Interface->StatusData.WeldSettings4Build[i].MaxRange;
            str = _Utility->FormatedDataToString(DINFormulaArea, (float)(area - 0.01));
            CurrentWeldSettings.WeldSettingFormula[i].Range.Maximum = str;
            break;
        case EnergyR4:
        case WidthR4:
        case PressureR4:
        case AmplitudeR4:
            area = _Interface->StatusData.WeldSettings4Build[i - 1].MinRange;
            str = _Utility->FormatedDataToString(DINFormulaArea, float(area + 0.02));
            CurrentWeldSettings.WeldSettingFormula[i].Range.Minimum = str;
            str = _Utility->FormatedDataToString(DINFormulaArea,MAXFORMULAAREA);
            CurrentWeldSettings.WeldSettingFormula[i].Range.Maximum = str;
            break;
        }
        offset = _Interface->StatusData.WeldSettings4Build[i].Offset;
        multiplier = _Interface->StatusData.WeldSettings4Build[i].Multplier ;
        switch (i)
        {
        case EnergyR1:
        case EnergyR2:
        case EnergyR3:
        case EnergyR4:
            str = _Utility->FormatedDataToString(DINFormulaEnergyOffset, offset);
            CurrentWeldSettings.WeldSettingFormula[i].Offset.Current = str;
            str = _Utility->FormatedDataToString(DINFormulaEnergyOffset, Maxmm2EnergyOffset);
            CurrentWeldSettings.WeldSettingFormula[i].Offset.Maximum = str;
            str = _Utility->FormatedDataToString(DINFormulaEnergyOffset, Maxmm2EnergyOffset);
            CurrentWeldSettings.WeldSettingFormula[i].Offset.Minimum = str;

            str = _Utility->FormatedDataToString(DINFormulaEnergyMult, multiplier);
            CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Current = str;
            str = _Utility->FormatedDataToString(DINFormulaEnergyMult, Maxmm2EnergyMult);
            CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Maximum = str;
            str = _Utility->FormatedDataToString(DINFormulaEnergyMult, Minmm2EnergyMult);
            CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Minimum = str;
            CurrentWeldSettings.WeldSettingFormula[i].Identifier = FormulaIdentifer[0];
            break;
        case WidthR1:
        case WidthR2:
        case WidthR3:
        case WidthR4:
            str = _Utility->FormatedDataToString(DINFormulaWidthOffset, offset);
            CurrentWeldSettings.WeldSettingFormula[i].Offset.Current = str;
            str = _Utility->FormatedDataToString(DINFormulaWidthOffset, 0);
            CurrentWeldSettings.WeldSettingFormula[i].Offset.Maximum = str;
            str = _Utility->FormatedDataToString(DINFormulaWidthOffset, 0);
            CurrentWeldSettings.WeldSettingFormula[i].Offset.Minimum = str;

            str = _Utility->FormatedDataToString(DINFormulaWidthMult, multiplier);
            CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Current = str;
            str = _Utility->FormatedDataToString(DINFormulaWidthMult, Maxmm2WidthAreaRatio);
            CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Maximum = str;
            str = _Utility->FormatedDataToString(DINFormulaEnergyMult, (float)Minmm2WidthAreaRatio);
            CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Minimum = str;

            CurrentWeldSettings.WeldSettingFormula[i].Identifier = FormulaIdentifer[1];
            break;
        case PressureR1:
        case PressureR2:
        case PressureR3:
        case PressureR4:
            str = _Utility->FormatedDataToString(DINFormulaPressureOffset, offset);
            CurrentWeldSettings.WeldSettingFormula[i].Offset.Current = str;
            str = _Utility->FormatedDataToString(DINFormulaPressureOffset, Maxmm2PressOffset);
            CurrentWeldSettings.WeldSettingFormula[i].Offset.Maximum = str;
            str = _Utility->FormatedDataToString(DINFormulaPressureOffset, Maxmm2PressOffset);
            CurrentWeldSettings.WeldSettingFormula[i].Offset.Minimum = str;

            str = _Utility->FormatedDataToString(DINFormulaPressureMult, multiplier);
            CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Current = str;
            str = _Utility->FormatedDataToString(DINFormulaPressureMult, Maxmm2PressMult);
            CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Maximum = str;
            str = _Utility->FormatedDataToString(DINFormulaPressureMult, (float)Minmm2PressMult);
            CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Minimum = str;
            CurrentWeldSettings.WeldSettingFormula[i].Identifier = FormulaIdentifer[2];
            break;
        case AmplitudeR1:
        case AmplitudeR2:
        case AmplitudeR3:
        case AmplitudeR4:
            str = _Utility->FormatedDataToString(DINFormulaAmplitudeOffset, offset);
            CurrentWeldSettings.WeldSettingFormula[i].Offset.Current = str;
            str = _Utility->FormatedDataToString(DINFormulaAmplitudeOffset, Maxmm2AmplitudeOffset);
            CurrentWeldSettings.WeldSettingFormula[i].Offset.Maximum = str;
            str = _Utility->FormatedDataToString(DINFormulaAmplitudeOffset, Maxmm2AmplitudeOffset);
            CurrentWeldSettings.WeldSettingFormula[i].Offset.Minimum = str;

            str = _Utility->FormatedDataToString(DINFormulaAmplitudeMult, multiplier);
            CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Current = str;
            str = _Utility->FormatedDataToString(DINFormulaAmplitudeMult, Maxmm2AmplitudeMult);
            CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Maximum = str;
            str = _Utility->FormatedDataToString(DINFormulaAmplitudeMult, (float)Minmm2AmplitudeMult);
            CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Minimum = str;

            CurrentWeldSettings.WeldSettingFormula[i].Identifier = FormulaIdentifer[3];
            break;
        }
    }
    return true;
}

bool WeldDefaults::_Set()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    M10INI* _M10INI = M10INI::Instance();
    M102IA* _M102IA = M102IA::Instance();
    M2010* _M2010 = M2010::Instance();
    switch(CurrentWeldSettings.Pressure2Unit)
    {
    case BRANSON_INI_STRUCT::ToPSI:
        _Interface->StatusData.Soft_Settings.Pressure2Unit = BRANSON_INI_STRUCT::ToPSI;
        break;
    case BRANSON_INI_STRUCT::ToBar:
        _Interface->StatusData.Soft_Settings.Pressure2Unit = BRANSON_INI_STRUCT::ToBar;
        break;
    case BRANSON_INI_STRUCT::TokPa:
        _Interface->StatusData.Soft_Settings.Pressure2Unit = BRANSON_INI_STRUCT::TokPa;
        break;
    default:
        _Interface->StatusData.Soft_Settings.Pressure2Unit = BRANSON_INI_STRUCT::ToPSI;
        break;
    }
    switch(CurrentWeldSettings.Length2Unit)
    {
    case BRANSON_INI_STRUCT::ToMM:
        _Interface->StatusData.Soft_Settings.Length2Unit = BRANSON_INI_STRUCT::ToMM;
        break;
    case BRANSON_INI_STRUCT::ToINCH:
        _Interface->StatusData.Soft_Settings.Length2Unit = BRANSON_INI_STRUCT::ToINCH;
        break;
    default:
        _Interface->StatusData.Soft_Settings.Length2Unit = BRANSON_INI_STRUCT::ToMM;
        break;
    }
    switch(CurrentWeldSettings.Square2Unit)
    {
    case BRANSON_INI_STRUCT::ToSqrMM:
        _Interface->StatusData.Soft_Settings.Square2Unit = BRANSON_INI_STRUCT::ToSqrMM;
        break;
    case BRANSON_INI_STRUCT::ToAWG:
        _Interface->StatusData.Soft_Settings.Square2Unit = BRANSON_INI_STRUCT::ToAWG;
        break;
    default:
        _Interface->StatusData.Soft_Settings.Square2Unit = BRANSON_INI_STRUCT::ToSqrMM;
        break;
    }
    _Utility->InitializeTextData();

    unsigned short Machineflags = _M10INI->TempSysConfig.Machineflags[0];
    if(CurrentWeldSettings.WidthEncoder == true)
    {
        if(_Interface->StatusData.Machineflags.Flag.WdthEncoderOff == ON)
        {
            _M10INI->TempSysConfig.Machineflags[0] &= ~(0x4000);
        }
        _Interface->StatusData.Machineflags.Flag.WdthEncoderOff = OFF;
    }
    else
    {
        if(_Interface->StatusData.Machineflags.Flag.WdthEncoderOff == OFF)
        {
            _M10INI->TempSysConfig.Machineflags[0] |= 0x4000;
        }
        _Interface->StatusData.Machineflags.Flag.WdthEncoderOff = ON;
    }

    if(CurrentWeldSettings.HeightEncoder == true)
    {
        if(_Interface->StatusData.Machineflags.Flag.HgtEncoderOff == ON)
        {
            _M10INI->TempSysConfig.Machineflags[0] &= ~(0x8000);
        }
        _Interface->StatusData.Machineflags.Flag.HgtEncoderOff = OFF;
    }
    else
    {
        if(_Interface->StatusData.Machineflags.Flag.HgtEncoderOff == OFF)
        {
            _M10INI->TempSysConfig.Machineflags[0] |= 0x8000;
        }
        _Interface->StatusData.Machineflags.Flag.HgtEncoderOff = ON;
    }

    if(CurrentWeldSettings.Seek == true)
    {
        if(_Interface->StatusData.Machineflags.Flag.SeekOff == ON)
        {
            _M10INI->TempSysConfig.Machineflags[0] &= ~(0x1000);
        }
        _Interface->StatusData.Machineflags.Flag.SeekOff = OFF;
    }else
    {
        if(_Interface->StatusData.Machineflags.Flag.SeekOff == OFF)
        {
            _M10INI->TempSysConfig.Machineflags[0] |= 0x1000;
        }
        _Interface->StatusData.Machineflags.Flag.SeekOff = ON;
    }
    if(Machineflags != _M10INI->TempSysConfig.Machineflags[0])
    {
        _M2010->ReceiveFlags.MachineFlagsData = false;
        _M102IA->SendIACommand(IAComSetMachineFlags, 0);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.MachineFlagsData);
    }

    unsigned short RunMode = _M10INI->TempSysConfig.RunMode;
    if(CurrentWeldSettings.FootPedalAbort == true)
    {
        if(_Interface->StatusData.RunMode.ModeFlag.DefeatWeldAbort == OFF)
        {
            _M10INI->TempSysConfig.RunMode &= ~0x1000;
        }
        _Interface->StatusData.RunMode.ModeFlag.DefeatWeldAbort = ON;
    }
    else
    {
        if(_Interface->StatusData.RunMode.ModeFlag.DefeatWeldAbort == ON)
        {
            _M10INI->TempSysConfig.RunMode |= 0x1000;
        }
        _Interface->StatusData.RunMode.ModeFlag.DefeatWeldAbort = OFF;
    }
    if(RunMode != _M10INI->TempSysConfig.RunMode)
    {
        _M2010->ReceiveFlags.FootPadelDATA = false;
        _M102IA->SendIACommand(IAComSetRunModeNew, _M10INI->TempSysConfig.RunMode);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.FootPadelDATA);
    }

    unsigned short CoolingMode = _M10INI->TempSysConfig.CoolingMode;
    bool CoolingChange = false;
    _Interface->StatusData.CurrentCoolingMode =
            CurrentWeldSettings.CurrentCoolingMode;
    _M10INI->TempSysConfig.CoolingMode = CurrentWeldSettings.CurrentCoolingMode;
    if(CoolingMode != _M10INI->TempSysConfig.CoolingMode)
        CoolingChange = true;

    unsigned short CoolingTooling = _M10INI->TempSysConfig.CoolingTooling;
    _Interface->StatusData.CurrentCoolingTooling =
            CurrentWeldSettings.CoolingForTooling;
    _M10INI->TempSysConfig.CoolingTooling = (int)CurrentWeldSettings.CoolingForTooling;
    if(CoolingTooling != _M10INI->TempSysConfig.CoolingTooling)
        CoolingChange = true;

    unsigned short CoolingDur = _M10INI->TempSysConfig.CoolingDur;
    int tmpValue = _Utility->StringToFormatedData(DINCoolDur,
        CurrentWeldSettings.CurrentCoolingDur.Current);
    if(tmpValue != -1)
        _Interface->StatusData.CurrentCoolingDur = tmpValue;
    else
        _Interface->StatusData.CurrentCoolingDur = 0;
    _M10INI->TempSysConfig.CoolingDur = _Interface->StatusData.CurrentCoolingDur;
    if(CoolingDur != _M10INI->TempSysConfig.CoolingDur)
        CoolingChange = true;

    unsigned short CoolingDel = _M10INI->TempSysConfig.CoolingDel;
    tmpValue = _Utility->StringToFormatedData(DINCoolDel,
        CurrentWeldSettings.CurrentCoolingDel.Current);
    if(tmpValue != -1)
        _Interface->StatusData.CurrentCoolingDel = tmpValue;
    else
        _Interface->StatusData.CurrentCoolingDel = 0;
    _M10INI->TempSysConfig.CoolingDel = _Interface->StatusData.CurrentCoolingDel;
    if(CoolingDel != _M10INI->TempSysConfig.CoolingDel)
        CoolingChange = true;
    if(CoolingChange == true)
    {
        _M2010->ReceiveFlags.CoolingTypeData = false;
        _M102IA->SendIACommand(IAComSetCooling, 0);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.CoolingTypeData);
    }

    _Interface->StatusData.KeepDailyHistory = true;
    _Interface->StatusData.HistoryGraphData = true;
    _Interface->StatusData.GraphSampleRatio
            = CurrentWeldSettings.SampleRatio;
    float area = 0;
    float offset = 0;
    float multiplier = 0;
    for(int i = EnergyR1; i < FormulaRangSize; i++)
    {
        area = _Utility->StringToFormatedData(DINFormulaArea,
            CurrentWeldSettings.WeldSettingFormula[i].Range.Current);
        switch(i)
        {
        case EnergyR1:
        case WidthR1:
        case PressureR1:
        case AmplitudeR1:
            _Interface->StatusData.WeldSettings4Build[i + 1].MinRange
                    = area;
            qDebug()<<"R1" << area;
            break;
        case EnergyR2:
        case WidthR2:
        case PressureR2:
        case AmplitudeR2:
            _Interface->StatusData.WeldSettings4Build[i-1].MaxRange
                    = area - 0.01;
            _Interface->StatusData.WeldSettings4Build[i + 1].MinRange
                    = area;
            qDebug()<<"R2"<< area;
            break;
        case EnergyR3:
        case WidthR3:
        case PressureR3:
        case AmplitudeR3:
            _Interface->StatusData.WeldSettings4Build[i-1].MaxRange
                    = area - 0.01;
            _Interface->StatusData.WeldSettings4Build[i].MaxRange
                    = area;
            qDebug()<<"R3"<<area;
            break;
        case EnergyR4:
        case WidthR4:
        case PressureR4:
        case AmplitudeR4:
            _Interface->StatusData.WeldSettings4Build[i-1].MaxRange
                    = area - 0.01;
            _Interface->StatusData.WeldSettings4Build[i].MaxRange
                    = MAXFORMULAAREA;
            qDebug()<<"R4"<<area;
            break;
        }
        switch (i)
        {
        case EnergyR1:
        case EnergyR2:
        case EnergyR3:
        case EnergyR4:
            offset = _Utility->StringToFormatedData(DINFormulaEnergyOffset,
                CurrentWeldSettings.WeldSettingFormula[i].Offset.Current);
            multiplier = _Utility->StringToFormatedData(DINFormulaEnergyMult,
                CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Current);
            break;
        case WidthR1:
        case WidthR2:
        case WidthR3:
        case WidthR4:
            offset = _Utility->StringToFormatedData(DINFormulaWidthOffset,
                 CurrentWeldSettings.WeldSettingFormula[i].Offset.Current);
            multiplier = _Utility->StringToFormatedData(DINFormulaWidthMult,
                 CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Current);
            break;
        case PressureR1:
        case PressureR2:
        case PressureR3:
        case PressureR4:
            offset = _Utility->StringToFormatedData(DINFormulaPressureOffset,
                 CurrentWeldSettings.WeldSettingFormula[i].Offset.Current);
            multiplier = _Utility->StringToFormatedData(DINFormulaPressureMult,
                 CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Current);
            break;
        case AmplitudeR1:
        case AmplitudeR2:
        case AmplitudeR3:
        case AmplitudeR4:
            offset = _Utility->StringToFormatedData(DINFormulaAmplitudeOffset,
                 CurrentWeldSettings.WeldSettingFormula[i].Offset.Current);
            multiplier = _Utility->StringToFormatedData(DINFormulaAmplitudeMult,
                 CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Current);
            break;
        }
        _Interface->StatusData.WeldSettings4Build[i].Offset = offset;
        _Interface->StatusData.WeldSettings4Build[i].Multplier = multiplier;

    }
    _Interface->StatusData.WriteStatusDataToQSetting();
    return true;
}
