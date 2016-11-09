#include "Calibration.h"
#include "Modules/M102IA.h"
#include "Interface/Interface.h"
Calibration::Calibration()
{

}

void Calibration::_start()
{
    M102IA* _M102IA = M102IA::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    if((_Interface->StatusData.MachineType == ACT2032) ||
            (_Interface->StatusData.MachineType == ACTNEWSPLICER))
    {
        _M102IA->SendIACommand(IAComAuxMotion, DO_CLOSE_SAFETY);
        _M102IA->SendIACommand(IAComAuxMotion, DO_OPEN_CLAMP);
    }
}

void Calibration::_stop()
{

}

void Calibration::_execute(int funCode)
{

}

void Calibration::WidthCalibration()
{
//   M102IA* _M102IA = M102IA::Instance();
//   _M102IA->SetIAWidth(0);
//   _M102IA->SetIAWidth()
}
