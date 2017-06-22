#include "Interface.h"

#include "Modules/M10INI.h"
#include "Modules/M2010.h"
#include "Modules/M102IA.h"
#include "Modules/UtilityClass.h"
#include "Modules/M10runMode.h"
#include "Modules/typedef.h"
#include <QtConcurrent/QtConcurrent>
#include "windows.h"
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
    M102IA* _M102IA = M102IA::Instance();
    connect(_M102IA, SIGNAL(AlarmStatusSignal(bool&)),
            this,SLOT(AnyAlarmEventSlot(bool&)));
}

InterfaceClass::~InterfaceClass()
{

}

void InterfaceClass::CheckBransonFolder()
{
    //the routine checks if the required folders exist in the C drive of
    //the system.If not exist it would be created
    M10INI *ptr_M10INI = M10INI::Instance();
    ptr_M10INI->ConfigFilesPath = "c:\\BransonData\\etc\\";
    QDir objDriveSystem;
    if (objDriveSystem.exists("c:\\BransonData\\") == false)
    {
        objDriveSystem.mkdir("c:\\BransonData\\"); //Creates a new directory or folder.
        objDriveSystem.mkdir("c:\\BransonData\\Library\\");
        objDriveSystem.mkdir("c:\\BransonData\\Library\\SpliceImage\\");
        objDriveSystem.mkdir("c:\\BransonData\\Modular Production\\");
        objDriveSystem.mkdir("c:\\BransonData\\History\\");
        objDriveSystem.mkdir("c:\\BransonData\\History\\Graph\\");
    }else{
        if (objDriveSystem.exists("c:\\BransonData\\History\\") == false)
           objDriveSystem.mkdir("c:\\BransonData\\History\\");
        else
        {
            if(objDriveSystem.exists("c:\\BransonData\\History\\Graph") == false)
                objDriveSystem.mkdir("c:\\BransonData\\History\\Graph\\");
        }

        if (objDriveSystem.exists("c:\\BransonData\\Library\\") == false)
           objDriveSystem.mkdir("c:\\BransonData\\Library\\");
        else
        {
            if(objDriveSystem.exists("c:\\BransonData\\Library\\SpliceImage\\") == false)
                objDriveSystem.mkdir("c:\\BransonData\\Library\\SpliceImage\\");
        }
        if (objDriveSystem.exists("c:\\BransonData\\Modular Production\\") == false)
            objDriveSystem.mkdir("c:\\BransonData\\Modular Production\\");
        else
        {
            if(objDriveSystem.exists("c:\\BransonData\\Modular Production\\SpliceImage\\") == false)
                objDriveSystem.mkdir("c:\\BransonData\\Modular Production\\SpliceImage\\");
        }
//        if(objDriveSystem.exists("c:\\BransonData\\ToolChangeImage\\") == false)
//            objDriveSystem.mkdir("c:\\BransonData\\ToolChangeImage\\");

    }

    QString FilePathQSTR = ptr_M10INI->ConfigFilesPath;
    if (objDriveSystem.exists(FilePathQSTR) == false)
    {
        objDriveSystem.mkdir(FilePathQSTR);
        size_t size = ptr_M10INI->ConfigFilesPath.length();
        wchar_t *buffer = new wchar_t[size + 1];
        MultiByteToWideChar(CP_ACP,0,ptr_M10INI->ConfigFilesPath.toStdString().c_str(),size,buffer,size * sizeof(wchar_t));
        buffer[size] = 0; //to figure out the '\0' at the end of  array.
        SetFileAttributes(buffer,FILE_ATTRIBUTE_HIDDEN);
        delete []buffer;
    }
    QString strFilePath = "C:\\Users\\jerryw.wang\\AppData\\Local\\Temp\\";
    if(objDriveSystem.exists(strFilePath))
    {
        objDriveSystem.setPath(strFilePath);
        objDriveSystem.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        objDriveSystem.setSorting(QDir::Size | QDir::Reversed);
        QStringList filters;
        filters << "*.tmp";
        objDriveSystem.setNameFilters(filters);// to filter the specific file "*.tmp"
        QFileInfoList list = objDriveSystem.entryInfoList();
        if(list.size() > 0)
        {
            int i = 0;
            do{
                QFileInfo fileInfo = list.at(i);
                fileInfo.dir().remove(fileInfo.fileName());
                i++;
            }while(i < list.size());
        }
    }
}

void InterfaceClass::cMsgBox(struct BransonMessageBox* MsgBox)
{
    tmpMsgBox.MsgPrompt = MsgBox->MsgPrompt;
    tmpMsgBox.MsgTitle = MsgBox->MsgTitle;
    tmpMsgBox.TipsMode = MsgBox->TipsMode;
    tmpMsgBox.OKfunc_ptr = MsgBox->OKfunc_ptr;
    tmpMsgBox.Cancelfunc_ptr = MsgBox->Cancelfunc_ptr;
    tmpMsgBox._Object = MsgBox->_Object;
    emit EnableErrorMessageSignal(tmpMsgBox);
}

void InterfaceClass::DispearMsgBox()
{
    emit DisableErrorMessageSignal(tmpMsgBox);
}

void InterfaceClass::ShownAlarmSign()
{
    qDebug() << "ThereAreAlarmItemsSignal";
    emit ThereAreAlarmItemsSignal();
}

void InterfaceClass::UpdateAlarmList()
{
    qDebug() << "ThereAreSomeAlarmReseted";
    emit ThereAreSomeAlarmReseted();
}

//void InterfaceClass::dlgMaintWarning()
//{
//    M10INI *ptr_M10INI = M10INI::Instance();
//    for(int i = 0; i < 8; i++)
//    {
//        if(i <= 3)
//        {
//            if ((StatusData.CurrentMaintenanceLimits[i] >=
//                    StatusData.MaintenanceLimits[i]) &&
//                    (StatusData.MaintenanceLimits[i] != 0))
//            {

//            }

//        }
//        else{
//            if ((StatusData.CurrentMaintenanceLimits[i] >=
//              StatusData.MaintenanceLimits[i]) &&
//                (StatusData.MaintenanceLimits[i] != 0))
//            {

//            }
//        }
//    }
//}

//void InterfaceClass::BackupStatusData()
//{
//    M10INI* _M10INI = M10INI::Instance();
//    _M10INI->Save_StatusData();
//}

void InterfaceClass::AnyAlarmEventSlot(bool &bResult)
{
    UNUSED(bResult);
    M10runMode* _M10runMode = M10runMode::Instance();
    _M10runMode->CheckWeldData(-1);
//    DEBUG_PRINT("AnyAlarmEventSlot");
}

void InterfaceClass::LockOnAlarm()
{
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    int LockAlarm = 0;
    switch(CurrentOperator.PermissionLevel)
    {
    case OperatorElement::LEVEL1:
    case OperatorElement::LEVEL2:
    case OperatorElement::LEVEL3:
    case OperatorElement::LEVEL4:
        if((StatusData.PasswordData[CurrentOperator.PermissionLevel].PWPermissions & BIT25) == BIT25)
            LockAlarm = ON;
        else
            LockAlarm = OFF;
        break;
    case OperatorElement::PHYKEY:
    case OperatorElement::INITIAL:
    case OperatorElement::BRANSON:
        LockAlarm = OFF;
        break;
    default:
        LockAlarm = OFF;
        break;
    }
    qDebug()<<"Lock Alarm: "<<LockAlarm;
    qDebug()<<"StatusData.LockonAlarm"<< StatusData.LockonAlarm;
    if(LockAlarm != StatusData.LockonAlarm)
    {
        StatusData.LockonAlarm = LockAlarm;
        _M2010->ReceiveFlags.LockOnAlarmData = false;
        _M102IA->SendIACommand(IAComSetLockonAlarm, StatusData.LockonAlarm);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.LockOnAlarmData);
    }
}

void InterfaceClass::HotRestartSys(void *_Obj)
{
    UNUSED(_Obj);
    QString program = QCoreApplication::applicationFilePath();
    QStringList arguments = QCoreApplication::arguments();
    QString workingDirectory = QDir::currentPath();
    QProcess::startDetached(program, arguments, workingDirectory);
    QCoreApplication::exit();
}
