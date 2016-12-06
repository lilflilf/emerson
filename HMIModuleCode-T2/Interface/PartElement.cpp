#include "PartElement.h"

PartElement::PartElement()
{
    RevCode = -1;
    PartID = -1;
    PartName.clear();
    CreatedDate = 0;
    OperatorID = -1;
    PartTypeSetting.BoardLayout.Columns = -1;
    PartTypeSetting.BoardLayout.Rows = -1;
    PartTypeSetting.BoardLayout.MaxSplicesPerZone = -1;
    PartTypeSetting.ProcessMode = BASIC;
    PartTypeSetting.WorkStations.MaxSplicesPerWorkstation = -1;
    PartTypeSetting.WorkStations.TotalWorkstation = -1;
    SpliceIndex.clear();
    NoOfSplice = SpliceIndex.size();
}

PartElement::~PartElement()
{
    SpliceIndex.clear();
}

PartElement PartElement::operator=(const PartElement &PartObject)
{
    if(this == &PartObject)
        return *this;
    this->RevCode = PartObject.RevCode;
    this->PartID = PartObject.PartID;
    this->PartName = PartObject.PartName;
    this->CreatedDate = PartObject.CreatedDate;
    this->OperatorID = PartObject.OperatorID;
    this->PartTypeSetting.BoardLayout.Columns =
            PartObject.PartTypeSetting.BoardLayout.Columns;
    this->PartTypeSetting.BoardLayout.Rows =
            PartObject.PartTypeSetting.BoardLayout.Rows;
    this->PartTypeSetting.BoardLayout.MaxSplicesPerZone
            = PartObject.PartTypeSetting.BoardLayout.MaxSplicesPerZone;
    this->PartTypeSetting.ProcessMode = PartObject.PartTypeSetting.ProcessMode;
    this->PartTypeSetting.WorkStations.MaxSplicesPerWorkstation
            = PartObject.PartTypeSetting.WorkStations.MaxSplicesPerWorkstation;
    this->PartTypeSetting.WorkStations.TotalWorkstation
            = PartObject.PartTypeSetting.WorkStations.TotalWorkstation;
    QMap<int, struct PARTATTRIBUTE>::const_iterator i
            = PartObject.SpliceIndex.constBegin();
    while(i != PartObject.SpliceIndex.constEnd())
    {
        this->SpliceIndex.insert(i.key(),i.value());
        ++i;
    }
    this->NoOfSplice = this->SpliceIndex.size();
    return *this;
}
