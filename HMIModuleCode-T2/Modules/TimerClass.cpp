#include "TimerClass.h"
#include <QTimer>
#include <QDebug>
TimerClass::TimerClass(QObject *parent) : QObject(parent)
{

}

void TimerClass::SetCommandTimer(int Time)
{
    b_Timeout = false;
    QTimer::singleShot(Time, Qt::VeryCoarseTimer, this, TimeoutEventSlot);
}

void TimerClass::TimeoutEventSlot()
{
    b_Timeout = true;
}

bool TimerClass::IsCommandTimeout()
{
    return b_Timeout;
}
