#ifndef TOOLCHANGE_H
#define TOOLCHANGE_H
#include "Maintenance.h"

class ToolChange : public Maintenance
{
public:
    virtual void _start();
    virtual void _stop();
    virtual void _execute(int funCode);
public:
    ToolChange();
};

#endif // TOOLCHANGE_H
