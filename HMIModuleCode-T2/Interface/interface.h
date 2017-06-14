#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include <QObject>
#include <QDebug>
//#include "definition.h"
#include "PresetElement.h"
#include "SysConfiguration.h"
#include "Settings/OperatorLibrary.h"
#include "WorkOrderElement.h"
#define HMI_PRINT (qDebug() <<"That needs to be fixed: " << __FILE__ << __FUNCTION__ << __LINE__ << ": ")
using namespace std;
enum TipsScreenMode{
    OKOnly      = 0x00, //only show Okay button
    OKCancel    = 0x01, //show Okay and cancel buttons
    RESETCancel = 0x02, //show Reset and cancel buttons
    ACCEPTReject = 0x04, //show Accept and Reject buttons
    Critical    = 0x10, //show Error sign
    Exclamation = 0x20, //show Warning sign
    Information = 0x40, //show Information sign
    Alarm       = 0x80, //show Alarm sign
    QualityAlarm = 0x100, //show Alarm Sign, and only for the lock on alarm.
    OFF_ON_LINE = 0x200,//show On Line and Off Line

};
struct BransonMessageBox{
    QString MsgTitle;
    QString MsgPrompt;
    int TipsMode;
    void* _Object;
    void (*func_ptr)(void*);
};


class InterfaceClass:public QObject
{
         Q_OBJECT
public:
    static InterfaceClass* Instance();
    //Following for the screen showing using signal
public:
    Status_Data StatusData;
    Status_Data tempStatusData;         //Used by routines before an OK or Save
    Status_Data DefaultStatusData;
    VersionList PreviousVersions;
    VersionList CurrentVersions;
    OperatorElement CurrentOperator;
    WorkOrderElement CurrentWorkOrder;
    bool FirstScreenComesUp;
    bool ApplicationFirstStartFlag;
public:
    void cMsgBox(struct BransonMessageBox* MsgBox);
    void DispearMsgBox();
    void ShownAlarmSign();
    void LockOnAlarm(OperatorElement::PASSWORDCONTROL ControlLevel);
    static void HotRestartSys(void* _Obj);
private:
    void CheckBransonFolder();
signals:
    void EnableErrorMessageSignal(struct BransonMessageBox &MsgBox);
    void DisableErrorMessageSignal(struct BransonMessageBox &MsgBox);
    void ThereAreAlarmItemsSignal();
public slots:
    void AnyAlarmEventSlot(bool &bResult);
protected:
    InterfaceClass(QObject *parent = 0);
private:
    BransonMessageBox MessageBox;
    static InterfaceClass* _instance;
    BransonMessageBox tmpMsgBox;
public:
    ~InterfaceClass();
};

#endif // INTERFACE_H
