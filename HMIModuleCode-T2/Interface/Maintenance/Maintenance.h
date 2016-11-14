#ifndef MAINTENANCE_H
#define MAINTENANCE_H
#include <QObject>
const QString MaintenanceTypeString[] = {
    QObject::tr("Calibration"),
    QObject::tr("Tooling Change"),
    QObject::tr("Advanced Maintenance"),
    QObject::tr("Maintenance Counter"),
};

const QString MaintenanceMessageString[] = {
    QObject::tr("Width & Height Calibration Process Start"),
    QObject::tr("Width & Height Calibration Process Complete"),
    QObject::tr("Width & Height Calibration Process Cancel"),
    QObject::tr("Amplitude Calibration Process Start"),
    QObject::tr("Amplitude Calibration Process Complete"),
    QObject::tr("Amplitude Calibration Process Cancel"),
    QObject::tr("Tooling Change Process Start"),
    QObject::tr("Tooling Change Process Finish"),
    QObject::tr("Anvil Arm Movement"),
    QObject::tr("Gather Movement"),
    QObject::tr("Cutter Movement"),
    QObject::tr("Crash Movement"),
    QObject::tr("Safety Movement"),
    QObject::tr("Horn Counter Limit Change"),
    QObject::tr("Horn Counter Reset"),
    QObject::tr("Anvil Tip Counter Limit Change"),
    QObject::tr("Anvil Tip Counter Reset"),
    QObject::tr("Gather Counter Limit Change"),
    QObject::tr("Gather Counter Reset"),
    QObject::tr("Anvil Guide Counter Limit Change"),
    QObject::tr("Anvil Guide Counter Reset"),
    QObject::tr("Converter Counter Limit Change"),
    QObject::tr("Converter Counter Reset"),
};

enum MAINTAINTYPE
{
    CALIBRATE,
    TOOLCHANGE,
    ADVMAINTAIN,
    MAINTAINCOUNT,

};

class MaintenanceLogElement
{
public:
    int RevCode;
    int MaintenanceLogID;
    enum MAINTAINTYPE MaintenanceType;
    int MaintenanceMsgIndex;
    unsigned int CreatedDate;
    int OperatorID;

};

class Maintenance : public QObject
{
public:
    virtual bool _start() = 0;
    virtual bool _stop() = 0;
    virtual bool _execute(int funCode) = 0;
};

#endif // MAINTENANCE_H
