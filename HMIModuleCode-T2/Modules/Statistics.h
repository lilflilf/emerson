#ifndef STATISTICS_H
#define STATISTICS_H
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include "m10definitions.h"
#include "Interface/SysConfiguration.h"
#include "Interface/WeldResultElement.h"
#include "Interface/PresetElement.h"
#include <QSettings>
#include <QDir>
#include <QString>
#include "UtilityClass.h"
using namespace std;

#define M20_Stat_Points  128  //The number of data points in the file
#define M20_Data_Points  128  //The number of data points on the screen
#define M20_Data_Pnt_MI  M20_Data_Points    //Max Index for data

#define iOverLoadFault  0x01
#define iTimeFault      0x20
#define iPowerFault     0x40
#define iHeightFault    0x80
#define iWidthFault     0x800
#define iAlarms         (iOverLoadFault | iTimeFault | iPowerFault | iHeightFault | iWidthFault)

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
    int Sum;
    double Sum_sqr;
};

struct WeldEventData{
    QList<int> Data;
};


class Splice_Statistics{
public:
    QString FileName;
    int prts_count;
    int data_ptr;
    unsigned int HashCode;
    StatStats Time;
    StatStats Power;
    StatStats Pre_hght;
    StatStats Height;
    WeldEventData TimeData;
    WeldEventData PowerData;
    WeldEventData PreHghtData;
    WeldEventData HeightData;
private:
    void InitializeSpliceStat()
    {
        prts_count = 0;
        data_ptr = 0;
        Time.max = 0;
        Time.min = 0;
        Time.Sum = 0;
        Time.Sum_sqr = 0;
        Power.max = 0;
        Power.min = 0;
        Power.Sum = 0;
        Power.Sum_sqr = 0;
        Pre_hght.max = 0;
        Pre_hght.min = 0;
        Pre_hght.Sum = 0;
        Pre_hght.Sum_sqr = 0;
        Height.max = 0;
        Height.min = 0;
        Height.Sum = 0;
        Height.Sum_sqr = 0;
        TimeData.Data.clear();
        PowerData.Data.clear();
        PreHghtData.Data.clear();
        HeightData.Data.clear();
    }

public:
    Splice_Statistics()
    {
        FileName.clear();
        HashCode = 0;
        InitializeSpliceStat();
    }

    bool ReadQSettingToSpliceStat(QString sPathName, PresetElement *_Splice)
    {
        bool bResult = false;
        UtilityClass *_Utility = UtilityClass::Instance();
        QDir dir;
        if(_Splice == NULL)
            return false;
        if (dir.exists(sPathName) == false)
        {
            FileName = _Splice->SpliceName;
            HashCode = _Splice->HashCode;
            InitializeSpliceStat();
            bResult = false;
        }else
        {
            QSettings settings(sPathName, QSettings::IniFormat);
            settings.beginGroup("SpliceStat");
            FileName =
                    settings.value("FileName").value<QString>();
            HashCode =
                    settings.value("HashCode").value<unsigned int>();
            prts_count =
                    settings.value("prts_count").value<int>();
            data_ptr =
                    settings.value("data_ptr").value<int>();
            Time.max =
                    settings.value("Time_Max").value<int>();
            Time.min =
                    settings.value("Time_Min").value<int>();
            Time.Sum =
                    settings.value("Time_Sum").value<long>();
            Time.Sum_sqr =
                    settings.value("Time_Sum_sqr").value<double>();
            Power.max =
                    settings.value("Power_Max").value<int>();
            Power.min =
                    settings.value("Power_Min").value<int>();
            Power.Sum =
                    settings.value("Power_Sum").value<long>();
            Power.Sum_sqr =
                    settings.value("Power_Sum_sqr").value<double>();
            Pre_hght.max =
                    settings.value("Pre_hght_Max").value<int>();
            Pre_hght.min =
                    settings.value("Pre_hght_Min").value<int>();
            Pre_hght.Sum =
                    settings.value("Pre_hght_Sum").value<long>();
            Pre_hght.Sum_sqr =
                    settings.value("Pre_hght_Sum_sqr").value<double>();
            Height.max =
                    settings.value("Height_Max").value<int>();
            Height.min =
                    settings.value("Height_Min").value<int>();
            Height.Sum =
                    settings.value("Height_Sum").value<long>();
            Height.Sum_sqr =
                    settings.value("Height_Sum_sqr").value<double>();
            QString JsonStr = settings.value("TimeData").value<QString>();
            _Utility->StringJsonToList(JsonStr, &(TimeData.Data));
            JsonStr = settings.value("PowerData").value<QString>();
            _Utility->StringJsonToList(JsonStr, &(PowerData.Data));
            JsonStr = settings.value("PreHghtData").value<QString>();
            _Utility->StringJsonToList(JsonStr, &(PreHghtData.Data));
            JsonStr = settings.value("HeightData").value<QString>();
            _Utility->StringJsonToList(JsonStr, &(HeightData.Data));
            settings.endGroup();
            if((FileName == _Splice->SpliceName) &&
                    (HashCode == _Splice->HashCode))
                bResult = true;
            else{
                bResult = false;
                FileName = _Splice->SpliceName;
                HashCode = _Splice->HashCode;
                InitializeSpliceStat();
            }
        }
        return bResult;
    }

    bool WriteSpliceStatToQSetting(QString sPathName)
    {
        bool bResult = true;
        UtilityClass *_Utility = UtilityClass::Instance();
        QDir dir;
        sPathName = sPathName + FileName + ".ini";
        QSettings settings(sPathName, QSettings::IniFormat);
        settings.beginGroup("SpliceStat");
        settings.setValue("FileName",FileName);
        settings.setValue("HashCode", HashCode);
        settings.setValue("prts_count", prts_count);
        settings.setValue("data_ptr", data_ptr);
        settings.setValue("Time_Max", Time.max);
        settings.setValue("Time_Min", Time.min);
        settings.setValue("Time_Sum", Time.Sum);
        settings.setValue("Time_Sum_sqr", Time.Sum_sqr);
        settings.setValue("Power_Max", Power.max);
        settings.setValue("Power_Min", Power.min);
        settings.setValue("Power_Sum", Power.Sum);
        settings.setValue("Power_Sum_sqr", Power.Sum_sqr);
        settings.setValue("Pre_hght_Max", Pre_hght.max);
        settings.setValue("Pre_hght_Min", Pre_hght.min);
        settings.setValue("Pre_hght_Sum", Pre_hght.Sum);
        settings.setValue("Pre_hght_Sum_sqr", Pre_hght.Sum_sqr);
        settings.setValue("Height_Max", Height.max);
        settings.setValue("Height_Min", Height.min);
        settings.setValue("Height_Sum", Height.Sum);
        settings.setValue("Height_Sum_sqr", Height.Sum_sqr);
        QString JsonStr;
        _Utility->ListJsonToString(&TimeData.Data, JsonStr);
        settings.setValue("TimeData", JsonStr);
        _Utility->ListJsonToString(&PowerData.Data, JsonStr);
        settings.setValue("PowerData", JsonStr);
        _Utility->ListJsonToString(&PreHghtData.Data, JsonStr);
        settings.setValue("PreHghtData", JsonStr);
        _Utility->ListJsonToString(&HeightData.Data, JsonStr);
        settings.setValue("HeightData", JsonStr);
        settings.endGroup();
        return bResult;
    }

};

//UpdateSpliceStatStats then use this data to show, print or otherwise get data
struct SpliceStatStats{
    int PartsCount;
    int StartIndex;
    int EndIndex;
    int MaxIndex;
    int DataBaseCount;
};

#define NOT_VALID           -1
#define MIN_STATS_QUANT     3

#define PI                  3.14159

#define M20ErrorLogEntries  128




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
    SoftLimitElement SoftLimitData[SLI_Size];
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
    QString HeaderString();
    QString GraphData(enum ScreenShowDataType DataType, QList<int> *_GraphData);
    void RotateIn(StatStats &SumStats, QList<int>& DataEvent, int NewData);
    void RotateOut(StatStats &SumStats, int OldData);
public:
    void UpdateSoftLimitData(bool ShowResults = true);

    void UpdateSpliceStatStats();
    void EnterM20DataEvent();
    void ZeroM20DataEvents();
    void UpdateCounter();
    void CalcConfLimits(PresetElement*);
    void GetLimitsAfterWeld(PresetElement*);
    void start_data_structures();
    void Open_Maint_Log();
    void HistoryEvent(QString WorkOrderName, QString PartName,
                      WeldResultElement *_WeldResult, PresetElement *_Splice);


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
