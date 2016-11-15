#include "Calibration.h"
#include "Modules/M102IA.h"
#include "Modules/M2010.h"
#include "Interface/Interface.h"
Calibration::Calibration()
{

}


bool Calibration::_start()
{
    bool bResult = true;
    M102IA* _M102IA = M102IA::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    M2010* _M2010 = M2010::Instance();
    struct BransonMessageBox tmpMsgBox;
    if((_Interface->StatusData.MachineType == ACT2032) ||
            (_Interface->StatusData.MachineType == ACTNEWSPLICER))
    {
        _M102IA->SendIACommand(IAComAuxMotion, DO_CLOSE_SAFETY);
        bool bResult = false;

        _M2010->ReceiveFlags.IOdata = false;
        _M102IA->IACommand(IAComSendIOdata);
        _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.IOdata); //Wait for the Safety Close
        if(_M2010->ReceiveFlags.IOdata == false)
        {
            tmpMsgBox.MsgTitle = QObject::tr("Warning");
            tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
            tmpMsgBox.TipsMode = Exclamation;
            tmpMsgBox.func_ptr = NULL;
            _Interface->cMsgBox(&tmpMsgBox);
            bResult = false;
        }else{
            if((_M102IA->IOstatus.IO & SAFETYOPEN) == SAFETYOPEN)
            {
                tmpMsgBox.MsgTitle = QObject::tr("Alarm");
                tmpMsgBox.MsgPrompt = QObject::tr("Weld Safety Alarm!");
                tmpMsgBox.TipsMode = Alarm;
                tmpMsgBox.func_ptr = NULL;
                _Interface->cMsgBox(&tmpMsgBox);
                bResult = false;
            }
        }
        if(bResult == true)
            _M102IA->SendIACommand(IAComAuxMotion, DO_OPEN_CLAMP);
    }
    return bResult;
}

bool Calibration::_stop()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    M102IA* _M102IA = M102IA::Instance();
    if((_Interface->StatusData.MachineType == ACT2032) ||
            (_Interface->StatusData.MachineType == ACTNEWSPLICER))
    {
        _M102IA->SendIACommand(IAComAuxMotion, DO_OPEN_SAFETY);
    }
    return true;
}

bool Calibration::_execute(int funCode)
{
    bool bResult = true;
    switch(funCode)
    {
    case WIDTH_CALIBRATE:
        WidthCalibration();
        break;
    case HEIGHT_CALIBRATE:
        HeightCalibration();
        break;
    case AMPLITUDE_CALIBRATE:
        HornCalibration();
        break;
    default:
        bResult = false;
        break;
    }
    return bResult;
}

void Calibration::WidthCalibration()
{
//   M102IA* _M102IA = M102IA::Instance();
//   _M102IA->SetIAWidth(0);
//   _M102IA->SetIAWidth()
}

void Calibration::HeightCalibration()
{

}

void Calibration::HornCalibration()
{

}
