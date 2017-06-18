#include "WeldResultElement.h"

WeldResultElement::WeldResultElement()
{
    RevCode = -1;
    WeldResultID = -1;
    OperatorName.clear();
    CreatedDate = 0;
    CurrentWorkOrder.WorkOrderID = -1;
    CurrentWorkOrder.WorkOrderName.clear();
    CurrentHarness.HarnessID = -1;
    CurrentHarness.HarnessName.clear();
    CurrentSequence.SequenceID = -1;
    CurrentSequence.SequenceName.clear();
    CurrentSplice.PartID = -1;
    CurrentSplice.PartName.clear();
    WeldCount = -1;
    PartCount = -1;
    OperateMode.clear();
    ActualResult.ActualAlarmflags = -1;
    ActualResult.ActualAmplitude = -1;
    ActualResult.ActualAmplitude2 = -1;
    ActualResult.ActualEnergy = -1;
    ActualResult.ActualPeakPower = -1;
    ActualResult.ActualPostheight = -1;
    ActualResult.ActualPreheight = -1;
    ActualResult.ActualPressure = -1;
    ActualResult.ActualTime = -1;
    ActualResult.ActualTPressure = -1;
    ActualResult.ActualWidth = -1;
    SampleRatio = SampleWith1ms;
    PowerGraph.clear();
    PostHeightGraph.clear();
    NoOfSamples = PowerGraph.size();
}

WeldResultElement::~WeldResultElement()
{
    PowerGraph.clear();
    PostHeightGraph.clear();
}

WeldResultElement WeldResultElement::operator=(const WeldResultElement &WeldResultObject)
{
    if(this == &WeldResultObject)
        return *this;
    this->RevCode = WeldResultObject.RevCode;
    this->WeldResultID = WeldResultObject.WeldResultID;
    this->OperatorName = WeldResultObject.OperatorName;
    this->CreatedDate = WeldResultObject.CreatedDate;
    this->CurrentWorkOrder.WorkOrderID = WeldResultObject.CurrentWorkOrder.WorkOrderID;
    this->CurrentWorkOrder.WorkOrderName
            = WeldResultObject.CurrentWorkOrder.WorkOrderName;
    this->CurrentHarness.HarnessID = WeldResultObject.CurrentHarness.HarnessID;
    this->CurrentHarness.HarnessName = WeldResultObject.CurrentHarness.HarnessName;
    this->CurrentSequence.SequenceID = WeldResultObject.CurrentSequence.SequenceID;
    this->CurrentSequence.SequenceName = WeldResultObject.CurrentSequence.SequenceName;
    this->CurrentSplice.PartID = WeldResultObject.CurrentSplice.PartID;
    this->CurrentSplice.PartName = WeldResultObject.CurrentSplice.PartName;
    this->WeldCount = WeldResultObject.WeldCount;
    this->PartCount = WeldResultObject.PartCount;
    this->OperateMode = WeldResultObject.OperateMode;
    this->ActualResult.ActualAlarmflags
            = WeldResultObject.ActualResult.ActualAlarmflags;
    this->ActualResult.ActualAmplitude = WeldResultObject.ActualResult.ActualAmplitude;
    this->ActualResult.ActualAmplitude2 = WeldResultObject.ActualResult.ActualAmplitude2;
    this->ActualResult.ActualEnergy = WeldResultObject.ActualResult.ActualEnergy;
    this->ActualResult.ActualPeakPower = WeldResultObject.ActualResult.ActualPeakPower;
    this->ActualResult.ActualPostheight = WeldResultObject.ActualResult.ActualPostheight;
    this->ActualResult.ActualPreheight = WeldResultObject.ActualResult.ActualPreheight;
    this->ActualResult.ActualPressure = WeldResultObject.ActualResult.ActualPressure;
    this->ActualResult.ActualTime = WeldResultObject.ActualResult.ActualTime;
    this->ActualResult.ActualTPressure = WeldResultObject.ActualResult.ActualTPressure;
    this->ActualResult.ActualWidth = WeldResultObject.ActualResult.ActualWidth;
    this->SampleRatio = WeldResultObject.SampleRatio;

    this->PowerGraph = WeldResultObject.PowerGraph;
    this->PostHeightGraph = WeldResultObject.PostHeightGraph;

    this->NoOfSamples = PowerGraph.size();
    return *this;
}
