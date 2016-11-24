#ifndef MAINTENANCECOUNTER_H
#define MAINTENANCECOUNTER_H
#include "Maintenance.h"
#include "Interface/Definition.h"
enum TOOLINGCOUNT
{
    HORNCHANGE,
    HORNRESET,
    ANVILTIPCHANGE,
    ANVILTIPRESET,
    GATHERCHANGE,
    GATHERRESET,
    ANVILGUIDECHANGE,
    ANVILGUIDERESET,
    CONVERTERCHANGE,
    CONVERTERRESET,
    ACTUATOR,
};
struct MaintenanceCounterForScreen
{
    BRANSONDATA HornCounterLimit;
    QString HornCurrentCount;
    QString HornDateStarted;
    BRANSONDATA AnvilTipCounterLimit;
    QString AnvilTipCurrentCount;
    QString AnvilTipDateStarted;
    BRANSONDATA GatherCounterLimit;
    QString GatherCurrentCount;
    QString GatherDateStarted;
    BRANSONDATA AnvilGuideCounterLimit;
    QString AnvilGuideCurrentCount;
    QString AnvilGuideDateStarted;
    BRANSONDATA ConverterCounterLimit;
    QString ConverterCurrentCount;
    QString ConverterDateStarted;
    QString ActuatorCurrentCount;
    QString ActuatorDateStarted;
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
