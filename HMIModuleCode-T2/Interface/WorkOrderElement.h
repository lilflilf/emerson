#ifndef WORKORDERELEMENT_H
#define WORKORDERELEMENT_H
#include "Definition.h"

class WorkOrderElement
{
public:
    enum WORKORDERMODE
    {
        SPLICE = 0,
        SEQUENCE,
        HARNESS,

    };
public:
    int RevCode;
    int WorkOrderID;
    QString WorkOrderName;
    unsigned int CreatedDate;
    int OperatorID;
    enum WORKORDERMODE WorkOrderMode;
    int CurrentSpliceIndex;
    int BatchSize; //only for splice or Harness
    TEACHMODESETTING::TEACH_MODE_TYPE Teach_Mode;
    int CurrentPartCount;//only for current cycle count
    QMap<int, QString> MissPartList;//harness
    QMap<int, QString> PartList;
    struct PartIndex CurrentPartIndex;
    bool WorkOrderDone;
public:
    WorkOrderElement operator=(const WorkOrderElement &WorkOrderObject);
public:
    WorkOrderElement();
    ~WorkOrderElement();
};

#endif // WORKORDERELEMENT_H
