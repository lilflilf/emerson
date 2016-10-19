#ifndef STATISTICS_H
#define STATISTICS_H
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include "m10definitions.h"
using namespace std;

const int M20_Stat_Points = 128;  //The number of data points in the file
const int M20_Data_Points = 128;  //The number of data points on the screen
const int M20_Data_Pnt_MI = M20_Data_Points;    //Max Index for data

const long QualGoodColor = 0xC000;
const long QualSLbadColor = 0xFFFF;
const long QualBadColor = 0x00FF;

enum SoftLimitStatusType{
    SLSTSoftLimitOFF,
    SLSTSoftLimitON,
};

struct SoftLimitElement{
    SoftLimitStatusType SoftLimitStatus;
    double LastData;
    double Average;
    double Sum;
    double SumOfSquares;
    double HighLimit;
    double LowLimit;
};

struct StatStats{
    int min;
    int max;
    long Sum;
    double Sum_sqr;
};

struct WeldEventData{
    int Data[M20_Data_Pnt_MI];
};


struct Splice_Statistics{
    string FileName;
    int prts_count;
    int data_ptr;
    StatStats Time;
    StatStats Power;
    StatStats Pre_hght;
    StatStats Height;
    WeldEventData TimeData;
    WeldEventData PowerData;
    WeldEventData PreHghtData;
    WeldEventData HeightData;
};

//UpdateSpliceStatStats then use this data to show, print or otherwise get data
struct SpliceStatStats{
    int PartsCount;
    int StartIndex;
    int EndIndex;
    int MaxIndex;
    int DataBaseCount;
};

const int NOT_VALID = -1;
const int MIN_STATS_QUANT = 3;

const float PI = 3.14159;

const int M20ErrorLogEntries = 128;




struct ERROR_LOG_ENTRY{
    string Date;
    string Time;
    string PartName;
    int Type;
    int Value;
};

struct ERROR_LOG_BOOK{
    int entries;
    int next_ptr;
    ERROR_LOG_ENTRY entry[M20ErrorLogEntries];
};



const string Error_Log_File = "Errors.log";

const int MaintLogEntries = 100;
const int HEIGHT_HARD_LIMIT = 20;
const int MAX_POWER = 3600;

struct Maint_Log_Entry{
    string EntryDate;
    string EntryData;
};


struct Maint_Log_File{
    int Entry_Tot;       //# of entries in the Maintenance log file
    Maint_Log_Entry MaintEntry[MaintLogEntries];
};

//--File name to store the maintenance entries
const string Maint_Log = "Maintlog.mnt";

class Statistics
{
public:
    SoftLimitElement SoftLimitData[SLIEND];
    //Public SoftLimitData(0 To 3) As SoftLimitElement

    SpliceStatStats SplicePointers;

    Splice_Statistics Splice_Stat;

    double time_lower_limit;
    double time_upper_limit;
    double power_lower_limit;
    double power_upper_limit;
    double pre_hght_lower_limit;
    double pre_hght_upper_limit;
    double height_lower_limit;
    double height_upper_limit;
    double f_of_x[101];

    ERROR_LOG_BOOK Error_Log;

    //--Varaible to hold MAINTENTRY
    Maint_Log_File Maint_Data;
    double Time_Average, Power_Average, PreHeight_Avreage, Height_Average;
private:
    void RotateIn(StatStats SumStats, string DataEvent, int NewData);
public:
    void UpdateSoftLimitData(bool ShowResults = true);
    void RotateOut(StatStats SumStats, int OldData);
    void UpdateSpliceStatStats();
    void EnterM20DataEvent();
    void ZeroM20DataEvents();
    void UpdateCounter();
    void CalcConfLimits();
    void start_data_structures();
    void Open_Maint_Log();
    void HistoryEvent();
    string HeaderString();

public:
    static Statistics* Instance();
protected:
    Statistics();
private:
    static Statistics* _instance;
public:
    ~Statistics(){} //do-nothing destructor
};

#endif // STATISTICS_H
