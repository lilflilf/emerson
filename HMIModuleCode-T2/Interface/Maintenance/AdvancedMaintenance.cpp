#include "AdvancedMaintenance.h"
#include "Modules/M2010.h"
#include "Modules/M102IA.h"
#include "Interface/Interface.h"
#include "Interface/Maintenance/MaintenanceLog.h"
#include "DataBase/DBMaintenanceLogTable.h"
#include <QDebug>

bool AdvancedMaintenance::HornTest = false;
bool AdvancedMaintenance::GatherTest = false;
bool AdvancedMaintenance::AnvilTest = false;
bool AdvancedMaintenance::Aux3Test = false;
bool AdvancedMaintenance::Aux4Test = false;
bool AdvancedMaintenance::Aux5Test = false;
bool AdvancedMaintenance::ConverterCoolingTest = false;
bool AdvancedMaintenance::ToolingCoolingTest = false;
unsigned long AdvancedMaintenance::PreviousIO = 0;

AdvancedMaintenance::AdvancedMaintenance()
{
    m_Thread = NULL;
}

bool AdvancedMaintenance::_start()
{
    m_Thread = new ThreadClass(0, (void*)(AdvancedMaintenance::AdvancedMaintenanceHandle), this);
    m_Thread->setStopEnabled(false);
    m_Thread->setSuspendEnabled(false);
    m_Thread->start();
    return true;
}

bool AdvancedMaintenance::_stop()
{
    m_Thread->setSuspendEnabled(true);
    m_Thread->setStopEnabled(true);
    qDebug()<<"Thread stop"<<m_Thread->wait();
    delete m_Thread;
    m_Thread = NULL;
    return true;
}

bool AdvancedMaintenance::_execute(int funCode)
{
    bool bResult = true;
    DBMaintenanceLogTable* _MaintenanceLog =
            DBMaintenanceLogTable::Instance();
    MaintenanceLogElement MaintenanceLog;
    InterfaceClass* _Interface = InterfaceClass::Instance();
    MaintenanceLog.MaintenanceType = MaintenanceTypeString[ADVMAINTAIN];
    MaintenanceLog.OperatorID = _Interface->CurrentOperator.OperatorID;
    MaintenanceLog.CreatedDate = QDateTime::currentDateTime().toTime_t();
    switch(funCode)
    {
    case ANVILARMCLICK:
        AnvilArm_Click();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[ANVILARM_MOVE];
        _MaintenanceLog->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case ANVILCLICK:
        Anvil_Click();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[ANVIL_MOVE];
        _MaintenanceLog->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case GATHERCLICK:
        Gather_Click();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[GATHER_MOVE];
        _MaintenanceLog->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case CUTTERCLICK:
        Cutter_Click();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[CUTTER_MOVE];
        _MaintenanceLog->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case CRASHCLICK:
        Crash_Click();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[CRASH_MOVE];
        _MaintenanceLog->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case SAFETYCLICK:
        Safety_Click();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[SAFETY_MOVE];
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
    m_Thread->setSuspendEnabled(true);
    if ((_M2010->M10Run.Gather_Close == false) &&
            (_Interface->StatusData.ActuatorMode == DOUBLEHITMODE))
    {
        BransonMessageBox tmpMsgBox;
        tmpMsgBox.MsgPrompt = QObject::tr("Mask Must be down");
        tmpMsgBox.MsgTitle = QObject::tr("Warning");
        tmpMsgBox.TipsMode = Exclamation;
        tmpMsgBox.func_ptr = NULL;
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
    m_Thread->setSuspendEnabled(false);
}

void AdvancedMaintenance::Anvil_Click()
{
//Procedure to Clamp/UnClamp the Anvil Block, used only by the Mod 9 & Mod 10
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    m_Thread->setSuspendEnabled(true);
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
    m_Thread->setSuspendEnabled(false);
}

void AdvancedMaintenance::Crash_Click()
{
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    m_Thread->setSuspendEnabled(true);
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
    m_Thread->setSuspendEnabled(false);
}

void AdvancedMaintenance::Cutter_Click()
{
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    m_Thread->setSuspendEnabled(true);
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
    m_Thread->setSuspendEnabled(false);
}

void AdvancedMaintenance::Gather_Click()
{
//Procedure to Open/Close the Gather for the Mod 9 & Mod 10
//    OR Open/Close the Anvil for the M2020 & M2030
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    m_Thread->setSuspendEnabled(true);
    if((GatherTest == false) || (_M2010->M10Run.Gather_Close == false))
    {
        //--Aux 1 Close
        _M102IA->IACommand(IAComAux1Close);
        GatherTest = true;
        _M2010->M10Run.Gather_Close = true;
    }else
    {
        //--Aux 2 Open (Reset Position)
        _M102IA->IACommand(IAComAux1Open);
        GatherTest = false;
        _M2010->M10Run.Gather_Close = false;
    }
    m_Thread->setSuspendEnabled(false);
}

void AdvancedMaintenance::Safety_Click()
{
    int CommandON = 0;
    int CommandOFF = 0;
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    m_Thread->setSuspendEnabled(true);
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
    m_Thread->setSuspendEnabled(false);
}

void AdvancedMaintenance::ConverterCooling_Click()
{
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    m_Thread->setSuspendEnabled(true);
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
    m_Thread->setSuspendEnabled(false);
}

void AdvancedMaintenance::ToolingCooling_click()
{
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    m_Thread->setSuspendEnabled(true);
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
    m_Thread->setSuspendEnabled(false);
}

void AdvancedMaintenance::AdvancedMaintenanceHandle(void* _obj)
{
    M102IA* _M102IA = M102IA::Instance();
    M2010* _M2010 = M2010::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _M2010->ReceiveFlags.IOdata = false;
    _M102IA->IACommand(IAComSendIOdata);
    _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.IOdata);
    if(_M2010->ReceiveFlags.IOdata == true)
    {
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
            emit ((AdvancedMaintenance*)_obj)->IOstatusFeedback(PreviousIO);
        }
       _M2010->ReceiveFlags.IOdata = false;
    }else{
        struct BransonMessageBox tmpMsgBox;
        tmpMsgBox.MsgTitle = QObject::tr("Warning");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
        tmpMsgBox.TipsMode = Exclamation;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
    }
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
