#include "ThreadClass.h"
#include <QDebug>
ThreadClass::ThreadClass(QObject *parent, void* _func,
                         void* arg) : QThread(parent)
{
    m_stop = false;
    m_suspend = false;
    m_callbackHandle = (ptrCallbackFun)_func;
    m_arg = arg;
}

ThreadClass::~ThreadClass()
{
    m_stop = false;
    m_suspend = false;
    m_callbackHandle = NULL;
    m_arg = NULL;
}

void ThreadClass::run()
{
    if(m_callbackHandle != NULL)
    {
        while(1)
        {
            if(m_stop == true)
                break;
            if(m_suspend == false)
            {
                m_callbackHandle(m_arg);
                qDebug()<<"Thread process";
            }else
            {
                qDebug()<<"Thread suspend";
            }
            QThread::msleep(500);
        }
    }else{
        qDebug()<<"No function need to be executed";
    }
}

void ThreadClass::setStopEnabled(bool enabled)
{
    m_stop = enabled;
}

void ThreadClass::setSuspendEnabled(bool enabled)
{
    m_suspend = enabled;
}
