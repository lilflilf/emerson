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
#include "Interface/interface.h"
#include <QDir>
#include <QFile>
#include <QString>
#include "windows.h"
#include <QCoreApplication>
#include <QObject>
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
//    Dim ConfigFilesPath = App.Path & "\etc\"
    MDefine *ptr_MDefine = MDefine::Instance();
    M10INI  *ptr_M10INI  = M10INI::Instance();
    M2010   *ptr_M2010   = M2010::Instance();
    M102IA  *ptr_M102IA  = M102IA::Instance();
    M10runMode *ptr_M10runMode = M10runMode::Instance();
    Statistics *ptr_Statistics = Statistics::Instance();
    ModRunSetup *ptr_ModRunSetup = ModRunSetup::Instance();
    InterfaceClass *ptr_InterfaceClass = InterfaceClass::Instance();
    int check_result = 0;

    App.Major    = "24";
    App.Minor    = "73";
    App.Revision = "815-Level1-T1";

    FirstScreenComesUp = false;
    ptr_MDefine->ModeChangeFlag = false;
    ptr_MDefine->WriteHistoryFlag = false;
    ptr_MDefine->MessageFlag.DataGraphComplete = true;
    ptr_MDefine->MessageFlag.EmergencyStopMessage = false;
    CheckBransonFolder(); //the routine checks whether Amtech folder exists on system drive or not

//    ptr_M10INI->Get_INI_File();

    ptr_M2010->Prog_Mode = Splash_SCREEN;
    ptr_M2010->Child_Mode = No_SCREEN;
    ptr_M2010->InputBox_Mode = No_SCREEN;

    CheckIOStatus();

//    GlobalInitM10();

//    ptr_Statistics->start_data_structures();   //Initializes the stats bell curve only

    if (ptr_M10INI->StatusData.ComInfo.COMport == -1)
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
        ptr_InterfaceClass->cMsgBox(&tmpMsgBox);

    }
    else
    {
        ptr_M102IA->SendIACommand(IAComgetActuator, 0);
        if ((ptr_M10INI->StatusData.EnableModularFlag == true) ||
            (ptr_M10INI->StatusData.Enable2DBarcodeFlag == true))
        {
//            dlgSelectMode.Show vbModal
        }
        //Send command to get Controller Version string.
        ptr_M102IA->SendIACommand(IAComGetControllerVer, 0);
        ptr_M102IA->WaitForResponseAfterSent(3000, &ptr_M2010->ReceiveFlags.ControllerVersionData);
        if(ptr_M2010->ReceiveFlags.ControllerVersionData)
            ptr_M2010->ReceiveFlags.ControllerVersionData = false;

        ptr_M102IA->SendIACommand(IAComGetActuatorVer, 0);
        ptr_M102IA->WaitForResponseAfterSent(3000, &ptr_M2010->ReceiveFlags.ActuatorVersionData);
        if(ptr_M2010->ReceiveFlags.ActuatorVersionData)
            ptr_M2010->ReceiveFlags.ActuatorVersionData = false;

        ptr_M102IA->SendIACommand(IAComGetActuatorPartNum, 0);
        ptr_M102IA->WaitForResponseAfterSent(3000, &ptr_M2010->ReceiveFlags.ActuatorPartNumData);
        if(ptr_M2010->ReceiveFlags.ActuatorPartNumData)
            ptr_M2010->ReceiveFlags.ActuatorPartNumData = false;

        ptr_M102IA->SendIACommand(IAComGetActuatorSerialNum, 0);
        ptr_M102IA->WaitForResponseAfterSent(3000, &ptr_M2010->ReceiveFlags.ActuatorSerialNumData);
        if(ptr_M2010->ReceiveFlags.ActuatorSerialNumData)
            ptr_M2010->ReceiveFlags.ActuatorSerialNumData = false;

        ptr_M102IA->IACommand(IAComSendPWRrating);
        ptr_M102IA->WaitForResponseAfterSent(3000, &ptr_M2010->ReceiveFlags.POWERrating);
        if (ptr_M2010->ReceiveFlags.POWERrating)
        {
            ptr_M2010->ReceiveFlags.POWERrating = false;
            ptr_M10INI->Power_to_Watts = ptr_M10INI->StatusData.Soft_Settings.SonicGenWatts / 200;
            for(int i = 0; i <= 6; i++)
            {
                ptr_M10INI->Pwr_Prefix_Data[i] = i * (int)(0.2 *
                    ptr_M10INI->StatusData.Soft_Settings.SonicGenWatts);
            }
        }

        ptr_M102IA->IACommand(IAComSendHornAmplitude);
        ptr_M102IA->WaitForResponseAfterSent(3000, &ptr_M2010->ReceiveFlags.HORNamplitude);
        if(ptr_M2010->ReceiveFlags.HORNamplitude == true)
            ptr_M2010->ReceiveFlags.HORNamplitude = false;


        ptr_M102IA->IACommand(IAComSendSonicHits);    //Always make this last, it terminates the watch loop
        ptr_M102IA->WaitForResponseAfterSent(3000, &ptr_M2010->ReceiveFlags.SonicHitsData);
        if (ptr_M2010->ReceiveFlags.SonicHitsData)
            ptr_M2010->ReceiveFlags.SonicHitsData = false;

        ptr_M102IA->IACommand(IAComSendWeldData);
        ptr_M102IA->WaitForResponseAfterSent(3000, &ptr_M2010->ReceiveFlags.WELDdata);
        if (ptr_M2010->ReceiveFlags.WELDdata)
            ptr_M2010->ReceiveFlags.WELDdata = false;

        //Prepare Current VersaGraphics Version String.
        ptr_M2010->CurrentVersions.SoftVersion = App.Major + "." + App.Minor + "." + App.Revision;

        //Current Version string of Controller code.
        ptr_M2010->CurrentVersions.ControllerVersion = ptr_M102IA->ContollerVersion;
        //Check for any version mismatch.
        CheckVersionFile(ptr_M2010->CurrentVersions);

        ptr_M102IA->IACommand(IAComSetM10Mode);
        ptr_ModRunSetup->OfflineModeEnabled = false;

        Update_from_StatusData_for_commands();
        ptr_ModRunSetup->InitialStartFlag = true;
        ApplicationFirstStartFlag = true;
        ptr_ModRunSetup->M10initiate();
        //Since Temporary Preset is lost at power up,this function deletes temporary Stat files if any
//        ptr_ModRunSetup->DeleteStatTempFiles();
        ptr_M2010->load_splice_file();
        Checkmaintenancelimit_EaWeld = true;
        if(Checkmaintenancelimit_EaWeld == true)
        {
            ptr_M10runMode->UpdateMaintenanceData();
            Checkmaintenancelimit_EaWeld = false;
        }
        ptr_Statistics->UpdateSoftLimitData(false);
        //Open Ethernet serer
        if (ptr_M10INI->StatusData.NetworkingEnabled == true)
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
    M2010 *ptr_M2010 = M2010::Instance();
    M10INI *ptr_M10INI = M10INI::Instance();
    M102IA *ptr_M102IA = M102IA::Instance();
    BransonSerial *ptr_Serial = BransonSerial::Instance();
    ModRunSetup   *ptr_ModRunSetup = ModRunSetup::Instance();
    ptr_M2010->TempActuatorInfo.CurrentActuatorType = ptr_M10INI->StatusData.MachineType;
    ptr_M2010->TempActuatorInfo.CurrentActuatorMode = ptr_M10INI->StatusData.ActuatorMode;
    ptr_M2010->TempActuatorInfo.CurrentAntisideSpliceTime = ptr_M10INI->StatusData.AntisideSpliceTime;

    ptr_M10INI->TempSysConfig.CoolingMode = ptr_M10INI->StatusData.CurrentCoolingMode;
    ptr_M10INI->TempSysConfig.CoolingDur = ptr_M10INI->StatusData.CurrentCoolingDur;
    ptr_M10INI->TempSysConfig.CoolingDel = ptr_M10INI->StatusData.CurrentCoolingDel;

    ptr_M10INI->TempSysConfig.LockAlarm = ptr_M10INI->StatusData.LockonAlarm;
    ptr_M10INI->TempSysConfig.CutoffMode = ptr_M10INI->StatusData.CutoffMode;
    ptr_M10INI->TempSysConfig.RunMode = ptr_M10INI->StatusData.RunMode;

    ptr_M10INI->TempMaintConfig.Amplitude = ptr_M10INI->StatusData.Soft_Settings.Horn_Calibrate;
    ptr_M10INI->TempMaintConfig.GenPower = ptr_M10INI->StatusData.Soft_Settings.SonicGenWatts;
    ptr_M10INI->TempMaintConfig.TunePoint = ptr_M10INI->StatusData.Soft_Settings.TunePoint;
    ptr_M10INI->TempMaintConfig.FrequencyOffset = ptr_M10INI->StatusData.Soft_Settings.FrequencyOffset;

    for (i = 0; i <= 3; i++)
        ptr_M10INI->TempSysConfig.Machineflags[i] = ptr_M10INI->StatusData.Machineflags[i];

    ptr_M102IA->SendIACommand(IAComSetActuator, 0);
    ptr_M102IA->SendIACommand(IAComSetCooling, 0);
    ptr_M102IA->SendIACommand(IAComSetLockonAlarm, ptr_M10INI->TempSysConfig.LockAlarm);
    ptr_M102IA->SendIACommand(IAComSetCutoff, ptr_M10INI->TempSysConfig.CutoffMode);
    ptr_M102IA->SendIACommand(IAComGetRunModeNew, 0);
    ptr_M2010->ReceiveFlags.FootPadelDATA = false;
    ptr_M102IA->WaitForResponseAfterSent(3000, &ptr_M2010->ReceiveFlags.FootPadelDATA);

    ptr_M10INI->StatusData.RunMode = ptr_M10INI->StatusData.RunMode | (ptr_M10INI->TempSysConfig.RunMode & 0x1000);
    ptr_M102IA->SendIACommand(IAComSetRunModeNew, ptr_M10INI->StatusData.RunMode);
    ptr_M10INI->TempSysConfig.RunMode = ptr_M10INI->StatusData.RunMode;
    ptr_M10INI->Save_StatusData(false);
    ptr_M102IA->SendIACommand(IAComSetMachineFlags, 0);
    ptr_M102IA->SendIACommand(IAComSetGenPower, ptr_M10INI->TempMaintConfig.GenPower);
    ptr_M102IA->SendIACommand(IAComSendHornAmplitude, ptr_M10INI->TempMaintConfig.Amplitude);
    ptr_M2010->ReceiveFlags.MAINTENANCEcounters = false;
    ptr_M102IA->SendIACommand(IAComGetMaintCntr, 0);
    ptr_M102IA->WaitForResponseAfterSent(3000, &ptr_M2010->ReceiveFlags.MAINTENANCEcounters);
    if(ptr_M2010->ReceiveFlags.MAINTENANCEcounters)
        ptr_M2010->ReceiveFlags.MAINTENANCEcounters = false;
    ptr_M102IA->SendIACommand(IAComGetCycleCntr, 0);   
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
    ptr_Password->SetPWPIMasks();
    ptr_M2010->M10Run.Auto_Set_Mode = false;
    ptr_M2010->M10Run.Load_From_Lib = false;
    ptr_M2010->M10Run.Initial_Startup = true;
    ptr_M2010->M10Run.Select_Part_file = false;
    ptr_M2010->M10Run.Select_Seq_file = false;
    ptr_M2010->M10Run.Alarm_found = false;
    ptr_M10INI->Power_to_Watts = ptr_M10INI->StatusData.Soft_Settings.SonicGenWatts / 200;
    ptr_M2010->Maxpower = int(1.2 * ptr_M10INI->StatusData.Soft_Settings.SonicGenWatts);
    for (i = 0; i <= 6; i++)
        ptr_M10INI->Pwr_Prefix_Data[i] = i * int(0.2 * ptr_M10INI->StatusData.Soft_Settings.SonicGenWatts);

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
    int FileNumber;
    ptr_M10INI->ConfigFilesPath = "c:\\Branson\\etc\\";
    QDir objDriveSystem;
    if (objDriveSystem.exists("c:\\BransonData\\") == false)
    {
        objDriveSystem.mkdir("c:\\BransonData\\"); //Creates a new directory or folder.
        objDriveSystem.mkdir("c:\\BransonData\\Library\\");
        objDriveSystem.mkdir("c:\\BransonData\\History\\");
    }else{
        if (objDriveSystem.exists("c:\\AmtData\\History\\") == false)
           objDriveSystem.mkdir("c:\\AmtData\\History\\");

        if (objDriveSystem.exists("c:\\AmtData\\Library\\") == false)
           objDriveSystem.mkdir("c:\\AmtData\\Library\\");

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
    FilePathQSTR = ptr_M10INI->ConfigFilesPath + Run_File_Name;
    if (objDriveSystem.exists(FilePathQSTR) == false)
    {
       QFile FileNumber(FilePathQSTR);
       FileNumber.open(QIODevice::ReadWrite);
    }

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
    M2010         *ptr_M2010  = M2010::Instance();
    M102IA        *ptr_M102IA = M102IA::Instance();
    ModRunSetup   *ptr_ModRunSetup = ModRunSetup::Instance();
    InterfaceClass *ptr_InterfaceClass = InterfaceClass::Instance();
    BransonSerial *ptr_Serial = BransonSerial::Instance();
    struct BransonMessageBox tmpMsgBox;


    //Check the COMport and do the appropriate thing
    ptr_Serial->FindIAport();
    if (!ptr_M2010->ReceiveFlags.IAFOUNDGOOD)
    {
        //--IA NOT ONLINE!, Communications ERROR
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("CONTROLLER NOT ONLINE!");
        FeedbackResult = 1;
        return FeedbackResult;
    }

    //--Get back the current I/O data!
    ptr_M102IA->IACommand(IAComSendIOdata);
    ptr_M102IA->WaitForResponseAfterSent(3000, &ptr_M2010->ReceiveFlags.IOdata);

    //--Check to make sure that the Pressure Rating is O.K.
    if (ptr_M102IA->IOstatus.IO & 0x08)
    {
        //--Check Line Pressure! , Pressure ERROR
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Check Line Pressure!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.func_ptr = NULL;
        ptr_InterfaceClass->cMsgBox(&tmpMsgBox);
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

}

//This funciton only for the Offline Initialization in case of the controller is not detected
void MODstart::OfflineInitialization(void* ptr)
{
    ModRunSetup *ptr_ModRunSetup = ModRunSetup::Instance();
    M10INI *ptr_M10INI = M10INI::Instance();
    M2010 *ptr_M2010 = M2010::Instance();
    Statistics *ptr_Statistics = Statistics::Instance();
    ptr_ModRunSetup->OfflineModeEnabled = true;
    ptr_ModRunSetup->GlobalOfflineModeEnabled = true;

    bool bLoadFailed = false;
    bLoadFailed = false;

    ptr_ModRunSetup->M10initiate(bLoadFailed);
    ptr_M2010->load_splice_file(); // 2

    ptr_M10INI->StatusData.LockKeyFlag = false;

    ptr_Statistics->UpdateSoftLimitData(false);
    //Open Ethernet serer
    if (ptr_M10INI->StatusData.NetworkingEnabled == true)
    {
//        AmtechServer.OpenEthernetserver();
    }
}
