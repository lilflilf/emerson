#include "MaintenanceCounter.h"
#include "MaintenanceLog.h"
#include "Interface/Interface.h"
#include "DataBase/DBMaintenanceLogTable.h"
#include "Modules/UtilityClass.h"
#include <QDateTime>
#include <QDebug>
MaintenanceCounter::MaintenanceCounter()
{

}

bool MaintenanceCounter::_start()
{
    return true;
}

bool MaintenanceCounter::_stop()
{
    return true;
}

bool MaintenanceCounter::_execute(int funCode)
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    DBMaintenanceLogTable* _MaintenanceLogTable = DBMaintenanceLogTable::Instance();
    MaintenanceLogElement MaintenanceLog;
    MaintenanceLog.MaintenanceType = MaintenanceTypeString[MAINTAINCOUNT];
    MaintenanceLog.OperatorID = _Interface->CurrentOperator.OperatorID;
    MaintenanceLog.CreatedDate = QDateTime::currentDateTime().toTime_t();
    switch(funCode)
    {
    case HORNCHANGE:
        ChangeHornCounterLimit();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[HORN_COUNT_LIMIT];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case HORNRESET:
        ResetHornCurrentCount();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[HORN_COUNT_RESET];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case ANVILTIPCHANGE:
        ChangeAnvilTipCounterLimit();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[ANVILTIP_COUNT_LIMIT];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case ANVILTIPRESET:
        ResetAnvilTipCurrentCount();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[ANVILTIP_COUNT_RESET];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case GATHERCHANGE:
        ChangeGatherCounterLimit();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[GATHER_COUNT_LIMIT];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case GATHERRESET:
        ResetGatherCurrentCount();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[GATHER_COUNT_RESET];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case ANVILGUIDECHANGE:
        ChangeAnvilGuideCounterLimit();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[ANVILGUIDE_COUNT_LIMIT];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case ANVILGUIDERESET:
        ResetAnvilGuideCurrentCount();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[ANVILGUIDE_COUNT_RESET];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case CONVERTERCHANGE:
        ChangeConverterCounterLimit();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[CONVERTER_COUNT_LIMIT];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case CONVERTERRESET:
        ResetConverterCurrentCount();
        MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[CONVERTER_COUNT_RESET];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    default:
        break;
    }
    _Interface->StatusData.WriteStatusDataToQSetting();
    return true;
}

void MaintenanceCounter::ChangeHornCounterLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString HornLimitStr =
            CurrentMaintenanceCounter.HornCounterLimit.Current;
    _Interface->StatusData.MaintenanceLimits[HORNCHANGE/2] =
            _Utility->StringToFormatedData(DINHornLimit, HornLimitStr);
}
void MaintenanceCounter::ResetHornCurrentCount()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.CurrentMaintenanceLimits[HORNRESET/2] = 0;
    _Interface->StatusData.MaintenanceDateStarted[HORNRESET/2] = 0;
    qDebug()<< HORNRESET/2<<_Interface->StatusData.CurrentMaintenanceLimits[HORNRESET/2]<<
               _Interface->StatusData.MaintenanceDateStarted[HORNRESET/2];
}

void MaintenanceCounter::ChangeAnvilTipCounterLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString AnvilTipLimitStr =
            CurrentMaintenanceCounter.AnvilTipCounterLimit.Current;
    _Interface->StatusData.MaintenanceLimits[ANVILTIPCHANGE/2] =
            _Utility->StringToFormatedData(DINAnvilTipLimit, AnvilTipLimitStr);
}

void MaintenanceCounter::ResetAnvilTipCurrentCount()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.CurrentMaintenanceLimits[ANVILTIPRESET/2] = 0;
    _Interface->StatusData.MaintenanceDateStarted[ANVILTIPRESET/2] = 0;
}

void MaintenanceCounter::ChangeGatherCounterLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString GatherLimitStr =
            CurrentMaintenanceCounter.GatherCounterLimit.Current;
    _Interface->StatusData.MaintenanceLimits[GATHERCHANGE/2] =
            _Utility->StringToFormatedData(DINGatherLimit, GatherLimitStr);

}

void MaintenanceCounter::ResetGatherCurrentCount()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.CurrentMaintenanceLimits[GATHERRESET/2] = 0;
    _Interface->StatusData.MaintenanceDateStarted[GATHERRESET/2] = 0;
}

void MaintenanceCounter::ChangeAnvilGuideCounterLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString AnvilGuideLimitStr =
            CurrentMaintenanceCounter.AnvilGuideCounterLimit.Current;
    _Interface->StatusData.MaintenanceLimits[ANVILGUIDECHANGE/2] =
            _Utility->StringToFormatedData(DINAnvilGuideLimit, AnvilGuideLimitStr);

}

void MaintenanceCounter::ResetAnvilGuideCurrentCount()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.CurrentMaintenanceLimits[ANVILGUIDERESET/2] = 0;
    _Interface->StatusData.MaintenanceDateStarted[ANVILGUIDERESET/2] = 0;
}

void MaintenanceCounter::ChangeConverterCounterLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString ConverterLimitStr =
            CurrentMaintenanceCounter.ConverterCounterLimit.Current;
    _Interface->StatusData.MaintenanceLimits[CONVERTERCHANGE/2] =
            _Utility->StringToFormatedData(DINConverterLimit, ConverterLimitStr);

}

void MaintenanceCounter::ResetConverterCurrentCount()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.CurrentMaintenanceLimits[CONVERTERRESET/2] = 0;
    _Interface->StatusData.MaintenanceDateStarted[CONVERTERRESET/2] = 0;
}

bool MaintenanceCounter::_recall()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    //Horn
    QString Str = _Utility->FormatedDataToString(DINHornLimit,
        _Interface->StatusData.MaintenanceLimits[HORNCHANGE/2]);
    CurrentMaintenanceCounter.HornCounterLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINHornLimit, MAXHORNLIMIT);
    CurrentMaintenanceCounter.HornCounterLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINHornLimit, MINHORNLIMIT);
    CurrentMaintenanceCounter.HornCounterLimit.Minimum = Str;

    long CurrentCount = _Interface->StatusData.CurrentMaintenanceLimits[HORNRESET/2];
    Str = QString::number(CurrentCount, 10);
    CurrentMaintenanceCounter.HornCurrentCount = Str;
    if(CurrentCount == 0)
        CurrentMaintenanceCounter.HornDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[HORNRESET/2]);
        CurrentMaintenanceCounter.HornDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    qDebug()<<"HornCurrentCount" <<CurrentMaintenanceCounter.HornCurrentCount<<
              "HornDateStarted" << CurrentMaintenanceCounter.HornDateStarted;
    //Anvil Tip
    Str = _Utility->FormatedDataToString(DINAnvilTipLimit,
        _Interface->StatusData.MaintenanceLimits[ANVILTIPCHANGE/2]);
    CurrentMaintenanceCounter.AnvilTipCounterLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINAnvilTipLimit, MAXANVILTIPLIMIT);
    CurrentMaintenanceCounter.AnvilTipCounterLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINAnvilTipLimit, MINANVILTIPLIMIT);
    CurrentMaintenanceCounter.AnvilTipCounterLimit.Minimum = Str;

    CurrentCount = _Interface->StatusData.CurrentMaintenanceLimits[ANVILTIPRESET/2];
    Str = QString::number(CurrentCount, 10);
    CurrentMaintenanceCounter.AnvilTipCurrentCount = Str;
    if(CurrentCount == 0)
        CurrentMaintenanceCounter.AnvilTipDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[ANVILTIPRESET/2]);
        CurrentMaintenanceCounter.AnvilTipDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    //Gather
    Str = _Utility->FormatedDataToString(DINGatherLimit,
        _Interface->StatusData.MaintenanceLimits[GATHERCHANGE/2]);
    CurrentMaintenanceCounter.GatherCounterLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINGatherLimit, MAXGATHERLIMIT);
    CurrentMaintenanceCounter.GatherCounterLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINGatherLimit, MINGATHERLIMIT);
    CurrentMaintenanceCounter.GatherCounterLimit.Minimum = Str;

    CurrentCount = _Interface->StatusData.CurrentMaintenanceLimits[GATHERRESET/2];
    Str = QString::number(CurrentCount, 10);
    CurrentMaintenanceCounter.GatherCurrentCount = Str;
    if(CurrentCount == 0)
        CurrentMaintenanceCounter.GatherDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[GATHERRESET/2]);
        CurrentMaintenanceCounter.GatherDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    //Anvil Guide
    Str = _Utility->FormatedDataToString(DINAnvilGuideLimit,
        _Interface->StatusData.MaintenanceLimits[ANVILGUIDECHANGE/2]);
    CurrentMaintenanceCounter.AnvilGuideCounterLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINAnvilGuideLimit, MAXANVILGUIDELIMIT);
    CurrentMaintenanceCounter.AnvilGuideCounterLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINAnvilGuideLimit, MINANVILGUIDELIMIT);
    CurrentMaintenanceCounter.AnvilGuideCounterLimit.Minimum = Str;

    CurrentCount = _Interface->StatusData.CurrentMaintenanceLimits[ANVILGUIDERESET/2];
    Str = QString::number(CurrentCount, 10);
    CurrentMaintenanceCounter.AnvilGuideCurrentCount = Str;
    if(CurrentCount == 0)
        CurrentMaintenanceCounter.AnvilGuideDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[ANVILGUIDERESET/2]);
        CurrentMaintenanceCounter.AnvilGuideDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    //Converter
    Str = _Utility->FormatedDataToString(DINConverterLimit,
        _Interface->StatusData.MaintenanceLimits[CONVERTERCHANGE/2]);
    CurrentMaintenanceCounter.ConverterCounterLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINConverterLimit, MAXCONVERTERLIMIT);
    CurrentMaintenanceCounter.ConverterCounterLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINConverterLimit, MINCONVERTERLIMIT);
    CurrentMaintenanceCounter.ConverterCounterLimit.Minimum = Str;

    CurrentCount = _Interface->StatusData.CurrentMaintenanceLimits[CONVERTERRESET/2];
    Str = QString::number(CurrentCount, 10);
    CurrentMaintenanceCounter.ConverterCurrentCount = Str;
    if(CurrentCount == 0)
        CurrentMaintenanceCounter.ConverterDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[CONVERTERRESET/2]);
        CurrentMaintenanceCounter.ConverterDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    //Actuator
    CurrentCount = _Interface->StatusData.CurrentMaintenanceLimits[ACTUATOR/2];
    Str = QString::number(CurrentCount,10);
    CurrentMaintenanceCounter.ActuatorCurrentCount = Str;
    if(CurrentCount == 0)
        CurrentMaintenanceCounter.ActuatorDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[ACTUATOR/2]);
        CurrentMaintenanceCounter.ActuatorDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }

    Str = _Interface->StatusData.ActuatorVersion;
    CurrentMaintenanceCounter.ActuatorSoftwareVersion = Str;
    Str = _Interface->StatusData.ActuatorPartNumber;
    CurrentMaintenanceCounter.ActuatorPartNumber = Str;
    Str = _Interface->StatusData.ActuatorSerialNumber;
    CurrentMaintenanceCounter.ActuatorSerialNumber = Str;
    Str = _Interface->StatusData.ActuatorModuleNumber;
    CurrentMaintenanceCounter.ActuatorModuleNumber = Str;
    return true;
}
