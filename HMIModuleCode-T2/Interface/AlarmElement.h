#ifndef ALARMELEMENT_H
#define ALARMELEMENT_H
#include "Definition.h"

class AlarmElement
{
public:
    int RevCode;
    int AlarmID;
    QString AlarmMsg;
    unsigned int CreatedDate;
//    enum ALARMTYPE AlarmType;
    QString AlarmType;
    int SpliceID;
    int OperatorID;
public:
    AlarmElement operator=(const AlarmElement &AlarmObject);
public:
    AlarmElement();
};

#endif // ALARMELEMENT_H
