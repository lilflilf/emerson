#include "Statistics.h"
#include "math.h"
#include "M2010.h"
#include "M10INI.h"
#include "M102IA.h"
#include "M10runMode.h"
#include "Interface/Interface.h"
#include "UtilityClass.h"
#include "QDateTime"
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
void Statistics::UpdateSoftLimitData(bool ShowResults)
{
    int SampleSize, PartCount, DataCount;
    int DataIndex;
    long SLindexer;
    WeldEventData DataBase;
    long FlagMask;
    long StartIndex;
    long FlagBit;
    double WELDdata, Sum, SumSquared, Average;
    double Sigma, SLLrange, SLHrange, Intermediate;
    double MinLimit, MaxLimit;
    int i;
    M2010 *ptr_M2010 = M2010::Instance();
//    M10INI *ptr_M10INI = M10INI::Instance();
    M102IA *ptr_M102IA = M102IA::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();

    for(i = SLITime; i <= SLIHeight; i++)
        SoftLimitData[i].SoftLimitStatus = SLSTSoftLimitOFF;

    //Is the soft limit device off or invalid?
    if (ptr_M2010->M10Run.Auto_Set_Mode == true)
        return;
    if ((_Interface->StatusData.SoftLimitsModeFlags & SoftLimitEnabledFlag) == 0)
        return;
    SampleSize = _Interface->StatusData.SoftLimitSampleSize;
    PartCount = Splice_Stat.prts_count;
    if (PartCount < SampleSize)
        return;

    //Global requirements met, check individual items and calculate the limits
    for (SLindexer = SLITime; SLindexer <= SLIHeight; SLindexer++)
    {
        switch(SLindexer)
        {
        case SLITime:
            DataBase = Splice_Stat.TimeData;
            FlagMask = SoftLimitTimeFlags;
            MinLimit = ptr_M102IA->IAsetup.Time.min;
            MaxLimit = ptr_M102IA->IAsetup.Time.max;
            break;
        case SLIPower:
            DataBase = Splice_Stat.PowerData;
            FlagMask = SoftLimitPowerFlags;
            MinLimit = ptr_M102IA->IAsetup.Power.min;
            MaxLimit = ptr_M102IA->IAsetup.Power.max;
            break;
        case SLIPreHeight:
            DataBase = Splice_Stat.PreHghtData;
            FlagMask = SoftLimitPreHeightFlags;
            MinLimit = ptr_M102IA->IAsetup.Preheight.min;
            MaxLimit = ptr_M102IA->IAsetup.Preheight.max;
            break;
        case SLIHeight:
            DataBase = Splice_Stat.HeightData;
            FlagMask = SoftLimitHeightFlags;
            MinLimit = ptr_M102IA->IAsetup.Height.min;
            MaxLimit = ptr_M102IA->IAsetup.Height.max;
            break;
        }
        FlagBit = _Interface->StatusData.SoftLimitsModeFlags & FlagMask;
        if (FlagBit != 0)
        {
            SoftLimitData[SLindexer].SoftLimitStatus = SLSTSoftLimitON;
            if (PartCount < M20_Data_Points)
            {
                DataCount = Splice_Stat.prts_count;
                StartIndex = 0;
            }
            else{
                DataCount = M20_Data_Points;         //Database is full
                StartIndex = Splice_Stat.data_ptr;   //Points to next item
            }
            //Record last data for comparisons:
            DataIndex = (DataCount - 1 + StartIndex) % M20_Data_Points;
            SoftLimitData[SLindexer].LastData = DataBase.Data[DataIndex];
            //Initialize the calculations with the last piece of data
            Sum = SoftLimitData[SLindexer].LastData;
            SumSquared = SoftLimitData[SLindexer].LastData *
                    SoftLimitData[SLindexer].LastData;
            //Add the previous elements to the data
            for(i = (DataCount - 2); i >= (DataCount - SampleSize); i--)
            {
                DataIndex = (i + StartIndex) % M20_Data_Points;
                WELDdata = DataBase.Data[DataIndex];
                Sum = Sum + WELDdata;
                SumSquared = SumSquared + WELDdata * WELDdata;
            }
            Average = Sum / SampleSize;
            if ((FlagBit % 3) == 2)   //High flag = Percent mode
            {
                //Calculate the upper soft limit
                //Convert a percentage to a decimal by half for the upper range
                SLHrange = _Interface->StatusData.SoftLimit[SLIUpperControlLimit][SLindexer] / 200;
                SLHrange = SLHrange * (MaxLimit - MinLimit);
                //Calculate the lower soft limit
                SLLrange = _Interface->StatusData.SoftLimit[SLILowerControlLimit][SLindexer] / 200;
                SLLrange = SLLrange * (MaxLimit - MinLimit);
            }
            else{
                //Sigma mode
                Intermediate = (SampleSize * SumSquared - Sum * Sum) / SampleSize;
                if ((_Interface->StatusData.SoftLimitsModeFlags & SoftLimitWeightFlag) == 0)
                    //Bias = N-1
                    Sigma = sqrt(Intermediate / (SampleSize - 1));
                else
                    //Bias = N
                    Sigma = sqrt(Intermediate / SampleSize);

                SLHrange = Sigma * _Interface->StatusData.SoftLimit[SLIUpperControlLimit][SLindexer];
                SLLrange = Sigma * _Interface->StatusData.SoftLimit[SLILowerControlLimit][SLindexer];
            }
            SoftLimitData[SLindexer].Average = Average;
            SoftLimitData[SLindexer].HighLimit = Average + SLHrange;
            SoftLimitData[SLindexer].LowLimit = Average - SLLrange;

            //Regardless of the results the limits must be in the hard limit windows
            if (SoftLimitData[SLindexer].HighLimit > MaxLimit)
                SoftLimitData[SLindexer].HighLimit = MaxLimit;
            if (SoftLimitData[SLindexer].LowLimit < MinLimit)
                SoftLimitData[SLindexer].LowLimit = MinLimit;
            if (ShowResults == true)
            {
                if ((SoftLimitData[SLindexer].LastData > SoftLimitData[SLindexer].HighLimit) ||
                    (SoftLimitData[SLindexer].LastData < SoftLimitData[SLindexer].LowLimit))
                {

                    if ((_Interface->StatusData.SoftLimitsModeFlags & SoftLimitAudibleFlag) != 0)
                        ptr_M102IA->Generate_Beep();
                }
            }      //ShowResults
        }          //FlagBit <> 0
    }             //SLindexer
}

//void Statistics::RotateOut(StatStats SumStats, int OldData)
//{

//}

//void Statistics::RotateIn(StatStats SumStats, string DataEvent, int NewData)
//{

//}

void Statistics::UpdateSpliceStatStats()
{

}

void Statistics::EnterM20DataEvent()
{

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

    for(int i = 0; i < M20_Data_Pnt_MI; i++)
        Splice_Stat.TimeData.Data[i] = NOT_VALID;

    ptr_M10runMode->InvalidWeldCounter = 0; //used in Auto Teach mode only
}

void Statistics::UpdateCounter()
{

}

void Statistics::CalcConfLimits()
{

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
void Statistics::HistoryEvent(QString WorkOrderName, QString PartName,
                WeldResultElement *_WeldResult, PresetElement *_Splice)
{
    InterfaceClass *_Interface = InterfaceClass::Instance();
    UtilityClass *_Utility = UtilityClass::Instance();
    M2010 *_M2010 = M2010::Instance();
    QString sDate, sTime, sEvent, sAlarms, sMode, sCut, sGraph, sStatus, sSampleRatio;
    QString sHeader;
    sHeader = HeaderString();
    if(_Interface->StatusData.NetworkingEnabled == false)
        return;
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
    case SampleWith1ms:
        sSampleRatio = "1ms";
        break;
    case SampleWith5ms:
        sSampleRatio = "5ms";
        break;
    case SampleWith10ms:
        sSampleRatio = "10ms";
        break;
    case SampleWith20ms:
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

    sEvent += WorkOrderName + "\t" + PartName + "\t" + _Splice->SpliceName;
    sEvent += "\t\t" + _Utility->FormatedDataToString(DINEnergy,
            _WeldResult->ActualResult.ActualEnergy);
    if(_M2010->Machine != Welder)
        sEvent += "\t" + _Utility->FormatedDataToString(DINWidth,
                _WeldResult->ActualResult.ActualWidth);
    sEvent += "\t" + _Utility->FormatedDataToString(DINTriggerPressure,
            _WeldResult->ActualResult.ActualTPressure);
    sEvent += "\t" + _Utility->FormatedDataToString(DINPressure,
            _WeldResult->ActualResult.ActualPressure);
    if(_Splice->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode != STEPDISABLE)
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
}

//string Statistics::HeaderString()
//{

//}
