#include "AlarmElement.h"

AlarmElement::AlarmElement()
{
    RevCode = -1;
    AlarmID = -1;
    AlarmMsg.clear();
    CreatedDate = 0;
    AlarmType = NONEALARM;
    SpliceID = -1;
    OperatorID = -1;
}

AlarmElement AlarmElement::operator=(const AlarmElement &AlarmObject)
{
    if(this == &AlarmObject)
        return *this;
    this->RevCode = AlarmObject.RevCode;
    this->AlarmID = AlarmObject.AlarmID;
    this->AlarmMsg = AlarmObject.AlarmMsg;
    this->CreatedDate = AlarmObject.CreatedDate;
    this->AlarmType = AlarmObject.AlarmType;
    this->SpliceID = AlarmObject.SpliceID;
    this->OperatorID = AlarmObject.OperatorID;
    return *this;
}
