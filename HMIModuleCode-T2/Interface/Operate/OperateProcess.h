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
};

class OperateProcess : public QObject
{
    Q_OBJECT
public:
    PresetElement CurrentSplice;
    struct NecessaryInfo CurrentNecessaryInfo;
private:
    WeldResultElement CurrentWeldResult;
    static ThreadClass* m_Thread;
//    OperatorElement CurrentOperator;
private:
    void UpdateIAFields();
    void UpdateWeldResult();
    bool HeightGraphReceive();
    bool PowerGraphReceive();
    static void WeldCycleDaemonThread(void*);
private slots:
    void WeldResultFeedbackEventSlot();
public:
    void _start();
    void _stop();
    void _execute();
signals:

public slots:

public:
    static OperateProcess* Instance();
private:
    explicit OperateProcess(QObject *parent = 0);
private:
    static OperateProcess* _instance;
};

#endif // OPERATEPROCESS_H
