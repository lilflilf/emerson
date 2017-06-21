#ifndef MAINTENANCECOUNTER_H
#define MAINTENANCECOUNTER_H
#include "Maintenance.h"
#include "Interface/Definition.h"

class MaintenanceCounter : public Maintenance
{
private:
    enum TOOLINGCOUNTCHANGE
    {
        HORNCOUNTCHANGE,
        ANVILCOUNTCHANGE,
        GATHERCOUNTCHANGE,
        GUIDECOUNTCHANGE,
    };

    enum TOOLINGENERGYCHANGE
    {
        HORNENERGYCHANGE,
        ANVILENERGYCHANGE,
        GATHERENERGYCHANGE,
        GUIDEENERGYCHANGE,
    };

    enum TOOLINGRESET
    {
        HORNRESET,
        ANVILRESET,
        GATHERRESET,
        GUIDERESET,
    };
    enum TOOLING80PERCENTALARM
    {
        HORNCOUNTER80PERCENTALARM = 0,
        HORNENERGY80PERCENTALARM = 1,
        ANVILCOUNTER80PERCENTALARM = 2,
        ANVILENERGY80PERCENTALARM = 3,
        GATHERCOUNTER80PERCENTALARM = 4,
        GATHERENERGY80PERCENTALARM = 5,
        GUIDCOUNTER80PERCENTALARM = 6,
        GUIDENERGY80PERCENTALARM = 7,
    };
    enum TOOLING100PERCENTLOCK
    {
        HORNCOUNTER100PERCENTLOCK = 0,
        HORNENERGY100PERCENTLOCK = 1,
        ANVILCOUNTER100PERCENTLOCK = 2,
        ANVILENERGY100PERCENTLOCK = 3,
        GATHERCOUNTER100PERCENTLOCK = 4,
        GATHERENERGY100PERCENTLOCK = 5,
        GUIDCOUNTER100PERCENTLOCK = 6,
        GUIDENERGY100PERCENTLOCK = 7,
    };
public:
    enum TOOLING
    {
        ITEM_HORN,
        ITEM_ANVIL,
        ITEM_GATHER,
        ITEM_GUIDE,
        ITEM_SYSTEM,
    };
    struct MaintenanceCounterForScreen
    {
        QString HornPartNumber;
        BRANSONDATA HornCounterLimit;
        BRANSONDATA HornEnergyLimit;
        QString HornCurrentCount;
        QString HornCurrentEnergy;
        QString HornDateStarted;
        bool HornCounter80PercentAlarm;
        bool HornCounter100PercentLock;
        bool HornEnergy80PercentAlarm;
        bool HornEnergy100PercentLock;

        QString AnvilPartNumber;
        BRANSONDATA AnvilCounterLimit;
        BRANSONDATA AnvilEnergyLimit;
        QString AnvilCurrentCount;
        QString AnvilCurrentEnergy;
        QString AnvilDateStarted;
        bool AnvilCounter80PercentAlarm;
        bool AnvilCounter100PercentLock;
        bool AnvilEnergy80PercentAlarm;
        bool AnvilEnergy100PercentLock;

        QString GatherPartNumber;
        BRANSONDATA GatherCounterLimit;
        BRANSONDATA GatherEnergyLimit;
        QString GatherCurrentCount;
        QString GatherCurrentEnergy;
        QString GatherDateStarted;
        bool GatherCounter80PercentAlarm;
        bool GatherCounter100PercentLock;
        bool GatherEnergy80PercentAlarm;
        bool GatherEnergy100PercentLock;

        QString GuidePartNumber;
        BRANSONDATA GuideCounterLimit;
        BRANSONDATA GuideEnergyLimit;
        QString GuideCurrentCount;
        QString GuideCurrentEnergy;
        QString GuideDateStarted;
        bool GuideCounter80PercentAlarm;
        bool GuideCounter100PercentLock;
        bool GuideEnergy80PercentAlarm;
        bool GuideEnergy100PercentLock;

        QString ActuatorCurrentCount;
        QString ActuatorDateStarted;
    };

private:
    void ChangeHornCounterLimit();
    void ChangeHornEnergyLimit();
    void ResetHornCurrentCountAndEnergy();
    void ChangeAnvilCounterLimit();
    void ChangeAnvilEnergyLimit();
    void ResetAnvilCurrentCountAndEnergy();
    void ChangeGatherCounterLimit();
    void ChangeGatherEnergyLimit();
    void ResetGatherCurrentCountAndEnergy();
    void ChangeGuideCounterLimit();
    void ChangeGuideEnergyLimit();
    void ResetGuideCurrentCountAndEnergy();
public:
    MaintenanceCounterForScreen CurrentMaintenanceCounter;
public:
    bool _recall();
    virtual bool _start();
    virtual bool _stop();
    virtual bool _execute(int funCode);
public:
    MaintenanceCounter();
};

#endif // MAINTENANCECOUNTER_H
