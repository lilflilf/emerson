#include "Statistics.h"
#include "math.h"
#include "M2010.h"
#include "M10INI.h"
#include "M102IA.h"
#include "M10runMode.h"
#include "Interface/Interface.h"
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

//Create a tab deliminated file for loading into an Excel worksheet
//It stores all the Actual data regarding a Preset in the .tsv file during welding.
//Also Displays Amplitude2 along with Amplitude1 if Amplitude Step is enabled
void Statistics::HistoryEvent()
{

}

//string Statistics::HeaderString()
//{

//}
