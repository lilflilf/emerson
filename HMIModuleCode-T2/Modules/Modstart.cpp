#include "MODstart.h"
#include "MDefine.h"
#include "M10INI.h"
#include "M2010.h"
#include "M102IA.h"
#include "BransonSerial.h"
#include "BransonServer.h"
#include "ModRunSetup.h"
#include "Password.h"
#include "Statistics.h"
#include "M10runMode.h"
#include "Interface/Interface.h"
#include "UtilityClass.h"
#include "TimerClass.h"
#include "DataBase/DBHarnessTable.h"
#include "DataBase/DBPresetTable.h"
#include "DataBase/DBWireTable.h"
#include "typedef.h"
#include <QString>
#include <QCoreApplication>
#include <QObject>
#include <QSettings>
#include <QDir>
#include <QDebug>
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
//    M10runMode *_M10runMode = M10runMode::Instance();
    ModRunSetup*    _ModRunSetup  = ModRunSetup::Instance();
    InterfaceClass* _Interface    = InterfaceClass::Instance();
    BransonServer*  _Server       = BransonServer::Instance();
    DBHarnessTable* _HarnessTable = DBHarnessTable::Instance();
    DBPresetTable*  _SpliceTable  = DBPresetTable::Instance();
    DBWireTable*    _WireTable    = DBWireTable::Instance();

    int check_result = 0;

    App.Major    = "26";
    App.Minor    = "73";
    App.Revision = "814-L2-T7";

    _Interface->FirstScreenComesUp = false;
    _MDefine->ModeChangeFlag = false;
    _MDefine->WriteHistoryFlag = false;
    _MDefine->MessageFlag.DataGraphComplete = true;
    _MDefine->MessageFlag.EmergencyStopMessage = false;
    GlobalInitM10();
    CheckIOStatus();
    if (_Interface->StatusData.ComInfo.COMport == -1)
        check_result = 1;
    else
        check_result = CheckIOStatus();
    if (check_result == 1)
    {
        BransonMessageBox tmpMsgBox;
        tmpMsgBox.MsgPrompt = QObject::tr("Currently, there is no New Wire Splicer Controller Online\n "
                                          "Do you want to work offline?");
        tmpMsgBox.MsgTitle = QObject::tr("Warning");
        tmpMsgBox.TipsMode = (OKCancel + OFF_ON_LINE + Exclamation);
        tmpMsgBox.OKfunc_ptr = MODstart::OfflineInitialization;
        tmpMsgBox.Cancelfunc_ptr = NULL;
        tmpMsgBox._Object = this;
        _Interface->cMsgBox(&tmpMsgBox);
    }
    else
    {
//        if (_Interface->StatusData.EnableModularFlag == true)
//        {
//            dlgSelectMode.Show vbModal
//        }
        _M2010->ReceiveFlags.ActuatorType = false;
        _M102IA->IACommand(IAComGetActuator);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.ActuatorType);
//        DEBUG_PRINT(_M2010->ReceiveFlags.ActuatorType);

        //Send command to get Controller Version string.
        _M2010->ReceiveFlags.ControllerVersionData = false;
        _M102IA->IACommand(IAComGetControllerVer);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.ControllerVersionData);
//        DEBUG_PRINT(_M2010->ReceiveFlags.ControllerVersionData);

        _M2010->ReceiveFlags.ActuatorVersionData = false;
        _M102IA->IACommand(IAComGetActuatorVer);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.ActuatorVersionData);
//        DEBUG_PRINT(_M2010->ReceiveFlags.ActuatorVersionData);

        _M2010->ReceiveFlags.ActuatorPartNumData = false;
        _M102IA->IACommand(IAComGetActuatorPartNum);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.ActuatorPartNumData);
//        DEBUG_PRINT(_M2010->ReceiveFlags.ActuatorPartNumData);

        _M2010->ReceiveFlags.ActuatorSerialNumData = false;
        _M102IA->IACommand(IAComGetActuatorSerialNum);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.ActuatorSerialNumData);
//        DEBUG_PRINT(_M2010->ReceiveFlags.ActuatorPartNumData);

        _M2010->ReceiveFlags.SNdata = false;
        _M102IA->IACommand(IAComGetSerialNumber);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.SNdata);
//        DEBUG_PRINT(_M2010->ReceiveFlags.SNdata);

        _M2010->ReceiveFlags.PNData = false;
        _M102IA->IACommand(IAComGetPartNumber);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.PNData);
//        DEBUG_PRINT(_M2010->ReceiveFlags.PNData);

        _M2010->ReceiveFlags.POWERrating = false;
        _M102IA->IACommand(IAComSendPWRrating);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.POWERrating);
//        DEBUG_PRINT(_M2010->ReceiveFlags.POWERrating);
        if (_M2010->ReceiveFlags.POWERrating == true)
        {
            _M2010->ReceiveFlags.POWERrating = false;
            _M10INI->Power_to_Watts = (float)_Interface->StatusData.Soft_Settings.SonicGenWatts / POWERFACTOR;
            for(int i = 0; i <= 6; i++)
            {
                _M10INI->Pwr_Prefix_Data[i] = i * (int)(0.2 *
                    _Interface->StatusData.Soft_Settings.SonicGenWatts);
            }
        }
        _M2010->ReceiveFlags.HORNamplitude = false;
        _M102IA->IACommand(IAComSendHornAmplitude);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.HORNamplitude);
//        DEBUG_PRINT(_M2010->ReceiveFlags.HORNamplitude);

        _M2010->ReceiveFlags.CycleCountData = false;
        _M102IA->IACommand(IAComGetCycleCntr);    //Always make this last, it terminates the watch loop
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.CycleCountData);
//        DEBUG_PRINT(_M2010->ReceiveFlags.CycleCountData);

        _M2010->ReceiveFlags.AlarmData = false;
        _M102IA->IACommand(IAComGetAlarmData);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.AlarmData);
//        DEBUG_PRINT(_M2010->ReceiveFlags.AlarmData);

//        _M2010->ReceiveFlags.WELDdata = false;
//        _M102IA->IACommand(IAComSendWeldData);
//        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.WELDdata);

        _M2010->ReceiveFlags.CoolingTypeData = false;
        _M102IA->IACommand(IAComGetCooling);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.CoolingTypeData);
//        DEBUG_PRINT(_M2010->ReceiveFlags.CoolingTypeData);

        _M2010->ReceiveFlags.LockOnAlarmData = false;
        _M102IA->IACommand(IAComGetLockonAlarm);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.LockOnAlarmData);
//        DEBUG_PRINT(_M2010->ReceiveFlags.LockOnAlarmData);

        _M2010->ReceiveFlags.FootPadelDATA = false;
        _M102IA->IACommand(IAComGetRunModeNew);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.FootPadelDATA);
        _Interface->StatusData.RunMode.Word &= 0xF800;
//        DEBUG_PRINT(_M2010->ReceiveFlags.FootPadelDATA);

        _M2010->ReceiveFlags.MachineFlagsData = false;
        _M102IA->IACommand(IAComGetMachineFlags);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.MachineFlagsData);
//        DEBUG_PRINT(_M2010->ReceiveFlags.MachineFlagsData);

        _M2010->ReceiveFlags.CutterResponseData = false;
        _M102IA->IACommand(IAComGetCutoff);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.CutterResponseData);
//        DEBUG_PRINT(_M2010->ReceiveFlags.CutterResponseData);

        _M2010->ReceiveFlags.TunePointData = false;
        _M102IA->IACommand(IAComGetTunePoint);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.TunePointData);
//        DEBUG_PRINT(_M2010->ReceiveFlags.TunePointData);

        _M2010->ReceiveFlags.FreqOffsetData = false;
        _M102IA->IACommand(IAComGetFrequencyOffset);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.FreqOffsetData);
//        DEBUG_PRINT(_M2010->ReceiveFlags.FreqOffsetData);

        _M2010->ReceiveFlags.PhysicalKeyData = false;
        _M102IA->IACommand(IAComGetPhysicalKey);
        _M102IA->WaitForResponseAfterSent(DELAY3SEC, &_M2010->ReceiveFlags.PhysicalKeyData);
//        DEBUG_PRINT(_M2010->ReceiveFlags.PhysicalKeyData);

        //Prepare Current VersaGraphics Version String.
        _Interface->CurrentVersions.SoftwareVersion = App.Major + "." + App.Minor + "." + App.Revision;

        //Current Version string of Controller code.
        _Interface->CurrentVersions.ControllerVersion = _M102IA->ContollerVersion;
        _Interface->CurrentVersions.ActuatorVersion = _M102IA->ActuatorVersion;

        _Interface->StatusData.PSPartNumber = _M102IA->PartNoData;
        _Interface->StatusData.PSSerialNumber = _M102IA->SerialNoData;

        _Interface->StatusData.ActuatorVersion = _M102IA->ActuatorVersion;
        _Interface->StatusData.ActuatorPartNumber = _M102IA->ActuatorPartNum;
        _Interface->StatusData.ActuatorSerialNumber = _M102IA->ActuatorSerialNum;
        //Check for any version mismatch.
        CheckVersionFile(_Interface->CurrentVersions);
        _M102IA->IACommand(IAComSetM10Mode);
        _ModRunSetup->OfflineModeEnabled = false;

//        Update_from_StatusData_for_commands();

        switch(_Interface->StatusData.MachineType)
        {
        case ACTULTRA20:
        case ACTULTRA40:
        case ACTMTS20:
        case ACTGUN40:
            _M2010->Machine = Welder;
            break;
        default:
            _M2010->Machine = WireSplicer;
            break;
        }

        _ModRunSetup->InitialStartFlag = true;
        ApplicationFirstStartFlag = true;
        //Since Temporary Preset is lost at power up,this function deletes temporary Stat files if any
//        ptr_ModRunSetup->DeleteStatTempFiles();
        _M2010->load_splice_file();
        Checkmaintenancelimit_EaWeld = true;
        if(Checkmaintenancelimit_EaWeld == true)
        {
//            _M10runMode->UpdateMaintenanceData();
            Checkmaintenancelimit_EaWeld = false;
        }
        //Open Ethernet serer
        if (_Interface->StatusData.NetworkingEnabled == true)
        {
            _Server->OpenEthernetServer();
        }
        if (_Interface->StatusData.ModularProductionEnabled == true)
        {
            _HarnessTable->SwitchDBObject(_Interface->StatusData.ModularProductionEnabled);
            _SpliceTable->SwitchDBObject(_Interface->StatusData.ModularProductionEnabled);
            _WireTable->SwitchDBObject(_Interface->StatusData.ModularProductionEnabled);
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
    _M10INI->TempSysConfig.CutoffMode = _Interface->StatusData.CutOffOption.CutOff;
    _M10INI->TempSysConfig.RunMode = _Interface->StatusData.RunMode.Word;

    _M10INI->TempMaintConfig.Amplitude = _Interface->StatusData.Soft_Settings.Horn_Calibrate;
    _M10INI->TempMaintConfig.GenPower = _Interface->StatusData.Soft_Settings.SonicGenWatts;
    _M10INI->TempMaintConfig.TunePoint = _Interface->StatusData.Soft_Settings.TunePoint;
    _M10INI->TempMaintConfig.FrequencyOffset = _Interface->StatusData.Soft_Settings.FrequencyOffset;

    for (i = 0; i <= 3; i++)
        _M10INI->TempSysConfig.Machineflags[i] = _Interface->StatusData.Machineflags.Word[i];

//    _M102IA->SendIACommand(IAComSetActuator, 0);
    _M102IA->SendIACommand(IAComSetCooling, 0);
    _M102IA->SendIACommand(IAComSetLockonAlarm, _M10INI->TempSysConfig.LockAlarm);
    _M102IA->SendIACommand(IAComSetCutoff, _M10INI->TempSysConfig.CutoffMode);

    _M2010->ReceiveFlags.FootPadelDATA = false;
    _M102IA->SendIACommand(IAComGetRunModeNew, 0);
    _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.FootPadelDATA);

    _Interface->StatusData.RunMode.Word =
            _Interface->StatusData.RunMode.Word | (_M10INI->TempSysConfig.RunMode & 0x1000);
    _M102IA->SendIACommand(IAComSetRunModeNew, _Interface->StatusData.RunMode.Word);
    _M10INI->TempSysConfig.RunMode = _Interface->StatusData.RunMode.Word;
    _M10INI->Save_StatusData(false);
    _M102IA->SendIACommand(IAComSetMachineFlags, 0);
    _M102IA->SendIACommand(IAComSetGenPower, _M10INI->TempMaintConfig.GenPower);
    _M102IA->SendIACommand(IAComSendHornAmplitude, _M10INI->TempMaintConfig.Amplitude);
    _M2010->ReceiveFlags.MAINTENANCEcounters = false;
    _M102IA->SendIACommand(IAComGetMaintCntr, 0);
    _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.MAINTENANCEcounters);

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
//    Password *ptr_Password = Password::Instance();
    UtilityClass *_Utility = UtilityClass::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    ptr_M2010->M10Run.Auto_Set_Mode = false;
    ptr_M2010->M10Run.Load_From_Lib = false;
    ptr_M2010->M10Run.Initial_Startup = true;
    ptr_M2010->M10Run.Select_Part_file = false;
    ptr_M2010->M10Run.Select_Seq_file = false;
    ptr_M2010->M10Run.Alarm_found = false;
    ptr_M10INI->Power_to_Watts = (float)_Interface->StatusData.Soft_Settings.SonicGenWatts / POWERFACTOR;
    _Utility->Maxpower = (float)(1.2 * _Interface->StatusData.Soft_Settings.SonicGenWatts);
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

int MODstart::CheckIOStatus()
{
    //Procedure to check the IO Status of the IA Controller
    string sTitle, sPrompt;
    //--Initialize the Function
    int FeedbackResult = 0;
    M2010         *_M2010  = M2010::Instance();
    M102IA        *_M102IA = M102IA::Instance();
    TimerClass *_Timer = new TimerClass();
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
        tmpMsgBox.OKfunc_ptr = NULL;
        tmpMsgBox.Cancelfunc_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
        FeedbackResult = 1;
        return FeedbackResult;
    }

    //--Get back the current I/O data!
    _M2010->ReceiveFlags.IOdata = false;
    _M102IA->IACommand(IAComSendIOdata);
    _Timer->SetCommandTimer(DELAY3SEC);
    while (_Timer->IsCommandTimeout() == false)
    {
        QCoreApplication::processEvents(); // Wait for response
        if (_M2010->ReceiveFlags.IOdata == true)
        {
            break;
        }
    }
    _Timer->ResetCommandTimer();
    delete _Timer;
    //--Check to make sure that the Pressure Rating is O.K.
    if (_M102IA->IOstatus.IO & 0x08)
    {
        //--Check Line Pressure! , Pressure ERROR
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Check Line Pressure!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.OKfunc_ptr = NULL;
        tmpMsgBox.Cancelfunc_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
        FeedbackResult = 1;
    }
    return FeedbackResult;
}

void MODstart::ViewIPConfiguration()
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
    sPathName = _M10INI->ConfigFilesPath + VERSION_NUM_FILE;

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
        tmpMsgBox.OKfunc_ptr = NULL;\
        tmpMsgBox.Cancelfunc_ptr = NULL;
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
        tmpMsgBox.OKfunc_ptr = NULL;
        tmpMsgBox.Cancelfunc_ptr = NULL;
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
        tmpMsgBox.OKfunc_ptr = NULL;
        tmpMsgBox.Cancelfunc_ptr = NULL;
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
    qDebug() << "OfflineInitialization";
    MODstart *_MODstart = (MODstart*)ptr;
    ModRunSetup *_ModRunSetup = ModRunSetup::Instance();
//    M10INI *_M10INI = M10INI::Instance();
    M2010 *_M2010 = M2010::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    BransonServer* _Server = BransonServer::Instance();
    DBHarnessTable* _HarnessTable = DBHarnessTable::Instance();
    DBPresetTable* _SpliceTable = DBPresetTable::Instance();
    DBWireTable* _WireTable = DBWireTable::Instance();
    _ModRunSetup->OfflineModeEnabled = true;
    _ModRunSetup->GlobalOfflineModeEnabled = true;

    _M2010->load_splice_file(); // 2

    _Interface->StatusData.LockKeyFlag = false;
    //Prepare Current VersaGraphics Version String.
    _Interface->CurrentVersions.SoftwareVersion
            = _MODstart->App.Major + "."
            + _MODstart->App.Minor + "."
            + _MODstart->App.Revision;

    //Open Ethernet serer
    if (_Interface->StatusData.NetworkingEnabled == true)
    {
        _Server->OpenEthernetServer();
    }
    if (_Interface->StatusData.ModularProductionEnabled == true)
    {
        _HarnessTable->SwitchDBObject(_Interface->StatusData.ModularProductionEnabled);
        _SpliceTable->SwitchDBObject(_Interface->StatusData.ModularProductionEnabled);
        _WireTable->SwitchDBObject(_Interface->StatusData.ModularProductionEnabled);
    }
    ptr = NULL;
}
