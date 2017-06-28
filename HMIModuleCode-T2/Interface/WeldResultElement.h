#ifndef WELDRESULTELEMENT_H
#define WELDRESULTELEMENT_H
#include "Definition.h"

class WeldResultElement
{
public:
    enum SAMPLERATIO
    {
        SampleWith1ms,
        SampleWith5ms,
        SampleWith10ms,
        SampleWith20ms,
    };
    int RevCode;
    int WeldResultID;
    QString OperatorName;
    unsigned int CreatedDate;
    struct WorkOrderIndex CurrentWorkOrder;
    struct HarnessIndex CurrentHarness;
    struct SequenceIndex CurrentSequence;
    struct PartIndex CurrentSplice;
    int CrossSection;         //Area of part in mm*mm/100
    int WeldCount;//just for the test mode
    int PartCount;//just for the operate mode
    QString OperateMode;
    WELDRESULT ActualResult;
    WELDSETTING WeldSettings;

    enum SAMPLERATIO SampleRatio;
    int NoOfSamples;
    QList<int> PowerGraph;
    QList<int> PostHeightGraph;
public:
    WeldResultElement operator=(const WeldResultElement &WeldResultObject);
public:
    WeldResultElement();
    ~WeldResultElement();
};

#endif // WELDRESULTELEMENT_H
