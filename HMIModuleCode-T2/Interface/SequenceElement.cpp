#include "SequenceElement.h"

SequenceElement::SequenceElement()
{
    RevCode = -1;
    SequenceID = -1;
    SequenceName.clear();
    CreatedDate = 0;
    OperatorID = -1;
    NoOfSplice = -1;
    SpliceList.clear();
}

SequenceElement::~SequenceElement()
{
    SpliceList.clear();
}

SequenceElement SequenceElement::operator=(const SequenceElement &SequenceObject)
{
    if(this == &SequenceObject)
        return *this;
    this->RevCode = SequenceObject.RevCode;
    this->SequenceID = SequenceObject.SequenceID;
    this->SequenceName = SequenceObject.SequenceName;
    this->CreatedDate = SequenceObject.CreatedDate;
    this->OperatorID = SequenceObject.OperatorID;
    QMap<int, struct SEQUENCEATTRIBUTE>::const_iterator i
            = SequenceObject.SpliceList.constBegin();
    struct SEQUENCEATTRIBUTE tmpSplice;
    while(i != SequenceObject.SpliceList.constEnd())
    {
        tmpSplice.SpliceID = i.value().SpliceID;
        tmpSplice.SpliceName = i.value().SpliceName;
        tmpSplice.Quantity = i.value().Quantity;
        this->SpliceList.insert(i.key(),tmpSplice);
        ++i;
    }
    this->NoOfSplice = this->SpliceList.size();
    return *this;
}
