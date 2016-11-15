#ifndef TOOLCHANGE_H
#define TOOLCHANGE_H
#include "Maintenance.h"

class ToolChange : public Maintenance
{
public:
    virtual bool _start();
    virtual bool _stop();
    virtual bool _execute(int funCode);
public:
    ToolChange();
};

#endif // TOOLCHANGE_H
