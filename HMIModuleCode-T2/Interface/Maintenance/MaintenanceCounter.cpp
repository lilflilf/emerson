#include "MaintenanceCounter.h"
#include "MaintenanceLog.h"
#include "Interface/Interface.h"
#include "DataBase/DBMaintenanceLogTable.h"
#include "Modules/UtilityClass.h"
#include <QDateTime>
#include <QDebug>
MaintenanceCounter::MaintenanceCounter()
{
    CurrentMaintenanceCounter.HornPartNumber = "HORN-456-789";
    CurrentMaintenanceCounter.AnvilPartNumber = "ANVIL-456-789";
    CurrentMaintenanceCounter.GatherPartNumber = "GATHER-456-789";
    CurrentMaintenanceCounter.GuidePartNumber = "GUIDE-456-789";
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
    MaintenanceLog.MaintenanceType =
            MaintenanceTypeString[MaintenanceLogElement::MAINTAINCOUNT];
    MaintenanceLog.OperatorID = _Interface->CurrentOperator.OperatorID;
    MaintenanceLog.CreatedDate = QDateTime::currentDateTime().toTime_t();

    switch(funCode)
    {
    case MaintenanceLogElement::HORN_COUNT_LIMIT:
        ChangeHornCounterLimit();
        MaintenanceLog.MaintenanceMsg =
                MaintenanceMessageString[MaintenanceLogElement::HORN_COUNT_LIMIT];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case MaintenanceLogElement::HORN_ENERGY_LIMIT:
        ChangeHornEnergyLimit();
        MaintenanceLog.MaintenanceMsg =
                MaintenanceMessageString[MaintenanceLogElement::HORN_ENERGY_LIMIT];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case MaintenanceLogElement::HORN_COUNT_RESET:
        ResetHornCurrentCountAndEnergy();
        MaintenanceLog.MaintenanceMsg =
                MaintenanceMessageString[MaintenanceLogElement::HORN_COUNT_RESET];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case MaintenanceLogElement::HORN_80PERCENT_ALARM:
        if(_Interface->StatusData.Maintenance80PercentAlarm[HORN80PERCENTALARM] == true)
            _Interface->StatusData.Maintenance80PercentAlarm[HORN80PERCENTALARM] = false;
        else
            _Interface->StatusData.Maintenance80PercentAlarm[HORN80PERCENTALARM] = true;
        break;
    case MaintenanceLogElement::HORN_100PERCENT_LOCK:
        if(_Interface->StatusData.Maintenance100PercentLock[HORN100PERCENTLOCK] == true)
            _Interface->StatusData.Maintenance100PercentLock[HORN100PERCENTLOCK] = false;
        else
            _Interface->StatusData.Maintenance100PercentLock[HORN100PERCENTLOCK] = true;
        break;
    case MaintenanceLogElement::ANVIL_COUNT_LIMIT:
        ChangeAnvilCounterLimit();
        MaintenanceLog.MaintenanceMsg =
                MaintenanceMessageString[MaintenanceLogElement::ANVIL_COUNT_LIMIT];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case MaintenanceLogElement::ANVIL_ENERGY_LIMIT:
        ChangeAnvilEnergyLimit();
        MaintenanceLog.MaintenanceMsg =
                MaintenanceMessageString[MaintenanceLogElement::ANVIL_ENERGY_LIMIT];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case MaintenanceLogElement::ANVIL_COUNT_RESET:
        ResetAnvilCurrentCountAndEnergy();
        MaintenanceLog.MaintenanceMsg =
                MaintenanceMessageString[MaintenanceLogElement::ANVIL_COUNT_RESET];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case MaintenanceLogElement::ANVIL_80PERCENT_ALARM:
        if(_Interface->StatusData.Maintenance80PercentAlarm[ANVIL80PERCENTALARM] == true)
            _Interface->StatusData.Maintenance80PercentAlarm[ANVIL80PERCENTALARM] = false;
        else
            _Interface->StatusData.Maintenance80PercentAlarm[ANVIL80PERCENTALARM] = true;
        break;
    case MaintenanceLogElement::ANVIL_100PERCENT_LOCK:
        if(_Interface->StatusData.Maintenance100PercentLock[ANVIL100PERCENTLOCK] == true)
            _Interface->StatusData.Maintenance100PercentLock[ANVIL100PERCENTLOCK] = false;
        else
            _Interface->StatusData.Maintenance100PercentLock[ANVIL100PERCENTLOCK] = true;
        break;
    case MaintenanceLogElement::GATHER_COUNT_LIMIT:
        ChangeGatherCounterLimit();
        MaintenanceLog.MaintenanceMsg =
                MaintenanceMessageString[MaintenanceLogElement::GATHER_COUNT_LIMIT];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case MaintenanceLogElement::GATHER_ENERGY_LIMIT:
        ChangeGatherEnergyLimit();
        MaintenanceLog.MaintenanceMsg =
                MaintenanceMessageString[MaintenanceLogElement::GATHER_ENERGY_LIMIT];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case MaintenanceLogElement::GATHER_COUNT_RESET:
        ResetGatherCurrentCountAndEnergy();
        MaintenanceLog.MaintenanceMsg =
                MaintenanceMessageString[MaintenanceLogElement::GATHER_COUNT_RESET];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case MaintenanceLogElement::GATHER_80PERCENT_ALARM:
        if(_Interface->StatusData.Maintenance80PercentAlarm[GATHER80PERCENTALARM] == true)
            _Interface->StatusData.Maintenance80PercentAlarm[GATHER80PERCENTALARM] = false;
        else
            _Interface->StatusData.Maintenance80PercentAlarm[GATHER80PERCENTALARM] = true;
        break;
    case MaintenanceLogElement::GATHER_100PERCENT_LOCK:
        if(_Interface->StatusData.Maintenance100PercentLock[GATHER100PERCENTLOCK] == true)
            _Interface->StatusData.Maintenance100PercentLock[GATHER100PERCENTLOCK] = false;
        else
            _Interface->StatusData.Maintenance100PercentLock[GATHER100PERCENTLOCK] = true;
        break;
    case MaintenanceLogElement::GUIDE_COUNT_LIMIT:
        ChangeGuideCounterLimit();
        MaintenanceLog.MaintenanceMsg =
                MaintenanceMessageString[MaintenanceLogElement::GUIDE_COUNT_LIMIT];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case MaintenanceLogElement::GUIDE_ENERGY_LIMIT:
        ChangeGuideEnergyLimit();
        MaintenanceLog.MaintenanceMsg =
                MaintenanceMessageString[MaintenanceLogElement::GUIDE_ENERGY_LIMIT];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case MaintenanceLogElement::GUIDE_COUNT_RESET:
        ResetAnvilCurrentCountAndEnergy();
        MaintenanceLog.MaintenanceMsg =
                MaintenanceMessageString[MaintenanceLogElement::GUIDE_COUNT_RESET];
        _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
        break;
    case MaintenanceLogElement::GUIDE_80PERCENT_ALARM:
        if(_Interface->StatusData.Maintenance80PercentAlarm[GUID80PERCENTALARM] == true)
            _Interface->StatusData.Maintenance80PercentAlarm[GUID80PERCENTALARM] = false;
        else
            _Interface->StatusData.Maintenance80PercentAlarm[GUID80PERCENTALARM] = true;
        break;
    case MaintenanceLogElement::GUIDE_100PERCENT_LOCK:
        if(_Interface->StatusData.Maintenance100PercentLock[GUID100PERCENTLOCK] == true)
            _Interface->StatusData.Maintenance100PercentLock[GUID100PERCENTLOCK] = false;
        else
            _Interface->StatusData.Maintenance100PercentLock[GUID100PERCENTLOCK] = true;
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
    _Interface->StatusData.MaintenanceCountLimits[HORNCOUNTCHANGE] =
            _Utility->StringToFormatedData(DINHornCountLimit, HornLimitStr);
}

void MaintenanceCounter::ChangeHornEnergyLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString HornLimitStr =
            CurrentMaintenanceCounter.HornEnergyLimit.Current;
    _Interface->StatusData.MaintenanceEnergyLimits[HORNENERGYCHANGE] =
            _Utility->StringToFormatedData(DINHornEnergyLimit, HornLimitStr);
}

void MaintenanceCounter::ResetHornCurrentCountAndEnergy()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.CurrentCountMaintenanceLimits[HORNRESET] = 0;
    _Interface->StatusData.CurrentEnergyMaintenanceLimits[HORNRESET] = 0;
    _Interface->StatusData.MaintenanceDateStarted[HORNRESET] = 0;
}

void MaintenanceCounter::ChangeAnvilCounterLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString AnvilLimitStr =
            CurrentMaintenanceCounter.AnvilCounterLimit.Current;
    _Interface->StatusData.MaintenanceCountLimits[ANVILCOUNTCHANGE] =
            _Utility->StringToFormatedData(DINAnvilCountLimit, AnvilLimitStr);
}

void MaintenanceCounter::ChangeAnvilEnergyLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString AnvilLimitStr =
            CurrentMaintenanceCounter.AnvilEnergyLimit.Current;
    _Interface->StatusData.MaintenanceEnergyLimits[ANVILENERGYCHANGE] =
            _Utility->StringToFormatedData(DINAnvilEnergyLimit, AnvilLimitStr);
}

void MaintenanceCounter::ResetAnvilCurrentCountAndEnergy()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.CurrentCountMaintenanceLimits[ANVILRESET] = 0;
    _Interface->StatusData.CurrentEnergyMaintenanceLimits[ANVILRESET] = 0;
    _Interface->StatusData.MaintenanceDateStarted[ANVILRESET] = 0;
}

void MaintenanceCounter::ChangeGatherCounterLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString GatherLimitStr =
            CurrentMaintenanceCounter.GatherCounterLimit.Current;
    _Interface->StatusData.MaintenanceCountLimits[GATHERCOUNTCHANGE] =
            _Utility->StringToFormatedData(DINGatherCountLimit, GatherLimitStr);

}

void MaintenanceCounter::ChangeGatherEnergyLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString GatherLimitStr =
            CurrentMaintenanceCounter.GatherEnergyLimit.Current;
    _Interface->StatusData.MaintenanceEnergyLimits[GATHERENERGYCHANGE] =
            _Utility->StringToFormatedData(DINGatherEnergyLimit, GatherLimitStr);
}

void MaintenanceCounter::ResetGatherCurrentCountAndEnergy()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.CurrentCountMaintenanceLimits[GATHERRESET] = 0;
    _Interface->StatusData.CurrentEnergyMaintenanceLimits[GATHERRESET] = 0;
    _Interface->StatusData.MaintenanceDateStarted[GATHERRESET] = 0;
}

void MaintenanceCounter::ChangeGuideCounterLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString AnvilGuideLimitStr =
            CurrentMaintenanceCounter.AnvilCounterLimit.Current;
    _Interface->StatusData.MaintenanceCountLimits[GUIDECOUNTCHANGE] =
            _Utility->StringToFormatedData(DINGuideCountLimit, AnvilGuideLimitStr);
}

void MaintenanceCounter::ChangeGuideEnergyLimit()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString AnvilGuideLimitStr =
            CurrentMaintenanceCounter.AnvilEnergyLimit.Current;
    _Interface->StatusData.MaintenanceEnergyLimits[GUIDEENERGYCHANGE] =
            _Utility->StringToFormatedData(DINGuideEnergyLimit, AnvilGuideLimitStr);
}

void MaintenanceCounter::ResetGuideCurrentCountAndEnergy()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.CurrentCountMaintenanceLimits[GUIDERESET] = 0;
    _Interface->StatusData.CurrentEnergyMaintenanceLimits[GUIDERESET] = 0;
    _Interface->StatusData.MaintenanceDateStarted[GUIDERESET] = 0;
}

bool MaintenanceCounter::_recall()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    //Horn
    QString Str = _Utility->FormatedDataToString(DINHornCountLimit,
        _Interface->StatusData.MaintenanceCountLimits[ITEM_HORN]);
    CurrentMaintenanceCounter.HornCounterLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINHornCountLimit, MAXHORNCOUNTLIMIT);
    CurrentMaintenanceCounter.HornCounterLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINHornCountLimit, MINHORNCOUNTLIMIT);
    CurrentMaintenanceCounter.HornCounterLimit.Minimum = Str;

    Str = _Utility->FormatedDataToString(DINHornEnergyLimit,
        _Interface->StatusData.MaintenanceEnergyLimits[ITEM_HORN]);
    CurrentMaintenanceCounter.HornEnergyLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINHornEnergyLimit, MAXHORNENERGYLIMIT);
    CurrentMaintenanceCounter.HornEnergyLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINHornEnergyLimit, MINHORNENERGYLIMIT);
    CurrentMaintenanceCounter.HornEnergyLimit.Minimum = Str;

    long CurrentCount = _Interface->StatusData.CurrentCountMaintenanceLimits[ITEM_HORN];
    Str = QString::number(CurrentCount, 10);
    CurrentMaintenanceCounter.HornCurrentCount = Str;
    double CurrentEnergy = _Interface->StatusData.CurrentEnergyMaintenanceLimits[ITEM_HORN];
    Str = _Utility->FormatedDataToString(DINHornEnergyLimit, CurrentEnergy);
    CurrentMaintenanceCounter.HornCurrentEnergy = Str;

    if(CurrentCount == 0)
        CurrentMaintenanceCounter.HornDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[ITEM_HORN]);
        CurrentMaintenanceCounter.HornDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    CurrentMaintenanceCounter.Horn80PercentAlarm =
            _Interface->StatusData.Maintenance80PercentAlarm[HORN80PERCENTALARM];
    CurrentMaintenanceCounter.Horn100PercentLock =
            _Interface->StatusData.Maintenance100PercentLock[HORN100PERCENTLOCK];

    //Anvil Tip
    Str = _Utility->FormatedDataToString(DINAnvilCountLimit,
        _Interface->StatusData.MaintenanceCountLimits[ITEM_ANVIL]);
    CurrentMaintenanceCounter.AnvilCounterLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINAnvilCountLimit, MAXANVILCOUNTLIMIT);
    CurrentMaintenanceCounter.AnvilCounterLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINAnvilCountLimit, MINANVILCOUNTLIMIT);
    CurrentMaintenanceCounter.AnvilCounterLimit.Minimum = Str;

    Str = _Utility->FormatedDataToString(DINAnvilEnergyLimit,
        _Interface->StatusData.MaintenanceEnergyLimits[ITEM_ANVIL]);
    CurrentMaintenanceCounter.AnvilEnergyLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINAnvilEnergyLimit, MAXANVILENERGYLIMIT);
    CurrentMaintenanceCounter.AnvilEnergyLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINAnvilEnergyLimit, MINANVILENERGYLIMIT);
    CurrentMaintenanceCounter.AnvilEnergyLimit.Minimum = Str;

    CurrentCount = _Interface->StatusData.CurrentCountMaintenanceLimits[ITEM_ANVIL];
    Str = QString::number(CurrentCount, 10);
    CurrentMaintenanceCounter.AnvilCurrentCount = Str;
    CurrentEnergy = _Interface->StatusData.CurrentEnergyMaintenanceLimits[ITEM_ANVIL];
    Str = _Utility->FormatedDataToString(DINAnvilEnergyLimit, CurrentEnergy);
    CurrentMaintenanceCounter.AnvilCurrentEnergy = Str;

    if(CurrentCount == 0)
        CurrentMaintenanceCounter.AnvilDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[ITEM_ANVIL]);
        CurrentMaintenanceCounter.AnvilDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    CurrentMaintenanceCounter.Anvil80PercentAlarm =
            _Interface->StatusData.Maintenance80PercentAlarm[ANVIL80PERCENTALARM];
    CurrentMaintenanceCounter.Anvil100PercentLock =
            _Interface->StatusData.Maintenance100PercentLock[ANVIL100PERCENTLOCK];

    //Gather
    Str = _Utility->FormatedDataToString(DINGatherCountLimit,
        _Interface->StatusData.MaintenanceCountLimits[ITEM_GATHER]);
    CurrentMaintenanceCounter.GatherCounterLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINGatherCountLimit, MAXGATHERCOUNTLIMIT);
    CurrentMaintenanceCounter.GatherCounterLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINGatherCountLimit, MINGATHERCOUNTLIMIT);
    CurrentMaintenanceCounter.GatherCounterLimit.Minimum = Str;

    Str = _Utility->FormatedDataToString(DINGatherEnergyLimit,
        _Interface->StatusData.MaintenanceEnergyLimits[ITEM_GATHER]);
    CurrentMaintenanceCounter.GatherEnergyLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINGatherEnergyLimit, MAXGATHERENERGYLIMIT);
    CurrentMaintenanceCounter.GatherEnergyLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINGatherEnergyLimit, MINGATHERENERGYLIMIT);
    CurrentMaintenanceCounter.GatherEnergyLimit.Minimum = Str;

    CurrentCount = _Interface->StatusData.CurrentCountMaintenanceLimits[ITEM_GATHER];
    Str = QString::number(CurrentCount, 10);
    CurrentMaintenanceCounter.GatherCurrentCount = Str;
    CurrentEnergy = _Interface->StatusData.CurrentEnergyMaintenanceLimits[ITEM_GATHER];
    Str = _Utility->FormatedDataToString(DINGatherEnergyLimit, CurrentEnergy);
    CurrentMaintenanceCounter.GatherCurrentEnergy = Str;

    if(CurrentCount == 0)
        CurrentMaintenanceCounter.GatherDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[ITEM_GATHER]);
        CurrentMaintenanceCounter.GatherDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    CurrentMaintenanceCounter.Gather80PercentAlarm =
            _Interface->StatusData.Maintenance80PercentAlarm[GATHER80PERCENTALARM];
    CurrentMaintenanceCounter.Gather100PercentLock =
            _Interface->StatusData.Maintenance100PercentLock[GATHER100PERCENTLOCK];

    //Anvil Guide
    Str = _Utility->FormatedDataToString(DINGuideCountLimit,
        _Interface->StatusData.MaintenanceCountLimits[ITEM_GUIDE]);
    CurrentMaintenanceCounter.GuideCounterLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINGuideCountLimit, MAXGUIDECOUNTLIMIT);
    CurrentMaintenanceCounter.GuideCounterLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINGuideCountLimit, MINGUIDECOUNTLIMIT);
    CurrentMaintenanceCounter.GuideCounterLimit.Minimum = Str;

    Str = _Utility->FormatedDataToString(DINGuideEnergyLimit,
        _Interface->StatusData.MaintenanceEnergyLimits[ITEM_GUIDE]);
    CurrentMaintenanceCounter.GuideEnergyLimit.Current = Str;
    Str = _Utility->FormatedDataToString(DINGuideEnergyLimit, MAXGUIDEENERGYLIMIT);
    CurrentMaintenanceCounter.GuideEnergyLimit.Maximum = Str;
    Str = _Utility->FormatedDataToString(DINGuideEnergyLimit, MINGUIDEENERGYLIMIT);
    CurrentMaintenanceCounter.GuideEnergyLimit.Minimum = Str;

    CurrentCount = _Interface->StatusData.CurrentCountMaintenanceLimits[ITEM_GUIDE];
    Str = QString::number(CurrentCount, 10);
    CurrentMaintenanceCounter.GuideCurrentCount = Str;
    CurrentEnergy = _Interface->StatusData.CurrentEnergyMaintenanceLimits[ITEM_GUIDE];
    Str = _Utility->FormatedDataToString(DINGuideEnergyLimit, CurrentEnergy);
    CurrentMaintenanceCounter.GuideCurrentEnergy = Str;

    if(CurrentCount == 0)
        CurrentMaintenanceCounter.GuideDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[ITEM_GUIDE]);
        CurrentMaintenanceCounter.GuideDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    CurrentMaintenanceCounter.Guide80PercentAlarm =
            _Interface->StatusData.Maintenance80PercentAlarm[GUID80PERCENTALARM];
    CurrentMaintenanceCounter.Gather100PercentLock =
            _Interface->StatusData.Maintenance100PercentLock[GUID100PERCENTLOCK];

    //Actuator
    CurrentCount = _Interface->StatusData.CurrentCountMaintenanceLimits[ITEM_SYSTEM];
    Str = QString::number(CurrentCount,10);
    CurrentMaintenanceCounter.ActuatorCurrentCount = Str;
    if(CurrentCount == 0)
        CurrentMaintenanceCounter.ActuatorDateStarted = "--/--/----";
    else
    {
        QDateTime TimeLabel = QDateTime::fromTime_t(
            _Interface->StatusData.MaintenanceDateStarted[ITEM_SYSTEM]);
        CurrentMaintenanceCounter.ActuatorDateStarted
            = TimeLabel.toString("MM/dd/yyyy");
    }
    return true;
}
