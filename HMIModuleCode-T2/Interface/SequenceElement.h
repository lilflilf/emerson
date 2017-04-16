#ifndef SEQUENCEELEMENT_H
#define SEQUENCEELEMENT_H
#include "Definition.h"

class SequenceElement
{
public:
    int RevCode;
    int SequenceID;
    QString SequenceName;
    unsigned int CreatedDate;
    int OperatorID;
//    struct HARNESSTYPE HarnessTypeSetting;

    int NoOfSplice;
    //#define SEQ_MAX_SPLICES  250
    QMap<int, struct SEQUENCEATTRIBUTE> SpliceList;
public:
    SequenceElement operator=(const SequenceElement &SequenceObject);
public:
    SequenceElement();
    ~SequenceElement();
};

#endif // SEQUENCEELEMENT_H
