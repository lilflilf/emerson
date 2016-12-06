#include "PresetElement.h"

PresetElement::PresetElement()
{
    RevCode = -1;
    SpliceID = -1;
    SpliceName.clear();
    CreatedDate = 0;
    OperatorID = -1;

    CrossSection = -1;
    PresetPicNamePath.clear();
    Verified = false;

    WeldSettings.BasicSetting.Energy = -1;
    WeldSettings.BasicSetting.Amplitude = -1;
    WeldSettings.BasicSetting.Pressure = -1;
    WeldSettings.BasicSetting.TrigPres = -1;
    WeldSettings.BasicSetting.Width = -1;
    WeldSettings.QualitySetting.Time.Minus = 0;
    WeldSettings.QualitySetting.Time.Plus = 1000;               //Seconds * 200
    WeldSettings.QualitySetting.Power.Minus = 0;
    WeldSettings.QualitySetting.Power.Plus = 4800;
    WeldSettings.QualitySetting.Preheight.Minus = 0;
    WeldSettings.QualitySetting.Preheight.Plus = 1500;               //mm * 100
    WeldSettings.QualitySetting.Height.Minus = 0;
    WeldSettings.QualitySetting.Height.Plus = 1500;
    WeldSettings.AdvanceSetting.ABDelay = 0;
    WeldSettings.AdvanceSetting.ABDur = 0;
    WeldSettings.AdvanceSetting.AntiSide = false;
    WeldSettings.AdvanceSetting.CutOff = false;
    WeldSettings.AdvanceSetting.HoldTime = 0;
    WeldSettings.AdvanceSetting.MeasuredHeight = 0;
    WeldSettings.AdvanceSetting.MeasuredWidth = 0;
    WeldSettings.AdvanceSetting.PreBurst = 0;
    WeldSettings.AdvanceSetting.SqzTime = 0;
    WeldSettings.AdvanceSetting.WeldMode = ENERGY;
    WeldSettings.AdvanceSetting.StepWeld.StepWeldMode = STEPDISABLE;
    WeldSettings.AdvanceSetting.StepWeld.Amplitude2 = -1;
    WeldSettings.AdvanceSetting.StepWeld.EnergyToStep = -1;
    WeldSettings.AdvanceSetting.StepWeld.PowerToStep = -1;
    WeldSettings.AdvanceSetting.StepWeld.TimeToStep = -1;
    WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption = false;
    WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature = -1;
    WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime = -1;
    WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID = -1;
    HashCode = qHashBits(&WeldSettings, sizeof(WeldSettings), 0);
    WireIndex.clear();
    NoOfWires = WireIndex.size();
    TestSetting.Qutanty = -1;
    TestSetting.StopCount = -1;
    TestSetting.TestMode = UNCONSTRAINED;
    TestSetting.TeachModeSetting.TeachModeType = STANDARD;
    TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG] = 40;
    TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG] = 40;
    TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG] = 25;
    TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG] = 25;
    TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG] = 15;
    TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG] = 15;
    TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG] = 10;
    TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG] = 10;
    TestSetting.TeachModeSetting.TeachModequal_Window[FORCE_PLRG] = 5;
    TestSetting.TeachModeSetting.TeachModequal_Window[FORCE_MSRG] = 10;
    for (int i = TIME_CONFRG_PL; i<= HEIGHT_CONFRG_MS; i++)
    {
        TestSetting.TeachModeSetting.TeachModequal_Window[i] = 4;
    }
    TestSetting.TestingDone = false;
}

PresetElement::~PresetElement()
{
    WireIndex.clear();
    NoOfWires = WireIndex.size();
}

PresetElement PresetElement::operator=(const PresetElement &PresetObject)
{
    if(this == &PresetObject)
        return *this;
    this->RevCode = PresetObject.RevCode;
    this->SpliceID = PresetObject.SpliceID;
    this->SpliceName = PresetObject.SpliceName;
    this->CreatedDate = PresetObject.CreatedDate;
    this->OperatorID = PresetObject.OperatorID;

    this->CrossSection = PresetObject.CrossSection;
    this->PresetPicNamePath = PresetObject.PresetPicNamePath;
    this->Verified = PresetObject.Verified;

    this->WeldSettings.BasicSetting.Energy =
            PresetObject.WeldSettings.BasicSetting.Energy;
    this->WeldSettings.BasicSetting.Amplitude = PresetObject.WeldSettings.BasicSetting.Amplitude;
    this->WeldSettings.BasicSetting.Pressure = PresetObject.WeldSettings.BasicSetting.Pressure;
    this->WeldSettings.BasicSetting.TrigPres = PresetObject.WeldSettings.BasicSetting.TrigPres;
    this->WeldSettings.BasicSetting.Width = PresetObject.WeldSettings.BasicSetting.Width;
    this->WeldSettings.QualitySetting.Time.Minus =
            PresetObject.WeldSettings.QualitySetting.Time.Minus;
    this->WeldSettings.QualitySetting.Time.Plus =
            PresetObject.WeldSettings.QualitySetting.Time.Plus;
    this->WeldSettings.QualitySetting.Power.Minus =
            PresetObject.WeldSettings.QualitySetting.Power.Minus;
    this->WeldSettings.QualitySetting.Power.Plus =
            PresetObject.WeldSettings.QualitySetting.Power.Plus;
    this->WeldSettings.QualitySetting.Preheight.Minus =
            PresetObject.WeldSettings.QualitySetting.Preheight.Minus;
    this->WeldSettings.QualitySetting.Preheight.Plus =
            PresetObject.WeldSettings.QualitySetting.Preheight.Plus;
    this->WeldSettings.QualitySetting.Height.Minus =
            PresetObject.WeldSettings.QualitySetting.Height.Minus;
    this->WeldSettings.QualitySetting.Height.Plus =
            PresetObject.WeldSettings.QualitySetting.Height.Plus;
    this->WeldSettings.AdvanceSetting.ABDelay =
            PresetObject.WeldSettings.AdvanceSetting.ABDelay;
    this->WeldSettings.AdvanceSetting.ABDur =
            PresetObject.WeldSettings.AdvanceSetting.ABDur;
    this->WeldSettings.AdvanceSetting.AntiSide =
            PresetObject.WeldSettings.AdvanceSetting.AntiSide;
    this->WeldSettings.AdvanceSetting.CutOff =
            PresetObject.WeldSettings.AdvanceSetting.CutOff;
    this->WeldSettings.AdvanceSetting.HoldTime =
            PresetObject.WeldSettings.AdvanceSetting.HoldTime;
    this->WeldSettings.AdvanceSetting.MeasuredHeight =
            PresetObject.WeldSettings.AdvanceSetting.MeasuredHeight;
    this->WeldSettings.AdvanceSetting.MeasuredWidth =
            PresetObject.WeldSettings.AdvanceSetting.MeasuredWidth;
    this->WeldSettings.AdvanceSetting.PreBurst =
            PresetObject.WeldSettings.AdvanceSetting.PreBurst;
    this->WeldSettings.AdvanceSetting.SqzTime =
            PresetObject.WeldSettings.AdvanceSetting.SqzTime;
    this->WeldSettings.AdvanceSetting.WeldMode =
            PresetObject.WeldSettings.AdvanceSetting.WeldMode;
    this->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode
            = PresetObject.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode;
    this->WeldSettings.AdvanceSetting.StepWeld.Amplitude2
            = PresetObject.WeldSettings.AdvanceSetting.StepWeld.Amplitude2;
    this->WeldSettings.AdvanceSetting.StepWeld.EnergyToStep
            = PresetObject.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep;
    this->WeldSettings.AdvanceSetting.StepWeld.PowerToStep
            = PresetObject.WeldSettings.AdvanceSetting.StepWeld.PowerToStep;
    this->WeldSettings.AdvanceSetting.StepWeld.TimeToStep
            = PresetObject.WeldSettings.AdvanceSetting.StepWeld.TimeToStep;
    this->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption
            = PresetObject.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption;
    this->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature
            = PresetObject.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature;
    this->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime
            = PresetObject.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime;
    this->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID
            = PresetObject.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID;
    this->HashCode = PresetObject.HashCode;
    QMap<int,QString>::const_iterator i
            = PresetObject.WireIndex.constBegin();
    while(i != PresetObject.WireIndex.constEnd())
    {
        this->WireIndex.insert(i.key(),i.value());
        ++i;
    }
    this->NoOfWires = this->WireIndex.size();
    this->TestSetting.Qutanty = PresetObject.TestSetting.Qutanty;
    this->TestSetting.StopCount = PresetObject.TestSetting.StopCount;
    this->TestSetting.TestMode = PresetObject.TestSetting.TestMode;
    this->TestSetting.TeachModeSetting.TeachModeType
            = PresetObject.TestSetting.TeachModeSetting.TeachModeType;
    for (int i = TIME_PLRG; i<= HEIGHT_CONFRG_MS; i++)
    {
        this->TestSetting.TeachModeSetting.TeachModequal_Window[i]
                = PresetObject.TestSetting.TeachModeSetting.TeachModequal_Window[i];
    }
    this->TestSetting.TestingDone = PresetObject.TestSetting.TestingDone;
    return *this;
}

void PresetElement::CalculateSpliceData()
{

}
