#ifndef PARTELEMENT_H
#define PARTELEMENT_H
#include "Definition.h"
class HarnessElement
{
public:
    int RevCode;
    int HarnessID;
    QString HarnessName;
    unsigned int CreatedDate;
    int OperatorID;
    struct HARNESSTYPE HarnessTypeSetting;

    int NoOfSplice;
    //#define SEQ_MAX_SPLICES  250
    QMap<int, struct HARNESSATTRIBUTE> SpliceList;
public:
    HarnessElement operator=(const HarnessElement &HarnessObject);
public:
    HarnessElement();
    ~HarnessElement();
};

#endif // PARTELEMENT_H
