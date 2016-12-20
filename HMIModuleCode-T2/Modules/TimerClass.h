#ifndef TIMERCLASS_H
#define TIMERCLASS_H

#include <QObject>

class TimerClass : public QObject
{
    Q_OBJECT
public:
    int m_nCurrentTimer;
    bool b_Timeout;
public:
    void SetCommandTimer(int Time = 3000);
//    void ResetCommandTimer();
    bool IsCommandTimeout();
public:
    explicit TimerClass(QObject *parent = 0);

signals:

private slots:
    void TimeoutEventSlot();
};

#endif // TIMERCLASS_H
