#ifndef TIMERCLASS_H
#define TIMERCLASS_H

#include <QObject>
#include <QTimer>
class TimerClass : public QObject
{
    Q_OBJECT
private:
    QTimer *Timer;
public:
    bool b_Timeout;
public:
    void SetCommandTimer(int Time = 3000);
//    void ResetCommandTimer();
    bool IsCommandTimeout();
    void ResetCommandTimer();
public:
    explicit TimerClass(QObject *parent = 0);
    ~TimerClass();
signals:

private slots:
    void TimeoutEventSlot();
};

#endif // TIMERCLASS_H
