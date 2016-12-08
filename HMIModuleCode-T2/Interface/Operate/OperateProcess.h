#ifndef OPERATEPROCESS_H
#define OPERATEPROCESS_H
#include <QObject>
#include "Interface/PresetElement.h"
#include "Interface/WeldResultElement.h"
#include "Modules/UtilityClass.h"

class OperateProcess : public QObject
{
public:
    PresetElement CurrentSplice;
private:
    WeldResultElement CurrentWeldResult;
    static ThreadClass* m_Thread;
//    OperatorElement CurrentOperator;
private:
    void UpdateIAFields();
    void UpdateWeldResult();
    static void WeldCycleDaemonHandle(void*);
private slots:
    static void WeldResultFeedbackEventSlot();
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
