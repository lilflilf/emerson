#include "Interface/Operate/OperateProcess.h"
#include "Modules/M102IA.h"
#include "Modules/M2010.h"
#include "Modules/ModRunSetup.h"
#include "Interface/Interface.h"
OperateProcess* OperateProcess::_instance = NULL;
OperateProcess* OperateProcess::Instance()
{
    if(_instance == NULL){
        _instance = new OperateProcess();
    }
    return _instance;
}

OperateProcess::OperateProcess(QObject *parent) : QObject(parent)
{

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