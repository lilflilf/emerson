#include "MODstart.h"
#include "MDefine.h"
#include "M10INI.h"
#include "M2010.h"
#include "M102IA.h"
#include "BransonSerial.h"
#include "ModRunSetup.h"
#include "Password.h"
#include "Statistics.h"
#include "M10runMode.h"
#include "Interface/Interface.h"
#include "UtilityClass.h"
#include <QString>
#include "windows.h"
#include <QCoreApplication>
#include <QObject>
#include <QSettings>
#include <QDir>
MODstart* MODstart::_instance = 0;
bool MODstart::Checkmaintenancelimit_EaWeld = false;
bool MODstart::ApplicationFirstStartFlag = false;
MODstart* MODstart::Instance()
{
    if(_instance == 0){
        _instance = new MODstart();
    }
    return _instance;
}

MODstart::MODstart()
{
    MDefine *_MDefine = MDefine::Instance();
    M10INI  *_M10INI  = M10INI::Instance();
    M2010   *_M2010   = M2010::Instance();
    M102IA  *_M102IA  = M102IA::Instance();
    M10runMode *_M10runMode = M10runMode::Instance();
    Statistics *_Statistics = Statistics::Instance();
    ModRunSetup *_ModRunSetup = ModRunSetup::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    int check_result = 0;

    App.Major    = "24";
    App.Minor    = "73";
    App.Revision = "815-Level1-T1";

    FirstScreenComesUp = false;
    _MDefine->ModeChangeFlag = false;
    _MDefine->WriteHistoryFlag = false;
    _MDefine->MessageFlag.DataGraphComplete = true;
    _MDefine->MessageFlag.EmergencyStopMessage = false;
    CheckBransonFolder(); //the routine checks whether Amtech folder exists on system drive or not
    _M10INI->Get_INI_File();
    CheckIOStatus();
    GlobalInitM10();
//    ptr_Statistics->start_data_structures();   //Initializes the stats bell curve only
    if (_Interface->StatusData.ComInfo.COMport == -1)
        check_result = 1;
    else
        check_result = CheckIOStatus();
    if (check_result == 1)
    {
        BransonMessageBox tmpMsgBox;
        tmpMsgBox.MsgPrompt = QObject::tr("Currently there is no New Wire Splicer Controller Online\n "
                                          "Do you want to work offline?");
        tmpMsgBox.MsgTitle = "Warning";
        tmpMsgBox.TipsMode = (OKCancel + Exclamation);
        tmpMsgBox.func_ptr = MODstart::OfflineInitialization;
        _Interface->cMsgBox(&tmpMsgBox);
    }
    else
    {
//        if (_Interface->StatusData.EnableModularFlag == true)
//        {
//            dlgSelectMode.Show vbModal
//        }
        _M102IA->SendIACommand(IAComgetActuator, 0);
        _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.ActuatorType);
        if(_M2010->ReceiveFlags.ActuatorType == true)
           _M2010->ReceiveFlags.ActuatorType = false;
        //Send command to get Controller Version string.
        _M102IA->SendIACommand(IAComGetControllerVer, 0);
        _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.ControllerVersionData);
        if(_M2010->ReceiveFlags.ControllerVersionData)
            _M2010->ReceiveFlags.ControllerVersionData = false;

        _M102IA->SendIACommand(IAComGetActuatorVer, 0);
        _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.ActuatorVersionData);
        if(_M2010->ReceiveFlags.ActuatorVersionData)
            _M2010->ReceiveFlags.ActuatorVersionData = false;

        _M102IA->SendIACommand(IAComGetActuatorPartNum, 0);
        _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.ActuatorPartNumData);
        if(_M2010->ReceiveFlags.ActuatorPartNumData)
            _M2010->ReceiveFlags.ActuatorPartNumData = false;

        _M102IA->SendIACommand(IAComGetActuatorSerialNum, 0);
        _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.ActuatorSerialNumData);
        if(_M2010->ReceiveFlags.ActuatorSerialNumData)
            _M2010->ReceiveFlags.ActuatorSerialNumData = false;

        _M102IA->IACommand(IAComSendPWRrating);
        _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.POWERrating);
        if (_M2010->ReceiveFlags.POWERrating)
        {
            _M2010->ReceiveFlags.POWERrating = false;
            _M10INI->Power_to_Watts = _Interface->StatusData.Soft_Settings.SonicGenWatts / 200;
            for(int i = 0; i <= 6; i++)
            {
                _M10INI->Pwr_Prefix_Data[i] = i * (int)(0.2 *
                    _Interface->StatusData.Soft_Settings.SonicGenWatts);
            }
        }
        _M102IA->IACommand(IAComSendHornAmplitude);
        _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.HORNamplitude);
        if(_M2010->ReceiveFlags.HORNamplitude == true)
            _M2010->ReceiveFlags.HORNamplitude = false;
        _M102IA->IACommand(IAComSendSonicHits);    //Always make this last, it terminates the watch loop
        _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.SonicHitsData);
        if (_M2010->ReceiveFlags.SonicHitsData)
            _M2010->ReceiveFlags.SonicHitsData = false;
        _M102IA->IACommand(IAComSendWeldData);
        _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.WELDdata);
        if (_M2010->ReceiveFlags.WELDdata)
            _M2010->ReceiveFlags.WELDdata = false;
        //Prepare Current VersaGraphics Version String.
        _Interface->CurrentVersions.SoftwareVersion = App.Major + "." + App.Minor + "." + App.Revision;

        //Current Version string of Controller code.
        _Interface->CurrentVersions.ControllerVersion = _M102IA->ContollerVersion;
        _Interface->CurrentVersions.ActuatorVersion = _M102IA->ActuatorVersion;
        //Check for any version mismatch.
        CheckVersionFile(_Interface->CurrentVersions);
        _M102IA->IACommand(IAComSetM10Mode);
        _ModRunSetup->OfflineModeEnabled = false;

        Update_from_StatusData_for_commands();
        _ModRunSetup->InitialStartFlag = true;
        ApplicationFirstStartFlag = true;
        _ModRunSetup->M10initiate();
        //Since Temporary Preset is lost at power up,this function deletes temporary Stat files if any
//        ptr_ModRunSetup->DeleteStatTempFiles();
        _M2010->load_splice_file();
        Checkmaintenancelimit_EaWeld = true;
        if(Checkmaintenancelimit_EaWeld == true)
        {
            _M10runMode->UpdateMaintenanceData();
            Checkmaintenancelimit_EaWeld = false;
        }
        _Statistics->UpdateSoftLimitData(false);
        //Open Ethernet serer
        if (_Interface->StatusData.NetworkingEnabled == true)
        {
//            AmtechServer.OpenEthernetserver();
        }
    }
}

void MODstart::Unload_Popups()
{

}

void MODstart::Update_from_StatusData_for_commands()
{
    // Sends status data to the controller at start up
    // Reads status data from status data structure and sends to controller
    int i;
    M2010 *_M2010 = M2010::Instance();
    M10INI *_M10INI = M10INI::Instance();
    M102IA *_M102IA = M102IA::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    _M2010->TempActuatorInfo.CurrentActuatorType = _Interface->StatusData.MachineType;
    _M2010->TempActuatorInfo.CurrentActuatorMode = _Interface->StatusData.ActuatorMode;
    _M2010->TempActuatorInfo.CurrentAntisideSpliceTime = _Interface->StatusData.AntisideSpliceTime;

    _M10INI->TempSysConfig.CoolingMode = _Interface->StatusData.CurrentCoolingMode;
    _M10INI->TempSysConfig.CoolingDur = _Interface->StatusData.CurrentCoolingDur;
    _M10INI->TempSysConfig.CoolingDel = _Interface->StatusData.CurrentCoolingDel;

    _M10INI->TempSysConfig.LockAlarm = _Interface->StatusData.LockonAlarm;
    _M10INI->TempSysConfig.CutoffMode = _Interface->StatusData.CutoffMode;
    _M10INI->TempSysConfig.RunMode = _Interface->StatusData.RunMode;

    _M10INI->TempMaintConfig.Amplitude = _Interface->StatusData.Soft_Settings.Horn_Calibrate;
    _M10INI->TempMaintConfig.GenPower = _Interface->StatusData.Soft_Settings.SonicGenWatts;
    _M10INI->TempMaintConfig.TunePoint = _Interface->StatusData.Soft_Settings.TunePoint;
    _M10INI->TempMaintConfig.FrequencyOffset = _Interface->StatusData.Soft_Settings.FrequencyOffset;

    for (i = 0; i <= 3; i++)
        _M10INI->TempSysConfig.Machineflags[i] = _Interface->StatusData.Machineflags[i];

    _M102IA->SendIACommand(IAComSetActuator, 0);
    _M102IA->SendIACommand(IAComSetCooling, 0);
    _M102IA->SendIACommand(IAComSetLockonAlarm, _M10INI->TempSysConfig.LockAlarm);
    _M102IA->SendIACommand(IAComSetCutoff, _M10INI->TempSysConfig.CutoffMode);
    _M102IA->SendIACommand(IAComGetRunModeNew, 0);
    _M2010->ReceiveFlags.FootPadelDATA = false;
    _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.FootPadelDATA);

    _Interface->StatusData.RunMode = _Interface->StatusData.RunMode | (_M10INI->TempSysConfig.RunMode & 0x1000);
    _M102IA->SendIACommand(IAComSetRunModeNew, _Interface->StatusData.RunMode);
    _M10INI->TempSysConfig.RunMode = _Interface->StatusData.RunMode;
    _M10INI->Save_StatusData(false);
    _M102IA->SendIACommand(IAComSetMachineFlags, 0);
    _M102IA->SendIACommand(IAComSetGenPower, _M10INI->TempMaintConfig.GenPower);
    _M102IA->SendIACommand(IAComSendHornAmplitude, _M10INI->TempMaintConfig.Amplitude);
    _M2010->ReceiveFlags.MAINTENANCEcounters = false;
    _M102IA->SendIACommand(IAComGetMaintCntr, 0);
    _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.MAINTENANCEcounters);
    if(_M2010->ReceiveFlags.MAINTENANCEcounters)
        _M2010->ReceiveFlags.MAINTENANCEcounters = false;
    _M102IA->SendIACommand(IAComGetCycleCntr, 0);
}

void MODstart::GlobalInitM10()
{
    //Initialize all global variables that can cause a problem if zero or false
    //Many of the setting are the default settings to keep the system from crashing at initial load

    int i;
    M2010 *ptr_M2010 = M2010::Instance();
    M10INI *ptr_M10INI = M10INI::Instance();
    M102IA *ptr_M102IA = M102IA::Instance();
    Password *ptr_Password = Password::Instance();
    UtilityClass *_Utility = UtilityClass::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    ptr_Password->SetPWPIMasks();
    ptr_M2010->M10Run.Auto_Set_Mode = false;
    ptr_M2010->M10Run.Load_From_Lib = false;
    ptr_M2010->M10Run.Initial_Startup = true;
    ptr_M2010->M10Run.Select_Part_file = false;
    ptr_M2010->M10Run.Select_Seq_file = false;
    ptr_M2010->M10Run.Alarm_found = false;
    ptr_M10INI->Power_to_Watts = _Interface->StatusData.Soft_Settings.SonicGenWatts / 200;
    _Utility->Maxpower = float(1.20 * _Interface->StatusData.Soft_Settings.SonicGenWatts);
    for (i = 0; i <= 6; i++)
        ptr_M10INI->Pwr_Prefix_Data[i] = i * float(0.2 * _Interface->StatusData.Soft_Settings.SonicGenWatts);

    //    PowerDataReady = False
    ptr_M10INI->ValidWeldData = false;
    ptr_M2010->MaintenceCounter = 0;
    ptr_M2010->MaintenceDueCounter = 0;
    ptr_M102IA->EnergyAccumulator = 0;
    ptr_M102IA->EnergyMaintenanceDue = 0;
    ptr_M2010->Shim1Val = 600;
    ptr_M2010->Shim2Val = 100;
}

void MODstart::GetSpliceFiles()
{

}

void MODstart::GetSequenceFiles()
{

}

/*********************************************************************/
/****************************FIXED************************************/
/*********************************************************************/
void MODstart::CheckBransonFolder()
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
        objDriveSystem.mkdir("c:\\BransonData\\History\\");
    }else{
        if (objDriveSystem.exists("c:\\BransonData\\History\\") == false)
           objDriveSystem.mkdir("c:\\BransonData\\History\\");

        if (objDriveSystem.exists("c:\\BransonData\\Library\\") == false)
           objDriveSystem.mkdir("c:\\BransonData\\Library\\");

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
//    FilePathQSTR = ptr_M10INI->ConfigFilesPath + Run_File_Name;
//    if (objDriveSystem.exists(FilePathQSTR) == false)
//    {
//       QFile FileNumber(FilePathQSTR);
//       FileNumber.open(QIODevice::ReadWrite);
//    }

    //delete temp files
    //if (objDriveSystem.exists("C:\\Documents and Settings\\Administrator\\Local Settings\\Temp\\*.TMP") == true)
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

int MODstart::CheckIOStatus()
{
    //Procedure to check the IO Status of the IA Controller
    string sTitle, sPrompt;
    //--Initialize the Function
    int FeedbackResult = 0;
    M2010         *_M2010  = M2010::Instance();
    M102IA        *_M102IA = M102IA::Instance();
//    ModRunSetup   *_ModRunSetup = ModRunSetup::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    BransonSerial *_Serial = BransonSerial::Instance();
    struct BransonMessageBox tmpMsgBox;


    //Check the COMport and do the appropriate thing
    _Serial->FindIAport();
    if (!_M2010->ReceiveFlags.IAFOUNDGOOD)
    {
        //--IA NOT ONLINE!, Communications ERROR
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("CONTROLLER NOT ONLINE!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
        FeedbackResult = 1;
        return FeedbackResult;
    }

    //--Get back the current I/O data!
    _M2010->ReceiveFlags.IOdata = false;
    _M102IA->IACommand(IAComSendIOdata);
    _Serial->SetCommandTimer(3000);
    while (_Serial->IsCommandTimeout() == false)
    {
        QCoreApplication::processEvents(); // Wait for response
        if (_M2010->ReceiveFlags.IOdata == true)
        {
            break;
        }
    }
    _Serial->ResetCommandTimer();
    //--Check to make sure that the Pressure Rating is O.K.
    if (_M102IA->IOstatus.IO & 0x08)
    {
        //--Check Line Pressure! , Pressure ERROR
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Check Line Pressure!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
        FeedbackResult = 1;
    }
    return FeedbackResult;
}

void MODstart::GetAuxillaryNamesToAuxNameArray()
{
//    Checks for AuxName.txt file if not present create one and writes default name strings  in it
//    string sFilePath, sTestPath, sTmpLine;
//    int iFileNumber, newFileNumber;
//    int Aux_Name_Index = Aux1;
//    sFilePath = ConfigFilesPath + "AuxName.txt";
//    QDir dir(QString::fromStdString(sFilePath));
//    if (dir.exists() == false)
//        GetDefaultNamesInAuxNameFile();


}

void MODstart::GetDefaultNamesInAuxNameFile()
{

}

void MODstart::ViewIPConfiguration()
{

}

void MODstart::SetDefaultIndicatorsForOperatorScreen()
{

}

void MODstart::StoreTopCoordinateCreateEditSpliceScreen()
{

}

//This function checks and retrieves the previous stored Versions of Controller
//and Versagraphix.It then compares the previous values to current ones,shows a
//pop up in case of different and finally stores the current Versions in a text file
void MODstart::CheckVersionFile(VersionList CurrVersions)
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    M10INI* _M10INI = M10INI::Instance();
    QString sPathName;
    bool Versionchanged = false;

    //Controller sends some fixed length string so it may have some garbage
    //values at the end of version number. Copy it to Vb6's Label controll
    //and vb will take care of it.
    sPathName = _M10INI->ConfigFilesPath + AVERSION_NUM_FILE;

    //Check if file exists, if not, create it.
    QDir dir;
    if (dir.exists(sPathName) == true)
    {
        // Get the previously stored version strings.
        QSettings settings(sPathName, QSettings::IniFormat);
        settings.beginGroup("Version");
        _Interface->PreviousVersions.SoftwareVersion =
                settings.value("PreviousSoftwareVersion").value<QString>();
        _Interface->PreviousVersions.ControllerVersion =
                settings.value("PreviousControllerVersion").value<QString>();
        _Interface->PreviousVersions.ActuatorVersion =
                settings.value("PreviousActuatorVersion").value<QString>();
        settings.endGroup();
    }

    struct BransonMessageBox tmpMsgBox;
    //Check for VersaGraphics Version change.
    if (_Interface->PreviousVersions.SoftwareVersion !=
            CurrVersions.SoftwareVersion)
    {
        Versionchanged = true;
        tmpMsgBox.MsgTitle = QObject::tr("Warning");
        tmpMsgBox.MsgPrompt = QObject::tr("VersaGraphix version has changed,check setup and calibration.");
        tmpMsgBox.TipsMode = Exclamation;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
    }

    //Check for Controller Version change.
    if (_Interface->PreviousVersions.ControllerVersion !=
            CurrVersions.ControllerVersion)
    {
        Versionchanged = true;
        tmpMsgBox.MsgTitle = QObject::tr("Warning");
        tmpMsgBox.MsgPrompt = QObject::tr("Controller version has changed,check setup and calibration.");
        tmpMsgBox.TipsMode = Exclamation;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
    }

    if (_Interface->PreviousVersions.ActuatorVersion !=
            CurrVersions.ActuatorVersion)
    {
        Versionchanged = true;
        Versionchanged = true;
        tmpMsgBox.MsgTitle = QObject::tr("Warning");
        tmpMsgBox.MsgPrompt = QObject::tr("Actuator version has changed,check setup and calibration.");
        tmpMsgBox.TipsMode = Exclamation;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
    }

    // Store the current version strings only if changed.
    if (Versionchanged == true)
    {
        QSettings settings(sPathName, QSettings::IniFormat);
        settings.beginGroup("Version");
        settings.setValue("PreviousSoftwareVersion", CurrVersions.SoftwareVersion);
        settings.setValue("PreviousControllerVersion", CurrVersions.ControllerVersion);
        settings.setValue("PreviousActuatorVersion", CurrVersions.ActuatorVersion);
        settings.endGroup();
    }
}

//This funciton only for the Offline Initialization in case of the controller is not detected
void MODstart::OfflineInitialization(void* ptr)
{
    ModRunSetup *_ModRunSetup = ModRunSetup::Instance();
//    M10INI *_M10INI = M10INI::Instance();
    M2010 *_M2010 = M2010::Instance();
    Statistics *_Statistics = Statistics::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _ModRunSetup->OfflineModeEnabled = true;
    _ModRunSetup->GlobalOfflineModeEnabled = true;

    bool bLoadFailed = false;
    bLoadFailed = false;

    _ModRunSetup->M10initiate(bLoadFailed);
    _M2010->load_splice_file(); // 2

    _Interface->StatusData.LockKeyFlag = false;

    _Statistics->UpdateSoftLimitData(false);
    //Open Ethernet serer
    if (_Interface->StatusData.NetworkingEnabled == true)
    {
//        AmtechServer.OpenEthernetserver();
    }
    ptr = NULL;
}
