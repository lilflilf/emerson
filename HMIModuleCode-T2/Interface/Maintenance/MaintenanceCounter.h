#ifndef MAINTENANCECOUNTER_H
#define MAINTENANCECOUNTER_H
#include "Maintenance.h"
#include "Interface/Definition.h"

class MaintenanceCounter : public Maintenance
{
private:
    enum TOOLING
    {
        ITEM_HORN,
        ITEM_ANVIL,
        ITEM_GATHER,
        ITEM_GUIDE,
        ITEM_SYSTEM,
    };

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
        HORN80PERCENTALARM,
        ANVIL80PERCENTALARM,
        GATHER80PERCENTALARM,
        GUID80PERCENTALARM,
    };
    enum TOOLING100PERCENTLOCK
    {
        HORN100PERCENTLOCK,
        ANVIL100PERCENTLOCK,
        GATHER100PERCENTLOCK,
        GUID100PERCENTLOCK,
    };
public:
    struct MaintenanceCounterForScreen
    {
        QString HornPartNumber;
        BRANSONDATA HornCounterLimit;
        BRANSONDATA HornEnergyLimit;
        QString HornCurrentCount;
        QString HornCurrentEnergy;
        QString HornDateStarted;
        bool Horn80PercentAlarm;
        bool Horn100PercentLock;

        QString AnvilPartNumber;
        BRANSONDATA AnvilCounterLimit;
        BRANSONDATA AnvilEnergyLimit;
        QString AnvilCurrentCount;
        QString AnvilCurrentEnergy;
        QString AnvilDateStarted;
        bool Anvil80PercentAlarm;
        bool Anvil100PercentLock;

        QString GatherPartNumber;
        BRANSONDATA GatherCounterLimit;
        BRANSONDATA GatherEnergyLimit;
        QString GatherCurrentCount;
        QString GatherCurrentEnergy;
        QString GatherDateStarted;
        bool Gather80PercentAlarm;
        bool Gather100PercentLock;

        QString GuidePartNumber;
        BRANSONDATA GuideCounterLimit;
        BRANSONDATA GuideEnergyLimit;
        QString GuideCurrentCount;
        QString GuideCurrentEnergy;
        QString GuideDateStarted;
        bool Guide80PercentAlarm;
        bool Guide100PercentLock;

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
