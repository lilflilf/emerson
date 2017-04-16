#include "ReadyStateMachine.h"
#include "Modules/typedef.h"
#include "Modules/M102IA.h"
#include "Modules/M2010.h"
ReadyStateMachine* ReadyStateMachine::_instance = NULL;
QTimer* ReadyStateMachine::m_pDaemonTmr = NULL;
ReadyStateMachine* ReadyStateMachine::Instance()
{
    if(_instance == NULL){
        _instance = new ReadyStateMachine();
    }
    return _instance;
}

ReadyStateMachine::ReadyStateMachine(QObject *parent) : QObject(parent)
{
    m_pDaemonTmr = NULL;
    ReadyState = IDLE;
}

void ReadyStateMachine::_start()
{
    if(m_pDaemonTmr != NULL)
    {
        delete m_pDaemonTmr;
        m_pDaemonTmr = NULL;
    }
    m_pDaemonTmr = new QTimer(this);
    connect(m_pDaemonTmr, SIGNAL(timeout()),this, SLOT(TimeoutEventSlot()));
    m_pDaemonTmr->setInterval(DELAY1SEC);//1second
    m_pDaemonTmr->start();
}

void ReadyStateMachine::_stop()
{
    if(m_pDaemonTmr != NULL)
    {
        if(m_pDaemonTmr->isActive() == true)
            m_pDaemonTmr->stop();
        delete m_pDaemonTmr;
        m_pDaemonTmr = NULL;
    }
}

void ReadyStateMachine::TimeoutEventSlot()
{
    M102IA *_M102IA = M102IA::Instance();
    M2010  *_M2010  = M2010::Instance();
    m_pDaemonTmr->stop();
    switch(ReadyState)
    {
    case READYON:
        if ((_M102IA->IOstatus.IO & BIT14) != BIT14)
        {
            _M2010->ReceiveFlags.HostReadyData = false;
            _M102IA->IACommand(IAComHostReady);
            _M102IA->WaitForResponseAfterSent(DELAY1SEC,&_M2010->ReceiveFlags.HostReadyData);
            DEBUG_PRINT(_M2010->ReceiveFlags.HostReadyData);
        }
        break;
    case READYOFF:
    default:
        break;
    }
    m_pDaemonTmr->start();
}
