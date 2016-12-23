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
    static TimerClass* Instance();
protected:
    explicit TimerClass(QObject *parent = 0);
private:
    static TimerClass* _instance;
public:
    ~TimerClass();
signals:

private slots:
    void TimeoutEventSlot();
};

#endif // TIMERCLASS_H
