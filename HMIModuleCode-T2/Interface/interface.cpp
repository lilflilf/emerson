#include "interface.h"
#include "Modules/Modstart.h"
#include "Modules/M10INI.h"
InterfaceClass* InterfaceClass::_instance = 0;

InterfaceClass* InterfaceClass::Instance()
{
    if(_instance == 0){
        _instance = new InterfaceClass();
    }
    return _instance;
}


InterfaceClass::InterfaceClass(QObject *parent)
    :QObject(parent)
{

}

InterfaceClass::~InterfaceClass()
{

}

void InterfaceClass::cMsgBox(struct BransonMessageBox* MsgBox)
{
    BransonMessageBox tmpMsgBox;
    tmpMsgBox.MsgPrompt = MsgBox->MsgPrompt;
    tmpMsgBox.MsgTitle = MsgBox->MsgTitle;
    tmpMsgBox.TipsMode = MsgBox->TipsMode;
    tmpMsgBox.func_ptr = MsgBox->func_ptr;
}

void InterfaceClass::dlgMaintWarning()
{
    M10INI *ptr_M10INI = M10INI::Instance();
    for(int i = 0; i < 8; i++)
    {
        if(i <= 3)
        {
            if ((ptr_M10INI->StatusData.currentMaintenanceLimits[i] >=
                    ptr_M10INI->StatusData.MaintenanceLimits[i]) &&
                    (ptr_M10INI->StatusData.MaintenanceLimits[i] != 0))
            {

            }

        }
        else{
            if ((ptr_M10INI->StatusData.currentMaintenanceLimits[i] >=
              ptr_M10INI->StatusData.MaintenanceLimits[i]) &&
                (ptr_M10INI->StatusData.MaintenanceLimits[i] != 0))
            {

            }
        }
    }
}

