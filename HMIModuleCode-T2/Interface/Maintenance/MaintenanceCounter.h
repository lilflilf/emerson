#ifndef MAINTENANCECOUNTER_H
#define MAINTENANCECOUNTER_H
#include "Maintenance.h"
#include "Interface/Definition.h"
enum TOOLINGCOUNT
{
    HORNCHANGE,
    HORNRESET,
    HORN80PERCENTALARM,
    ANVILTIPCHANGE,
    ANVILTIPRESET,
    ANVILTIP80PERCENTALARM,
    GATHERCHANGE,
    GATHERRESET,
    GATHER80PERCENTALARM,
    ANVILGUIDECHANGE,
    ANVILGUIDERESET,
    ANVILGUID80PERCENTALARM,
    CONVERTERCHANGE,
    CONVERTERRESET,
    CONVERTER80PERCENTALARM,
    ACTUATOR,
};
struct MaintenanceCounterForScreen
{
    BRANSONDATA HornCounterLimit;
    QString HornCurrentCount;
    QString HornDateStarted;
    bool Horn80PercentAlarm;
    BRANSONDATA AnvilTipCounterLimit;
    QString AnvilTipCurrentCount;
    QString AnvilTipDateStarted;
    bool Anvil80PercentAlarm;
    BRANSONDATA GatherCounterLimit;
    QString GatherCurrentCount;
    QString GatherDateStarted;
    bool Gather80PercentAlarm;
    BRANSONDATA AnvilGuideCounterLimit;
    QString AnvilGuideCurrentCount;
    QString AnvilGuideDateStarted;
    bool AnvilGuide80PercentAlarm;
    BRANSONDATA ConverterCounterLimit;
    QString ConverterCurrentCount;
    QString ConverterDateStarted;
    bool Converter80PercentAlarm;
    QString ActuatorCurrentCount;
    QString ActuatorDateStarted;
    QString ActuatorSoftwareVersion;
    QString ActuatorPartNumber;
    QString ActuatorSerialNumber;
    QString ActuatorModuleNumber;
};

class MaintenanceCounter : public Maintenance
{
private:
    void ChangeHornCounterLimit();
    void ResetHornCurrentCount();
    void ChangeAnvilTipCounterLimit();
    void ResetAnvilTipCurrentCount();
    void ChangeGatherCounterLimit();
    void ResetGatherCurrentCount();
    void ChangeAnvilGuideCounterLimit();
    void ResetAnvilGuideCurrentCount();
    void ChangeConverterCounterLimit();
    void ResetConverterCurrentCount();
public:
    struct MaintenanceCounterForScreen CurrentMaintenanceCounter;
public:
    bool _recall();
    virtual bool _start();
    virtual bool _stop();
    virtual bool _execute(int funCode);
public:
    MaintenanceCounter();
};

#endif // MAINTENANCECOUNTER_H
