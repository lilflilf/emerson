#include "Interface/Operate/OperateProcess.h"
#include "Modules/M102IA.h"
#include "Modules/M2010.h"
#include "Modules/M10INI.h"
#include "Modules/ModRunSetup.h"
#include "Interface/Interface.h"
#include "DataBase/DBWeldResultTable.h"
#include <QDebug>
OperateProcess* OperateProcess::_instance = NULL;
ThreadClass* OperateProcess::m_Thread = NULL;
OperateProcess* OperateProcess::Instance()
{
    if(_instance == NULL){
        _instance = new OperateProcess();
    }
    return _instance;
}

OperateProcess::OperateProcess(QObject *parent) : QObject(parent)
{
    M102IA* _M102IA = M102IA::Instance();
    connect(_M102IA, SIGNAL(WeldResultFeedback()),
            this,SLOT(WeldResultFeedbackEventSlot));
}

void OperateProcess::UpdateIAFields()
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
    _M102IA->IAsetup.Time.max = CurrentSplice.WeldSettings.QualitySetting.Time.Plus / 2;
    _M102IA->IAsetup.Time.min = CurrentSplice.WeldSettings.QualitySetting.Time.Minus / 2;
    _M102IA->IAsetup.Power.max = CurrentSplice.WeldSettings.QualitySetting.Power.Plus;
    _M102IA->IAsetup.Power.min = CurrentSplice.WeldSettings.QualitySetting.Power.Minus;
    _M102IA->IAsetup.Preheight.max = CurrentSplice.WeldSettings.QualitySetting.Preheight.Plus;
    _M102IA->IAsetup.Preheight.min = CurrentSplice.WeldSettings.QualitySetting.Preheight.Minus;
    _M102IA->IAsetup.Height.max = CurrentSplice.WeldSettings.QualitySetting.Height.Plus;
    _M102IA->IAsetup.Height.min = CurrentSplice.WeldSettings.QualitySetting.Height.Minus;

    _M102IA->IAsetup.EnergyToStep = CurrentSplice.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep;
    _M102IA->IAsetup.PowerToStep = CurrentSplice.WeldSettings.AdvanceSetting.StepWeld.PowerToStep;
    _M102IA->IAsetup.TimeToStep = CurrentSplice.WeldSettings.AdvanceSetting.StepWeld.TimeToStep;
}

void OperateProcess::UpdateWeldResult()
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

bool OperateProcess::PowerGraphReceive()
{
    bool bResult = false;
    M102IA *_M102IA = M102IA::Instance();
    M2010 *_M2010 = M2010::Instance();

    int Index;

    Index = _M102IA->RawPowerDataGraph.CurrentIndex;
    _M102IA->SendIACommand(IAComSendPowerGraph, Index);
    _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.PowerGraphData);
    if(_M2010->ReceiveFlags.PowerGraphData == true)
    {
        bResult = true;
    }
    if(_M102IA->RawPowerDataGraph.GraphDataList.size() == 0)
    {
        bResult = false;
    }
    return bResult;
}

bool OperateProcess::HeightGraphReceive()
{
    bool bResult = false;
    M102IA *_M102IA = M102IA::Instance();
    M2010 *_M2010 = M2010::Instance();

    int Index;

    Index = _M102IA->RawHeightDataGraph.CurrentIndex;
    _M102IA->SendIACommand(IAComSendHeightGraph, Index);
    _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.HeightGraphData);
    if(_M2010->ReceiveFlags.HeightGraphData == true)
    {
        bResult = true;
    }
    if(_M102IA->RawHeightDataGraph.GraphDataList.size() == 0)
    {
        bResult = false;
    }
    return bResult;
}

void OperateProcess::WeldCycleDaemonThread(void* _obj)
{
    M2010 *_M2010 = M2010::Instance();
    M102IA *_M102IA = M102IA::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    OperateProcess* _ObjectPtr = (OperateProcess*)_obj;
    DBWeldResultTable* _WeldResultDB = DBWeldResultTable::Instance();
    switch(_ObjectPtr->CurrentStep)
    {
    case POWERFst:
        if(_M2010->ReceiveFlags.PowerGraphData == false)
        {
            _ObjectPtr->PowerGraphReceive();
            _ObjectPtr->m_triedCount++;
        }
        else
        {
            _M2010->ConvertGraphData(_M102IA->RawPowerDataGraph.GraphDataList,
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
        if(_M2010->ReceiveFlags.HeightGraphData == false)
        {
            _ObjectPtr->HeightGraphReceive();
            _ObjectPtr->m_triedCount++;
        }
        else
        {
            _M2010->ConvertGraphData(_M102IA->RawHeightDataGraph.GraphDataList,
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
            tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
            tmpMsgBox.TipsMode = Critical;
            tmpMsgBox.func_ptr = NULL;
            _Interface->cMsgBox(&tmpMsgBox);
            _ObjectPtr->WeldCycleStatus = false;
        }else
        {
            _ObjectPtr->WeldCycleStatus = true;
        }
        m_Thread->setStopEnabled(true);
        m_Thread->setSuspendEnabled(true);
        _WeldResultDB->InsertRecordIntoTable(&_ObjectPtr->CurrentWeldResult);

        m_Thread->wait();
        delete m_Thread;
        m_Thread = NULL;
        emit _ObjectPtr->WeldCycleCompleted(&_ObjectPtr->WeldCycleStatus);
    }
}

void OperateProcess::WeldResultFeedbackEventSlot()
{
    M102IA *_M102IA = M102IA::Instance();
    M2010 *_M2010 = M2010::Instance();
    UpdateWeldResult();
    _M2010->ReceiveFlags.PowerGraphData = false;
    _M102IA->RawPowerDataGraph.GraphDataList.clear();
    _M102IA->RawPowerDataGraph.CurrentIndex = 0;
    _M2010->ReceiveFlags.HeightGraphData = false;
    _M102IA->RawHeightDataGraph.GraphDataList.clear();
    _M102IA->RawHeightDataGraph.CurrentIndex = 0;

    m_triedCount = 0;
    CurrentStep = POWERFst;
    m_Thread->start();
}

void OperateProcess::_start()
{
    M102IA *_M102IA = M102IA::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    struct BransonMessageBox tmpMsgBox;
    if(_M102IA->SendCommandSetRunMode(1) == false)
    {
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
    }else{
        m_Thread = new ThreadClass(0, (void*)(OperateProcess::WeldCycleDaemonThread), this);
        m_Thread->setStopEnabled(false);
        m_Thread->setSuspendEnabled(false);
    }

}

void OperateProcess::_stop()
{
    M102IA *_M102IA = M102IA::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    struct BransonMessageBox tmpMsgBox;
    if(_M102IA->SendCommandSetRunMode(0) == false)
    {
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
    }
    if(m_Thread != NULL)
    {
        m_Thread->setSuspendEnabled(true);
        m_Thread->setStopEnabled(true);
        qDebug()<<"Thread stop"<<m_Thread->wait();
        delete m_Thread;
        m_Thread = NULL;
    }
}

//this function is used to send the preset data to controller
//this also send width calibration data, trigpress, amplitude and pre burst.
//Command for Sending Amplitude Step parameters is also added before the Preset is sent to the controller
void OperateProcess::_execute()
{
    M102IA *_M102IA = M102IA::Instance();
    M2010  *_M2010  = M2010::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    ModRunSetup *_ModRunSetup = ModRunSetup::Instance();
    int Retries = 0;
    struct BransonMessageBox tmpMsgBox;
    UpdateIAFields();

    _M2010->ReceiveFlags.SYSTEMid = false;

    while(_M2010->ReceiveFlags.SYSTEMid == false)
    {
        if (_ModRunSetup->OfflineModeEnabled == true)
            break;
        if(Retries < 20)
        {
            _M102IA->SendPresetToIA(0);
            _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.SYSTEMid);
            Retries++;
        }else
            break;
    }

    if( Retries >= 20)
    {
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
    }

    if(_ModRunSetup->OfflineModeEnabled == false)
    {
        _M102IA->SetIAWidth();
        _M102IA->SendIACommand(IAComSetPressure, CurrentSplice.WeldSettings.BasicSetting.TrigPres);
        _M102IA->SendIACommand(IAComSetAmplitude, CurrentSplice.WeldSettings.BasicSetting.Amplitude);
        _M102IA->SendIACommand(IAComSetPreburst, CurrentSplice.WeldSettings.AdvanceSetting.PreBurst);
    }

    if(_ModRunSetup->OfflineModeEnabled == false)
    {
        Retries = 0;
        _M2010->ReceiveFlags.HostReadyData = false;
        while(_M2010->ReceiveFlags.HostReadyData == false)
        {
            _M102IA->IACommand(IAComHostReady);
            _M102IA->WaitForResponseAfterSent(3000,&_M2010->ReceiveFlags.HostReadyData);
            if(_M2010->ReceiveFlags.HostReadyData == false)
                Retries++;
            if(Retries > 3)
                break;
        }
        if(Retries > 3)
        {
            tmpMsgBox.MsgTitle = QObject::tr("ERROR");
            tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
            tmpMsgBox.TipsMode = Critical;
            tmpMsgBox.func_ptr = NULL;
            _Interface->cMsgBox(&tmpMsgBox);
        }
    }
}
