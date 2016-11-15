#include "MaintenanceCounter.h"
#include "MaintenanceLog.h"
#include "Interface/Interface.h"
#include "DataBase/DBMaintenanceLogTable.h"
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

}
void MaintenanceCounter::ResetHornCurrentCount()
{

}

void MaintenanceCounter::ChangeAnvilTipCounterLimit()
{

}

void MaintenanceCounter::ResetAnvilTipCurrentCount()
{

}

void MaintenanceCounter::ChangeGatherCounterLimit()
{

}

void MaintenanceCounter::ResetGatherCurrentCount()
{

}

void MaintenanceCounter::ChangeAnvilGuideCounterLimit()
{

}

void MaintenanceCounter::ResetAnvilGuideCurrentCount()
{

}

void MaintenanceCounter::ChangeConverterCounterLimit()
{

}

void MaintenanceCounter::ResetConverterCurrentCount()
{

}
