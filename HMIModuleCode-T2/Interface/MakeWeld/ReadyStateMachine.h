#ifndef READYSTATEMACHINE_H
#define READYSTATEMACHINE_H

#include <QObject>
#include <QTimer>
class ReadyStateMachine : public QObject
{
    Q_OBJECT
private:
    static QTimer *m_pDaemonTmr;
public:
    enum STATE
    {
        IDLE = 0,
        READYON,
        READYOFF,
    };
    STATE ReadyState;
    void _start();
    void _stop();
signals:

public slots:
    void TimeoutEventSlot();
public:
    static ReadyStateMachine* Instance();
private:
    explicit ReadyStateMachine(QObject *parent = 0);
private:
    static ReadyStateMachine* _instance;
};

#endif // READYSTATEMACHINE_H
