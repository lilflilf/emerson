#include "Statistics.h"
#include "math.h"
#include "M2010.h"
#include "M10INI.h"
#include "M102IA.h"
#include "M10runMode.h"
#include "SaveReplace.h"
#include "Interface/Interface.h"
#include "UtilityClass.h"
#include <QDateTime>
#include <QDebug>
Statistics* Statistics::_instance = 0;
Statistics* Statistics::Instance()
{
    if(_instance == 0){
        _instance = new Statistics();
    }
    return _instance;
}

Statistics::Statistics()
{

}

//void Statistics::UpdateSoftLimitData(bool ShowResults)
//{
//    int SampleSize, PartCount, DataCount;
//    int DataIndex;
//    long SLindexer;
//    QList<int> DataBase;
//    long FlagMask;
//    long StartIndex;
//    long FlagBit;
//    double WELDdata, Sum, SumSquared, Average;
//    double Sigma, SLLrange, SLHrange, Intermediate;
//    double MinLimit, MaxLimit;
//    int i;
//    M2010 *ptr_M2010 = M2010::Instance();
////    M10INI *ptr_M10INI = M10INI::Instance();
//    M102IA *ptr_M102IA = M102IA::Instance();
//    InterfaceClass* _Interface = InterfaceClass::Instance();

//    for(i = SLITime; i <= SLIHeight; i++)
//        SoftLimitData[i].SoftLimitStatus = SLSTSoftLimitOFF;

//    //Is the soft limit device off or invalid?
//    if (ptr_M2010->M10Run.Auto_Set_Mode == true)
//        return;
//    if ((_Interface->StatusData.SoftLimitsModeFlags & SoftLimitEnabledFlag) == 0)
//        return;
//    SampleSize = _Interface->StatusData.SoftLimitSampleSize;
//    PartCount = Splice_Stat.prts_count;
//    if (PartCount < SampleSize)
//        return;

//    //Global requirements met, check individual items and calculate the limits
//    for (SLindexer = SLITime; SLindexer <= SLIHeight; SLindexer++)
//    {
//        switch(SLindexer)
//        {
//        case SLITime:
//            DataBase = Splice_Stat.TimeData;
//            FlagMask = SoftLimitTimeFlags;
//            MinLimit = ptr_M102IA->IAsetup.Time.min;
//            MaxLimit = ptr_M102IA->IAsetup.Time.max;
//            break;
//        case SLIPower:
//            DataBase = Splice_Stat.PowerData;
//            FlagMask = SoftLimitPowerFlags;
//            MinLimit = ptr_M102IA->IAsetup.Power.min;
//            MaxLimit = ptr_M102IA->IAsetup.Power.max;
//            break;
//        case SLIPreHeight:
//            DataBase = Splice_Stat.PreHghtData;
//            FlagMask = SoftLimitPreHeightFlags;
//            MinLimit = ptr_M102IA->IAsetup.Preheight.min;
//            MaxLimit = ptr_M102IA->IAsetup.Preheight.max;
//            break;
//        case SLIHeight:
//            DataBase = Splice_Stat.HeightData;
//            FlagMask = SoftLimitHeightFlags;
//            MinLimit = ptr_M102IA->IAsetup.Height.min;
//            MaxLimit = ptr_M102IA->IAsetup.Height.max;
//            break;
//        }
//        FlagBit = _Interface->StatusData.SoftLimitsModeFlags & FlagMask;
//        if (FlagBit != 0)
//        {
//            SoftLimitData[SLindexer].SoftLimitStatus = SLSTSoftLimitON;
//            if (PartCount < M20_Data_Points)
//            {
//                DataCount = Splice_Stat.prts_count;
//                StartIndex = 0;
//            }
//            else{
//                DataCount = M20_Data_Points;         //Database is full
//                StartIndex = Splice_Stat.data_ptr;   //Points to next item
//            }
//            //Record last data for comparisons:
//            DataIndex = (DataCount - 1 + StartIndex) % M20_Data_Points;
//            SoftLimitData[SLindexer].LastData = DataBase[DataIndex];
//            //Initialize the calculations with the last piece of data
//            Sum = SoftLimitData[SLindexer].LastData;
//            SumSquared = SoftLimitData[SLindexer].LastData *
//                    SoftLimitData[SLindexer].LastData;
//            //Add the previous elements to the data
//            for(i = (DataCount - 2); i >= (DataCount - SampleSize); i--)
//            {
//                DataIndex = (i + StartIndex) % M20_Data_Points;
//                WELDdata = DataBase[DataIndex];
//                Sum += WELDdata;
//                SumSquared += (WELDdata * WELDdata);
//            }
//            Average = Sum / SampleSize;
//            if ((FlagBit % 3) == 2)   //High flag = Percent mode
//            {
//                //Calculate the upper soft limit
//                //Convert a percentage to a decimal by half for the upper range
//                SLHrange = _Interface->StatusData.SoftLimit[SLIUpperControlLimit][SLindexer] / 200;
//                SLHrange = SLHrange * (MaxLimit - MinLimit);
//                //Calculate the lower soft limit
//                SLLrange = _Interface->StatusData.SoftLimit[SLILowerControlLimit][SLindexer] / 200;
//                SLLrange = SLLrange * (MaxLimit - MinLimit);
//            }
//            else{
//                //Sigma mode
//                Intermediate = (SampleSize * SumSquared - Sum * Sum) / SampleSize;
//                if ((_Interface->StatusData.SoftLimitsModeFlags & SoftLimitWeightFlag) == 0)
//                    //Bias = N-1
//                    Sigma = sqrt(Intermediate / (SampleSize - 1));
//                else
//                    //Bias = N
//                    Sigma = sqrt(Intermediate / SampleSize);

//                SLHrange = Sigma * _Interface->StatusData.SoftLimit[SLIUpperControlLimit][SLindexer];
//                SLLrange = Sigma * _Interface->StatusData.SoftLimit[SLILowerControlLimit][SLindexer];
//            }
//            SoftLimitData[SLindexer].Average = Average;
//            SoftLimitData[SLindexer].HighLimit = Average + SLHrange;
//            SoftLimitData[SLindexer].LowLimit = Average - SLLrange;

//            //Regardless of the results the limits must be in the hard limit windows
//            if (SoftLimitData[SLindexer].HighLimit > MaxLimit)
//                SoftLimitData[SLindexer].HighLimit = MaxLimit;
//            if (SoftLimitData[SLindexer].LowLimit < MinLimit)
//                SoftLimitData[SLindexer].LowLimit = MinLimit;
//            if (ShowResults == true)
//            {
//                if ((SoftLimitData[SLindexer].LastData > SoftLimitData[SLindexer].HighLimit) ||
//                    (SoftLimitData[SLindexer].LastData < SoftLimitData[SLindexer].LowLimit))
//                {

//                    if ((_Interface->StatusData.SoftLimitsModeFlags & SoftLimitAudibleFlag) != 0)
//                        ptr_M102IA->Generate_Beep();
//                }
//            }      //ShowResults
//        }          //FlagBit <> 0
//    }             //SLindexer
//}

void Statistics::RotateOut(StatStats &SumStats, int OldData)
{
    SumStats.Sum = SumStats.Sum - OldData;
    SumStats.Sum_sqr = SumStats.Sum_sqr - (OldData * OldData);
}

void Statistics::RotateIn(StatStats &SumStats, int* DataEvent, int NewData)
{
    *DataEvent = NewData;
    SumStats.Sum += NewData;
    SumStats.Sum_sqr += (NewData * NewData);
}

void Statistics::UpdateSpliceStatStats()
{

}

void Statistics::EnterM20DataEvent()
{
    int ptr;
    M102IA *_M102IA = M102IA::Instance();
    ptr = Splice_Stat.data_ptr;
    if (Splice_Stat.prts_count >= M20_Stat_Points)
    {
       RotateOut(Splice_Stat.Time, Splice_Stat.TimeData[ptr]);
       RotateOut(Splice_Stat.Power, Splice_Stat.PowerData[ptr]);
       RotateOut(Splice_Stat.Pre_hght, Splice_Stat.PreHghtData[ptr]);
       RotateOut(Splice_Stat.Height, Splice_Stat.HeightData[ptr]);
    }

    RotateIn(Splice_Stat.Time, &Splice_Stat.TimeData[ptr], _M102IA->IAactual.Time);
    RotateIn(Splice_Stat.Power, &Splice_Stat.PowerData[ptr], _M102IA->IAactual.Power);
    RotateIn(Splice_Stat.Pre_hght, &Splice_Stat.PreHghtData[ptr], _M102IA->IAactual.Preheight);
    RotateIn(Splice_Stat.Height, &Splice_Stat.HeightData[ptr], _M102IA->IAactual.Height);


    Splice_Stat.prts_count += 1;
    Splice_Stat.data_ptr += 1;
    Splice_Stat.data_ptr %= M20_Stat_Points;
    //Cannot allow counter to go negative
    //It also must be set to a high number to keep the count tests to display the correct data
    if (Splice_Stat.prts_count > 32760) Splice_Stat.prts_count = 1000;
}

void Statistics::ZeroM20DataEvents()
{
    M10runMode* ptr_M10runMode = M10runMode::Instance();
    Splice_Stat.prts_count = 0;
    Splice_Stat.data_ptr = 0;
    Splice_Stat.Time.Sum = 0;
    Splice_Stat.Time.Sum_sqr = 0;
    Splice_Stat.Power.Sum = 0;
    Splice_Stat.Power.Sum_sqr = 0;
    Splice_Stat.Pre_hght.Sum = 0;
    Splice_Stat.Pre_hght.Sum_sqr = 0;
    Splice_Stat.Power.Sum_sqr = 0;
    Splice_Stat.Height.Sum = 0;
    Splice_Stat.Height.Sum_sqr = 0;

    Splice_Stat.TimeData.clear();
    Splice_Stat.PowerData.clear();
    Splice_Stat.PreHghtData.clear();
    Splice_Stat.HeightData.clear();
    for(int i = 0; i < M20_Data_Pnt_MI; i++)
    {
        Splice_Stat.TimeData.push_back(NOT_VALID);
        Splice_Stat.PowerData.push_back(NOT_VALID);
        Splice_Stat.PreHghtData.push_back(NOT_VALID);
        Splice_Stat.HeightData.push_back(NOT_VALID);
    }

    ptr_M10runMode->InvalidWeldCounter = 0; //used in Auto Teach mode only
}

void Statistics::UpdateCounter()
{
    EnterM20DataEvent();
}

void Statistics::start_data_structures()
{
    //Chart_f_of_x function
    int i;
    double sqrt_2PI, X;

    sqrt_2PI = sqrt(2 * PI);  //Constant divisor

    //Plot the normal curve
    for (i = 0; i <= 100; i++)
    {
        X = 0.1 * (i - 50);
        f_of_x[i] = (exp(-0.5 * X * X)) / sqrt_2PI;
    }
}

void Statistics::Open_Maint_Log()
{

}

QString Statistics::HeaderString()
{
    QString sHeader;
    QString WidthString;
    M2010 *_M2010 = M2010::Instance();
    if(_M2010->Machine != Welder)
        WidthString = "\t" + QObject::tr("Width") + "\t";
    else
        WidthString = "\t";
    sHeader = QObject::tr("Cycle count") + "\t" + QObject::tr("Date") + "\t" +
            QObject::tr("Time") + "\t" + QObject::tr("Work Order Name") + "\t" +
            QObject::tr("Part Name") + "\t" + QObject::tr("Splice Name") + "\t" +
            QObject::tr("Process Parameters") + "\t" +
            QObject::tr("Energy") + WidthString + QObject::tr("Trigger Pressure") + "\t" +
            QObject::tr("Pressure") + "\t" + QObject::tr("Amplitude") + "\t" +
            QObject::tr("Quality Windows") + "\t" + QObject::tr("Time+") + "\t" +
            QObject::tr("Time-") + "\t" + QObject::tr("Power+") + "\t" +
            QObject::tr("Power-") + "\t" + QObject::tr("PreHeight+") + "\t" +
            QObject::tr("PreHeight-") + "\t" + QObject::tr("Height+") + "\t" +
            QObject::tr("Height-") + "\t" + QObject::tr("Weld result") + "\t" +
            QObject::tr("Time") + "\t" + QObject::tr("Power") + "\t" +
            QObject::tr("Pre-Height") + "\t" + QObject::tr("Height") + "\t" +
            QObject::tr("Alarm") + "\t" + QObject::tr("Graph Data Ratio") + "\t" +
            QObject::tr("Graph Data");

     return sHeader;
}

QString Statistics::GraphData(enum ScreenShowDataType DataType, QList<int> *_GraphData)
{
    UtilityClass *_Utility = UtilityClass::Instance();
    QString sGraphData;

    for(int i = 0; i< _GraphData->size(); i++)
        sGraphData += (_Utility->FormatedDataToString(DataType,
                    _GraphData->at(i))) + "\t";
    return sGraphData;
}

//Create a tab deliminated file for loading into an Excel worksheet
//It stores all the Actual data regarding a Preset in the .tsv file during welding.
//Also Displays Amplitude2 along with Amplitude1 if Amplitude Step is enabled
QString Statistics::HistoryEvent(WeldResultElement *_WeldResult, PresetElement *_Splice)
{
    InterfaceClass *_Interface = InterfaceClass::Instance();
    UtilityClass *_Utility = UtilityClass::Instance();
    M2010 *_M2010 = M2010::Instance();
    QString sDate, sTime, sEvent, sAlarms, sMode, sCut, sGraph, sStatus, sSampleRatio;
//    QString sHeader;
//    sHeader = HeaderString();
//    if(_Interface->StatusData.NetworkingEnabled == false)
//        return;
    //Build alarm string, Overload precludes any other and pre-hiehgt can't get here
    if ((_WeldResult->ActualResult.ActualAlarmflags & iAlarms) == 0)
    {
        sAlarms = "-";
        sStatus = "OK";
    }else
    {
        sStatus = "NOK";
        if((_WeldResult->ActualResult.ActualAlarmflags & iOverLoadFault) == iOverLoadFault)
            sAlarms = "O";
        else
        {
            sAlarms = "";
            if((_WeldResult->ActualResult.ActualAlarmflags & iTimeFault) == iTimeFault)
                sAlarms = "T";
            if((_WeldResult->ActualResult.ActualAlarmflags & iPowerFault) == iPowerFault)
                sAlarms = "P";
            if((_WeldResult->ActualResult.ActualAlarmflags & iHeightFault) == iHeightFault)
                sAlarms = "H";
            if((_WeldResult->ActualResult.ActualAlarmflags & iWidthFault) == iWidthFault)
                sAlarms = "W";
        }
    }
    switch(_Interface->StatusData.GraphSampleRatio)
    {
    case WeldResultElement::SampleWith1ms:
        sSampleRatio = "1ms";
        break;
    case WeldResultElement::SampleWith5ms:
        sSampleRatio = "5ms";
        break;
    case WeldResultElement::SampleWith10ms:
        sSampleRatio = "10ms";
        break;
    case WeldResultElement::SampleWith20ms:
        sSampleRatio = "20ms";
        break;
    default:
        sSampleRatio = "1ms";
        break;
    }
    QDateTime CurrentTime = QDateTime::currentDateTime();
    sDate = CurrentTime.toString("yyyy/MM/dd");
    sTime = CurrentTime.toString("hh:mm:ss");

    if (sAlarms == "-")
        sEvent = _Interface->StatusData.CycleCount + "\t" + sDate + "\t" + sTime;
    else
        sEvent = _Interface->StatusData.CycleCount + "*\t" + sDate + "\t" + sTime;

    QString PartName;
    switch(_Interface->CurrentWorkOrder.WorkOrderMode)
    {
    case WorkOrderElement::SPLICE:
        PartName = "NONE";
        break;
    case WorkOrderElement::SEQUENCE:
        PartName = _WeldResult->CurrentSequence.SequenceName;
        break;
    case WorkOrderElement::HARNESS:
        PartName = _WeldResult->CurrentHarness.HarnessName;
        break;
    default:
        PartName = "NONE";
        break;
    }
    sEvent += "\t" + PartName + "\t" + _Splice->SpliceName;
    sEvent += "\t\t" + _Utility->FormatedDataToString(DINEnergy,
            _WeldResult->ActualResult.ActualEnergy);
    if(_M2010->Machine != Welder)
        sEvent += "\t" + _Utility->FormatedDataToString(DINWidth,
                _WeldResult->ActualResult.ActualWidth);
    sEvent += "\t" + _Utility->FormatedDataToString(DINTriggerPressure,
            _WeldResult->ActualResult.ActualTPressure);
    sEvent += "\t" + _Utility->FormatedDataToString(DINPressure,
            _WeldResult->ActualResult.ActualPressure);
    if(_Splice->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode != STEPWELD::STEPDISABLE)
        sEvent += "\t" + _Utility->FormatedDataToString(DINAmplitude, _WeldResult->ActualResult.ActualAmplitude) +
                "/" + _Utility->FormatedDataToString(DINAmplitude2, _WeldResult->ActualResult.ActualAmplitude2);
    else
        sEvent += "\t" + _Utility->FormatedDataToString(DINAmplitude,
                _WeldResult->ActualResult.ActualAmplitude);
    sEvent += "\t\t" + _Utility->FormatedDataToString(DINTimePl,
            _Splice->WeldSettings.QualitySetting.Time.Plus);
    sEvent += "\t" + _Utility->FormatedDataToString(DINTimeMs,
            _Splice->WeldSettings.QualitySetting.Time.Minus);
    sEvent += "\t" + _Utility->FormatedDataToString(DINPowerPl,
            _Splice->WeldSettings.QualitySetting.Power.Plus);
    sEvent += "\t" + _Utility->FormatedDataToString(DINPowerMs,
            _Splice->WeldSettings.QualitySetting.Power.Minus);
    sEvent += "\t" + _Utility->FormatedDataToString(DINPre_HgtPl,
            _Splice->WeldSettings.QualitySetting.Preheight.Plus);
    sEvent += "\t" + _Utility->FormatedDataToString(DINPre_HgtMs,
            _Splice->WeldSettings.QualitySetting.Preheight.Minus);
    sEvent += "\t" + _Utility->FormatedDataToString(DINHeightPl,
            _Splice->WeldSettings.QualitySetting.Height.Plus);
    sEvent += "\t" + _Utility->FormatedDataToString(DINHeightMs,
            _Splice->WeldSettings.QualitySetting.Height.Minus);

    sEvent += "\t\t" + _Utility->FormatedDataToString(DINActTime,
            _WeldResult->ActualResult.ActualTime);
    sEvent += "\t" + _Utility->FormatedDataToString(DINActPower,
            _WeldResult->ActualResult.ActualPeakPower);
    sEvent += "\t" + _Utility->FormatedDataToString(DINActPreHgt,
            _WeldResult->ActualResult.ActualPreheight);
    sEvent += "\t" + _Utility->FormatedDataToString(DINActHgt,
            _WeldResult->ActualResult.ActualPostheight);

    sEvent += "\t" + sAlarms;
    sEvent += "\t" + sSampleRatio;

    //Now handle Graph Data
    sGraph = GraphData(DINActPower, &_WeldResult->PowerGraph);
    sGraph += GraphData(DINActHgt, &_WeldResult->PostHeightGraph);
    QString sRecord = sEvent + "\t" + sGraph + "\r\n";
    return sRecord;
}

void Statistics::CalcConfLimits(PresetElement *_Splice)
{
    UtilityClass *_Utility = UtilityClass::Instance();
    M102IA *_M102IA = M102IA::Instance();
    int entries;
    double time_sigma, power_sigma, pre_hght_sigma, height_sigma;
    double time_x_bar, power_x_bar, pre_hght_x_bar, height_x_bar;
    if(Splice_Stat.prts_count < 1)
    {
        time_lower_limit = (double)_M102IA->IAsetup.Time.min;
        time_upper_limit = (double)_M102IA->IAsetup.Time.max;
        power_lower_limit = (double)_M102IA->IAsetup.Power.min;
        power_upper_limit = (double)_M102IA->IAsetup.Power.max;
        pre_hght_lower_limit = (double)_M102IA->IAsetup.Preheight.min;
        pre_hght_upper_limit = (double)_M102IA->IAsetup.Preheight.max;
        height_lower_limit = (double)_M102IA->IAsetup.Height.min;
        height_upper_limit = (double)_M102IA->IAsetup.Height.max;
        Splice_Stat.prts_count = 0;
        return;
    }

    if(Splice_Stat.prts_count >= M20_Stat_Points)
        entries = M20_Stat_Points;
    else
        entries = Splice_Stat.prts_count;

    //average of weld results so far
    time_x_bar = Splice_Stat.Time.Sum/entries;
    power_x_bar = Splice_Stat.Power.Sum/entries;
    pre_hght_x_bar = Splice_Stat.Pre_hght.Sum/entries;
    height_x_bar = Splice_Stat.Height.Sum/entries;

    if(Splice_Stat.prts_count == TEACH_AUTO_THRESHOLD)
    {
        Time_Average = time_x_bar;
        Power_Average = power_x_bar;
        PreHeight_Avreage = pre_hght_x_bar;
        Height_Average = height_x_bar;
    }
    switch(_Splice->TestSetting.TeachModeSetting.TeachModeType)
    {
    case TEACHMODESETTING::SIGMA:
        if(entries < MIN_STATS_QUANT)
        {
            time_lower_limit = 0.5 * time_x_bar;
            time_upper_limit = 1.5 * time_x_bar;
            power_lower_limit = 0.5 * power_x_bar;
            power_upper_limit = 1.5 * power_x_bar;
            pre_hght_lower_limit = 0.5 * pre_hght_x_bar;
            pre_hght_upper_limit = 1.5 * pre_hght_x_bar;
            height_lower_limit = 0.5 * height_x_bar;
            height_upper_limit = 1.5 * height_x_bar;
        }
        else
        {
            power_sigma = (Splice_Stat.Power.Sum_sqr - Splice_Stat.Power.Sum *
                           Splice_Stat.Power.Sum / entries) / (entries - 1);
            if(power_sigma < 0) power_sigma = power_sigma * (-1);
            power_sigma = sqrt(power_sigma);

            time_sigma = (Splice_Stat.Time.Sum_sqr - Splice_Stat.Time.Sum *
                    Splice_Stat.Time.Sum / entries) / (entries - 1);
            if(time_sigma < 0) time_sigma = time_sigma * (-1);
            time_sigma = sqrt(time_sigma);    //find square root

            pre_hght_sigma = (Splice_Stat.Pre_hght.Sum_sqr - Splice_Stat.Pre_hght.Sum *
                    Splice_Stat.Pre_hght.Sum / entries) / (entries - 1);
            if(pre_hght_sigma < 0) pre_hght_sigma = pre_hght_sigma * (-1);
            pre_hght_sigma = sqrt(pre_hght_sigma);

            height_sigma = (Splice_Stat.Height.Sum_sqr - Splice_Stat.Height.Sum *
                    Splice_Stat.Height.Sum / entries) / (entries - 1);
            if(height_sigma < 0) height_sigma = height_sigma * (-1);
            height_sigma = sqrt(height_sigma);

            time_lower_limit = time_x_bar - _Splice->TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_MS] * time_sigma;
            time_upper_limit = time_x_bar + _Splice->TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_PL] * time_sigma;
            power_lower_limit = power_x_bar - _Splice->TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_MS] * power_sigma;
            power_upper_limit = power_x_bar + _Splice->TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_PL] * power_sigma;
            pre_hght_lower_limit = pre_hght_x_bar - _Splice->TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_MS] * pre_hght_sigma;
            pre_hght_upper_limit = pre_hght_x_bar + _Splice->TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_PL] * pre_hght_sigma;
            height_lower_limit = height_x_bar - _Splice->TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_MS] * height_sigma;
            height_upper_limit = height_x_bar + _Splice->TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_PL] * height_sigma;
        }
        break;
    case TEACHMODESETTING::STANDARD:
        time_lower_limit = time_x_bar * (1 - (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG_STD] * 0.01));
        time_upper_limit = time_x_bar * (1 + (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG_STD] * 0.01));
        power_lower_limit = power_x_bar * (1 - (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG_STD] * 0.01));
        power_upper_limit = power_x_bar * (1 + (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG_STD] * 0.01));
        pre_hght_lower_limit = pre_hght_x_bar * (1 - (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG_STD] * 0.01));
        pre_hght_upper_limit = pre_hght_x_bar * (1 + (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG_STD] * 0.01));
        height_lower_limit = height_x_bar * (1 - (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG_STD] * 0.01));
        height_upper_limit = height_x_bar * (1 + (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG_STD] * 0.01));
        break;
    case TEACHMODESETTING::AUTO:
        time_lower_limit = time_x_bar * (1 - (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG_AUTO] * 0.01));
        time_upper_limit = time_x_bar * (1 + (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG_AUTO] * 0.01));
        power_lower_limit = power_x_bar * (1 - (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG_AUTO] * 0.01));
        power_upper_limit = power_x_bar * (1 + (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG_AUTO] * 0.01));
        pre_hght_lower_limit = pre_hght_x_bar * (1 - (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG_AUTO] * 0.01));
        pre_hght_upper_limit = pre_hght_x_bar * (1 + (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG_AUTO] * 0.01));
        height_lower_limit = height_x_bar * (1 - (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG_AUTO] * 0.01));
        height_upper_limit = height_x_bar * (1 + (_Splice->TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG_AUTO] * 0.01));
        break;
    case TEACHMODESETTING::UNDEFINED:
        break;
    }
    if (time_lower_limit < 0) time_lower_limit = MINTIME;
    if (time_upper_limit > (MAXTIME / 2)) time_lower_limit = MAXTIME / 2;
    if (power_lower_limit < 0) power_lower_limit = 0;
    if (power_upper_limit > _Utility->Maxpower) power_upper_limit = _Utility->Maxpower;
    if (pre_hght_lower_limit < 0) pre_hght_lower_limit = MINPREHEIGHT;
    if (pre_hght_upper_limit > MAXPREHEIGHT) pre_hght_upper_limit = MAXPREHEIGHT;
    if (height_lower_limit < 0) height_lower_limit = MINHEIGHT;
    if (height_upper_limit > MAXHEIGHT) height_upper_limit = MAXHEIGHT;
    qDebug()<<"time_lower_limit: "<<time_lower_limit<<
              "time_upper_limit: "<<time_upper_limit<<
              "power_lower_limit: "<<power_lower_limit<<
              "power_upper_limit: "<<power_upper_limit<<
              "pre_hght_lower_limit: "<<pre_hght_lower_limit<<
              "pre_hght_upper_limit: "<<pre_hght_upper_limit<<
              "height_lower_limit: "<<height_lower_limit<<
              "height_upper_limit: "<<height_upper_limit;

}

void Statistics::CalcConfLimits(Status_Data *_StatusData)
{
    int entries = 0;
    double time_sigma = 0.0, power_sigma = 0.0, pre_hght_sigma = 0.0, height_sigma = 0.0;
    double time_x_bar = 0.0, power_x_bar = 0.0, pre_hght_x_bar = 0.0, height_x_bar = 0.0;
    M102IA *_M102IA = M102IA::Instance();
    UtilityClass *_Utility = UtilityClass::Instance();
    //Check for enough data to produce graphs
    if(Splice_Stat.prts_count < 1)
    {
        time_lower_limit = (double)_M102IA->IAsetup.Time.min;
        time_upper_limit = (double)_M102IA->IAsetup.Time.max;
        power_lower_limit = (double)_M102IA->IAsetup.Power.min;
        power_upper_limit = (double)_M102IA->IAsetup.Power.max;
        pre_hght_lower_limit = (double)_M102IA->IAsetup.Preheight.min;
        pre_hght_upper_limit = (double)_M102IA->IAsetup.Preheight.max;
        height_lower_limit = (double)_M102IA->IAsetup.Height.min;
        height_upper_limit = (double)_M102IA->IAsetup.Height.max;
        Splice_Stat.prts_count = 0;
        return;
    }

    if(Splice_Stat.prts_count > M20_Stat_Points)
        entries = M20_Stat_Points;
    else
        entries = Splice_Stat.prts_count;

    time_x_bar = (double)(Splice_Stat.Time.Sum / entries);          //average of weld results so far
    power_x_bar = (double)(Splice_Stat.Power.Sum / entries);
    pre_hght_x_bar = (double)(Splice_Stat.Pre_hght.Sum / entries);
    height_x_bar = (double)(Splice_Stat.Height.Sum / entries);
    if(Splice_Stat.prts_count == TEACH_AUTO_THRESHOLD)              //for use in Auto Teach stage 2
    {
        Time_Average = time_x_bar;
        Power_Average = power_x_bar;
        PreHeight_Avreage = pre_hght_x_bar;
        Height_Average = height_x_bar;
    }

    switch(_StatusData->Soft_Settings.Teach_Mode)
    {
    case TEACHMODESETTING::SIGMA:
        if(entries < MIN_STATS_QUANT)
        {
            time_lower_limit = 0.5 * time_x_bar;
            time_upper_limit = 1.5 * time_x_bar;
            power_lower_limit = 0.5 * power_x_bar;
            power_upper_limit = 1.5 * power_x_bar;
            pre_hght_lower_limit = 0.5 * pre_hght_x_bar;
            pre_hght_upper_limit = 1.5 * pre_hght_x_bar;
            height_lower_limit = 0.5 * height_x_bar;
            height_upper_limit = 1.5 * height_x_bar;
        }
        else
        {
            power_sigma = ((double)(Splice_Stat.Power.Sum_sqr) - (double)(Splice_Stat.Power.Sum) *
                    (double)(Splice_Stat.Power.Sum) / entries) / (entries - 1);
            if(power_sigma < 0) power_sigma = power_sigma * (-1);
            power_sigma = sqrt(power_sigma);

            time_sigma = ((double)(Splice_Stat.Time.Sum_sqr) - (double)(Splice_Stat.Time.Sum) *
                    (double)(Splice_Stat.Time.Sum) / entries) / (entries - 1);
            if(time_sigma < 0) time_sigma = time_sigma * (-1);
            time_sigma = sqrt(time_sigma);    //find square root

            pre_hght_sigma = ((double)(Splice_Stat.Pre_hght.Sum_sqr) - (double)(Splice_Stat.Pre_hght.Sum) *
                    (double)(Splice_Stat.Pre_hght.Sum) / entries) / (entries - 1);
            if(pre_hght_sigma < 0) pre_hght_sigma = pre_hght_sigma * (-1);
            pre_hght_sigma = sqrt(pre_hght_sigma);

            height_sigma = ((double)(Splice_Stat.Height.Sum_sqr) - (double)(Splice_Stat.Height.Sum) *
                    (double)(Splice_Stat.Height.Sum) / entries) / (entries - 1);
            if(height_sigma < 0) height_sigma = height_sigma * (-1);
            height_sigma = sqrt(height_sigma);

            time_lower_limit = (double)(time_x_bar) - _StatusData->Cust_Data.cust_qual_range[TIME_CONFRG_MS] * time_sigma;
            time_upper_limit = (double)(time_x_bar) + _StatusData->Cust_Data.cust_qual_range[TIME_CONFRG_PL] * time_sigma;
            power_lower_limit = (double)(power_x_bar) - _StatusData->Cust_Data.cust_qual_range[POWER_CONFRG_MS] * power_sigma;
            power_upper_limit = (double)(power_x_bar) + _StatusData->Cust_Data.cust_qual_range[POWER_CONFRG_PL] * power_sigma;
            pre_hght_lower_limit = (double)(pre_hght_x_bar) - _StatusData->Cust_Data.cust_qual_range[PRE_HGT_CONFRG_MS] * pre_hght_sigma;
            pre_hght_upper_limit = (double)(pre_hght_x_bar) + _StatusData->Cust_Data.cust_qual_range[PRE_HGT_CONFRG_PL] * pre_hght_sigma;
            height_lower_limit = (double)(height_x_bar) - _StatusData->Cust_Data.cust_qual_range[HEIGHT_CONFRG_MS] * height_sigma;
            height_upper_limit = (double)(height_x_bar) + _StatusData->Cust_Data.cust_qual_range[HEIGHT_CONFRG_PL] * height_sigma;
        }
        break;
    case TEACHMODESETTING::STANDARD:
        time_lower_limit = (double)(time_x_bar) * (1 - (_StatusData->Cust_Data.cust_qual_range[TIME_MSRG_STD] * 0.01));
        time_upper_limit = (double)(time_x_bar) * (1 + (_StatusData->Cust_Data.cust_qual_range[TIME_PLRG_STD] * 0.01));
        power_lower_limit = (double)(power_x_bar) * (1 - (_StatusData->Cust_Data.cust_qual_range[POWER_MSRG_STD] * 0.01));
        power_upper_limit = (double)(power_x_bar) * (1 + (_StatusData->Cust_Data.cust_qual_range[POWER_PLRG_STD] * 0.01));
        pre_hght_lower_limit = (double)(pre_hght_x_bar) * (1 - (_StatusData->Cust_Data.cust_qual_range[PRE_HGT_MSRG_STD] * 0.01));
        pre_hght_upper_limit = (double)(pre_hght_x_bar) * (1 + (_StatusData->Cust_Data.cust_qual_range[PRE_HGT_PLRG_STD] * 0.01));
        height_lower_limit = (double)(height_x_bar) * (1 - (_StatusData->Cust_Data.cust_qual_range[HEIGHT_MSRG_STD] * 0.01));
        height_upper_limit = (double)(height_x_bar) * (1 + (_StatusData->Cust_Data.cust_qual_range[HEIGHT_PLRG_STD] * 0.01));
        break;
    case TEACHMODESETTING::AUTO:
        time_lower_limit = (double)(time_x_bar) * (1 - (_StatusData->Cust_Data.cust_qual_range[TIME_MSRG_AUTO] * 0.01));
        time_upper_limit = (double)(time_x_bar) * (1 + (_StatusData->Cust_Data.cust_qual_range[TIME_PLRG_AUTO] * 0.01));
        power_lower_limit = (double)(power_x_bar) * (1 - (_StatusData->Cust_Data.cust_qual_range[POWER_MSRG_AUTO] * 0.01));
        power_upper_limit = (double)(power_x_bar) * (1 + (_StatusData->Cust_Data.cust_qual_range[POWER_PLRG_AUTO] * 0.01));
        pre_hght_lower_limit = (double)(pre_hght_x_bar) * (1 - (_StatusData->Cust_Data.cust_qual_range[PRE_HGT_MSRG_AUTO] * 0.01));
        pre_hght_upper_limit = (double)(pre_hght_x_bar) * (1 + (_StatusData->Cust_Data.cust_qual_range[PRE_HGT_PLRG_AUTO] * 0.01));
        height_lower_limit = (double)(height_x_bar) * (1 - (_StatusData->Cust_Data.cust_qual_range[HEIGHT_MSRG_AUTO] * 0.01));
        height_upper_limit = (double)(height_x_bar) * (1 + (_StatusData->Cust_Data.cust_qual_range[HEIGHT_PLRG_AUTO] * 0.01));
        break;
    default:
        break;
    }
    if(time_lower_limit < 0) time_lower_limit = MINTIME;
    if(time_upper_limit > MAXTIME / 2) time_lower_limit = MAXTIME / 2;
    if(power_lower_limit < 0) power_lower_limit = 0;
    if(power_upper_limit > _Utility->Maxpower) power_upper_limit = _Utility->Maxpower;
    if(pre_hght_lower_limit < 0) pre_hght_lower_limit = MINPREHEIGHT;
    if(pre_hght_upper_limit > MAXPREHEIGHT) pre_hght_upper_limit = MAXPREHEIGHT;
    if(height_lower_limit < 0) height_lower_limit = MINHEIGHT;
    if(height_upper_limit > MAXHEIGHT) height_upper_limit = MAXHEIGHT;
}

void Statistics::GetLimitsAfterWeld(PresetElement *_Splice)
{
    if(_Splice->TestSetting.TeachModeSetting.TeachModeType != TEACHMODESETTING::AUTO)
        return;
    if(Splice_Stat.prts_count != TEACH_AUTO_THRESHOLD)
        return;
    power_lower_limit = Power_Average * 0.9;
    power_upper_limit = Power_Average * 1.1;
    pre_hght_lower_limit = PreHeight_Avreage * 0.9;
    pre_hght_upper_limit = PreHeight_Avreage * 1.1;
    if(_Splice->WeldSettings.AdvanceSetting.WeldMode != ADVANCESETTING::TIME)
    {
        time_lower_limit = Time_Average * 0.9;               //down by ten percent
        time_upper_limit = Time_Average * 1.1;               //up by ten percent
        _Splice->WeldSettings.QualitySetting.Time.Minus = 2 * int(time_lower_limit);
        _Splice->WeldSettings.QualitySetting.Time.Plus = 2 * int(time_upper_limit);
    }
   _Splice->WeldSettings.QualitySetting.Power.Minus = int(power_lower_limit);
   _Splice->WeldSettings.QualitySetting.Power.Plus = int(power_upper_limit);
   _Splice->WeldSettings.QualitySetting.Preheight.Minus = int(pre_hght_lower_limit);
   _Splice->WeldSettings.QualitySetting.Preheight.Plus = int(pre_hght_upper_limit);
   if((_Splice->WeldSettings.AdvanceSetting.WeldMode != ADVANCESETTING::HEIGHT) &&
       (_Splice->WeldSettings.AdvanceSetting.WeldMode != ADVANCESETTING::ENERGYWITHHEIGHT))
   {
      height_lower_limit = Height_Average * 0.9;
      height_upper_limit = Height_Average * 1.1;
      _Splice->WeldSettings.QualitySetting.Height.Minus = int(height_lower_limit);
      _Splice->WeldSettings.QualitySetting.Height.Plus = int(height_upper_limit);
   }
   qDebug()<<"Time.Minus: "<<_Splice->WeldSettings.QualitySetting.Time.Minus<<
             "Time.Plus: "<<_Splice->WeldSettings.QualitySetting.Time.Plus<<
             "Power.Minus: "<<_Splice->WeldSettings.QualitySetting.Power.Minus<<
             "Power.Plus: "<<_Splice->WeldSettings.QualitySetting.Power.Plus<<
             "Preheight.Minus: "<<_Splice->WeldSettings.QualitySetting.Preheight.Minus<<
             "Preheight.Plus: "<<_Splice->WeldSettings.QualitySetting.Preheight.Plus<<
             "Height.Minus: "<<_Splice->WeldSettings.QualitySetting.Height.Minus<<
             "Height.Plus: "<<_Splice->WeldSettings.QualitySetting.Height.Plus;
}
