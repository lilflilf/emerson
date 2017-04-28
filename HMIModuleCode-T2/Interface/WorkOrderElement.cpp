#include "WorkOrderElement.h"

WorkOrderElement::WorkOrderElement()
{
    RevCode = -1;
    WorkOrderID = -1;
    WorkOrderName.clear();
    CreatedDate = 0;
    OperatorID = -1;
    PartList.clear();
    CurrentSpliceIndex = -1;
    BatchSize = -1;
    CurrentPartCount = -1;
    MissPartList.clear();
    CurrentPartIndex.PartID = -1;
    CurrentPartIndex.PartName.clear();
    WorkOrderDone = true;
    WorkOrderMode = WorkOrderElement::SPLICE;
}

WorkOrderElement::~WorkOrderElement()
{
    PartList.clear();
    MissPartList.clear();
}

WorkOrderElement WorkOrderElement::operator=(const WorkOrderElement &WorkOrderObject)
{
    if(this == &WorkOrderObject)
        return *this;
    this->RevCode = WorkOrderObject.RevCode;
    this->WorkOrderID = WorkOrderObject.WorkOrderID;
    this->WorkOrderName = WorkOrderObject.WorkOrderName;
    this->CreatedDate = WorkOrderObject.CreatedDate;
    this->OperatorID = WorkOrderObject.OperatorID;
    QMap<int, QString>::const_iterator i = WorkOrderObject.PartList.constBegin();
    while(i != WorkOrderObject.PartList.constEnd())
    {
        this->PartList.insert(i.key(),i.value());
        ++i;
    }
    this->CurrentSpliceIndex = WorkOrderObject.CurrentSpliceIndex;
    this->BatchSize = WorkOrderObject.BatchSize;
    this->CurrentPartCount = WorkOrderObject.CurrentPartCount;
    i = WorkOrderObject.MissPartList.constBegin();
    while(i != WorkOrderObject.MissPartList.constEnd())
    {
        this->MissPartList.insert(i.key(),i.value());
        ++i;
    }
    this->CurrentPartIndex.PartID = WorkOrderObject.CurrentPartIndex.PartID;
    this->CurrentPartIndex.PartName = WorkOrderObject.CurrentPartIndex.PartName;
    this->WorkOrderDone = WorkOrderObject.WorkOrderDone;
    this->WorkOrderMode = WorkOrderObject.WorkOrderMode;
    return *this;
}
