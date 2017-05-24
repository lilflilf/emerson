#ifndef CSVWELDRESULTDATA_H
#define CSVWELDRESULTDATA_H
#include "DataClass.h"

class CSVWeldResultData : public DataClass
{
public:
    enum WeldResultItem
    {
        WeldResultID = 0,
        OperatorName = 1,
        CreatedDate = 2,
        WorkOrderID = 3,
        WorkOrderName = 4,
        HarnessID = 5,
        HarnessName = 6,
        SequenceID = 7,
        SequenceName = 8,
        SpliceID = 9,
        SpliceName = 10,
        SpliceHash = 11,
        WeldCount = 12,
        PartCount = 13,
        ActualEnergy = 14,
        ActualTPressure = 15,
        ActualPressure = 16,
        ActualAmplitude = 17,
        ActualAmplitude2 = 18,
        ActualWidth = 19,
        ActualTime = 20,
        ActualPeakPower = 21,
        ActualPreheight = 22,
        ActualPostheight = 23,
        ActualAlarmFlags = 24,
        SampleRatio = 25,
        NoOfSamples = 26,
        CurrentGraphDirectory = 27
    };

public:
    virtual bool ExportData(int ID, QString fileUrl);
    virtual bool ExportData(QList<int> IDList, QString fileUrl);
    virtual QString GetExportString(int ID);
    virtual int ImportData(QString StrValue);
public:
    static CSVWeldResultData* Instance();
protected:
    CSVWeldResultData();
private:
    static CSVWeldResultData* _instance;
public:
    ~CSVWeldResultData();
};

#endif // CSVWELDRESULTDATA_H
