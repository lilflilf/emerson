#include "MaintenanceCounter.h"
#include "MaintenanceLog.h"
#include "Interface/Interface.h"
#include "DataBase/DBMaintenanceLogTable.h"
#include "Modules/UtilityClass.h"
#include <QDateTime>
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
