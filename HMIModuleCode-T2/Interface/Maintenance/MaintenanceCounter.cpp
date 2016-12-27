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
    case HORN80PERCENTALARM:
        if(_Interface->StatusData.Maintenance80PercentAlarm[HORN80PERCENTALARM/3] == true)
            _Interface->StatusData.Maintenance80PercentAlarm[HORN80PERCENTALARM/3] = false;
        else
            _Interface->StatusData.Maintenance80PercentAlarm[HORN80PERCENTALARM/3] = true;
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
    case ANVILTIP80PERCENTALARM:
        if(_Interface->StatusData.Maintenance80PercentAlarm[ANVILTIP80PERCENTALARM/3] == true)
            _Interface->StatusData.Maintenance80PercentAlarm[ANVILTIP80PERCENTALARM/3] = false;
        else
            _Interface->StatusData.Maintenance80PercentAlarm[ANVILTIP80PERCENTALARM/3] = true;
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
    case GATHER80PERCENTALARM:
        if(_Interface->StatusData.Maintenance80PercentAlarm[GATHER80PERCENTALARM/3] == true)
            _Interface->StatusData.Maintenance80PercentAlarm[GATHER80PERCENTALARM/3] = false;
        else
            _Interface->StatusData.Maintenance80PercentAlarm[GATHER80PERCENTALARM/3] = true;
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
    case ANVILGUID80PERCENTALARM:
        if(_Interface->StatusData.Maintenance80PercentAlarm[ANVILGUID80PERCENTALARM/3] == true)
            _Interface->StatusData.Maintenance80PercentAlarm[ANVILGUID80PERCENTALARM/3] = false;
        else
            _Interface->StatusData.Maintenance80PercentAlarm[ANVILGUID80PERCENTALARM/3] = true;
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
    case CONVERTER80PERCENTALARM:
        if(_Interface->StatusData.Maintenance80PercentAlarm[CONVERTER80PERCENTALARM/3] == true)
            _Interface->StatusData.Maintenance80PercentAlarm[CONVERTER80PERCENTALARM/3] = false;
        else
            _Interface->StatusData.Maintenance80PercentAlarm[CONVERTER80PERCENTALARM/3] = true;
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
    _Interface->StatusData.MaintenanceLimits[HORNCHANGE/3] =
            _Utility->StringToFormatedData(DINHornLimit, HornLimitStr);
}
void MaintenanceCounter::ResetHornCurrentCount()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.CurrentMaintenanceLimits[HORNRESET/3] = 0;
    _Interface->StatusData.MaintenanceDateStarted[HORNRESET/3] = 0;
    qDebug()<< HORNRESET/3<<_Interface->StatusData.CurrentMaintenanceLimits[HORNRESET/3]<<
               _Interface->StatusData.MaintenanceDateStarted[HORNRESET/3];
}

void MaintenanceCounter::ChangeAnvilTipCounterLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString AnvilTipLimitStr =
            CurrentMaintenanceCounter.AnvilTipCounterLimit.Current;
    _Interface->StatusData.MaintenanceLimits[ANVILTIPCHANGE/3] =
            _Utility->StringToFormatedData(DINAnvilTipLimit, AnvilTipLimitStr);
}

void MaintenanceCounter::ResetAnvilTipCurrentCount()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.CurrentMaintenanceLimits[ANVILTIPRESET/3] = 0;
    _Interface->StatusData.MaintenanceDateStarted[ANVILTIPRESET/3] = 0;
}

void MaintenanceCounter::ChangeGatherCounterLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString GatherLimitStr =
            CurrentMaintenanceCounter.GatherCounterLimit.Current;
    _Interface->StatusData.MaintenanceLimits[GATHERCHANGE/3] =
            _Utility->StringToFormatedData(DINGatherLimit, GatherLimitStr);

}

void MaintenanceCounter::ResetGatherCurrentCount()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.CurrentMaintenanceLimits[GATHERRESET/3] = 0;
    _Interface->StatusData.MaintenanceDateStarted[GATHERRESET/3] = 0;
}

void MaintenanceCounter::ChangeAnvilGuideCounterLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString AnvilGuideLimitStr =
            CurrentMaintenanceCounter.AnvilGuideCounterLimit.Current;
    _Interface->StatusData.MaintenanceLimits[ANVILGUIDECHANGE/3] =
            _Utility->StringToFormatedData(DINAnvilGuideLimit, AnvilGuideLimitStr);

}

void MaintenanceCounter::ResetAnvilGuideCurrentCount()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.CurrentMaintenanceLimits[ANVILGUIDERESET/3] = 0;
    _Interface->StatusData.MaintenanceDateStarted[ANVILGUIDERESET/3] = 0;
}

void MaintenanceCounter::ChangeConverterCounterLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString ConverterLimitStr =
            CurrentMaintenanceCounter.ConverterCounterLimit.Current;
    _Interface->StatusData.MaintenanceLimits[CONVERTERCHANGE/3] =
            _Utility->StringToFormatedData(DINConverterLimit, ConverterLimitStr);

}

void MaintenanceCounter::ResetConverterCurrentCount()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.CurrentMaintenanceLimits[CONVERTERRESET/3] = 0;
    _Interface->StatusData.MaintenanceDateStarted[CONVERTERRESET/3] = 0;
}

bool MaintenanceCounter::_recall()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    //Horn
    QString Str = _Utility->FormatedDataToString(DINHornLimit,
        _Interface->StatusData.MaintenanceLimits[HORNCHANGE/3]);
    CurrentMaintenanceCounter.HornCounterLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINHornLimit, MAXHORNLIMIT);
    CurrentMaintenanceCounter.HornCounterLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINHornLimit, MINHORNLIMIT);
    CurrentMaintenanceCounter.HornCounterLimit.Minimum = Str;

    long CurrentCount = _Interface->StatusData.CurrentMaintenanceLimits[HORNRESET/3];
    Str = QString::number(CurrentCount, 10);
    CurrentMaintenanceCounter.HornCurrentCount = Str;
    if(CurrentCount == 0)
        CurrentMaintenanceCounter.HornDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[HORNRESET/3]);
        CurrentMaintenanceCounter.HornDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    CurrentMaintenanceCounter.Horn80PercentAlarm =
            _Interface->StatusData.Maintenance80PercentAlarm[HORN80PERCENTALARM/3];

    //Anvil Tip
    Str = _Utility->FormatedDataToString(DINAnvilTipLimit,
        _Interface->StatusData.MaintenanceLimits[ANVILTIPCHANGE/3]);
    CurrentMaintenanceCounter.AnvilTipCounterLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINAnvilTipLimit, MAXANVILTIPLIMIT);
    CurrentMaintenanceCounter.AnvilTipCounterLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINAnvilTipLimit, MINANVILTIPLIMIT);
    CurrentMaintenanceCounter.AnvilTipCounterLimit.Minimum = Str;

    CurrentCount = _Interface->StatusData.CurrentMaintenanceLimits[ANVILTIPRESET/3];
    Str = QString::number(CurrentCount, 10);
    CurrentMaintenanceCounter.AnvilTipCurrentCount = Str;
    if(CurrentCount == 0)
        CurrentMaintenanceCounter.AnvilTipDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[ANVILTIPRESET/3]);
        CurrentMaintenanceCounter.AnvilTipDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    CurrentMaintenanceCounter.Anvil80PercentAlarm =
            _Interface->StatusData.Maintenance80PercentAlarm[ANVILTIP80PERCENTALARM/3];
    //Gather
    Str = _Utility->FormatedDataToString(DINGatherLimit,
        _Interface->StatusData.MaintenanceLimits[GATHERCHANGE/3]);
    CurrentMaintenanceCounter.GatherCounterLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINGatherLimit, MAXGATHERLIMIT);
    CurrentMaintenanceCounter.GatherCounterLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINGatherLimit, MINGATHERLIMIT);
    CurrentMaintenanceCounter.GatherCounterLimit.Minimum = Str;

    CurrentCount = _Interface->StatusData.CurrentMaintenanceLimits[GATHERRESET/3];
    Str = QString::number(CurrentCount, 10);
    CurrentMaintenanceCounter.GatherCurrentCount = Str;
    if(CurrentCount == 0)
        CurrentMaintenanceCounter.GatherDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[GATHERRESET/3]);
        CurrentMaintenanceCounter.GatherDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    CurrentMaintenanceCounter.Gather80PercentAlarm =
            _Interface->StatusData.Maintenance80PercentAlarm[GATHER80PERCENTALARM/3];
    //Anvil Guide
    Str = _Utility->FormatedDataToString(DINAnvilGuideLimit,
        _Interface->StatusData.MaintenanceLimits[ANVILGUIDECHANGE/3]);
    CurrentMaintenanceCounter.AnvilGuideCounterLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINAnvilGuideLimit, MAXANVILGUIDELIMIT);
    CurrentMaintenanceCounter.AnvilGuideCounterLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINAnvilGuideLimit, MINANVILGUIDELIMIT);
    CurrentMaintenanceCounter.AnvilGuideCounterLimit.Minimum = Str;

    CurrentCount = _Interface->StatusData.CurrentMaintenanceLimits[ANVILGUIDERESET/3];
    Str = QString::number(CurrentCount, 10);
    CurrentMaintenanceCounter.AnvilGuideCurrentCount = Str;
    if(CurrentCount == 0)
        CurrentMaintenanceCounter.AnvilGuideDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[ANVILGUIDERESET/3]);
        CurrentMaintenanceCounter.AnvilGuideDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    CurrentMaintenanceCounter.AnvilGuide80PercentAlarm =
            _Interface->StatusData.Maintenance80PercentAlarm[ANVILGUID80PERCENTALARM/3];

    //Converter
    Str = _Utility->FormatedDataToString(DINConverterLimit,
        _Interface->StatusData.MaintenanceLimits[CONVERTERCHANGE/3]);
    CurrentMaintenanceCounter.ConverterCounterLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINConverterLimit, MAXCONVERTERLIMIT);
    CurrentMaintenanceCounter.ConverterCounterLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINConverterLimit, MINCONVERTERLIMIT);
    CurrentMaintenanceCounter.ConverterCounterLimit.Minimum = Str;

    CurrentCount = _Interface->StatusData.CurrentMaintenanceLimits[CONVERTERRESET/3];
    Str = QString::number(CurrentCount, 10);
    CurrentMaintenanceCounter.ConverterCurrentCount = Str;
    if(CurrentCount == 0)
        CurrentMaintenanceCounter.ConverterDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[CONVERTERRESET/3]);
        CurrentMaintenanceCounter.ConverterDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    CurrentMaintenanceCounter.Converter80PercentAlarm =
            _Interface->StatusData.Maintenance80PercentAlarm[CONVERTER80PERCENTALARM/3];
    //Actuator
    CurrentCount = _Interface->StatusData.CurrentMaintenanceLimits[ACTUATOR/3];
    Str = QString::number(CurrentCount,10);
    CurrentMaintenanceCounter.ActuatorCurrentCount = Str;
    if(CurrentCount == 0)
        CurrentMaintenanceCounter.ActuatorDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[ACTUATOR/3]);
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
