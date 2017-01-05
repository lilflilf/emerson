#include "Interface/MakeWeld/MakeWeldProcess.h"
#include "Modules/M102IA.h"
#include "Modules/M2010.h"
#include "Modules/M10INI.h"
#include "Modules/ModRunSetup.h"
#include "Interface/Interface.h"
#include "DataBase/DBWeldResultTable.h"
#include "Modules/M10runMode.h"
#include "Modules/UtilityClass.h"
#include "Modules/StatisticalFunction.h"
#include "Modules/Statistics.h"
#include <QDateTime>
#include <QDebug>
MakeWeldProcess* MakeWeldProcess::_instance = NULL;
ThreadClass* MakeWeldProcess::m_Thread = NULL;
MakeWeldProcess* MakeWeldProcess::Instance()
{
    if(_instance == NULL){
        _instance = new MakeWeldProcess();
    }
    return _instance;
}

MakeWeldProcess::MakeWeldProcess(QObject *parent) : QObject(parent)
{
    M102IA* _M102IA = M102IA::Instance();
    WeldCycleStatus = true;
    PowerGraphReady = false;
    HeightGraphReady = false;
    connect(_M102IA, SIGNAL(AlarmStatusSignal(bool&)),
            this,SLOT(AnyAlarmEventSlot(bool&)));
}

void MakeWeldProcess::UpdateIAFields()
{
    M102IA *_M102IA = M102IA::Instance();
    _M102IA->IAsetup.Energy = CurrentSplice.WeldSettings.BasicSetting.Energy;
    _M102IA->IAsetup.Width = CurrentSplice.WeldSettings.BasicSetting.Width;
    _M102IA->IAsetup.WeldPressure = CurrentSplice.WeldSettings.BasicSetting.Pressure;
    _M102IA->IAsetup.TriggerPressure = CurrentSplice.WeldSettings.BasicSetting.TrigPres;
    _M102IA->IAsetup.Amplitude = CurrentSplice.WeldSettings.BasicSetting.Amplitude;
    _M102IA->IAsetup.Amplitude2 = CurrentSplice.WeldSettings.AdvanceSetting.StepWeld.Amplitude2;
    _M102IA->IAsetup.SqueezeTime = CurrentSplice.WeldSettings.AdvanceSetting.SqzTime;
//    _M102IA->IAsetup.PartCounter = CurrentSplice.
    _M102IA->IAsetup.HoldTime = CurrentSplice.WeldSettings.AdvanceSetting.HoldTime;
    _M102IA->IAsetup.ABDelay = CurrentSplice.WeldSettings.AdvanceSetting.ABDelay;
    _M102IA->IAsetup.ABDuration = CurrentSplice.WeldSettings.AdvanceSetting.ABDur;
    _M102IA->IAsetup.PartName = CurrentSplice.SpliceName;

    //Bits 0 and 1 used
    //00B = Energy
    //01B = Time
    //10B = Height
    //11B = Egy/Hgt

    _M102IA->IAsetup.ModeFlags = CurrentSplice.WeldSettings.AdvanceSetting.WeldMode;
    _M102IA->IAsetup.Time.max = CurrentSplice.WeldSettings.QualitySetting.Time.Plus;
    qDebug()<<"Time.Max: "<< _M102IA->IAsetup.Time.max;
    _M102IA->IAsetup.Time.min = CurrentSplice.WeldSettings.QualitySetting.Time.Minus;
    qDebug()<<"Time.Min: "<< _M102IA->IAsetup.Time.min;
    _M102IA->IAsetup.Power.max = CurrentSplice.WeldSettings.QualitySetting.Power.Plus;
    _M102IA->IAsetup.Power.min = CurrentSplice.WeldSettings.QualitySetting.Power.Minus;
    _M102IA->IAsetup.Preheight.max = CurrentSplice.WeldSettings.QualitySetting.Preheight.Plus;
    _M102IA->IAsetup.Preheight.min = CurrentSplice.WeldSettings.QualitySetting.Preheight.Minus;
    _M102IA->IAsetup.Height.max = CurrentSplice.WeldSettings.QualitySetting.Height.Plus;
    _M102IA->IAsetup.Height.min = CurrentSplice.WeldSettings.QualitySetting.Height.Minus;

    _M102IA->IAsetup.EnergyToStep = CurrentSplice.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep;
    _M102IA->IAsetup.PowerToStep = CurrentSplice.WeldSettings.AdvanceSetting.StepWeld.PowerToStep;
    _M102IA->IAsetup.TimeToStep = CurrentSplice.WeldSettings.AdvanceSetting.StepWeld.TimeToStep;
    _M102IA->RawPowerDataGraph.GraphDataList.clear();
    _M102IA->RawHeightDataGraph.GraphDataList.clear();
}

void MakeWeldProcess::UpdateWeldResult()
{
    M102IA *_M102IA = M102IA::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    CurrentWeldResult.ActualResult.ActualEnergy = _M102IA->IAactual.Energy;
    CurrentWeldResult.ActualResult.ActualWidth = _M102IA->IAactual.Width;
    CurrentWeldResult.ActualResult.ActualTime = _M102IA->IAactual.Time;
    CurrentWeldResult.ActualResult.ActualPeakPower = _M102IA->IAactual.Power;
    CurrentWeldResult.ActualResult.ActualPreheight = _M102IA->IAactual.Preheight;
    CurrentWeldResult.ActualResult.ActualAmplitude = _M102IA->IAactual.Amplitude;
    CurrentWeldResult.ActualResult.ActualPostheight = _M102IA->IAactual.Height;
    CurrentWeldResult.ActualResult.ActualAmplitude2 = _M102IA->IAactual.Amplitude2;
    CurrentWeldResult.ActualResult.ActualPressure = _M102IA->IAactual.Pressure;
    CurrentWeldResult.ActualResult.ActualTPressure = _M102IA->IAactual.TPressure;
    CurrentWeldResult.ActualResult.ActualAlarmflags = _M102IA->IAactual.Alarmflags;
    if(CurrentSplice.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode == STEPDISABLE)
        CurrentWeldResult.ActualResult.ActualAmplitude2 = 0;

    CurrentWeldResult.OperatorName = _Interface->CurrentOperator.OperatorName;
    CurrentWeldResult.CurrentWorkOrder.WorkOrderID
            = CurrentNecessaryInfo.CurrentWorkOrder.WorkOrderID;
    CurrentWeldResult.CurrentWorkOrder.WorkOrderName
            = CurrentNecessaryInfo.CurrentWorkOrder.WorkOrderName;
    CurrentWeldResult.CurrentPart.PartID = CurrentNecessaryInfo.CurrentPart.PartID;
    CurrentWeldResult.CurrentPart.PartName = CurrentNecessaryInfo.CurrentPart.PartName;

    CurrentWeldResult.CurrentSplice.SpliceID = CurrentSplice.SpliceID;
    CurrentWeldResult.CurrentSplice.SpliceName = CurrentSplice.SpliceName;
    CurrentWeldResult.CurrentSplice.SpliceHash = CurrentSplice.HashCode;

    CurrentWeldResult.SampleRatio = _Interface->StatusData.GraphSampleRatio;
    CurrentWeldResult.PostHeightGraph.clear();
    CurrentWeldResult.PowerGraph.clear();
}

bool MakeWeldProcess::PowerGraphReceive()
{
    bool bResult = false;
    M102IA *_M102IA = M102IA::Instance();
    M2010 *_M2010 = M2010::Instance();
    int Index;
    Index = _M102IA->RawPowerDataGraph.CurrentIndex;
    if(Index != (_M102IA->RawPowerDataGraph.TotalFrame - 1))
    {
        _M2010->ReceiveFlags.PowerGraphData = false;
        _M102IA->SendIACommand(IAComSendPowerGraph, Index);
        _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.PowerGraphData);
    }else
        bResult = true;

    return bResult;
}

bool MakeWeldProcess::HeightGraphReceive()
{
    bool bResult = false;
    M102IA *_M102IA = M102IA::Instance();
    M2010 *_M2010 = M2010::Instance();
    int Index;
    Index = _M102IA->RawHeightDataGraph.CurrentIndex;
    if(Index != (_M102IA->RawHeightDataGraph.TotalFrame - 1))
    {
        _M2010->ReceiveFlags.HeightGraphData = false;
        _M102IA->SendIACommand(IAComSendHeightGraph, Index);
        _M102IA->WaitForResponseAfterSent(5000, &_M2010->ReceiveFlags.HeightGraphData);
        m_triedCount++;
    }else
        bResult = true;
    return bResult;
}

void MakeWeldProcess::TeachModeProcess()
{
    qDebug() << "TeachModeProcess";
    M10runMode* _M10runMode = M10runMode::Instance();
    Statistics *_Statistics = Statistics::Instance();
    _M10runMode->CalculateTeachMode(&CurrentSplice);
    _Statistics->GetLimitsAfterWeld(&CurrentSplice);
}

void MakeWeldProcess::WeldCycleDaemonThread(void* _obj)
{
    M2010 *_M2010 = M2010::Instance();
    M102IA *_M102IA = M102IA::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    MakeWeldProcess* _ObjectPtr = (MakeWeldProcess*)_obj;
    Statistics* _Statistics = Statistics::Instance();
    DBWeldResultTable* _WeldResultDB = DBWeldResultTable::Instance();
    //1. Receive Power and Height Graph Data
    switch(_ObjectPtr->CurrentStep)
    {
    case POWERFst:
        if(_ObjectPtr->PowerGraphReady == false)
        {
            _M102IA->WaitForResponseAfterSent(3000, &_ObjectPtr->PowerGraphReady);
            _ObjectPtr->m_triedCount++;
        }
        else
        {
            _ObjectPtr->CurrentWeldResult.PowerGraph.clear();
            qDebug()<<"GraphDataList.size"<<_M102IA->RawPowerDataGraph.GraphDataList.size();
            _M2010->ConvertPowerGraphData(_M102IA->RawPowerDataGraph.GraphDataList,
                                     &_ObjectPtr->CurrentWeldResult.PowerGraph);
            for(int i = 0; i < _ObjectPtr->CurrentWeldResult.PowerGraph.size(); i++)
            {
                _ObjectPtr->CurrentWeldResult.PowerGraph[i] *=
                        (_Interface->StatusData.Soft_Settings.SonicGenWatts / 200);
            }
            _ObjectPtr->CurrentStep = HEIGHTSnd;
            _ObjectPtr->m_triedCount = 0;
        }
        break;
    case HEIGHTSnd:
        if(_ObjectPtr->HeightGraphReady == false)
        {
            _M102IA->WaitForResponseAfterSent(3000, &_ObjectPtr->HeightGraphReady);
            _ObjectPtr->m_triedCount++;
        }
        else
        {
            _ObjectPtr->CurrentWeldResult.PostHeightGraph.clear();
            _M2010->ConvertHeightGraphData(_M102IA->RawHeightDataGraph.GraphDataList,
                                     &_ObjectPtr->CurrentWeldResult.PostHeightGraph);
            _ObjectPtr->CurrentStep = STEPTrd;
            _ObjectPtr->m_triedCount = 0;
        }
        break;
    default:
        _ObjectPtr->CurrentStep = STEPTrd;
        break;
    }
    if((_ObjectPtr->m_triedCount > 1) || (_ObjectPtr->CurrentStep == STEPTrd))
    {
        if(_ObjectPtr->m_triedCount > 1)
        {
            struct BransonMessageBox tmpMsgBox;
            tmpMsgBox.MsgTitle = QObject::tr("ERROR");
            tmpMsgBox.MsgPrompt = QObject::tr("Can't get full Power & Post Height Graph from controller!");
            tmpMsgBox.TipsMode = Critical;
            tmpMsgBox.func_ptr = NULL;
            _Interface->cMsgBox(&tmpMsgBox);
            _ObjectPtr->WeldCycleStatus = false;
            _ObjectPtr->CurrentWeldResult.PowerGraph.clear();
            _ObjectPtr->CurrentWeldResult.PostHeightGraph.clear();

        }else
        {
            _ObjectPtr->WeldCycleStatus = true;
        }
        //2. Save the Weld result into the Database
        int iResult =
            _WeldResultDB->InsertRecordIntoTable(&_ObjectPtr->CurrentWeldResult);
        _ObjectPtr->CurrentWeldResult.WeldResultID = iResult;

        //6. Shrink Tube
        //7. Remote Data sending
        _Statistics->HistoryEvent(_ObjectPtr->CurrentNecessaryInfo.CurrentWorkOrder.WorkOrderName,
                _ObjectPtr->CurrentNecessaryInfo.CurrentPart.PartName, &_ObjectPtr->CurrentWeldResult, &_ObjectPtr->CurrentSplice);
        if((_M102IA->IAactual.Alarmflags & 0x4000) == 0x4000)
            _ObjectPtr->WeldCycleStatus = true;
        else
            _ObjectPtr->WeldCycleStatus = false;
        emit _ObjectPtr->WeldCycleCompleted(&_ObjectPtr->WeldCycleStatus);
        m_Thread->setStopEnabled(true);
        m_Thread->setSuspendEnabled(true);
    }
}

void MakeWeldProcess::WeldResultEventSlot(bool& bResult)
{
    bool Invalidweld = false;
    M10runMode* _M10runMode = M10runMode::Instance();
    if(bResult == false)
        return;
    UpdateWeldResult();
    m_triedCount = 0;
    CurrentStep = POWERFst;
    WeldCycleStatus = false;
    //3. Alarm handle
    Invalidweld = _M10runMode->CheckWeldData(CurrentSplice.SpliceID);
    //4. Update Maintenance Count
    if(Invalidweld == false)
        _M10runMode->UpdateMaintenanceData(); //Increment Maintenance Counters here

    m_Thread->setStopEnabled(false);
    m_Thread->setSuspendEnabled(false);
    m_Thread->start();
}

void MakeWeldProcess::AnyAlarmEventSlot(bool &bResult)
{
    M10runMode* _M10runMode = M10runMode::Instance();
    _M10runMode->CheckWeldData(-1);
}

void MakeWeldProcess::PowerGraphEventSlot(bool &bResult)
{
    PowerGraphReady = PowerGraphReceive();
}

void MakeWeldProcess::HeightGraphEventSlot(bool &bResult)
{
    HeightGraphReady = HeightGraphReceive();
}

bool MakeWeldProcess::_start()
{
    M102IA *_M102IA = M102IA::Instance();
    M10runMode* _M10runMode = M10runMode::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    struct BransonMessageBox tmpMsgBox;
    _Interface->FirstScreenComesUp = true;
    bool bResult = true;
    if(_M102IA->SendCommandSetRunMode(1) == false)
    {
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
        bResult = false;
    }else{
        m_Thread = new ThreadClass(0, (void*)(MakeWeldProcess::WeldCycleDaemonThread), this);
        m_Thread->setStopEnabled(false);
        m_Thread->setSuspendEnabled(false);
        if(CurrentNecessaryInfo.IsTestProcess == true)
        {
            if(CurrentSplice.TestSetting.TeachModeSetting.TeachModeType != UNDEFINED)
                _M10runMode->init_m20_data_events(&CurrentSplice);
        }
        connect(_M102IA, SIGNAL(WeldCycleSignal(bool&)),
                this,SLOT(WeldResultEventSlot(bool&)));
        connect(_M102IA, SIGNAL(PowerGraphSignal(bool&)),
                this, SLOT(PowerGraphEventSlot(bool&)));
        connect(_M102IA, SIGNAL(HeightGraphSignal(bool&)),
                this, SLOT(HeightGraphEventSlot(bool&)));

    }
    return bResult;
}

bool MakeWeldProcess::_stop()
{
    M102IA *_M102IA = M102IA::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    struct BransonMessageBox tmpMsgBox;
    bool bResult = true;
    disconnect(_M102IA, SIGNAL(WeldResultFeedback(bool&)),this, SLOT(WeldResultFeedbackEventSlot(bool&)));
    qDebug()<<"Operate Stop";
    if(_M102IA->SendCommandSetRunMode(0) == false)
    {
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
        bResult = false;
    }
    if(m_Thread != NULL)
    {
        m_Thread->setSuspendEnabled(true);
        m_Thread->setStopEnabled(true);
        qDebug()<<"Thread stop"<<m_Thread->wait();
        delete m_Thread;
        m_Thread = NULL;
    }
    connect(_M102IA, SIGNAL(WeldResultSignal(bool&)),
            this,SLOT(CheckWeldAlarm(bool&)));
    return bResult;
}

//this function is used to send the preset data to controller
//this also send width calibration data, trigpress, amplitude and pre burst.
//Command for Sending Amplitude Step parameters is also added before the Preset is sent to the controller
bool MakeWeldProcess::_execute()
{
    M102IA *_M102IA = M102IA::Instance();
    M2010  *_M2010  = M2010::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    bool bResult = true;
    int Retries = 0;
    struct BransonMessageBox tmpMsgBox;
    PowerGraphReady = false;
    HeightGraphReady = false;
    UpdateIAFields();
    qDebug()<<"Step1";
    _M2010->ReceiveFlags.SYSTEMid = false;
    while(_M2010->ReceiveFlags.SYSTEMid == false)
    {
        if(Retries < 2)
        {
            qDebug()<<"SendPreset";
            _M102IA->SendPresetToIA(0);
            qDebug()<<"SendPresetEnd";
            _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.SYSTEMid);
            Retries++;
        }else
            break;
        qDebug()<<"Retries"<<Retries;
    }
    qDebug()<<"Step2";
    if( Retries >= 2)
    {
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
        bResult = false;
    }
    qDebug()<<"Step3"<<bResult;
    if(bResult == false)
        return bResult;

    _M102IA->SetIAWidth();
    _M102IA->SendIACommand(IAComSetPressure, CurrentSplice.WeldSettings.BasicSetting.TrigPres);
    _M102IA->SendIACommand(IAComSetAmplitude, CurrentSplice.WeldSettings.BasicSetting.Amplitude);
    _M102IA->SendIACommand(IAComSetPreburst, CurrentSplice.WeldSettings.AdvanceSetting.PreBurst);
    qDebug()<<"Step4"<<WeldCycleStatus;

    if(WeldCycleStatus == false)
    {
        bResult = false;
        return bResult;
    }
    qDebug()<<"Step5";
    Retries = 0;
    _M2010->ReceiveFlags.HostReadyData = false;
    while(_M2010->ReceiveFlags.HostReadyData == false)
    {
        _M102IA->IACommand(IAComHostReady);
        _M102IA->WaitForResponseAfterSent(5000,&_M2010->ReceiveFlags.HostReadyData);
        Retries++;
        if(Retries > 3)
            break;
    }
    qDebug()<<"Step6";
    if(Retries > 3)
    {
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
        bResult = false;
    }
    qDebug()<<"Step7";
    return bResult;
}

//this functio is only for the UCL & LCL calculation.
// the UCL & LCL is the middle point of the USL & LSL +/- 3 standard deviation
void MakeWeldProcess::ControlLimitProcess(QUALITYTYPE Type, QList<int> &RawList,
                                         int USL, int LSL,
                                         int *UCL, int *LCL)
{
    UtilityClass *_Utility = UtilityClass::Instance();
    QList<float> tmpList;
    float tmpValue = 0;
    float UpperSpecValue = 0;
    float LowerSpecValue = 0;
    float UpperControlValue = 0;
    float LowerControlValue = 0;
    float CentralValue;
    float AverageValue;
    float Sigam;
    tmpList.clear();
    *UCL = USL;
    *LCL = LSL;
    switch(Type)
    {
    case QUALITYTIME:
        UpperSpecValue = _Utility->FormatedDataToFloat(DINTimePl,
                    USL);
        LowerSpecValue = _Utility->FormatedDataToFloat(DINTimeMs,
                    LSL);
        break;
    case QUALITYPOWER:
        UpperSpecValue = _Utility->FormatedDataToInteger(DINPowerPl,
                    USL);
        LowerSpecValue = _Utility->FormatedDataToInteger(DINPowerMs,
                    LSL);
        break;
    case QUALITYPREHEIGHT:
        UpperSpecValue = _Utility->FormatedDataToFloat(DINPre_HgtPl,
                    USL);
        LowerSpecValue = _Utility->FormatedDataToFloat(DINPre_HgtMs,
                    LSL);
        break;
    case QUALITYPOSTHEIGHT:
        UpperSpecValue = _Utility->FormatedDataToFloat(DINPre_HgtPl,
                    USL);
        LowerSpecValue = _Utility->FormatedDataToFloat(DINPre_HgtMs,
                    LSL);
        break;
    }
    CentralValue = (UpperSpecValue + LowerSpecValue)/ 2;
    for(int i = 0; i< RawList.size(); i++)
    {
        switch(Type)
        {
        case QUALITYTIME:
            tmpValue = _Utility->FormatedDataToFloat(DINActTime, RawList.at(i));
            break;
        case QUALITYPOWER:
            tmpValue = _Utility->FormatedDataToInteger(DINActPower, RawList.at(i));
            break;
        case QUALITYPREHEIGHT:
            tmpValue = _Utility->FormatedDataToFloat(DINActPreHgt, RawList.at(i));
            break;
        case QUALITYPOSTHEIGHT:
            tmpValue = _Utility->FormatedDataToFloat(DINActHgt, RawList.at(i));
            break;
        }
        tmpList.push_back(tmpValue);
    }

    AverageValue = StatisticalFunction::Mean(tmpList);
    if(tmpList.size() < 2)
        Sigam = 0;
    else
        Sigam = StatisticalFunction::StandardDeviation(tmpList,AverageValue);
//    UpperControlValue = CentralValue + 3 * Sigam;
//    LowerControlValue = CentralValue - 3 * Sigam;
    if(UpperSpecValue > (3 * Sigam))
        UpperControlValue = UpperSpecValue - 3 * Sigam;
    else
        UpperControlValue = UpperSpecValue;
    if(UpperControlValue < CentralValue)
        UpperControlValue = CentralValue;
    LowerControlValue = LowerSpecValue + 3 * Sigam;
    if(LowerControlValue > CentralValue)
        LowerControlValue = CentralValue;
    switch(Type)
    {
    case QUALITYTIME:
        *UCL = (UpperControlValue) / _Utility->txtData[DINActTime].Factor;
        *LCL = (LowerControlValue) / _Utility->txtData[DINActTime].Factor;
        break;
    case QUALITYPOWER:
        *UCL = UpperControlValue / _Utility->txtData[DINActPower].Factor;
        *LCL = LowerControlValue / _Utility->txtData[DINActPower].Factor;
        break;
    case QUALITYPREHEIGHT:
        *UCL = UpperControlValue / _Utility->txtData[DINActPreHgt].Factor;
        *LCL = LowerControlValue / _Utility->txtData[DINActPreHgt].Factor;
        break;
    case QUALITYPOSTHEIGHT:
        *UCL = UpperControlValue / _Utility->txtData[DINActHgt].Factor;
        *LCL = LowerControlValue / _Utility->txtData[DINActHgt].Factor;
        break;
    }
}

void MakeWeldProcess::StopTeachMode()
{
    M10runMode* _M10runMode = M10runMode::Instance();
    _M10runMode->TeachModeFinished(&CurrentSplice);
}
