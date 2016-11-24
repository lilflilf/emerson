#include "WeldDefaults.h"
#include "Interface/Interface.h"
#include "Interface/Settings/SysConfiguration.h"
#include "Modules/M10INI.h"
#include "Modules/M10definitions.h"
#include "Modules/UtilityClass.h"
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

}

bool WeldDefaults::_Recall()
{

    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    if(_Interface->StatusData.Soft_Settings.Pressure2Unit == ToPSI)
        CurrentWeldSettings.Imperical2Metric = false;
    else
        CurrentWeldSettings.Imperical2Metric = true;
    _Utility->InitializeTextData();
    if(_Interface->StatusData.Machineflags.Flag.WdthEncoderOff == 0)
        CurrentWeldSettings.WidthEncoder = true;
    else
        CurrentWeldSettings.WidthEncoder = false;
    if(_Interface->StatusData.Machineflags.Flag.HgtEncoderOff == 0)
        CurrentWeldSettings.HeightEncoder = true;
    else
        CurrentWeldSettings.HeightEncoder = false;
    if(_Interface->StatusData.RunMode.ModeFlag.DefeatWeldAbort == 1)
        CurrentWeldSettings.FootPedalAbort = true;
    else
        CurrentWeldSettings.FootPedalAbort = false;
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
            str = _Utility->FormatedDataToString(DINFormulaArea, MAXFORMULAAREA);
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
            CurrentWeldSettings.WeldSettingFormula[i].Identifier = FormulaIdentifer[0];
            break;
        case AmplitudeR1:
        case AmplitudeR2:
        case AmplitudeR3:
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

            CurrentWeldSettings.WeldSettingFormula[i].Identifier = FormulaIdentifer[0];
            break;
        }
    }
    return true;
}

bool WeldDefaults::_Set()
{
    qDebug() << "WeldDefaults set srart";
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();

    if(CurrentWeldSettings.Imperical2Metric == true)
    {
        _Interface->StatusData.Soft_Settings.Mm2Awg = true;
        _Interface->StatusData.Soft_Settings.Mm2Inch = true;
        _Interface->StatusData.Soft_Settings.Pressure2Unit = ToBar;
    }else
    {
        _Interface->StatusData.Soft_Settings.Mm2Awg = false;
        _Interface->StatusData.Soft_Settings.Mm2Inch = false;
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
        _Interface->StatusData.WeldSettings4Build[i].MinRange = area;
        switch(i)
        {
        case EnergyR2:
        case WidthR2:
        case PressureR2:
        case AmplitudeR2:
            _Interface->StatusData.WeldSettings4Build[i-1].MaxRange
                    = area - 0.01;
            break;
        case EnergyR3:
            _Interface->StatusData.WeldSettings4Build[i-1].MaxRange
                    = area - 0.01;
            _Interface->StatusData.WeldSettings4Build[i].MaxRange
                    = MAXFORMULAAREA;
            break;
        case WidthR3:
            _Interface->StatusData.WeldSettings4Build[i-1].MaxRange
                    = area - 0.01;
            _Interface->StatusData.WeldSettings4Build[i].MaxRange
                    = MAXFORMULAAREA;
            break;
        case PressureR3:
            _Interface->StatusData.WeldSettings4Build[i-1].MaxRange
                    = area - 0.01;
            _Interface->StatusData.WeldSettings4Build[PressureR3].MaxRange
                    = MAXFORMULAAREA;
            break;
        case AmplitudeR3:
            _Interface->StatusData.WeldSettings4Build[i-1].MaxRange
                    = area - 0.01;
            _Interface->StatusData.WeldSettings4Build[i].MaxRange
                    = MAXFORMULAAREA;
            break;
        }
        switch (i)
        {
        case EnergyR1:
        case EnergyR2:
        case EnergyR3:
            offset = _Utility->StringToFormatedData(DINFormulaEnergyOffset,
                CurrentWeldSettings.WeldSettingFormula[i].Offset.Current);
            multiplier = _Utility->StringToFormatedData(DINFormulaEnergyMult,
                CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Current);
            break;
        case WidthR1:
        case WidthR2:
        case WidthR3:
            offset = _Utility->StringToFormatedData(DINFormulaWidthOffset,
                 CurrentWeldSettings.WeldSettingFormula[i].Offset.Current);
            multiplier = _Utility->StringToFormatedData(DINFormulaWidthMult,
                 CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Current);
            break;
        case PressureR1:
        case PressureR2:
        case PressureR3:
            offset = _Utility->StringToFormatedData(DINFormulaPressureOffset,
                 CurrentWeldSettings.WeldSettingFormula[i].Offset.Current);
            multiplier = _Utility->StringToFormatedData(DINFormulaPressureMult,
                 CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Current);
            break;
        case AmplitudeR1:
        case AmplitudeR2:
        case AmplitudeR3:
            offset = _Utility->StringToFormatedData(DINFormulaAmplitudeOffset,
                 CurrentWeldSettings.WeldSettingFormula[i].Offset.Current);
            multiplier = _Utility->StringToFormatedData(DINFormulaAmplitudeMult,
                 CurrentWeldSettings.WeldSettingFormula[i].Multiplier.Current);
            break;
        }
        _Interface->StatusData.WeldSettings4Build[i].Offset = offset;
        _Interface->StatusData.WeldSettings4Build[i].Multplier = multiplier;

    }
    qDebug() << "WeldDefaults set end";
    return true;
}
