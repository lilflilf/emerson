#include "StringToVariant.h"
#include "Interface/Interface.h"
UtilityClass* StringToVariant::_Utility = NULL;
StringToVariant::StringToVariant()
{
    _Utility = UtilityClass::Instance();
    _Utility->InitializeTextData();
}

bool StringToVariant::GaugeToInt(QString strGauge, int &GaugeAWG, int &GaugeMM)
{
    bool bResult = false;
    InterfaceClass* _Interface = InterfaceClass::Instance();
    if(strGauge.contains("AWG") == true)
    {
        GaugeAWG = (int)_Utility->StringToFormatedData(DINGaugeAWG, strGauge);
        if(_Interface->StatusData.AWGToAreaTable.contains(GaugeAWG) == true)
        {
            QMap<int, int>::iterator at
                    = _Interface->StatusData.AWGToAreaTable.find(GaugeAWG);
            GaugeMM = at.value();
            bResult = true;
        }else
            GaugeMM = -1;
    }else if(strGauge.contains("mm²") == true)
    {
        GaugeAWG = -1;
        GaugeMM = (int)_Utility->StringToFormatedData(DINGauge, strGauge);
        bResult = true;
    }
    return bResult;
}

int StringToVariant::CrossSectionToInt(QString strCrossSection)
{
    return (int)_Utility->StringToFormatedData(DINCrossSection, strCrossSection);
}

int StringToVariant::EnergyToInt(QString strEnergy)
{
    return (int)_Utility->StringToFormatedData(DINEnergy, strEnergy);
}

int StringToVariant::AmplitudeToInt(QString strAmplitude)
{
    return (int)_Utility->StringToFormatedData(DINAmplitude, strAmplitude);
}

int StringToVariant::WidthToInt(QString strWidth)
{
    return (int)_Utility->StringToFormatedData(DINWidth, strWidth);
}

int StringToVariant::TriggerPressureToInt(QString strTPressure)
{
    return (int)_Utility->StringToFormatedData(DINTriggerPressure, strTPressure);
}

int StringToVariant::WeldPressureToInt(QString strPressure)
{
    return (int)_Utility->StringToFormatedData(DINPressure, strPressure);
}

int StringToVariant::TimePlusToInt(QString strTime)
{
    return (int)_Utility->StringToFormatedData(DINTimePl, strTime);
}

int StringToVariant::TimeMinusToInt(QString strTime)
{
    return (int)_Utility->StringToFormatedData(DINTimeMs, strTime);
}

int StringToVariant::PowerPlusToInt(QString strPower)
{
    return (int)_Utility->StringToFormatedData(DINPowerPl, strPower);
}

int StringToVariant::PowerMinusToInt(QString strPower)
{
    return (int)_Utility->StringToFormatedData(DINPowerMs, strPower);
}

int StringToVariant::PreHeightPlusToInt(QString strHeight)
{
    return (int)_Utility->StringToFormatedData(DINPre_HgtPl, strHeight);
}

int StringToVariant::PreHeightMinusToInt(QString strHeight)
{
    return (int)_Utility->StringToFormatedData(DINPre_HgtMs, strHeight);
}

int StringToVariant::HeightPlusToInt(QString strHeight)
{
    return (int)_Utility->StringToFormatedData(DINHeightPl, strHeight);
}

int StringToVariant::HeightMinusToInt(QString strHeight)
{
    return (int)_Utility->StringToFormatedData(DINHeightMs, strHeight);
}

int StringToVariant::AfterBurstDelayToInt(QString strTime)
{
    return (int)_Utility->StringToFormatedData(DINABDelay, strTime);
}

int StringToVariant::AfterBurstDuringToInt(QString strTime)
{
    return (int)_Utility->StringToFormatedData(DINABDuration, strTime);
}

int StringToVariant::AntiSideSpliceTimeToInt(QString strTime)
{
    return (int)_Utility->StringToFormatedData(DINAntiSpliceTime, strTime);
}

int StringToVariant::CutOffSpliceTimeToInt(QString strTime)
{
    return (int)_Utility->StringToFormatedData(DINCutOffTime,strTime);
}

int StringToVariant::HoldTimeToInt(QString strTime)
{
    return (int)_Utility->StringToFormatedData(DINHoldTime, strTime);
}

int StringToVariant::MeasureWidthToInt(QString strWidth)
{
    return (int)_Utility->StringToFormatedData(DINWidth, strWidth);
}

int StringToVariant::MeasureHeightToInt(QString strHeight)
{
    return (int)_Utility->StringToFormatedData(DINActHgt, strHeight);
}

int StringToVariant::PreBurstTimeToInt(QString strTime)
{
    return (int)_Utility->StringToFormatedData(DINPreBurst, strTime);
}

int StringToVariant::SqueezeTimeToInt(QString strTime)
{
    return (int)_Utility->StringToFormatedData(DINSqueezeTime, strTime);
}

int StringToVariant::Amplitude2ToInt(QString strAmplitude2)
{
    return (int)_Utility->StringToFormatedData(DINAmplitude2, strAmplitude2);
}

int StringToVariant::StepEnergyToInt(QString strEnergy)
{
    return (int)_Utility->StringToFormatedData(DINEnergy2Step, strEnergy);
}

int StringToVariant::StepPowerToInt(QString strPower)
{
    return (int)_Utility->StringToFormatedData(DINPower2Step, strPower);
}

int StringToVariant::StepTimeToInt(QString strTime)
{
    return (int)_Utility->StringToFormatedData(DINTime2Step, strTime);
}

int StringToVariant::ShrinkTemperatureToInt(QString strTemperature)
{
    return (int)_Utility->StringToFormatedData(DINShrinkTubeTemperature, strTemperature);
}

int StringToVariant::ShrinkTimeToInt(QString strTime)
{
    return (int)_Utility->StringToFormatedData(DINShrinkTubeTime, strTime);
}
