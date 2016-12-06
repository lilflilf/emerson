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
    int CrossSection;
    struct WELDRESULT ActualResult;
    enum SAMPLERATIO SampleRatio;
    int NoOfSamples;
    QMap<int, QString> PowerGraph;
    QMap<int, QString> PostHeightGraph;
public:
    WeldResultElement operator=(const WeldResultElement &WeldResultObject);
public:
    WeldResultElement();
    ~WeldResultElement();
};

#endif // WELDRESULTELEMENT_H
