#ifndef OPERATEPROCESS_H
#define OPERATEPROCESS_H
#include <QObject>
#include "Interface/PresetElement.h"
#include "Interface/WeldResultElement.h"
#include "Modules/UtilityClass.h"
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

enum QUALITYTYPE
{
    QUALITYTIME,
    QUALITYPOWER,
    QUALITYPREHEIGHT,
    QUALITYPOSTHEIGHT,
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
    static void AcceptWeldResult(void*);
signals:
    void WeldCycleCompleted(const bool &_status);
private slots:
    void WeldResultFeedbackEventSlot();
public:
    void _start();
    void _stop();
    void _execute();

    void ControlLimitProcess(enum QUALITYTYPE Type, QList<int> &RawList, int USL, int LSL,
                             int* UCL, int* LCL);
    void StopTeachMode();
public:
    static OperateProcess* Instance();
private:
    explicit OperateProcess(QObject *parent = 0);
private:
    static OperateProcess* _instance;
};

#endif // OPERATEPROCESS_H
