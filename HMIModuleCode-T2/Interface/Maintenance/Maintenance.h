#ifndef MAINTENANCE_H
#define MAINTENANCE_H
#include <QObject>

class Maintenance : public QObject
{
public:
    virtual bool _start() = 0;
    virtual bool _stop() = 0;
    virtual bool _execute(int funCode) = 0;
};

#endif // MAINTENANCE_H
