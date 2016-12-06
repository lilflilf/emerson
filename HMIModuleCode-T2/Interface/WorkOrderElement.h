#ifndef WORKORDERELEMENT_H
#define WORKORDERELEMENT_H
#include "Definition.h"

class WorkOrderElement
{
public:
    int RevCode;
    int WorkOrderID;
    QString WorkOrderName;
    unsigned int CreatedDate;
    int OperatorID;
    int NoOfPart;
    QMap<int, QString> PartIndex;

    int Quantity;
    int CurrentPartCount;
    QMap<int, QString> MissSpliceList;
    struct SpliceIndex CurrentSplice;
    bool WorkOrderDone;
public:
    WorkOrderElement operator=(const WorkOrderElement &WorkOrderObject);
public:
    WorkOrderElement();
    ~WorkOrderElement();
};

#endif // WORKORDERELEMENT_H
