#include "VariantToString.h"
#include "Interface/Interface.h"
#include "Modules/typedef.h"
UtilityClass* VariantToString::_Utility = NULL;
VariantToString* VariantToString::_instance = NULL;
VariantToString* VariantToString::Instance()
{
    if(_instance == NULL){
        _instance = new VariantToString();
    }
    return _instance;
}

VariantToString::VariantToString()
{
    _Utility = UtilityClass::Instance();
    _Utility->InitializeTextData();
}

struct BRANSONDATA VariantToString::GaugeToString(int Gauge, int GaugeAWG)
{
    struct BRANSONDATA tmpData;
    InterfaceClass* _Interface = InterfaceClass::Instance();
    if(_Interface->StatusData.Soft_Settings.Square2Unit ==
            BRANSON_INI_STRUCT::ToAWG)
    {
        if(GaugeAWG != -1)
        {
            tmpData.Current = _Utility->FormatedDataToString(DINGaugeAWG, GaugeAWG);
            tmpData.Maximum = _Utility->FormatedDataToString(DINGaugeAWG,
                            _Utility->txtData[DINGaugeAWG].max);
            tmpData.Minimum = _Utility->FormatedDataToString(DINGaugeAWG,
                            _Utility->txtData[DINGaugeAWG].min);
            return tmpData;
        }
    }
    tmpData.Current = _Utility->FormatedDataToString(DINGauge, Gauge);
    tmpData.Maximum = _Utility->FormatedDataToString(DINGauge,
                    _Utility->txtData[DINGauge].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINGauge,
                    _Utility->txtData[DINGauge].min);
    return tmpData;
}

QString VariantToString::CrossSectionToString(int CrossSection)
{
    return _Utility->FormatedDataToString(DINCrossSection, CrossSection);
}

struct BRANSONDATA VariantToString::EnergyToString(int Energy)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINEnergy, Energy);
    tmpData.Maximum = _Utility->FormatedDataToString(DINEnergy,
                    _Utility->txtData[DINEnergy].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINEnergy,
                    _Utility->txtData[DINEnergy].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::AmplitudeToString(int iAmplitude)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINAmplitude, iAmplitude);
    tmpData.Maximum = _Utility->FormatedDataToString(DINAmplitude,
                    _Utility->txtData[DINAmplitude].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINAmplitude,
                    _Utility->txtData[DINAmplitude].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::DefaultAmpToString(int iAmplitude)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINDefaultAmplitude, iAmplitude);
    tmpData.Maximum = _Utility->FormatedDataToString(DINDefaultAmplitude,
                    _Utility->txtData[DINDefaultAmplitude].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINDefaultAmplitude,
                    _Utility->txtData[DINDefaultAmplitude].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::WidthToString(int Width)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINWidth, Width);
    tmpData.Maximum = _Utility->FormatedDataToString(DINWidth,
                    _Utility->txtData[DINWidth].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINWidth,
                    _Utility->txtData[DINWidth].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::TriggerPressureToString(int TPressure)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINTriggerPressure, TPressure);
    tmpData.Maximum = _Utility->FormatedDataToString(DINTriggerPressure,
                    _Utility->txtData[DINTriggerPressure].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINTriggerPressure,
                    _Utility->txtData[DINTriggerPressure].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::WeldPressureToString(int Pressure)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINPressure, Pressure);
    tmpData.Maximum = _Utility->FormatedDataToString(DINPressure,
                    _Utility->txtData[DINPressure].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINPressure,
                    _Utility->txtData[DINPressure].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::TimePlusToString(int Time)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINTimePl, Time);
    tmpData.Maximum = _Utility->FormatedDataToString(DINTimePl,
                    _Utility->txtData[DINTimePl].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINTimePl,
                    _Utility->txtData[DINTimePl].min);
    return tmpData;
}

QString VariantToString::Time_PlusToString(int Time)
{
    return _Utility->FormatedDataToString(DINTimePl, Time);
}

struct BRANSONDATA VariantToString::TimeMinusToString(int Time)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINTimeMs, Time);
    tmpData.Maximum = _Utility->FormatedDataToString(DINTimeMs,
                    _Utility->txtData[DINTimeMs].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINTimeMs,
                    _Utility->txtData[DINTimeMs].min);
    return tmpData;
}

QString VariantToString::Time_MinusToString(int Time)
{
    return _Utility->FormatedDataToString(DINTimeMs, Time);
}

struct BRANSONDATA VariantToString::PowerPlusToString(int Power)
{
    struct BRANSONDATA tmpData;
//    DEBUG_PRINT (Power);
    tmpData.Current = _Utility->FormatedDataToString(DINPowerPl, Power);
    tmpData.Maximum = _Utility->FormatedDataToString(DINPowerPl,
                    _Utility->txtData[DINPowerPl].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINPowerPl,
                    _Utility->txtData[DINPowerPl].min);
    return tmpData;
}

QString VariantToString::Power_PlusToString(int Power)
{
    return _Utility->FormatedDataToString(DINPowerPl, Power);
}

struct BRANSONDATA VariantToString::PowerMinusToString(int Power)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINPowerMs, Power);
    tmpData.Maximum = _Utility->FormatedDataToString(DINPowerMs,
                    _Utility->txtData[DINPowerMs].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINPowerMs,
                    _Utility->txtData[DINPowerMs].min);
    return tmpData;
}

QString VariantToString::Power_MinusToString(int Power)
{
    return _Utility->FormatedDataToString(DINPowerMs, Power);
}

struct BRANSONDATA VariantToString::PreHeightPlusToString(int PreHeight)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINPre_HgtPl, PreHeight);
    tmpData.Maximum = _Utility->FormatedDataToString(DINPre_HgtPl,
                    _Utility->txtData[DINPre_HgtPl].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINPre_HgtPl,
                    _Utility->txtData[DINPre_HgtPl].min);
    return tmpData;
}

QString VariantToString::PreHeight_PlusToString(int PreHeight)
{
    return _Utility->FormatedDataToString(DINPre_HgtPl, PreHeight);
}

struct BRANSONDATA VariantToString::PreHeightMinusToString(int PreHeight)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINPre_HgtMs, PreHeight);
    tmpData.Maximum = _Utility->FormatedDataToString(DINPre_HgtMs,
                    _Utility->txtData[DINPre_HgtMs].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINPre_HgtMs,
                    _Utility->txtData[DINPre_HgtMs].min);
    return tmpData;
}

QString VariantToString::PreHeight_MinusToString(int PreHeight)
{
    return _Utility->FormatedDataToString(DINPre_HgtMs, PreHeight);
}

struct BRANSONDATA VariantToString::HeightPlusToString(int Height)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINHeightPl, Height);
    tmpData.Maximum = _Utility->FormatedDataToString(DINHeightPl,
                    _Utility->txtData[DINHeightPl].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINHeightPl,
                    _Utility->txtData[DINHeightPl].min);
    return tmpData;
}

QString VariantToString::Height_PlusToString(int Height)
{
   return _Utility->FormatedDataToString(DINHeightPl, Height);
}

struct BRANSONDATA VariantToString::HeightMinusToString(int Height)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINHeightMs, Height);
    tmpData.Maximum = _Utility->FormatedDataToString(DINHeightMs,
                    _Utility->txtData[DINHeightMs].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINHeightMs,
                    _Utility->txtData[DINHeightMs].min);
    return tmpData;
}

QString VariantToString::Height_MinusToString(int Height)
{
    return _Utility->FormatedDataToString(DINHeightMs, Height);
}

struct BRANSONDATA VariantToString::AfterBurstDelayToString(int Time)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINABDelay, Time);
    tmpData.Maximum = _Utility->FormatedDataToString(DINABDelay,
                    _Utility->txtData[DINABDelay].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINABDelay,
                    _Utility->txtData[DINABDelay].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::AfterBurstDuringToString(int Time)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINABDuration, Time);
    tmpData.Maximum = _Utility->FormatedDataToString(DINABDuration,
                    _Utility->txtData[DINABDuration].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINABDuration,
                    _Utility->txtData[DINABDuration].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::AntiSideSpliceTimeToString(int Time)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINAntiSpliceTime, Time);
    tmpData.Maximum = _Utility->FormatedDataToString(DINAntiSpliceTime,
                    _Utility->txtData[DINAntiSpliceTime].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINAntiSpliceTime,
                    _Utility->txtData[DINAntiSpliceTime].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::CutOffSpliceTimeToString(int Time)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINCutOffTime, Time);
    tmpData.Maximum = _Utility->FormatedDataToString(DINCutOffTime,
                    _Utility->txtData[DINCutOffTime].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINCutOffTime,
                    _Utility->txtData[DINCutOffTime].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::HoldTimeToString(int Time)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINHoldTime, Time);
    tmpData.Maximum = _Utility->FormatedDataToString(DINHoldTime,
                    _Utility->txtData[DINHoldTime].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINHoldTime,
                    _Utility->txtData[DINHoldTime].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::MeasureWidthToString(int Width)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINWidth, Width);
    tmpData.Maximum = _Utility->FormatedDataToString(DINWidth,
                    _Utility->txtData[DINWidth].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINWidth,
                    _Utility->txtData[DINWidth].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::MeasureHeightToString(int Height)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINActHgt, Height);
    tmpData.Maximum = _Utility->FormatedDataToString(DINActHgt,
                    _Utility->txtData[DINActHgt].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINActHgt,
                    _Utility->txtData[DINActHgt].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::PreBurstTimeToString(int Time)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINPreBurst, Time);
    tmpData.Maximum = _Utility->FormatedDataToString(DINPreBurst,
                    _Utility->txtData[DINPreBurst].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINPreBurst,
                    _Utility->txtData[DINPreBurst].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::SqueezeTimeToString(int Time)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINSqueezeTime, Time);
    tmpData.Maximum = _Utility->FormatedDataToString(DINSqueezeTime,
                    _Utility->txtData[DINSqueezeTime].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINSqueezeTime,
                    _Utility->txtData[DINSqueezeTime].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::Amplitude2ToString(int Amplitude)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINAmplitude2, Amplitude);
    tmpData.Maximum = _Utility->FormatedDataToString(DINAmplitude2,
                    _Utility->txtData[DINAmplitude2].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINAmplitude2,
                    _Utility->txtData[DINAmplitude2].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::StepEnergyToString(int Energy)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINEnergy2Step, Energy);
    tmpData.Maximum = _Utility->FormatedDataToString(DINEnergy2Step,
                    _Utility->txtData[DINEnergy2Step].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINEnergy2Step,
                    _Utility->txtData[DINEnergy2Step].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::StepPowerToString(int Power)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINPower2Step, Power);
    tmpData.Maximum = _Utility->FormatedDataToString(DINPower2Step,
                    _Utility->txtData[DINPower2Step].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINPower2Step,
                    _Utility->txtData[DINPower2Step].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::StepTimeToString(int Time)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINTime2Step, Time);
    tmpData.Maximum = _Utility->FormatedDataToString(DINTime2Step,
                    _Utility->txtData[DINTime2Step].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINTime2Step,
                    _Utility->txtData[DINTime2Step].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::ShrinkTemperatureToString(int Temperature)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINShrinkTubeTemperature, Temperature);
    tmpData.Maximum = _Utility->FormatedDataToString(DINShrinkTubeTemperature,
                    _Utility->txtData[DINShrinkTubeTemperature].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINShrinkTubeTemperature,
                    _Utility->txtData[DINShrinkTubeTemperature].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::ShrinkTimeToString(int Time)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINShrinkTubeTime, Time);
    tmpData.Maximum = _Utility->FormatedDataToString(DINShrinkTubeTime,
                    _Utility->txtData[DINShrinkTubeTime].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINShrinkTubeTime,
                    _Utility->txtData[DINShrinkTubeTime].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::StandardAutoTeachModeToString(int parameter)
{
    struct BRANSONDATA tmpData;
    tmpData.Current =  _Utility->FormatedDataToString(DINPercentTeachMode, parameter);
    tmpData.Maximum = _Utility->FormatedDataToString(DINPercentTeachMode,
                    _Utility->txtData[DINPercentTeachMode].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINPercentTeachMode,
                    _Utility->txtData[DINPercentTeachMode].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::SigmaTeachModeToString(int parameter)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINSigmaTeachMode, parameter);
    tmpData.Maximum = _Utility->FormatedDataToString(DINSigmaTeachMode,
                    _Utility->txtData[DINSigmaTeachMode].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINSigmaTeachMode,
                    _Utility->txtData[DINSigmaTeachMode].min);
    return tmpData;

}

struct BRANSONDATA VariantToString::TestQuantity(int parameter)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINTestQuantity, parameter);
    tmpData.Maximum = _Utility->FormatedDataToString(DINTestQuantity,
                    _Utility->txtData[DINTestQuantity].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINTestQuantity,
                    _Utility->txtData[DINTestQuantity].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::TeachModeQuantity(int parameter)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINTeachModeQuantity, parameter);
    tmpData.Maximum = _Utility->FormatedDataToString(DINTeachModeQuantity,
                    _Utility->txtData[DINTeachModeQuantity].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINTeachModeQuantity,
                    _Utility->txtData[DINTeachModeQuantity].min);
    return tmpData;
}

struct BRANSONDATA VariantToString::SequenceQuantity(int parameter)
{
    struct BRANSONDATA tmpData;
    tmpData.Current = _Utility->FormatedDataToString(DINSequenceQuantity, parameter);
    tmpData.Maximum = _Utility->FormatedDataToString(DINSequenceQuantity,
                    _Utility->txtData[DINSequenceQuantity].max);
    tmpData.Minimum = _Utility->FormatedDataToString(DINSequenceQuantity,
                    _Utility->txtData[DINSequenceQuantity].min);
    return tmpData;
}

//Weld History
QString VariantToString::WeldModeToString(ADVANCESETTING::WELDMODE weldmode,
                                          STEPWELD::STEPWELDMODE stepmode)
{
    QString str;
    switch(weldmode)
    {
    case ADVANCESETTING::ENERGY:
        str = QObject::tr("Energy");
        break;
    case ADVANCESETTING::TIME:
        str = QObject::tr("Time");
        break;
    case ADVANCESETTING::HEIGHT:
        str = QObject::tr("Height");
        break;
    case ADVANCESETTING::ENERGYWITHHEIGHT:
        str = QObject::tr("Energy/Height");
        break;
    default:
        str.clear();
        break;
    }
    switch(stepmode)
    {
    case STEPWELD::STEPENERGY:
        str = QObject::tr("Step-Energy");
        break;
    case STEPWELD::STEPPOWER:
        str = QObject::tr("Step-Power");
        break;
    case STEPWELD::STEPTIME:
        str = QObject::tr("Step-Time");
        break;
    default:
        break;
    }
    return str;
}

QString VariantToString::HistoryAmplitudeToString(int Amplitude1, int Amplitude2)
{
    QString Amp1 = _Utility->FormatedDataToString(DINAmplitude, Amplitude1);
    QString Amp2 = _Utility->FormatedDataToString(DINAmplitude2, Amplitude2);
    QString str = Amp1 + "/" + Amp2;
    return str;
}

QString VariantToString::AlarmToString(unsigned int Alarm)
{
    QString str;

    //Build alarm string, Overload precludes any other and pre-height can't get here
    if((Alarm & AlarmsFault) == 0)
        str = "-";
    else
    {
        if ((Alarm & OverLoadFault) == OverLoadFault)
            str = "O";
        else
        {
            str.clear();
            if ((Alarm & TimeFault) == TimeFault)
                str = "T";
            if ((Alarm & PowerFault) == PowerFault)
            {
                if(str.isEmpty() == true)
                    str += "P";
                else
                    str += "/P";
            }
            if ((Alarm & HeightFault) == HeightFault)
            {
                if(str.isEmpty() == true)
                    str += "H";
                else
                    str += "/H";
            }
            if ((Alarm & WidthFault) == WidthFault)
            {
                if(str.isEmpty() == true)
                    str += "W";
                else
                    str += "/W";
            }
        }
    }
    return str;
}

QString VariantToString::SampleRatioToString(WeldResultElement::SAMPLERATIO ratio)
{
    QString str;
    switch(ratio)
    {
    case WeldResultElement::SampleWith1ms:
        str = QObject::tr("1ms");
        break;
    case WeldResultElement::SampleWith5ms:
        str = QObject::tr("5ms");
        break;
    case WeldResultElement::SampleWith10ms:
        str = QObject::tr("10ms");
        break;
    case WeldResultElement::SampleWith20ms:
        str = QObject::tr("20ms");
        break;
    default:
        str = QObject::tr("1ms");
        break;
    }
    return str;
}

QString VariantToString::ActualTimeToString(int ActualTime)
{
    return _Utility->FormatedDataToString(DINActTime, ActualTime);
}

QString VariantToString::ActualPowerToString(int ActualPower)
{
    return _Utility->FormatedDataToString(DINActPower, ActualPower);
}

QString VariantToString::ActualPreHeightToString(int ActualPreHeight)
{
    return _Utility->FormatedDataToString(DINActPreHgt, ActualPreHeight);
}

QString VariantToString::ActualHeightToString(int ActualHeight)
{
    return _Utility->FormatedDataToString(DINActHgt, ActualHeight);
}

//Alarm History
QString VariantToString::AlarmTypeToString(enum ALARMTYPE type)
{
    QString str;
    switch(type)
    {
    case TIMEALARM:
        str = QObject::tr("Weld time alarm");
        break;
    case PEAKPOWERALARM:
        str = QObject::tr("Weld Peak Power alarm");
        break;
    case PREHEIGHTALARM:
        str = QObject::tr("Weld Pre-height alarm");
        break;
    case HEIGHTALARM:
        str = QObject::tr("Weld Post-height alarm");
        break;
    case OVERLOADALARM:
        str = QObject::tr("Overload");
        break;
    case MOTORERROR:
        str = QObject::tr("Motor error");
        break;
    case HEIGHTENCODERERROR:
        str = QObject::tr("Height encoder error");
        break;
    case SAFETYERROR:
        str = QObject::tr("Safety cover error");
        break;
    case VOL24ERROR:
        str = QObject::tr("24V checking");
        break;
    case CUTERROR:
        str = QObject::tr("Cutter error");
        break;
    case IDCHIPERROR:
        str = QObject::tr("ID Chip error");
        break;
    case RAMERROR:
        str = QObject::tr("Fram error");
        break;
    case E_STOP:
        str = QObject::tr("E-Stop");
        break;
    case HORN80PERCENTCOUNTALARM:
        str = QObject::tr("Horn count 80% alarm");
        break;
    case ANVIL80PERCENTCOUNTALARM:
        str = QObject::tr("Anvil count 80% alarm");
        break;
    case GATHER80PERCENTCOUNTALARM:
        str = QObject::tr("Gather count 80% alarm");
        break;
    case GUIDE80PERCENTCOUNTALARM:
        str = QObject::tr("Guide count 80% alarm");
        break;
    case HORN80PERCENTENERGYALARM:
        str = QObject::tr("Horn energy 80% alarm");
        break;
    case ANVIL80PERCENTENERGYALARM:
        str = QObject::tr("Anvil energy 80% alarm");
        break;
    case GATHER80PERCENTENERGYALARM:
        str = QObject::tr("Gather energy 80% alarm");
        break;
    case GUIDE80PERCENTENERGYALARM:
        str = QObject::tr("Guide energy 80% alarm");
        break;

    case HORN100PERCENTCOUNTALARM:
        str = QObject::tr("Horn count 100% lock");
        break;
    case ANVIL100PERCENTCOUNTALARM:
        str = QObject::tr("Anvil count 100% lock");
        break;
    case GATHER100PERCENTCOUNTALARM:
        str = QObject::tr("Gather count 100% lock");
        break;
    case GUIDE100PERCENTCOUNTALARM:
        str = QObject::tr("Guide count 100% lock");
        break;
    case HORN100PERCENTENERGYALARM:
        str = QObject::tr("Horn energy 100% lock");
        break;
    case ANVIL100PERCENTENERGYALARM:
        str = QObject::tr("Anvil energy 100% lock");
        break;
    case GATHER100PERCENTENERGYALARM:
        str = QObject::tr("Gather energy 100% lock");
        break;
    case GUIDE100PERCENTENERGYALARM:
        str = QObject::tr("Guide energy 100% lock");
        break;
    default:
        str.clear();
        break;
    }
    return str;
}

QString VariantToString::AlarmLevelToString(enum ALARMTYPE Alarmtype)
{
    QString str;
    switch(Alarmtype)
    {
    case OVERLOADALARM:
    case MOTORERROR:
    case HEIGHTENCODERERROR:
    case SAFETYERROR:
    case CUTERROR:
    case E_STOP:
    case IDCHIPERROR:
    case RAMERROR:
    case HORN100PERCENTCOUNTALARM:
    case ANVIL100PERCENTCOUNTALARM:
    case GATHER100PERCENTCOUNTALARM:
    case GUIDE100PERCENTCOUNTALARM:
    case HORN100PERCENTENERGYALARM:
    case ANVIL100PERCENTENERGYALARM:
    case GATHER100PERCENTENERGYALARM:
    case GUIDE100PERCENTENERGYALARM:
        str = QObject::tr("High-level");
        break;
    case TIMEALARM:
    case PEAKPOWERALARM:
    case PREHEIGHTALARM:
    case HEIGHTALARM:
    case VOL24ERROR:
    case HORN80PERCENTCOUNTALARM:
    case ANVIL80PERCENTCOUNTALARM:
    case GATHER80PERCENTCOUNTALARM:
    case GUIDE80PERCENTCOUNTALARM:
    case HORN80PERCENTENERGYALARM:
    case ANVIL80PERCENTENERGYALARM:
    case GATHER80PERCENTENERGYALARM:
    case GUIDE80PERCENTENERGYALARM:
        str = QObject::tr("Mid-level");
        break;
    default:
        str = QObject::tr("None-level");
        break;
    }
    return str;
}

QString VariantToString::AlarmLevelToString(QString AlarmType)
{
    QString str;
    if ( AlarmType == QObject::tr("Weld time alarm"))
        str = QObject::tr("Mid-level");
    else if(AlarmType == QObject::tr("Weld Peak Power alarm"))
        str = QObject::tr("Mid-level");
    else if(AlarmType == QObject::tr("Weld Pre-height alarm"))
        str = QObject::tr("Mid-level");
    else if(AlarmType == QObject::tr("Weld Post-height alarm"))
        str = QObject::tr("Mid-level");
    else if(AlarmType == QObject::tr("24V checking"))
        str = QObject::tr("Mid-level");
    else if(AlarmType == QObject::tr("Horn count 80% alarm"))
        str = QObject::tr("Mid-level");
    else if(AlarmType == QObject::tr("Anvil count 80% alarm"))
        str = QObject::tr("Mid-level");
    else if(AlarmType == QObject::tr("Gather count 80% alarm"))
        str = QObject::tr("Mid-level");
    else if(AlarmType == QObject::tr("Guide count 80% alarm"))
        str = QObject::tr("Mid-level");
    else if(AlarmType == QObject::tr("Horn energy 80% alarm"))
        str = QObject::tr("Mid-level");
    else if(AlarmType == QObject::tr("Anvil energy 80% alarm"))
        str = QObject::tr("Mid-level");
    else if(AlarmType == QObject::tr("Gather energy 80% alarm"))
        str = QObject::tr("Mid-level");
    else if(AlarmType == QObject::tr("Guide energy 80% alarmm"))
        str = QObject::tr("Mid-level");

    else if(AlarmType == QObject::tr("Overload"))
        str = QObject::tr("High-level");
    else if(AlarmType == QObject::tr("Motor error"))
        str = QObject::tr("High-level");
    else if(AlarmType == QObject::tr("Height encoder error"))
        str = QObject::tr("High-level");
    else if(AlarmType == QObject::tr("Safety cover error"))
        str = QObject::tr("High-level");
    else if(AlarmType == QObject::tr("Cutter error"))
        str = QObject::tr("High-level");
    else if(AlarmType == QObject::tr("E-Stop"))
        str = QObject::tr("High-level");
    else if(AlarmType == QObject::tr("Horn count 100% lock"))
        str = QObject::tr("High-level");
    else if(AlarmType == QObject::tr("Anvil count 100% lock"))
        str = QObject::tr("High-level");
    else if(AlarmType == QObject::tr("Gather count 100% lock"))
        str = QObject::tr("High-level");
    else if(AlarmType == QObject::tr("Guide count 100% lock"))
        str = QObject::tr("High-level");
    else if(AlarmType == QObject::tr("Horn energy 100% lock"))
        str = QObject::tr("High-level");
    else if(AlarmType == QObject::tr("Anvil energy 100% lock"))
        str = QObject::tr("High-level");
    else if(AlarmType == QObject::tr("Gather energy 100% lock"))
        str = QObject::tr("High-level");
    else if(AlarmType == QObject::tr("Guide energy 100% lock"))
        str = QObject::tr("High-level");
    else
        str = QObject::tr("Low-level");
    return str;
}

QString VariantToString::GraphTimeToString(int ActualTime)
{
    return _Utility->FormatedDataToString(DINGraphTimeMS, ActualTime);
}

QString VariantToString::GraphPowerToString(int ActualPower)
{
    return _Utility->FormatedDataToString(DINGraphPower, ActualPower);
}

QString VariantToString::GraphHeightToString(int ActualHeight)
{
    return _Utility->FormatedDataToString(DINGraphHeight, ActualHeight);
}
