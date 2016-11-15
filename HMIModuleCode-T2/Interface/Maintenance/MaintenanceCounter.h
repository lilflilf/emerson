#ifndef MAINTENANCECOUNTER_H
#define MAINTENANCECOUNTER_H
#include "Maintenance.h"

class MaintenanceCounter : public Maintenance
{
public:
    virtual bool _start();
    virtual bool _stop();
    virtual bool _execute(int funCode);
public:
    MaintenanceCounter();
};

#endif // MAINTENANCECOUNTER_H
