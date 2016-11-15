#ifndef MAINTENANCECOUNTER_H
#define MAINTENANCECOUNTER_H
#include "Maintenance.h"
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
    virtual bool _start();
    virtual bool _stop();
    virtual bool _execute(int funCode);
public:
    MaintenanceCounter();
};

#endif // MAINTENANCECOUNTER_H
