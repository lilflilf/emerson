#include "Maintenance.h"
#include "Modules/M2010.h"
#include "Modules/M102IA.h"
#include "Interface.h"
#include "SysConfiguration.h"
#include "Modules/UtilityClass.h"
#include <QDebug>
bool Maintenance::HornTest = false;
bool Maintenance::GatherTest = false;
bool Maintenance::AnvilTest = false;
bool Maintenance::Aux3Test = false;
bool Maintenance::Aux4Test = false;
bool Maintenance::Aux5Test = false;
bool Maintenance::ConverterCoolingTest = false;
bool Maintenance::ToolingCoolingTest = false;
unsigned long Maintenance::PreviousIO = 0;

Maintenance::Maintenance(QObject *parent)
    :QObject(parent)
{
    m_Thread = NULL;
}

Maintenance::~Maintenance()
{
    m_Thread = NULL;
}

void Maintenance::AnvilArm_Click()
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

void Maintenance::Anvil_Click()
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

void Maintenance::Crash_Click()
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

void Maintenance::Cutter_Click()
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

void Maintenance::Gather_Click()
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

void Maintenance::Safety_Click()
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
    if ((Aux3Test == false) || (_M2010->M10Run.Aux3On))
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

void Maintenance::ConverterCooling_Click()
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

void Maintenance::ToolingCooling_click()
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

void Maintenance::AdvancedMaintenanceHandle(void* _obj)
{
    M102IA* _M102IA = M102IA::Instance();
    M2010* _M2010 = M2010::Instance();
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
            emit ((Maintenance*)_obj)->IOstatusFeedback(PreviousIO);
        }
       _M2010->ReceiveFlags.IOdata = false;
    }

    qDebug()<<"Advanced Maintenace processing";
}

void Maintenance::AdvancedMaintenanceStart()
{
    m_Thread = new ThreadClass(0, (void*)(Maintenance::AdvancedMaintenanceHandle), this);
    m_Thread->setStopEnabled(false);
    m_Thread->setSuspendEnabled(false);
    m_Thread->start();


}

void Maintenance::AdvancedMaintenanceStop()
{
    m_Thread->setSuspendEnabled(true);
    m_Thread->setStopEnabled(true);
    qDebug()<<"Thread stop"<<m_Thread->wait();
    delete m_Thread;
    m_Thread = NULL;
}

void Maintenance::UpdateAnvil()
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

void Maintenance::UpdateAnvilArm()
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

void Maintenance::UpdateGather()
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

void Maintenance::UpdateConverterCooling()
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

void Maintenance::UpdateCrash()
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

void Maintenance::UpdateCutter()
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

void Maintenance::UpdateIN2()
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

void Maintenance::UpdateSafety()
{
    M2010* _M2010 = M2010::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    if(_Interface->StatusData.MachineType != ACTXL)
    {
        if((PreviousIO & IN0_OFF) == IN0_OFF)
        {
            Aux3Test = false;
            _M2010->M10Run.Aux3On = false;
        }else{
            Aux3Test = true;
            _M2010->M10Run.Aux3On = true;
        }
    }
}

void Maintenance::UpdateToolingCooling()
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
