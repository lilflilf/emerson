#include "Interface.h"
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
    emit EnableErrorMessageSignal(tmpMsgBox);
}

void InterfaceClass::dlgMaintWarning()
{
    M10INI *ptr_M10INI = M10INI::Instance();
    for(int i = 0; i < 8; i++)
    {
        if(i <= 3)
        {
            if ((StatusData.CurrentMaintenanceLimits[i] >=
                    StatusData.MaintenanceLimits[i]) &&
                    (StatusData.MaintenanceLimits[i] != 0))
            {

            }

        }
        else{
            if ((StatusData.CurrentMaintenanceLimits[i] >=
              StatusData.MaintenanceLimits[i]) &&
                (StatusData.MaintenanceLimits[i] != 0))
            {

            }
        }
    }
}

void InterfaceClass::BackupStatusData()
{
    M10INI* _M10INI = M10INI::Instance();
    _M10INI->Save_StatusData();
}
