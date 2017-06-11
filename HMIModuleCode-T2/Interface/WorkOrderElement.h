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
        UNDEFINE, //meanings the current workorder has not any new splice/ sequence/ Harness loaded
    };
public:
    int RevCode;
    int WorkOrderID;
    QString WorkOrderName;
    QString CreatedDate;
    int OperatorID;
    enum WORKORDERMODE WorkOrderMode;
    int CurrentSpliceIndex;
    bool IsConstrainedFlag;//only for splice or harness
    int BatchSize; //only for splice or Harness
    TEACHMODESETTING::TEACH_MODE_TYPE Teach_Mode;
//    int CurrentPartCount;//only for current cycle count
    struct PartIndex CurrentPartIndex; //only for current splice Information
    QMap<int, QString> MissPartList;//harness & Sequence
//    QMap<int, QString> PartList;

public:
    WorkOrderElement operator=(const WorkOrderElement &WorkOrderObject);
    void WriteWorkOrderToQSetting();
    bool ReadWorkOrderFromQSetting();
public:
    WorkOrderElement();
    ~WorkOrderElement();
};

#endif // WORKORDERELEMENT_H
