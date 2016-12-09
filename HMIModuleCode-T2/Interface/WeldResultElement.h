#ifndef WELDRESULTELEMENT_H
#define WELDRESULTELEMENT_H
#include "Definition.h"

class WeldResultElement
{
public:
    int RevCode;
    int WeldResultID;
    QString TableName;
    QString OperatorName;
    unsigned int CreatedDate;
    struct WorkOrderIndex CurrentWorkOrder;
    struct PartIndex CurrentPart;
    struct SpliceIndex CurrentSplice;
    int WeldCount;//just for the test mode
    int PartCount;//just for the operate mode
    struct WELDRESULT ActualResult;
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
