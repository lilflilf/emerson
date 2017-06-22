#include "AdvancedMaintenance.h"
#include "Modules/M2010.h"
#include "Modules/M102IA.h"
#include "Modules/typedef.h"
#include "Modules/UtilityClass.h"
#include "Interface/Interface.h"
#include "Interface/Maintenance/MaintenanceLog.h"
#include "DataBase/DBMaintenanceLogTable.h"
#include <QDebug>
#include <QThread>
#include <QCoreApplication>

bool AdvancedMaintenance::HornTest = false;
bool AdvancedMaintenance::GatherTest = false;
bool AdvancedMaintenance::AnvilTest = false;
bool AdvancedMaintenance::Aux3Test = false;
bool AdvancedMaintenance::Aux4Test = false;
bool AdvancedMaintenance::Aux5Test = false;
bool AdvancedMaintenance::ConverterCoolingTest = false;
bool AdvancedMaintenance::ToolingCoolingTest = false;
unsigned long AdvancedMaintenance::PreviousIO = 0;
bool AdvancedMaintenance::SonicsOnFlag = false;
QList<QTimer*> *AdvancedMaintenance::_TimerList = NULL;
AdvancedMaintenance::AdvancedMaintenance()
{
//    m_Thread = NULL;
    _TimerList = new QList<QTimer*>();
    _TimerList->clear();
}

bool AdvancedMaintenance::_start()
{
    QTimer *_Timer = new QTimer(this);
    _TimerList->push_back(_Timer);
//    _Timer->setObjectName("Test1");
    connect(_Timer, SIGNAL(timeout()),this, SLOT(TimeoutEventSlot()));
    _Timer->setInterval(DELAY500MSEC);//500msecond
    if(_Timer->isActive() == true)
        _Timer->stop();
    _Timer->start();
    return true;
}

bool AdvancedMaintenance::_stop()
{
    QTimer *_Timer = NULL;
    if(_TimerList->size() == 0)
        return true;
    _Timer = _TimerList->at(0);
    if(_Timer->isActive() == true)
        _Timer->stop();
    delete _Timer;
    _TimerList->pop_front();
    return true;
}

bool AdvancedMaintenance::_execute(int funCode)
{
    bool bResult = true;
    DBMaintenanceLogTable* _MaintenanceLog =
            DBMaintenanceLogTable::Instance();
    MaintenanceLogElement MaintenanceLog;
    InterfaceClass* _Interface = InterfaceClass::Instance();
    MaintenanceLog.MaintenanceType = MaintenanceTypeString[MaintenanceLogElement::ADVMAINTAIN];
    MaintenanceLog.OperatorID = _Interface->CurrentOperator.OperatorID;
    MaintenanceLog.CreatedDate = QDateTime::currentDateTime().toTime_t();
    switch(funCode)
    {
    case ANVILARMCLICK:
        AnvilArm_Click();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[MaintenanceLogElement::ANVILARM_MOVE];
        _MaintenanceLog->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case ANVILCLICK:
        Anvil_Click();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[MaintenanceLogElement::ANVIL_MOVE];
        _MaintenanceLog->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case GATHERCLICK:
        qDebug()<<"Gather";
        Gather_Click();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[MaintenanceLogElement::GATHER_MOVE];
        _MaintenanceLog->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case CUTTERCLICK:
        Cutter_Click();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[MaintenanceLogElement::CUTTER_MOVE];
        _MaintenanceLog->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case CRASHCLICK:
        Crash_Click();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[MaintenanceLogElement::CRASH_MOVE];
        _MaintenanceLog->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case SAFETYCLICK:
        Safety_Click();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[MaintenanceLogElement::SAFETY_MOVE];
        _MaintenanceLog->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case CONVERTERCOOLINGCLICK:
        ConverterCooling_Click();
        break;
    case TOOLINGCOOLINGCLICK:
        ToolingCooling_click();
        break;
    default:
        bResult = false;
        break;
    }
    return bResult;
}

void AdvancedMaintenance::AnvilArm_Click()
{
//Procedure to bring the Horn Up/Down for the Mod 9 & Mod 10
//    OR to bring the Anvil Up/Sown for the M2020 & M2030
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    if ((_M2010->M10Run.Gather_Close == false) &&
            (_Interface->StatusData.ActuatorMode == Status_Data::DOUBLEHITMODE))
    {
        BransonMessageBox tmpMsgBox;
        tmpMsgBox.MsgPrompt = QObject::tr("Mask Must be down");
        tmpMsgBox.MsgTitle = QObject::tr("Warning");
        tmpMsgBox.TipsMode = Exclamation;
        tmpMsgBox.OKfunc_ptr = NULL;
        tmpMsgBox.Cancelfunc_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
    }else if((HornTest == false) || (_M2010->M10Run.Horn_Close == false))
    {
        _M102IA->IACommand(IAComHornClose);
        HornTest = true;
        _M2010->M10Run.Horn_Close = true;
    }else
    {
        _M102IA->IACommand(IAComHornOpen);
        HornTest = false;
        _M2010->M10Run.Horn_Close = false;
    }
}

void AdvancedMaintenance::Anvil_Click()
{
//Procedure to Clamp/UnClamp the Anvil Block, used only by the Mod 9 & Mod 10
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    if ((AnvilTest == false) || (_M2010->M10Run.Anvil_Clamped == false))
    {
        _M102IA->SendIACommand(IAComAuxMotion, DO_CLOSE_CLAMP);
        AnvilTest = true;
        _M2010->M10Run.Anvil_Clamped = true;
    }else
    {
        //--Clamp Anvil
        _M102IA->SendIACommand(IAComAuxMotion, DO_OPEN_CLAMP);
        AnvilTest = false;
        _M2010->M10Run.Anvil_Clamped = false;
    }
}

void AdvancedMaintenance::Crash_Click()
{
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    if ((Aux5Test == false) || (_M2010->M10Run.Aux5On == false))
    {
        _M102IA->SendIACommand(IAComAuxMotion, DO_AUX5_ON);
        Aux5Test = true;
        _M2010->M10Run.Aux5On = true;
    }else
    {
        //--Crash
        _M102IA->SendIACommand(IAComAuxMotion, DO_AUX5_OFF);
        Aux5Test = false;
        _M2010->M10Run.Aux5On = false;
    }
}

void AdvancedMaintenance::Cutter_Click()
{
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    if((Aux4Test == false) || (_M2010->M10Run.Aux4On == false))
    {
        _M102IA->SendIACommand(IAComAuxMotion, DO_AUX4_ON);
        Aux4Test = true;
        _M2010->M10Run.Aux4On = true;
    }else
    {
        _M102IA->SendIACommand(IAComAuxMotion, DO_AUX4_OFF);
        Aux4Test = false;
        _M2010->M10Run.Aux4On = false;
    }
}

void AdvancedMaintenance::Gather_Click()
{
//Procedure to Open/Close the Gather for the Mod 9 & Mod 10
//    OR Open/Close the Anvil for the M2020 & M2030
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    if((GatherTest == false) || (_M2010->M10Run.Gather_Close == false))
    {
        //--Aux 1 Close
        _M102IA->IACommand(IAComAux1Close);
        GatherTest = true;
        _M2010->M10Run.Gather_Close = true;
        qDebug()<<"Gather Close";
    }else
    {
        //--Aux 2 Open (Reset Position)
        _M102IA->IACommand(IAComAux1Open);
        GatherTest = false;
        _M2010->M10Run.Gather_Close = false;
        qDebug()<<"Gather Open";
    }
}

void AdvancedMaintenance::Safety_Click()
{
    int CommandON = 0;
    int CommandOFF = 0;
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    if(_M2010->Machine == Welder)
    {
        CommandON = DO_AUX3_ON;
        CommandOFF = DO_AUX3_OFF;
    }else
    {
        CommandON = DO_CLOSE_SAFETY;
        CommandOFF = DO_OPEN_SAFETY;
    }
    if ((Aux3Test == false) || (_M2010->M10Run.Aux3On == false))
    {
        _M102IA->SendIACommand(IAComAuxMotion, CommandON);
        Aux3Test = true;
        _M2010->M10Run.Aux3On = true;
    }else
    {
        //--Clamp Anvil
        _M102IA->SendIACommand(IAComAuxMotion, CommandOFF);
        Aux3Test = false;
        _M2010->M10Run.Aux3On = false;
    }
}

void AdvancedMaintenance::ConverterCooling_Click()
{
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    if((ConverterCoolingTest == false) || (_M2010->M10Run.CoolingOn == false))
    {
        _M102IA->SendIACommand(IAComAuxMotion, DO_COOLING_ON);
        ConverterCoolingTest = true;
        _M2010->M10Run.CoolingOn = true;
    }else
    {
        _M102IA->SendIACommand(IAComAuxMotion, DO_COOLING_OFF);
        ConverterCoolingTest = false;
        _M2010->M10Run.CoolingOn = false;
    }
}

void AdvancedMaintenance::ToolingCooling_click()
{
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    if ((ToolingCoolingTest == false) || (_M2010->M10Run.ToolingCoolingOn == false))
    {
        _M102IA->SendIACommand(IAComAuxMotion, DO_AUX3_ON);
        ToolingCoolingTest = true;
        _M2010->M10Run.ToolingCoolingOn = true;
    }else
    {
        _M102IA->SendIACommand(IAComAuxMotion, DO_AUX3_OFF);
        ToolingCoolingTest = false;
        _M2010->M10Run.ToolingCoolingOn = false;
    }
}

void AdvancedMaintenance::TimeoutEventSlot()
{
//    sender()->objectName() == "test1"
    QTimer *_Timer = (QTimer*)sender();
    _Timer->stop();
    M102IA* _M102IA = M102IA::Instance();
    M2010* _M2010 = M2010::Instance();
    UtilityClass* _Utiltiy = UtilityClass::Instance();
    if(_M102IA->IOstatus.IO != PreviousIO)
    {
        PreviousIO = _M102IA->IOstatus.IO;
        UpdateAnvilArm();
        UpdateAnvil();
        UpdateGather();
        UpdateSafety();
        UpdateConverterCooling();
        UpdateIN2();
        UpdateCrash();
        UpdateCutter();
        UpdateToolingCooling();
        emit IOstatusFeedbackSignal(PreviousIO);
    }else if(SonicsOnFlag == true)
    {
        _M2010->ReceiveFlags.PowerFreqData = false;
        _M102IA->IACommand(IAComGetPowerFreq);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.PowerFreqData);
//        _M102IA->ActualPower = 4000;
//        _M102IA->ActualFrequency = 19950;
        QString FrequencyStr = _Utiltiy->FormatedDataToString(DINActualFrequence, _M102IA->ActualFrequency);
        emit CurrentPowerAndFrequencySignal(_M102IA->ActualPower, FrequencyStr);
    }
    _Timer->start(DELAY500MSEC);//500 msecond
}

void AdvancedMaintenance::UpdateAnvil()
{
    M2010* _M2010 = M2010::Instance();
    if((PreviousIO & CLAMP_ON) == CLAMP_ON)
    {
        AnvilTest = true;
        _M2010->M10Run.Anvil_Clamped = true;
    }else{
        AnvilTest = false;
        _M2010->M10Run.Anvil_Clamped = false;
    }
}

void AdvancedMaintenance::UpdateAnvilArm()
{
    M2010* _M2010 = M2010::Instance();
    if((PreviousIO & HORN_ON) == HORN_ON)
    {
        HornTest = true;
        _M2010->M10Run.Horn_Close = true;
    }else{
        HornTest = false;
        _M2010->M10Run.Horn_Close = false;
    }
}

void AdvancedMaintenance::UpdateGather()
{
    M2010* _M2010 = M2010::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    if(_Interface->StatusData.MachineType == ACTXL)
    {
        if((PreviousIO & GATHER_ON) == GATHER_ON)
        {
            Aux3Test = true;
            _M2010->M10Run.Aux3On = true;
        }else{
            Aux3Test = false;
            _M2010->M10Run.Aux3On = false;
        }
    }else{
        if((PreviousIO & GATHER_ON) == GATHER_ON)
        {
            GatherTest = true;
            _M2010->M10Run.Gather_Close = true;
        }else{
            GatherTest = false;
            _M2010->M10Run.Gather_Close = false;
        }
    }
}

void AdvancedMaintenance::UpdateConverterCooling()
{
    M2010* _M2010 = M2010::Instance();
    if((PreviousIO & CONVERTERCOOL_ON) == CONVERTERCOOL_ON)
    {
        ConverterCoolingTest = true;
        _M2010->M10Run.CoolingOn = true;
    }else{
        ConverterCoolingTest = false;
        _M2010->M10Run.CoolingOn = false;
    }
}

void AdvancedMaintenance::UpdateCrash()
{
    M2010* _M2010 = M2010::Instance();
    if((PreviousIO & CRASH_ON) == CRASH_ON)
    {
        Aux5Test = true;
        _M2010->M10Run.Aux5On = true;
    }
    else{
        Aux5Test = false;
        _M2010->M10Run.Aux5On = false;
    }
}

void AdvancedMaintenance::UpdateCutter()
{
    M2010* _M2010 = M2010::Instance();
    if((PreviousIO & CUTTER_ON) == CUTTER_ON)
    {
        Aux4Test = true;
        _M2010->M10Run.Aux4On = true;
    }
    else{
        Aux4Test = false;
        _M2010->M10Run.Aux4On = false;
    }
}

void AdvancedMaintenance::UpdateIN2()
{
    M2010* _M2010 = M2010::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    if((_Interface->StatusData.MachineType == ACTULTRA20) ||
            (_Interface->StatusData.MachineType == ACTULTRA40))
    {
        if((PreviousIO & IN2_OFF) == IN2_OFF)
        {
            AnvilTest = false;
            _M2010->M10Run.Anvil_Clamped = false;
        }else{
            AnvilTest = true;
            _M2010->M10Run.Anvil_Clamped = true;
        }
    }
}

void AdvancedMaintenance::UpdateSafety()
{
    M2010* _M2010 = M2010::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    if(_Interface->StatusData.MachineType != ACTXL)
    {
        if((PreviousIO & COVER_OPEN) == COVER_OPEN)
        {
            Aux3Test = false;
            _M2010->M10Run.Aux3On = false;
        }else{
            Aux3Test = true;
            _M2010->M10Run.Aux3On = true;
        }
    }
}

void AdvancedMaintenance::UpdateToolingCooling()
{
    M2010* _M2010 = M2010::Instance();
    if((PreviousIO & TOOLINGCOOL_ON) == TOOLINGCOOL_ON)
    {
        ToolingCoolingTest = true;
        _M2010->M10Run.ToolingCoolingOn = true;
    }
    else{
        ToolingCoolingTest = false;
        _M2010->M10Run.ToolingCoolingOn = false;
    }
}

//**************************Following is Branson Special Setting******************************/

void AdvancedMaintenance::Reset()
{
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    //Send Command to reset
    _M2010->M10Run.Alarm_found = false;
//    _M102IA->IACommand(IAComSigLightOff);
    _M102IA->IACommand(IAComClrAlarms);
}

void AdvancedMaintenance::RunSonicsPressed()
{
    M102IA* _M102IA = M102IA::Instance();
    _M102IA->SendIACommand(IAComAuxMotion, DO_SONICS_ON);
    SonicsOnFlag = true;

}

void AdvancedMaintenance::RunSonicsUnPressed()
{
    M102IA* _M102IA = M102IA::Instance();
    _M102IA->SendIACommand(IAComAuxMotion, DO_SONICS_OFF);
    SonicsOnFlag = false;

}

void AdvancedMaintenance::RunSonics100Pressed()
{
    M102IA* _M102IA = M102IA::Instance();
    _M102IA->SendIACommand(IAComAuxMotion, DO_SONICS_FULL);
    SonicsOnFlag = true;
}

void AdvancedMaintenance::RunSonics100UnPressed()
{
    M102IA* _M102IA = M102IA::Instance();
    _M102IA->SendIACommand(IAComAuxMotion, DO_SONICS_OFF);
    SonicsOnFlag = false;
}

void AdvancedMaintenance::AmplitudeSetText(QString AmplitudeStr)
{
    M102IA* _M102IA = M102IA::Instance();
    M2010* _M2010 = M2010::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    int iAmplitude = (int)_Utility->StringToFormatedData(DINDefaultAmplitude, AmplitudeStr);
    _Interface->StatusData.Soft_Settings.Horn_Calibrate = iAmplitude;
    _M2010->ReceiveFlags.HORNamplitude = false;
    _M102IA->SendIACommand(IAComSetHornCalibAmplitude, iAmplitude);
    _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.HORNamplitude);
    _Interface->StatusData.WriteStatusDataToQSetting();
    DEBUG_PRINT(_M2010->ReceiveFlags.HORNamplitude);
}

void AdvancedMaintenance::PowerSetText(QString PowerStr)
{
    M102IA* _M102IA = M102IA::Instance();
    M2010* _M2010 = M2010::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    int iPower = (int)_Utility->StringToFormatedData(DINPowerSupply, PowerStr);
    _Interface->StatusData.Soft_Settings.SonicGenWatts = iPower;
    _Utility->Maxpower = (float)(1.2 * _Interface->StatusData.Soft_Settings.SonicGenWatts);
    _Utility->InitializeTextData();
    _M2010->ReceiveFlags.POWERrating = false;
    _M102IA->SendIACommand(IAComSetGenPower, iPower);
    _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.POWERrating);
    _Interface->StatusData.WriteStatusDataToQSetting();
}

void AdvancedMaintenance::TunePointText(QString TunePointHzStr)
{
    M102IA* _M102IA = M102IA::Instance();
    M2010* _M2010 = M2010::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    int iTunePointHz = (int)_Utility->StringToFormatedData(DINTuneFrequence, TunePointHzStr);
    _Interface->StatusData.Soft_Settings.TunePoint = iTunePointHz;
    _M2010->ReceiveFlags.TunePointData = false;
    _M102IA->SendIACommand(IAComSetTunePoint, iTunePointHz);
    _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.TunePointData);
    _Interface->StatusData.WriteStatusDataToQSetting();
}

void AdvancedMaintenance::FrequencyOffsetText(QString FrequencyHzStr)
{
    M102IA* _M102IA = M102IA::Instance();
    M2010* _M2010 = M2010::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    int iFrequencyHz = (int)_Utility->StringToFormatedData(DINFreqOffset, FrequencyHzStr);
    _Interface->StatusData.Soft_Settings.FrequencyOffset = iFrequencyHz;
    _M2010->ReceiveFlags.FreqOffsetData = false;
    _M102IA->SendIACommand(IAComSetFrequencyOffset, (iFrequencyHz + 500));
    _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.FreqOffsetData);
    _Interface->StatusData.WriteStatusDataToQSetting();
}

void AdvancedMaintenance::RecallAdvancedParameter()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();

    AdvParameter[AMPLITUDE].Current =
            _Utility->FormatedDataToString(DINDefaultAmplitude,
            _Interface->StatusData.Soft_Settings.Horn_Calibrate);
    AdvParameter[AMPLITUDE].Maximum = _Utility->FormatedDataToString(DINDefaultAmplitude,
                                    _Utility->txtData[DINDefaultAmplitude].max);
    AdvParameter[AMPLITUDE].Minimum = _Utility->FormatedDataToString(DINDefaultAmplitude,
                                    _Utility->txtData[DINDefaultAmplitude].min);

    AdvParameter[POWER].Current =
            _Utility->FormatedDataToString(DINPowerSupply,
            _Interface->StatusData.Soft_Settings.SonicGenWatts);
    AdvParameter[POWER].Maximum = _Utility->FormatedDataToString(DINPowerSupply,
                                _Utility->txtData[DINPowerSupply].max);
    AdvParameter[POWER].Minimum = _Utility->FormatedDataToString(DINPowerSupply,
                                _Utility->txtData[DINPowerSupply].min);

    AdvParameter[TUNEPOINT].Current =
            _Utility->FormatedDataToString(DINTuneFrequence,
            _Interface->StatusData.Soft_Settings.TunePoint);
    AdvParameter[TUNEPOINT].Maximum = _Utility->FormatedDataToString(DINTuneFrequence,
                                    _Utility->txtData[DINTuneFrequence].max);
    AdvParameter[TUNEPOINT].Minimum = _Utility->FormatedDataToString(DINTuneFrequence,
                                    _Utility->txtData[DINTuneFrequence].min);


    AdvParameter[FREQOFFSET].Current =
            _Utility->FormatedDataToString(DINFreqOffset,
            _Interface->StatusData.Soft_Settings.FrequencyOffset);
    AdvParameter[FREQOFFSET].Maximum = _Utility->FormatedDataToString(DINFreqOffset,
                                    _Utility->txtData[DINFreqOffset].max);
    AdvParameter[FREQOFFSET].Minimum = _Utility->FormatedDataToString(DINFreqOffset,
                                    _Utility->txtData[DINFreqOffset].min);

}

bool AdvancedMaintenance::GetReliabilityOption()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    return _Interface->StatusData.ReliabilityMode;
}

void AdvancedMaintenance::SetReliabilityOption(bool status)
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    int iReliability = (int)status;
    _Interface->StatusData.ReliabilityMode = status;
    _M2010->ReceiveFlags.ReliabilityModeData = false;
    _M102IA->SendIACommand(IAComSetReliabilityMode, iReliability);
    _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.ReliabilityModeData);
    _Interface->StatusData.WriteStatusDataToQSetting();
}
