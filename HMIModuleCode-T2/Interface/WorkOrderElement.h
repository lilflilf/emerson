#ifndef WORKORDERELEMENT_H
#define WORKORDERELEMENT_H
#include "Definition.h"

class WorkOrderElement
{
public:
    enum WORKORDERMODE
    {
        SPLICE = 0,
        HARNESS,
        SEQUENCE,
    };
public:
    int RevCode;
    int WorkOrderID;
    QString WorkOrderName;
    unsigned int CreatedDate;
    int OperatorID;
    enum WORKORDERMODE WorkOrderMode;
    int NoOfPart;
    int Quantity;
    int CurrentPartCount;
    QMap<int, QString> MissPartList;
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
