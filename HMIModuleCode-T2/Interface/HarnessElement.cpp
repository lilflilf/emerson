#include "HarnessElement.h"

HarnessElement::HarnessElement()
{
    RevCode = -1;
    HarnessID = -1;
    HarnessName.clear();
    CreatedDate = 0;
    OperatorID = -1;
    HarnessTypeSetting.BoardLayout.Columns = 1;
    HarnessTypeSetting.BoardLayout.Rows = 1;
    HarnessTypeSetting.BoardLayout.MaxSplicesPerZone = 0;
    HarnessTypeSetting.ProcessMode = BASIC;
    HarnessTypeSetting.WorkStations.MaxSplicesPerWorkstation = 0;
    HarnessTypeSetting.WorkStations.TotalWorkstation = 0;
    SpliceList.clear();
    NoOfSplice = SpliceList.size();
}

HarnessElement::~HarnessElement()
{
    SpliceList.clear();
}

HarnessElement HarnessElement::operator=(const HarnessElement &HarnessObject)
{
    if(this == &HarnessObject)
        return *this;
    this->RevCode = HarnessObject.RevCode;
    this->HarnessID = HarnessObject.HarnessID;
    this->HarnessName = HarnessObject.HarnessName;
    this->CreatedDate = HarnessObject.CreatedDate;
    this->OperatorID = HarnessObject.OperatorID;
    this->HarnessTypeSetting.BoardLayout.Columns =
            HarnessObject.HarnessTypeSetting.BoardLayout.Columns;
    this->HarnessTypeSetting.BoardLayout.Rows =
            HarnessObject.HarnessTypeSetting.BoardLayout.Rows;
    this->HarnessTypeSetting.BoardLayout.MaxSplicesPerZone
            = HarnessObject.HarnessTypeSetting.BoardLayout.MaxSplicesPerZone;
    this->HarnessTypeSetting.ProcessMode = HarnessObject.HarnessTypeSetting.ProcessMode;
    this->HarnessTypeSetting.WorkStations.MaxSplicesPerWorkstation
            = HarnessObject.HarnessTypeSetting.WorkStations.MaxSplicesPerWorkstation;
    this->HarnessTypeSetting.WorkStations.TotalWorkstation
            = HarnessObject.HarnessTypeSetting.WorkStations.TotalWorkstation;
    QMap<int, struct HARNESSATTRIBUTE>::const_iterator i
            = HarnessObject.SpliceList.constBegin();
    struct HARNESSATTRIBUTE tmpSplice;
    while(i != HarnessObject.SpliceList.constEnd())
    {
        tmpSplice.SpliceID = i.value().SpliceID;
        tmpSplice.SpliceName = i.value().SpliceName;
        tmpSplice.CurrentBoardLayoutZone =
                i.value().CurrentBoardLayoutZone;
        tmpSplice.CurrentWorkstation =
                i.value().CurrentWorkstation;
        this->SpliceList.insert(i.key(),tmpSplice);
        ++i;
    }
    this->NoOfSplice = this->SpliceList.size();
    return *this;
}
