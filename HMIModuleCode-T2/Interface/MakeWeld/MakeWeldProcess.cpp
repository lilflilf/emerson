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
#include "Modules/typedef.h"
#include "Modules/BransonServer.h"
#include <QDateTime>
#include <QDebug>
MakeWeldProcess* MakeWeldProcess::_instance = NULL;
QList<ThreadClass*>* MakeWeldProcess::_ThreadList = NULL;
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
    m_pReadySM = ReadyStateMachine::Instance();
    _ThreadList = new QList<ThreadClass*>();
    WeldCycleStatus = true;
    PowerGraphReady = false;
    HeightGraphReady = false;
    IsWeldingStatus = false;

    connect(_M102IA, SIGNAL(WeldCycleSignal(bool&)),
            this,SLOT(WeldResultEventSlot(bool&)));
    connect(_M102IA, SIGNAL(PowerGraphSignal(bool&)),
            this, SLOT(PowerGraphEventSlot(bool&)));
    connect(_M102IA, SIGNAL(HeightGraphSignal(bool&)),
            this, SLOT(HeightGraphEventSlot(bool&)));
}

void MakeWeldProcess::UpdateIAFields()
{
    M102IA *_M102IA = M102IA::Instance();
    _M102IA->IAsetup.Energy = CurrentSplice.WeldSettings.BasicSetting.Energy;
//    DEBUG_PRINT(_M102IA->IAsetup.Energy);
    _M102IA->IAsetup.Width = CurrentSplice.WeldSettings.BasicSetting.Width;
//    DEBUG_PRINT(_M102IA->IAsetup.Width);
    _M102IA->IAsetup.WeldPressure = CurrentSplice.WeldSettings.BasicSetting.Pressure;
//    DEBUG_PRINT(_M102IA->IAsetup.WeldPressure);
    _M102IA->IAsetup.TriggerPressure = CurrentSplice.WeldSettings.BasicSetting.TrigPres;
//    DEBUG_PRINT(_M102IA->IAsetup.TriggerPressure);
    _M102IA->IAsetup.Amplitude = CurrentSplice.WeldSettings.BasicSetting.Amplitude;
//    DEBUG_PRINT(_M102IA->IAsetup.Amplitude);
    _M102IA->IAsetup.Amplitude2 = CurrentSplice.WeldSettings.AdvanceSetting.StepWeld.Amplitude2;
    _M102IA->IAsetup.SqueezeTime = CurrentSplice.WeldSettings.AdvanceSetting.SqzTime;
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
    _M102IA->IAsetup.Time.min = CurrentSplice.WeldSettings.QualitySetting.Time.Minus;
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
    CurrentWeldResult.WeldSettings = CurrentSplice.WeldSettings;
    CurrentWeldResult.CrossSection = CurrentSplice.CrossSection;
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
    if(CurrentSplice.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode == STEPWELD::STEPDISABLE)
    {
        CurrentWeldResult.ActualResult.ActualAmplitude2 = 0;
    }

    CurrentWeldResult.OperatorName = _Interface->CurrentOperator.OperatorName;
    CurrentWeldResult.OperateMode = _Interface->CurrentWorkOrder.OperateMode;
    CurrentWeldResult.CurrentWorkOrder.WorkOrderID = INVALID;
    CurrentWeldResult.CurrentWorkOrder.WorkOrderName.clear();
    switch(_Interface->CurrentWorkOrder.WorkOrderMode)
    {
    case WorkOrderElement::SPLICE:
        CurrentWeldResult.CurrentHarness.HarnessID = INVALID;
        CurrentWeldResult.CurrentHarness.HarnessName.clear();
        CurrentWeldResult.CurrentSequence.SequenceID = INVALID;
        CurrentWeldResult.CurrentSequence.SequenceName.clear();
        break;
    case WorkOrderElement::SEQUENCE:
        CurrentWeldResult.CurrentHarness.HarnessID = INVALID;
        CurrentWeldResult.CurrentHarness.HarnessName.clear();
        CurrentWeldResult.CurrentSequence.SequenceID = _Interface->CurrentWorkOrder.WorkOrderID;
        CurrentWeldResult.CurrentSequence.SequenceName = _Interface->CurrentWorkOrder.WorkOrderName;
        break;
    case WorkOrderElement::HARNESS:
        CurrentWeldResult.CurrentHarness.HarnessID = _Interface->CurrentWorkOrder.WorkOrderID;
        CurrentWeldResult.CurrentHarness.HarnessName = _Interface->CurrentWorkOrder.WorkOrderName;
        CurrentWeldResult.CurrentSequence.SequenceID = INVALID;
        CurrentWeldResult.CurrentSequence.SequenceName.clear();
        break;
    default:
        CurrentWeldResult.CurrentHarness.HarnessID = INVALID;
        CurrentWeldResult.CurrentHarness.HarnessName.clear();
        CurrentWeldResult.CurrentSequence.SequenceID = INVALID;
        CurrentWeldResult.CurrentSequence.SequenceName.clear();
        break;
    }
    CurrentWeldResult.CurrentSplice.PartID = CurrentSplice.SpliceID;
    CurrentWeldResult.CurrentSplice.PartName = CurrentSplice.SpliceName;
    CurrentWeldResult.CurrentSplice.PartHash = CurrentSplice.HashCode;

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
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.PowerGraphData);
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
        _M102IA->WaitForResponseAfterSent(DELAY5SEC, &_M2010->ReceiveFlags.HeightGraphData);
        m_triedCount++;
    }else
        bResult = true;
    return bResult;
}

void MakeWeldProcess::WeldCycleDaemonThread(void* _obj)
{
    M2010 *_M2010 = M2010::Instance();
    M102IA *_M102IA = M102IA::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    MakeWeldProcess* _ObjectPtr = (MakeWeldProcess*)_obj;
    Statistics* _Statistics = Statistics::Instance();
    DBWeldResultTable* _WeldResultDB = DBWeldResultTable::Instance();
    bool StopThreadFlag = false;
    //1. Receive Power and Height Graph Data
    switch(_ObjectPtr->CurrentStep)
    {
    case POWERFst:
        if(_ObjectPtr->PowerGraphReady == false)
        {
            _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_ObjectPtr->PowerGraphReady);
            _ObjectPtr->m_triedCount++;
        }
        else
        {
            _ObjectPtr->CurrentWeldResult.PowerGraph.clear();
            _M2010->ConvertPowerGraphData(_M102IA->RawPowerDataGraph.GraphDataList,
                                     &_ObjectPtr->CurrentWeldResult.PowerGraph);
            for(int i = 0; i < _ObjectPtr->CurrentWeldResult.PowerGraph.size(); i++)
            {
                _ObjectPtr->CurrentWeldResult.PowerGraph[i] *=
                        ((float)_Interface->StatusData.Soft_Settings.SonicGenWatts / POWERFACTOR);
//                DEBUG_PRINT(_ObjectPtr->CurrentWeldResult.PowerGraph[i]);
            }
            _ObjectPtr->CurrentStep = HEIGHTSnd;
            _ObjectPtr->m_triedCount = 0;
        }
        break;
    case HEIGHTSnd:
        if(_ObjectPtr->HeightGraphReady == false)
        {
            _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_ObjectPtr->HeightGraphReady);
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
    if(_ObjectPtr->m_triedCount > 1)
    {
        struct BransonMessageBox tmpMsgBox;
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get full Power & Post Height Graph from controller!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.OKfunc_ptr = NULL;
        tmpMsgBox.Cancelfunc_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
        _ObjectPtr->WeldCycleStatus = false;
        _ObjectPtr->CurrentWeldResult.PowerGraph.clear();
        _ObjectPtr->CurrentWeldResult.PostHeightGraph.clear();
        StopThreadFlag = true;
    }
    else if(_ObjectPtr->CurrentStep == STEPTrd)
    {
        //2. Save the Weld result into the Database
        if(((_M102IA->IAactual.Alarmflags & BIT4) == BIT4) ||
            ((_M102IA->IAactual.Alarmflags & BIT9) == BIT9) ||
            ((_M102IA->IAactual.Alarmflags & BIT10) == BIT10))
        {
            _ObjectPtr->WeldCycleStatus = false;
            _ObjectPtr->m_pReadySM->ReadyState = ReadyStateMachine::READYON;
        }else
        {
            int iResult =
                _WeldResultDB->InsertRecordIntoTable(&_ObjectPtr->CurrentWeldResult);
            qDebug()<<"Ordername"<<_ObjectPtr->CurrentWeldResult.CurrentWorkOrder.WorkOrderName;
            _ObjectPtr->CurrentWeldResult.WeldResultID = iResult;
    //        _ObjectPtr->WeldCycleStatus = true;
            //6. Shrink Tube
            //7. Remote Data sending
            if (_Interface->StatusData.NetworkingEnabled == true)
            {
                QString StrRecord =
                        _Statistics->HistoryEvent(&_ObjectPtr->CurrentWeldResult);
                BransonServer *_Server = BransonServer::Instance();
                _Server->SendDataToClients(StrRecord);
            }
            if((_M102IA->IAactual.Alarmflags & BIT14) == BIT14)
            {
                _ObjectPtr->WeldCycleStatus = true;
                _ObjectPtr->m_pReadySM->ReadyState = ReadyStateMachine::READYON;
            }
            else
            {
                _ObjectPtr->WeldCycleStatus = true;
                _ObjectPtr->m_pReadySM->ReadyState = ReadyStateMachine::READYOFF;
            }
        }
        StopThreadFlag = true;
    }
    if(StopThreadFlag == true)
    {
        emit _ObjectPtr->WeldCycleCompleted(_ObjectPtr->WeldCycleStatus);
        ThreadClass* _pThread = _ThreadList->at(0);
        _pThread->setStopEnabled(true);
        _pThread->setSuspendEnabled(true);
        _M102IA->RawPowerDataGraph.GraphDataList.clear();
        _M102IA->RawHeightDataGraph.GraphDataList.clear();
        _ObjectPtr->PowerGraphReady = false;
        _ObjectPtr->HeightGraphReady = false;
    }
}

void MakeWeldProcess::WeldResultEventSlot(bool& bResult)
{
    bool Invalidweld = false;
    M10runMode* _M10runMode = M10runMode::Instance();
    if(bResult == false)
        return;
    m_pReadySM->ReadyState = ReadyStateMachine::READYOFF;
    UpdateWeldResult();
    m_triedCount = 0;
    CurrentStep = POWERFst;
    WeldCycleStatus = false;
    //1. Alarm handle
    Invalidweld = _M10runMode->CheckWeldData(CurrentSplice.SpliceID);
    //2. Update Maintenance Count
    if(Invalidweld == false)
    {
        _M10runMode->UpdateMaintenanceData(); //Increment Maintenance Counters here
        _M10runMode->CheckMaintenanceData();
    }
    ThreadClass* _pThread = _ThreadList->at(0);
    _pThread->setStopEnabled(false);
    _pThread->setSuspendEnabled(false);
    _pThread->start();
}

void MakeWeldProcess::PowerGraphEventSlot(bool &bResult)
{
    UNUSED(bResult);
    PowerGraphReady = PowerGraphReceive();
}

void MakeWeldProcess::HeightGraphEventSlot(bool &bResult)
{
    UNUSED(bResult);
    HeightGraphReady = HeightGraphReceive();
}

bool MakeWeldProcess::_start()
{
    M102IA *_M102IA = M102IA::Instance();
    M10runMode* _M10runMode = M10runMode::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    Statistics* _Statistics = Statistics::Instance();
    struct BransonMessageBox tmpMsgBox;
    _Interface->FirstScreenComesUp = true;
    bool bResult = true;
    qDebug()<<"Make Weld Start";

    if(_M10runMode->CheckMaintenanceData() == false)
    {
        m_pReadySM->ReadyState = ReadyStateMachine::READYOFF;
        _M102IA->SendCommandSetRunMode(OFF);
        return false;
    }

    if(_M102IA->SendCommandSetRunMode(ON) == false)
    {
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.OKfunc_ptr = NULL;
        tmpMsgBox.Cancelfunc_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
        bResult = false;
        DEBUG_PRINT("_M102IA->SendCommandSetRunMode(ON");
    }else{
        ThreadClass* _pThread = new ThreadClass(0, (void*)(MakeWeldProcess::WeldCycleDaemonThread), this);
        _ThreadList->append(_pThread);
        _pThread->setStopEnabled(false);
        _pThread->setSuspendEnabled(false);
        if(CurrentSplice.TestSetting.TeachModeSetting.TeachModeType != TEACHMODESETTING::UNDEFINED)
        {
            _M10runMode->init_m20_data_events(&CurrentSplice);
            _Statistics->ZeroM20DataEvents();
        }
        m_pReadySM->_start();
        m_pReadySM->ReadyState = ReadyStateMachine::READYON;
        IsWeldingStatus = true;
    }
    return bResult;
}

bool MakeWeldProcess::_stop()
{
    M102IA *_M102IA = M102IA::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    struct BransonMessageBox tmpMsgBox;
    bool bResult = true;
    //Delete Thread and release resource
    ThreadClass* _Thread = NULL;
    if(_ThreadList->size() > 0)
    {
        _Thread = _ThreadList->at(0);
        _Thread->setSuspendEnabled(true);
        _Thread->setStopEnabled(true);
        qDebug()<<"Weld Process stop"<<_Thread->wait();
        delete _Thread;
        _ThreadList->pop_front();
        IsWeldingStatus = false;
    }
    //Delect Thread and release resource
    m_pReadySM->_stop();
    if(_M102IA->SendCommandSetRunMode(OFF) == false)
    {
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.OKfunc_ptr = NULL;
        tmpMsgBox.Cancelfunc_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
        bResult = false;
        DEBUG_PRINT("_M102IA->SendCommandSetRunMode(OFF");
    }
    qDebug()<<"Weld Process end";
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
    M10runMode* _M10runMode = M10runMode::Instance();
    bool bResult = true;
    int Retries = 0;
    struct BransonMessageBox tmpMsgBox;
    PowerGraphReady = false;
    HeightGraphReady = false;

    if(_M10runMode->CheckMaintenanceData() == false)
    {
        m_pReadySM->ReadyState = ReadyStateMachine::READYOFF;
        _M102IA->SendCommandSetRunMode(OFF);
        return false;
    }

    UpdateIAFields();
    _M2010->ReceiveFlags.SYSTEMid = false;
    while(_M2010->ReceiveFlags.SYSTEMid == false)
    {
        if(Retries < 2)
        {
            _M102IA->SendPresetToIA(0);
            _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.SYSTEMid);
            Retries++;
        }else
            break;
    }
    if( Retries >= 2)
    {
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.OKfunc_ptr = NULL;
        tmpMsgBox.Cancelfunc_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
        bResult = false;
        DEBUG_PRINT(_M2010->ReceiveFlags.SYSTEMid);
    }
    if(bResult == false)
        return bResult;

    _M102IA->SetIAWidth();
    _M102IA->SendIACommand(IAComSetPressure, CurrentSplice.WeldSettings.BasicSetting.TrigPres);
    _M102IA->SendIACommand(IAComSetAmplitude, CurrentSplice.WeldSettings.BasicSetting.Amplitude);
    _M102IA->SendIACommand(IAComSetPreburst, CurrentSplice.WeldSettings.AdvanceSetting.PreBurst);

//    _M2010->ReceiveFlags.ActuatorType = false;
//    if(CurrentSplice.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideMode == true)
//    {
//        _M2010->TempActuatorInfo.CurrentActuatorMode = Status_Data::ANTISIDESPLICE;
//        _M2010->TempActuatorInfo.CurrentAntisideSpliceTime =
//                CurrentSplice.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideSpliceTime;
//    }else{
//        _M2010->TempActuatorInfo.CurrentActuatorMode = Status_Data::ANTISIDESPLICEOFF;
//    }
//    _M2010->TempActuatorInfo.CurrentActuatorType =
//            _Interface->StatusData.MachineType;
//    _M102IA->SendIACommand(IAComSetActuator, 0);
//    _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.ActuatorType);

//    _M2010->ReceiveFlags.CutterResponseData = false;
//    if(CurrentSplice.WeldSettings.AdvanceSetting.CutOffOption.CutOff == true)
//        _M102IA->SendIACommand(IAComSetCutoff, ON);
//    else
//        _M102IA->SendIACommand(IAComSetCutoff, OFF);
//    _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.CutterResponseData);

    if(WeldCycleStatus == false)
    {
        bResult = false;
        return bResult;
    }
    Retries = 0;
    _M2010->ReceiveFlags.HostReadyData = false;
    while(_M2010->ReceiveFlags.HostReadyData == false)
    {
        _M102IA->IACommand(IAComHostReady);
        _M102IA->WaitForResponseAfterSent(DELAY5SEC,&_M2010->ReceiveFlags.HostReadyData);
        Retries++;
        if(Retries > 3)
            break;
    }
    if(Retries > 3)
    {
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.OKfunc_ptr = NULL;
        tmpMsgBox.Cancelfunc_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
        bResult = false;
        DEBUG_PRINT(_M2010->ReceiveFlags.HostReadyData);
    }
    return bResult;
}

void MakeWeldProcess::StopTeachMode()
{
    M10runMode* _M10runMode = M10runMode::Instance();
    _M10runMode->TeachModeFinished(&CurrentSplice);
}

void MakeWeldProcess::TeachModeProcess()
{
    qDebug() << "TeachModeProcess";
    Statistics *_Statistics = Statistics::Instance();
    M2010 *_M2010 = M2010::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    if(_M2010->M10Run.Alarm_found == false)
    {
        if(_Interface->StatusData.Cust_Data.PresetTeachModeSetting == QUALITY_DATA_FILE::GLOBALS)
            _Statistics->CalcConfLimits(&_Interface->StatusData);
        else
            _Statistics->CalcConfLimits(&CurrentSplice);
    }
    _Statistics->GetLimitsAfterWeld(&CurrentSplice);
}

void MakeWeldProcess::EraseLastEntry()
{
    Statistics *_Statistics = Statistics::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    M10runMode *_M10RunMode = M10runMode::Instance();
    if(_Statistics->Splice_Stat.prts_count <= 0) return;
    if(((_Interface->StatusData.Soft_Settings.Teach_Mode == TEACHMODESETTING::STANDARD) ||
            (_Interface->StatusData.Soft_Settings.Teach_Mode == TEACHMODESETTING::SIGMA)))
    {
        if(_M10RunMode->PreviousWeldValid == true)
        {
            _Statistics->Splice_Stat.prts_count -= 1;
            if(_Statistics->Splice_Stat.data_ptr > 0)
                _Statistics->Splice_Stat.data_ptr -= 1;
            else
                _Statistics->Splice_Stat.data_ptr = M20_Data_Pnt_MI;

            _Statistics->RotateOut(_Statistics->Splice_Stat.Time,
                _Statistics->Splice_Stat.TimeData[_Statistics->Splice_Stat.data_ptr]);
            _Statistics->RotateOut(_Statistics->Splice_Stat.Power,
                _Statistics->Splice_Stat.PowerData[_Statistics->Splice_Stat.data_ptr]);
            _Statistics->RotateOut(_Statistics->Splice_Stat.Pre_hght,
                _Statistics->Splice_Stat.PreHghtData[_Statistics->Splice_Stat.data_ptr]);
            _Statistics->RotateOut(_Statistics->Splice_Stat.Height,
                _Statistics->Splice_Stat.HeightData[_Statistics->Splice_Stat.data_ptr]);
            _Statistics->CalcConfLimits(&_Interface->StatusData);
        }
    }
}

bool MakeWeldProcess::GetWeldStatus()
{
    return IsWeldingStatus;
}
