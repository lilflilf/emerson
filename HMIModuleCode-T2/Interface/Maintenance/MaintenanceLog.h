#ifndef MAINTENANCELOG_H
#define MAINTENANCELOG_H
#include <QObject>

enum MAINTAINTYPE
{
    CALIBRATE,
    TOOLCHANGE,
    ADVMAINTAIN,
    MAINTAINCOUNT,
};
const QString MaintenanceTypeString[] = {
    QObject::tr("Calibration"),
    QObject::tr("Tooling Change"),
    QObject::tr("Advanced Maintenance"),
    QObject::tr("Maintenance Counter"),
};

enum MaintenanceMsgItem{
    CALIBRATE_W_H_START    = 0,
    CALIBRATE_W_H_COMPLETE = 1,
    CALIBRATE_W_H_FALSE    = 2,
    CALIBRATE_W_H_CANCEL   = 3,
    CALIBRATE_AMP_START    = 4,
    CALIBRATE_AMP_COMPLETE = 5,
    CALIBRATE_AMP_FALSE    = 6,
    CALIBRATE_AMP_CANCEL   = 7,
    TOOL_CHANGE_START      = 8,
    TOOL_CHANGE_COMPLETE   = 9,
    ANVILARM_MOVE          = 10,
    ANVIL_MOVE             = 11,
    GATHER_MOVE            = 12,
    CUTTER_MOVE            = 13,
    CRASH_MOVE             = 14,
    SAFETY_MOVE            = 15,
    HORN_COUNT_LIMIT       = 16,
    HORN_COUNT_RESET       = 17,
    ANVILTIP_COUNT_LIMIT   = 18,
    ANVILTIP_COUNT_RESET   = 19,
    GATHER_COUNT_LIMIT     = 20,
    GATHER_COUNT_RESET     = 21,
    ANVILGUIDE_COUNT_LIMIT = 22,
    ANVILGUIDE_COUNT_RESET = 23,
    CONVERTER_COUNT_LIMIT  = 24,
    CONVERTER_COUNT_RESET  = 25,


};

const QString MaintenanceMessageString[] = {
    QObject::tr("Width & Height Calibration Process Start"), // 0
    QObject::tr("Width & Height Calibration Process Complete"),//1
    QObject::tr("Width & Height Calibration Process Unsuccessful"),//2
    QObject::tr("Width & Height Calibration Process Cancel"),//3
    QObject::tr("Amplitude Calibration Process Start"),//4
    QObject::tr("Amplitude Calibration Process Complete"),//5
    QObject::tr("Amplitude Calibration Process Unsuccessful"),//6
    QObject::tr("Amplitude Calibration Process Cancel"),//7
    QObject::tr("Tooling Change Process Start"),//8
    QObject::tr("Tooling Change Process Finish"),//9
    QObject::tr("Anvil Arm Movement"),//10
    QObject::tr("Avil Movement"),//11
    QObject::tr("Gather Movement"),//12
    QObject::tr("Cutter Movement"),//13
    QObject::tr("Crash Movement"),//14
    QObject::tr("Safety Movement"),//15
    QObject::tr("Horn Counter Limit Change"),//16
    QObject::tr("Horn Counter Reset"),//17
    QObject::tr("Anvil Tip Counter Limit Change"),//18
    QObject::tr("Anvil Tip Counter Reset"),//19
    QObject::tr("Gather Counter Limit Change"),//20
    QObject::tr("Gather Counter Reset"),//21
    QObject::tr("Anvil Guide Counter Limit Change"),//22
    QObject::tr("Anvil Guide Counter Reset"),//23
    QObject::tr("Converter Counter Limit Change"),//24
    QObject::tr("Converter Counter Reset"),//25
};


class MaintenanceLogElement
{
public:
    int RevCode;
    int MaintenanceLogID;
    QString MaintenanceType;
    QString MaintenanceMsg;
    unsigned int CreatedDate;
    int OperatorID;
public:
    MaintenanceLogElement()
    {
        RevCode = -1;
        MaintenanceLogID = -1;
        MaintenanceType.clear();
        MaintenanceMsg.clear();
        CreatedDate = 0;
        OperatorID = -1;
    }
    ~MaintenanceLogElement()
    {
        RevCode = -1;
        MaintenanceLogID = -1;
        MaintenanceType.clear();
        MaintenanceMsg.clear();
        CreatedDate = 0,
        OperatorID = -1;
    }
    MaintenanceLogElement operator=
    (const MaintenanceLogElement &MaintenanceLogObject) const
    {
        MaintenanceLogElement Obj;
        Obj.RevCode = MaintenanceLogObject.RevCode;
        Obj.MaintenanceLogID = MaintenanceLogObject.MaintenanceLogID;
        Obj.MaintenanceType = MaintenanceLogObject.MaintenanceType;
        Obj.MaintenanceMsg = MaintenanceLogObject.MaintenanceMsg;
        Obj.CreatedDate = MaintenanceLogObject.CreatedDate;
        Obj.OperatorID = MaintenanceLogObject.OperatorID;
        return Obj;
    }
};
#endif // MAINTENANCELOG_H
