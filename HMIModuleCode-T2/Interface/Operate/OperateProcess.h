#ifndef OPERATEPROCESS_H
#define OPERATEPROCESS_H
#include <QObject>
#include "Interface/PresetElement.h"
#include "Interface/WeldResultElement.h"
#include "Modules/ThreadClass.h"
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

class OperateProcess : public QObject
{
    Q_OBJECT
public:
    PresetElement CurrentSplice;
    struct NecessaryInfo CurrentNecessaryInfo;
    WeldResultElement CurrentWeldResult;

private:
    static ThreadClass* m_Thread;
    int m_triedCount;
    GRAPHSTEP CurrentStep;
    bool WeldCycleStatus;
//    OperatorElement CurrentOperator;
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
    void WeldResultFeedbackEventSlot(bool &bResult);
    void CheckWeldAlarm();
public:
    bool _start();
    bool _stop();
    bool _execute();

    void ControlLimitProcess(enum QUALITYTYPE Type, QList<int> &RawList, int USL, int LSL,
                             int* UCL, int* LCL);
    void StopTeachMode();
    void TeachModeProcess();
public:
    static OperateProcess* Instance();
private:
    explicit OperateProcess(QObject *parent = 0);
private:
    static OperateProcess* _instance;
};

#endif // OPERATEPROCESS_H
