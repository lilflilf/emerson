#include "Calibration.h"
#include "Modules/M102IA.h"
#include "Modules/M2010.h"
#include "Modules/ModRunSetup.h"
#include "Interface/Interface.h"
#include "AdvancedMaintenance.h"
#include "MaintenanceLog.h"
#include "DataBase/DBMaintenanceLogTable.h"
#include "Modules/typedef.h"
#include <QDateTime>
#include <QDebug>
Calibration::Calibration()
{
    CalbCount = 0;
    CalStarted = false;
}

bool Calibration::CloseSafetyGuard()
{
    bool bResult = true;
    M102IA* _M102IA = M102IA::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    M2010* _M2010 = M2010::Instance();
    DBMaintenanceLogTable* _MaintenanceLogTable = DBMaintenanceLogTable::Instance();
    MaintenanceLogElement MaintenanceLog;
    MaintenanceLog.MaintenanceType = MaintenanceTypeString[CALIBRATE];
    MaintenanceLog.OperatorID = _Interface->CurrentOperator.OperatorID;
    MaintenanceLog.CreatedDate = QDateTime::currentDateTime().toTime_t();
    struct BransonMessageBox tmpMsgBox;
    if((_Interface->StatusData.MachineType == ACT2032) ||
            (_Interface->StatusData.MachineType == ACTNEWSPLICER))
    {
        _M102IA->SendIACommand(IAComAuxMotion, DO_CLOSE_SAFETY);
        bool bResult = false;
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[CALIBRATE_W_H_START];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
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
                MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[CALIBRATE_W_H_FALSE];
                _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
            }
        }
        if(bResult == true)
            _M102IA->SendIACommand(IAComAuxMotion, DO_OPEN_CLAMP);
    }
    return bResult;
}

void Calibration::OpenSafetyGuard()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    M102IA* _M102IA = M102IA::Instance();
    DBMaintenanceLogTable* _MaintenanceLogTable = DBMaintenanceLogTable::Instance();
    MaintenanceLogElement MaintenanceLog;
    MaintenanceLog.MaintenanceType = MaintenanceTypeString[CALIBRATE];
    MaintenanceLog.OperatorID = _Interface->CurrentOperator.OperatorID;
    MaintenanceLog.CreatedDate = QDateTime::currentDateTime().toTime_t();
    if((_Interface->StatusData.MachineType == ACT2032) ||
            (_Interface->StatusData.MachineType == ACTNEWSPLICER))
    {
        _M102IA->SendIACommand(IAComAuxMotion, DO_OPEN_SAFETY);
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[CALIBRATE_W_H_CANCEL];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
    }
}

bool Calibration::_start()
{
    CloseSafetyGuard();
    return true;
}

bool Calibration::_stop()
{
    OpenSafetyGuard();
    return true;
}

bool Calibration::_execute(int funCode)
{
    qDebug() << "Calibration::_execute" << funCode;
    bool bResult = true;
    switch(funCode)
    {
    case WIDTH_CALIBRATE:
        WidthCalibration();
        break;
    case HEIGHT_CALIBRATE:
        CloseSafetyGuard();
        HeightCalibration();
        OpenSafetyGuard();
        break;
    case AMPLITUDE_CALIBRATE_PRESS:
        HornCalibrationStart();
        break;
    case AMPLITUDE_CALIBRATE_UPPRESS:
        qDebug() << "AMPLITUDE_CALIBRATE_UPPRESS";
        HornCalibrationStop();
        break;
    default:
        bResult = false;
        break;
    }
    return bResult;
}

void Calibration::WidthCalibration()
{
   M102IA* _M102IA = M102IA::Instance();
   bool bResult = false;
   bResult = _M102IA->SetIAWidth(0);
   qDebug()<<"WidthCalibration :" <<bResult;
//   bResult = _M102IA->SetIAWidth(_M102IA->IAsetup.Width);
   emit this->WidthCalibrationFinish(bResult);
}

void Calibration::HeightCalibration()
{
    M102IA* _M102IA = M102IA::Instance();
    M2010* _M2010 = M2010::Instance();
    ModRunSetup* _ModRunSetup = ModRunSetup::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    DBMaintenanceLogTable* _MaintenanceLogTable = DBMaintenanceLogTable::Instance();
    MaintenanceLogElement MaintenanceLog;
    MaintenanceLog.MaintenanceType = MaintenanceTypeString[CALIBRATE];
    MaintenanceLog.OperatorID = _Interface->CurrentOperator.OperatorID;
    MaintenanceLog.CreatedDate = QDateTime::currentDateTime().toTime_t();
    bool bResult = false;
    _M2010->ReceiveFlags.CalibrationDone = false;
    _M102IA->IACommand(IAComHeightZero, 2);
    _M102IA->WaitForResponseAfterSent(15000, &_M2010->ReceiveFlags.CalibrationDone);
    struct BransonMessageBox tmpMsgBox;
    if (_M2010->ReceiveFlags.CalibrationDone == true)
    {
        if(_ModRunSetup->OfflineModeEnabled == true)
            _M102IA->HeightCalResult = 2;
        if (_M102IA->HeightCalResult == 2)
        {
            tmpMsgBox.MsgTitle = QObject::tr("Information");
            tmpMsgBox.MsgPrompt = QObject::tr("Calibration Done");
            tmpMsgBox.TipsMode = Information;
            tmpMsgBox.func_ptr = NULL;
            _Interface->cMsgBox(&tmpMsgBox);
            CalbCount = 1;
            bResult = true;
            MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[CALIBRATE_W_H_COMPLETE];
            _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        }else if (_M102IA->HeightCalResult == 0)
        {
            tmpMsgBox.MsgTitle = QObject::tr("Information");
            tmpMsgBox.MsgPrompt = QObject::tr("UnSuccessful! Try again...");
            tmpMsgBox.TipsMode = Information;
            tmpMsgBox.func_ptr = NULL;
            _Interface->cMsgBox(&tmpMsgBox);
            CalbCount = 1;
            MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[CALIBRATE_W_H_FALSE];
            _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        }else{

        }
    }else{
        tmpMsgBox.MsgTitle = QObject::tr("Information");
        tmpMsgBox.MsgPrompt = QObject::tr("UnSuccessful! Try again...");
        tmpMsgBox.TipsMode = Information;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
        CalbCount = 1;
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[CALIBRATE_W_H_FALSE];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
    }
    _M102IA->IACommand(IAComHornOpen);
    AdvancedMaintenance::HornTest = false;
    _M2010->M10Run.Horn_Close = false;
    CalStarted = false;
    emit this->HeightCalibrationFinish(bResult);
}

void Calibration::HornCalibrationStart()
{
    M102IA* _M102IA = M102IA::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    DBMaintenanceLogTable* _MaintenanceLogTable = DBMaintenanceLogTable::Instance();
    MaintenanceLogElement MaintenanceLog;
    MaintenanceLog.MaintenanceType = MaintenanceTypeString[CALIBRATE];
    MaintenanceLog.OperatorID = _Interface->CurrentOperator.OperatorID;
    MaintenanceLog.CreatedDate = QDateTime::currentDateTime().toTime_t();
    MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[CALIBRATE_AMP_START];
    _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
    bool bResult = false;
    RunSonicsPressed();
    _M102IA->WaitForResponseAfterSent(1000, &bResult);
    RunSonicsUnPressed();
    _M102IA->WaitForResponseAfterSent(1000, &bResult);
    RunSonics100Pressed();
}

void Calibration::HornCalibrationStop()
{
    RunSonicsUnPressed();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    DBMaintenanceLogTable* _MaintenanceLogTable = DBMaintenanceLogTable::Instance();
    MaintenanceLogElement MaintenanceLog;
    MaintenanceLog.MaintenanceType = MaintenanceTypeString[CALIBRATE];
    MaintenanceLog.OperatorID = _Interface->CurrentOperator.OperatorID;
    MaintenanceLog.CreatedDate = QDateTime::currentDateTime().toTime_t();
    MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[CALIBRATE_AMP_COMPLETE];
    _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
}

void Calibration::RunSonicsPressed()
{
    M102IA* _M102IA = M102IA::Instance();
    _M102IA->SendIACommand(IAComAuxMotion, DO_SONICS_ON);
}

void Calibration::RunSonicsUnPressed()
{
    M102IA* _M102IA = M102IA::Instance();
    _M102IA->SendIACommand(IAComAuxMotion, DO_SONICS_OFF);
}

void Calibration::RunSonics100Pressed()
{
    M102IA* _M102IA = M102IA::Instance();
    _M102IA->SendIACommand(IAComAuxMotion, DO_SONICS_FULL);
}

void Calibration::RunSonics100UnPressed()
{
    M102IA* _M102IA = M102IA::Instance();
    _M102IA->SendIACommand(IAComAuxMotion, DO_SONICS_OFF);
}

void Calibration::HornCalibrationComplete(int iAmplitude)
{
    DEBUG_PRINT(iAmplitude);
    bool bResult = false;
    M102IA* _M102IA = M102IA::Instance();
    M2010* _M2010 = M2010::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.Soft_Settings.Horn_Calibrate = iAmplitude;
    _M102IA->SendIACommand(IAComSetHornCalibAmplitude, iAmplitude);
    _M102IA->WaitForResponseAfterSent(500, &bResult);
    _M2010->ReceiveFlags.HORNamplitude = false;
    _M102IA->SendIACommand(IAComSendHornAmplitude, 0);
    _M102IA->WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.HORNamplitude);
    _Interface->StatusData.WriteStatusDataToQSetting();

}
