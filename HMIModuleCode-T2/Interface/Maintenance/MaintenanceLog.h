#ifndef MAINTENANCELOG_H
#define MAINTENANCELOG_H
#include <QObject>

const QString MaintenanceTypeString[] = {
    QObject::tr("Calibration"),
    QObject::tr("Tooling Change"),
    QObject::tr("Advanced Maintenance"),
    QObject::tr("Maintenance Counter"),
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
    QObject::tr("Horn Energy Limit Change"), //17
    QObject::tr("Horn Counter Reset"),//18
    QObject::tr("Horn 80% Limit Alarm "), //19
    QObject::tr("Horn 100% Limit Lock "), //20

    QObject::tr("Anvil Counter Limit Change"),//21
    QObject::tr("Anvil Energy Limit Change"), //22
    QObject::tr("Anvil Counter Reset"),//23
    QObject::tr("Anvil 80% Limit Alarm "), //24
    QObject::tr("Anvil 100% Limit Lock "), //25

    QObject::tr("Gather Counter Limit Change"),//26
    QObject::tr("Gather Energy Limit Change"), //27
    QObject::tr("Gather Counter Reset"),//28
    QObject::tr("Gather 80% Limit Alarm "),//29
    QObject::tr("Gather 100% Limit Lock "),//30

    QObject::tr("Guide Counter Limit Change"),//31
    QObject::tr("Guide Energy Limit Change"), //32
    QObject::tr("Guide Counter Reset"),//33
    QObject::tr("Guide 80% Limit Alarm "),//34
    QObject::tr("Guide 100% Limit Lock "),//35
};


class MaintenanceLogElement
{
public:
    enum MAINTAINTYPE
    {
        CALIBRATE,
        TOOLCHANGE,
        ADVMAINTAIN,
        MAINTAINCOUNT,
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
        HORN_ENERGY_LIMIT      = 17,
        HORN_COUNT_RESET       = 18,
        HORN_80PERCENT_ALARM   = 19,
        HORN_100PERCENT_LOCK   = 20,

        ANVIL_COUNT_LIMIT      = 21,
        ANVIL_ENERGY_LIMIT     = 22,
        ANVIL_COUNT_RESET      = 23,
        ANVIL_80PERCENT_ALARM  = 24,
        ANVIL_100PERCENT_LOCK  = 25,

        GATHER_COUNT_LIMIT     = 26,
        GATHER_ENERGY_LIMIT    = 27,
        GATHER_COUNT_RESET     = 28,
        GATHER_80PERCENT_ALARM = 29,
        GATHER_100PERCENT_LOCK = 30,

        GUIDE_COUNT_LIMIT      = 31,
        GUIDE_ENERGY_LIMIT     = 32,
        GUIDE_COUNT_RESET      = 33,
        GUIDE_80PERCENT_ALARM  = 34,
        GUIDE_100PERCENT_LOCK  = 35,
    };

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
