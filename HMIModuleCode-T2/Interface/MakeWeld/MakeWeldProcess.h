#ifndef OPERATEPROCESS_H
#define OPERATEPROCESS_H
#include <QObject>
#include "Interface/PresetElement.h"
#include "Interface/WeldResultElement.h"
#include "Modules/ThreadClass.h"
#include <QTimer>
struct NecessaryInfo
{
    struct WorkOrderIndex CurrentWorkOrder;
    struct PartIndex CurrentPart;
    bool IsTestProcess;
};
enum GRAPHSTEP
{
    POWERFst,
    HEIGHTSnd,
    STEPTrd,
};

class MakeWeldProcess : public QObject
{
    Q_OBJECT
public:
    PresetElement CurrentSplice;
    struct NecessaryInfo CurrentNecessaryInfo;
    WeldResultElement CurrentWeldResult;

private:
    static ThreadClass* m_Thread;
    static QTimer *m_DaemonTmr;
    static bool m_bTmrRunningFlag;
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
//    static void AcceptWeldResult(void*);
signals:
    void WeldCycleCompleted(const bool &_status);
public slots:
    void WeldResultEventSlot(bool &bResult);
    void AnyAlarmEventSlot(bool &bResult);
    void HeightGraphEventSlot(bool &bResult);
    void PowerGraphEventSlot(bool &bResult);
    void TimeoutEventSlot();
public:
    bool _start();
    bool _stop();
    bool _execute();

    void ControlLimitProcess(enum QUALITYTYPE Type, QList<int> &RawList, int USL, int LSL,
                             int* UCL, int* LCL);
    void StopTeachMode();
    void TeachModeProcess();
public:
    static MakeWeldProcess* Instance();
private:
    explicit MakeWeldProcess(QObject *parent = 0);
private:
    static MakeWeldProcess* _instance;
};

#endif // OPERATEPROCESS_H
