#include "ToolChange.h"
#include "MaintenanceLog.h"
#include "Interface/Interface.h"
#include "DataBase/DBMaintenanceLogTable.h"
#include "Modules/typedef.h"
#include <QDateTime>
ToolChange::ToolChange()
{

}

bool ToolChange::_start()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    DBMaintenanceLogTable* _MaintenanceLogTable = DBMaintenanceLogTable::Instance();
    MaintenanceLogElement MaintenanceLog;
    MaintenanceLog.MaintenanceType = MaintenanceTypeString[MaintenanceLogElement::MAINTAINCOUNT];
    MaintenanceLog.OperatorID = _Interface->CurrentOperator.OperatorID;
    MaintenanceLog.CreatedDate = QDateTime::currentDateTime().toTime_t();
    MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[MaintenanceLogElement::TOOL_CHANGE_START];
    _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
    return true;
}

bool ToolChange::_stop()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    DBMaintenanceLogTable* _MaintenanceLogTable = DBMaintenanceLogTable::Instance();
    MaintenanceLogElement MaintenanceLog;
    MaintenanceLog.MaintenanceType = MaintenanceTypeString[MaintenanceLogElement::MAINTAINCOUNT];
    MaintenanceLog.OperatorID = _Interface->CurrentOperator.OperatorID;
    MaintenanceLog.CreatedDate = QDateTime::currentDateTime().toTime_t();
    MaintenanceLog.MaintenanceMsg = MaintenanceMessageString[MaintenanceLogElement::TOOL_CHANGE_COMPLETE];
    _MaintenanceLogTable->InsertRecordIntoTable(&MaintenanceLog);
    return true;
}

bool ToolChange::_execute(int funCode)
{
    UNUSED(funCode);
    return true;
}
