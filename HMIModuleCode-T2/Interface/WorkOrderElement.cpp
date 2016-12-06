#include "WorkOrderElement.h"

WorkOrderElement::WorkOrderElement()
{
    RevCode = -1;
    WorkOrderID = -1;
    WorkOrderName.clear();
    CreatedDate = 0;
    OperatorID = -1;
    PartIndex.clear();
    NoOfPart = PartIndex.size();
    Quantity = -1;
    CurrentPartCount = -1;
    MissSpliceList.clear();
    CurrentSplice.SpliceID = -1;
    CurrentSplice.SpliceName.clear();
    WorkOrderDone = true;
}

WorkOrderElement::~WorkOrderElement()
{
    PartIndex.clear();
    MissSpliceList.clear();
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
    QMap<int, QString>::const_iterator i = WorkOrderObject.PartIndex.constBegin();
    while(i != WorkOrderObject.PartIndex.constEnd())
    {
        this->PartIndex.insert(i.key(),i.value());
        ++i;
    }
    this->NoOfPart = this->PartIndex.size();
    this->Quantity = WorkOrderObject.Quantity;
    this->CurrentPartCount = WorkOrderObject.CurrentPartCount;
    i = WorkOrderObject.MissSpliceList.constBegin();
    while(i != WorkOrderObject.MissSpliceList.constEnd())
    {
        this->MissSpliceList.insert(i.key(),i.value());
        ++i;
    }
    this->CurrentSplice.SpliceID = WorkOrderObject.CurrentSplice.SpliceID;
    this->CurrentSplice.SpliceName = WorkOrderObject.CurrentSplice.SpliceName;
    this->WorkOrderDone = WorkOrderObject.WorkOrderDone;
    return *this;
}
