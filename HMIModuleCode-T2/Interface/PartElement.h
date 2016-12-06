#ifndef PARTELEMENT_H
#define PARTELEMENT_H
#include "Definition.h"
class PartElement
{
public:
    int RevCode;
    int PartID;
    QString PartName;
    unsigned int CreatedDate;
    int OperatorID;
    struct PARTTYPE PartTypeSetting;

    int NoOfSplice;
    //#define SEQ_MAX_SPLICES  250
    QMap<int, struct PARTATTRIBUTE> SpliceIndex;
public:
    PartElement operator=(const PartElement &PartObject);
public:
    PartElement();
    ~PartElement();
};

#endif // PARTELEMENT_H
