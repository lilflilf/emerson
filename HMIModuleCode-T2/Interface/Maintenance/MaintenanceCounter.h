#ifndef MAINTENANCECOUNTER_H
#define MAINTENANCECOUNTER_H
#include "Maintenance.h"

class MaintenanceCounter : public Maintenance
{
public:
    virtual void _start();
    virtual void _stop();
    virtual void _execute(int funCode);
public:
    MaintenanceCounter();
};

#endif // MAINTENANCECOUNTER_H
