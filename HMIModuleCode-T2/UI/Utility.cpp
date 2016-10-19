#include "UI\Utility.h"
#include <QTimerEvent>
#include <QDateTime>
#include <qdebug>
Utility::Utility(QObject *parent)
    :QObject(parent)
    ,m_nCurrentTimer(0)
{
    qDebug()<<"Utility::Utility() called";
    start();

}

void Utility::start()
{
    if(m_nCurrentTimer == 0){
        qDebug()<<"Utility::start() called";
        m_nCurrentTimer = startTimer(1000);
    }
}

void Utility::stop()
{
    if(m_nCurrentTimer > 0)
    {
        killTimer(m_nCurrentTimer);
        m_nCurrentTimer = 0;
    }
}

void Utility::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_nCurrentTimer)
    {
        emit currentTime(QDateTime::currentDateTime().toString("h:mm AP    d MMM yyyy "));
    }
    else
    {
        QObject::timerEvent(event);
    }
}
