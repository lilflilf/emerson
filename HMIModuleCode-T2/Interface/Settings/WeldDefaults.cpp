#include "WeldDefaults.h"
#include "Interface/Interface.h"
#include "Interface/Settings/SysConfiguration.h"
#include "Modules/M10INI.h"
#include "Modules/M10definitions.h"
#include "Modules/UtilityClass.h"
struct WeldSettingForScreen WeldDefaults::CurrentWeldSettings;
WeldDefaults::WeldDefaults(QObject *parent) : QObject(parent)
{
    InitWeldSettings();
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
    WeldSettingsInfo[SDNEnergy].MultFormat = "%.2fJ";
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
    WeldSettingsInfo[SDNWidth].OffsetFormat = "%d";

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
    WeldSettingsInfo[SDNAmplitude].OffsetFormat = "%.2f";
}

void WeldDefaults::_Default()
{

}

bool WeldDefaults::_Recall()
{

}

bool WeldDefaults::_Set()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    if(CurrentWeldSettings.Imperical2Metric == true)
    {
        _Interface->StatusData.Soft_Settings.Mm2Awg = false;
        _Interface->StatusData.Soft_Settings.Mm2Inch = false;
        _Interface->StatusData.Soft_Settings.Pressure2Unit = ToBar;
    }else
    {
        _Interface->StatusData.Soft_Settings.Mm2Awg = true;
        _Interface->StatusData.Soft_Settings.Mm2Inch = true;
        _Interface->StatusData.Soft_Settings.Pressure2Unit = ToPSI;
    }
    _Utility->InitializeTextData();

    if(CurrentWeldSettings.WidthEncoder == true)
        _Interface->StatusData.Machineflags.Flag.WdthEncoderOff = 0;
    else
        _Interface->StatusData.Machineflags.Flag.WdthEncoderOff = 1;

    if(CurrentWeldSettings.HeightEncoder == true)
        _Interface->StatusData.Machineflags.Flag.HgtEncoderOff = 0;
    else
        _Interface->StatusData.Machineflags.Flag.HgtEncoderOff = 1;

    if(CurrentWeldSettings.FootPedalAbort == true)
        _Interface->StatusData.RunMode.ModeFlag.DefeatWeldAbort = 1;
    else
        _Interface->StatusData.RunMode.ModeFlag.DefeatWeldAbort = 0;

    _Interface->StatusData.CurrentCoolingMode =
            CurrentWeldSettings.CurrentCoolingMode;
    _Interface->StatusData.CurrentCoolingTooling =
            CurrentWeldSettings.CoolingForTooling;
    int tmpValue = _Utility->StringToFormatedData(DINCoolDur,
        CurrentWeldSettings.CurrentCoolingDur.Current);
    if(tmpValue != -1)
        _Interface->StatusData.CurrentCoolingDur = tmpValue;
    else
        _Interface->StatusData.CurrentCoolingDur = 0;
    tmpValue = _Utility->StringToFormatedData(DINCoolDel,
        CurrentWeldSettings.CurrentCoolingDel.Current);
    if(tmpValue != -1)
        _Interface->StatusData.CurrentCoolingDel = tmpValue;
    else
        _Interface->StatusData.CurrentCoolingDel = 0;

    _Interface->StatusData.KeepDailyHistory = true;
    _Interface->StatusData.GraphSampleRatio
            = CurrentWeldSettings.SampleRatio;
    for(int i = EnergyR1; i < FormulaRangSize; i++)
    {
        tmpValue = _Utility->StringToFormatedData(DINFormulaArea,
            CurrentWeldSettings.WeldSettingFormula[i].Range.Current);
        if(tmpValue != -1)
            _Interface->StatusData.WeldSettings4Build[i].MinRange = tmpValue;
        else
            _Interface->StatusData.WeldSettings4Build[i].MinRange = 0;
    }
    return true;
}
