#include "TimerClass.h"
#include <QDebug>

TimerClass::TimerClass(QObject *parent) : QObject(parent)
{
    Timer = NULL;
    b_Timeout = false;
    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()),this, SLOT(TimeoutEventSlot()));

}
TimerClass::~TimerClass()
{
    if(Timer != NULL)
    {
        delete Timer;
        Timer = NULL;
    }
}

void TimerClass::SetCommandTimer(int Time)
{
    Timer->start(Time);
}

void TimerClass::TimeoutEventSlot()
{
    b_Timeout = true;
}

bool TimerClass::IsCommandTimeout()
{
    return b_Timeout;
}

void TimerClass::ResetCommandTimer()
{
    if(Timer->isActive() == true)
    {
        Timer->stop();
    }
}
