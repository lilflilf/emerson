#include "TimerClass.h"
#include <QTimer>
#include <QDebug>
TimerClass* TimerClass::_instance = NULL;
TimerClass* TimerClass::Instance()
{
    if(_instance == 0){
        _instance = new TimerClass();
    }
    return _instance;
}
TimerClass::TimerClass(QObject *parent) : QObject(parent)
{
    Timer = NULL;
}
TimerClass::~TimerClass()
{
    Timer = NULL;
}

void TimerClass::SetCommandTimer(int Time)
{
    b_Timeout = false;
    Timer = new QTimer();
    connect((QTimer*)Timer, SIGNAL(timeout()),this, SLOT(IsCommandTimeout));
    ((QTimer*)Timer)->start(Time);
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
    if(((QTimer*)Timer)->isActive() == true)
        ((QTimer*)Timer)->stop();
    if(Timer != NULL)
    {
        delete (QTimer*)Timer;
        Timer = NULL;
    }
}
