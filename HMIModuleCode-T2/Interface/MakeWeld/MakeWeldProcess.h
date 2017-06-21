#ifndef OPERATEPROCESS_H
#define OPERATEPROCESS_H
#include <QObject>
#include "Interface/PresetElement.h"
#include "Interface/WeldResultElement.h"
#include "Modules/ThreadClass.h"
#include "ReadyStateMachine.h"

struct NecessaryInfo
{
    struct WorkOrderIndex CurrentWorkOrder;
    struct HarnessIndex CurrentHarness;
    struct SequenceIndex CurrentSequence;
    bool IsTestProcess;
};

class MakeWeldProcess : public QObject
{
    Q_OBJECT
public:
    enum GRAPHSTEP
    {
        POWERFst,
        HEIGHTSnd,
        STEPTrd,
    };
    PresetElement CurrentSplice;
    NecessaryInfo CurrentNecessaryInfo;
    WeldResultElement CurrentWeldResult;
private:
    static ThreadClass* m_pThread;
    ReadyStateMachine *m_pReadySM;
    int m_triedCount;
    GRAPHSTEP CurrentStep;
    bool WeldCycleStatus;
    bool PowerGraphReady;
    bool HeightGraphReady;

private:
    void UpdateIAFields();
    void UpdateWeldResult();
    bool HeightGraphReceive();
    bool PowerGraphReceive();
    static void WeldCycleDaemonThread(void*);
signals:
    void WeldCycleCompleted(const bool _status);
public slots:
    void WeldResultEventSlot(bool &bResult);
    void HeightGraphEventSlot(bool &bResult);
    void PowerGraphEventSlot(bool &bResult);
public:
    bool _start();
    bool _stop();
    bool _execute();
public:
    void StopTeachMode();
    void TeachModeProcess();
    void EraseLastEntry();
public:
    static MakeWeldProcess* Instance();
private:
    explicit MakeWeldProcess(QObject *parent = 0);
private:
    static MakeWeldProcess* _instance;
};

#endif // OPERATEPROCESS_H
