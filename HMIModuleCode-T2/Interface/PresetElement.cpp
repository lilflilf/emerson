#include "PresetElement.h"
#include "Interface.h"
#include "Modules/M2010.h"
#include "Modules/UtilityClass.h"
#include "Modules/typedef.h"
PresetElement::PresetElement()
{
    UtilityClass *_Utility = UtilityClass::Instance();
//    InterfaceClass *_Interface = InterfaceClass::Instance();
    RevCode = -1;
    SpliceID = -1;
    SpliceName.clear();
    CreatedDate = 0;
    OperatorID = -1;

    CrossSection = -1;
    PresetPicNamePath.clear();
    Verified = false;

    WeldSettings.BasicSetting.Energy = 100;
    WeldSettings.BasicSetting.Amplitude = 18;
    WeldSettings.BasicSetting.Pressure = 200;
    WeldSettings.BasicSetting.TrigPres = 200;
    WeldSettings.BasicSetting.Width = 200;
    WeldSettings.QualitySetting.Time.Minus = MINTIME;
    WeldSettings.QualitySetting.Time.Plus = MAXTIME;               //Seconds * 200
    WeldSettings.QualitySetting.Power.Minus = MINPOWER;
    _Utility->InitializeTextData();
    WeldSettings.QualitySetting.Power.Plus = _Utility->Maxpower;
//    DEBUG_PRINT(_Utility->Maxpower);
    WeldSettings.QualitySetting.Preheight.Minus = MINHEIGHT;
    WeldSettings.QualitySetting.Preheight.Plus = MAXHEIGHT;               //mm * 100
    WeldSettings.QualitySetting.Height.Minus = MINHEIGHT;
    WeldSettings.QualitySetting.Height.Plus = MAXHEIGHT;
    WeldSettings.AdvanceSetting.ABDelay = 0;
    WeldSettings.AdvanceSetting.ABDur = 0;
    WeldSettings.AdvanceSetting.AntiSideOption.AntiSideMode = false;
    WeldSettings.AdvanceSetting.CutOffOption.CutOff = false;
    WeldSettings.AdvanceSetting.HoldTime = 0;
    WeldSettings.AdvanceSetting.OffsetOption.MeasuredHeight = 0;
    WeldSettings.AdvanceSetting.OffsetOption.MeasuredWidth = 0;
    WeldSettings.AdvanceSetting.OffsetOption.DisplayHeight = 0;
    WeldSettings.AdvanceSetting.OffsetOption.DisplayWidth = 0;
    WeldSettings.AdvanceSetting.PreBurst = 0;
    WeldSettings.AdvanceSetting.SqzTime = 0;
    WeldSettings.AdvanceSetting.WeldMode = ADVANCESETTING::ENERGY;
    WeldSettings.AdvanceSetting.StepWeld.StepWeldMode = STEPWELD::STEPDISABLE;
    WeldSettings.AdvanceSetting.StepWeld.Amplitude2 = 0;
    WeldSettings.AdvanceSetting.StepWeld.EnergyToStep = 0;
    WeldSettings.AdvanceSetting.StepWeld.PowerToStep = 0;
    WeldSettings.AdvanceSetting.StepWeld.TimeToStep = 0;
    WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption = false;
    WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature
            = 260; //_Interface->StatusData.ShrinkTubeDefaults.at(0).temp;
    WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime
            = 9; //_Interface->StatusData.ShrinkTubeDefaults.at(0).Time;
    WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID = 1;
    HashCode = qHashBits(&WeldSettings, sizeof(WeldSettings), 0);
    WireIndex.clear();
    NoOfWires = WireIndex.size();
    TestSetting.BatchSize = -1;
    TestSetting.StopCount = -1;
    TestSetting.TestMode = TESTSETTING::UNCONSTRAINED;
    TestSetting.TeachModeSetting.TeachModeType = TEACHMODESETTING::STANDARD;
    TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG_STD] = 40;
    TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG_STD] = 40;
    TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG_STD] = 25;
    TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG_STD] = 25;
    TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG_STD] = 15;
    TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG_STD] = 15;
    TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG_STD] = 10;
    TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG_STD] = 10;
    TestSetting.TeachModeSetting.TeachModequal_Window[FORCE_PLRG_STD] = 5;
    TestSetting.TeachModeSetting.TeachModequal_Window[FORCE_MSRG_STD] = 10;
    TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG_AUTO] = 40;
    TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG_AUTO] = 40;
    TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG_AUTO] = 25;
    TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG_AUTO] = 25;
    TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG_AUTO] = 15;
    TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG_AUTO] = 15;
    TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG_AUTO] = 10;
    TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG_AUTO] = 10;
    TestSetting.TeachModeSetting.TeachModequal_Window[FORCE_PLRG_AUTO] = 5;
    TestSetting.TeachModeSetting.TeachModequal_Window[FORCE_MSRG_AUTO] = 10;
    for (int i = TIME_CONFRG_PL; i<= HEIGHT_CONFRG_MS; i++)
    {
        TestSetting.TeachModeSetting.TeachModequal_Window[i] = 4;
    }
    TestSetting.TeachModeSetting.StandardRunQuantity = 10;
    TestSetting.TeachModeSetting.AutoRunQuantity = 5;
    TestSetting.TeachModeSetting.SigmaRunQuantity = 128;
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
    this->WeldSettings.AdvanceSetting.AntiSideOption.AntiSideMode =
            PresetObject.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideMode;
    this->WeldSettings.AdvanceSetting.CutOffOption.CutOff =
            PresetObject.WeldSettings.AdvanceSetting.CutOffOption.CutOff;
    this->WeldSettings.AdvanceSetting.HoldTime =
            PresetObject.WeldSettings.AdvanceSetting.HoldTime;
    this->WeldSettings.AdvanceSetting.OffsetOption.MeasuredHeight =
            PresetObject.WeldSettings.AdvanceSetting.OffsetOption.MeasuredHeight;
    this->WeldSettings.AdvanceSetting.OffsetOption.MeasuredWidth =
            PresetObject.WeldSettings.AdvanceSetting.OffsetOption.MeasuredWidth;
    this->WeldSettings.AdvanceSetting.OffsetOption.DisplayHeight =
            PresetObject.WeldSettings.AdvanceSetting.OffsetOption.DisplayHeight;
    this->WeldSettings.AdvanceSetting.OffsetOption.DisplayWidth =
            PresetObject.WeldSettings.AdvanceSetting.OffsetOption.DisplayWidth;
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
    this->TestSetting.BatchSize = PresetObject.TestSetting.BatchSize;
    this->TestSetting.StopCount = PresetObject.TestSetting.StopCount;
    this->TestSetting.TestMode = PresetObject.TestSetting.TestMode;
    this->TestSetting.TeachModeSetting.TeachModeType
            = PresetObject.TestSetting.TeachModeSetting.TeachModeType;
    for (int i = TIME_PLRG_STD; i<= HEIGHT_CONFRG_MS; i++)
    {
        this->TestSetting.TeachModeSetting.TeachModequal_Window[i]
                = PresetObject.TestSetting.TeachModeSetting.TeachModequal_Window[i];
    }
    this->TestSetting.TeachModeSetting.StandardRunQuantity =
            PresetObject.TestSetting.TeachModeSetting.StandardRunQuantity;
    this->TestSetting.TeachModeSetting.AutoRunQuantity =
            PresetObject.TestSetting.TeachModeSetting.AutoRunQuantity;
    this->TestSetting.TeachModeSetting.SigmaRunQuantity =
            PresetObject.TestSetting.TeachModeSetting.SigmaRunQuantity;
    this->TestSetting.TestingDone = PresetObject.TestSetting.TestingDone;
    return *this;
}

bool PresetElement::CalculateSpliceData()
{
    InterfaceClass *_Interface = InterfaceClass::Instance();
    M2010 *_M2010 = M2010::Instance();
    int TempMaxWidth;
    bool bResult = true;
    float Area = (float)CrossSection/100;
    unsigned int Index = -1;
    if ((Area >= _Interface->StatusData.WeldSettings4Build[0].MinRange) &&
        (Area <= _Interface->StatusData.WeldSettings4Build[0].MaxRange))
        Index = 0;
    else if((Area >= _Interface->StatusData.WeldSettings4Build[1].MinRange) &&
        (Area <= _Interface->StatusData.WeldSettings4Build[1].MaxRange))
        Index = 1;
    else if((Area >= _Interface->StatusData.WeldSettings4Build[2].MinRange) &&
        (Area <= _Interface->StatusData.WeldSettings4Build[2].MaxRange))
        Index = 2;
    else
    {
        Index = -1;
        bResult = false;

    }
    if(bResult == false)
        return bResult;
    int MAXwatts = (float)(1.2 * _Interface->StatusData.Soft_Settings.SonicGenWatts);

    if(_M2010->Machine == Welder)
    {
        WeldSettings.BasicSetting.Energy = MINENERGY;
        WeldSettings.BasicSetting.Width  = MINWIDTH;
        WeldSettings.BasicSetting.Pressure = DEFAULTPRESSURE;
        WeldSettings.BasicSetting.Amplitude = DEFAULTAMPLITUDE;
        WeldSettings.AdvanceSetting.StepWeld.Amplitude2 =
                DEFAULTAMPLITUDE;
    }else{
        WeldSettings.BasicSetting.Energy =
                (int)(Area * _Interface->StatusData.WeldSettings4Build[Index].Multplier +
                      _Interface->StatusData.WeldSettings4Build[Index].Offset);
        if (WeldSettings.BasicSetting.Energy < MINENERGY)
            WeldSettings.BasicSetting.Energy = MINENERGY;
        if (WeldSettings.BasicSetting.Energy > MAXwatts)
            WeldSettings.BasicSetting.Energy = MAXwatts;

        double SqrtArea = sqrt(Area);
        WeldSettings.BasicSetting.Width =
            (int)(100 * SqrtArea *
                  _Interface->StatusData.WeldSettings4Build[3 + Index].Multplier);
        if (WeldSettings.BasicSetting.Width < MINWIDTH)
            WeldSettings.BasicSetting.Width = MINWIDTH;
        if ((_Interface->StatusData.MachineType != ACT2032) &&
            (_Interface->StatusData.MachineType != ACTNEWSPLICER))
            TempMaxWidth = MAXWIDTH;
        else
            TempMaxWidth = MAXWIDTH2032;
        if (WeldSettings.BasicSetting.Width > TempMaxWidth)
            WeldSettings.BasicSetting.Width = TempMaxWidth;

        float Pressure = Area * _Interface->StatusData.WeldSettings4Build[6 + Index].Multplier +
                _Interface->StatusData.WeldSettings4Build[6 + Index].Offset;
        WeldSettings.BasicSetting.Pressure = (int)(10 * Pressure);
        if (WeldSettings.BasicSetting.Pressure < MINWELDPRESSURE)
            WeldSettings.BasicSetting.Pressure = MINWELDPRESSURE;
        if (WeldSettings.BasicSetting.Pressure > MAXWELDPRESSURE)
            WeldSettings.BasicSetting.Pressure = MAXWELDPRESSURE;

        WeldSettings.BasicSetting.TrigPres = WeldSettings.BasicSetting.Pressure;
        if (WeldSettings.BasicSetting.TrigPres < MINTRIGPRESSURE)
            WeldSettings.BasicSetting.TrigPres = MINTRIGPRESSURE;
        if (WeldSettings.BasicSetting.TrigPres > MAXTRIGPRESSURE)
            WeldSettings.BasicSetting.TrigPres = MAXTRIGPRESSURE;

        WeldSettings.BasicSetting.Amplitude =
                (int)(Area * _Interface->StatusData.WeldSettings4Build[9 + Index].Multplier +
                _Interface->StatusData.WeldSettings4Build[9 + Index].Offset);
        if (WeldSettings.BasicSetting.Amplitude < MINAMPLITUDE)
            WeldSettings.BasicSetting.Amplitude = MINAMPLITUDE;
        if (WeldSettings.BasicSetting.Amplitude > _Interface->StatusData.Soft_Settings.Horn_Calibrate)
            WeldSettings.BasicSetting.Amplitude =
                    _Interface->StatusData.Soft_Settings.Horn_Calibrate;
        WeldSettings.AdvanceSetting.StepWeld.Amplitude2 =
                WeldSettings.BasicSetting.Amplitude;
    }
    return bResult;
}
