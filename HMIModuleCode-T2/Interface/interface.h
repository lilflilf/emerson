#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include <QObject>
//#include "definition.h"
#include "PresetElement.h"
#include "Settings/SysConfiguration.h"
#include "Settings/OperatorLibrary.h"

using namespace std;
enum TipsScreenMode{
    OKOnly      = 0x00, //only show Okay button
    OKCancel    = 0x01, //show Okay and cancel buttons
    RESETCancel = 0x02, //show Reset and cancel buttons
    Critical    = 0x10, //show Error sign
    Exclamation = 0x20, //show Warning sign
    Information = 0x40, //show Information sign
    Alarm       = 0x80, //show Alarm sign
};
struct BransonMessageBox{
    QString MsgTitle;
    QString MsgPrompt;
    int TipsMode;
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
public:
    void cMsgBox(struct BransonMessageBox* MsgBox);
    void dlgMaintWarning();
    //Recall for Screen
    void DatabaseOperating(int OperatingType, void*);

    //Following for the screen recall

    void BackupStatusData();

    bool SQLQuery(void* _DBObj, QMap<int, QString>* _EntireTableInfo);
    bool SQLQuery(void* _DBObj, int ID, QString Name, void* _DataStructure);

    bool SQLInsert(void* _DBObj, void* _DataStructure);

    bool SQLUpdate(void* _DBObj, void* _DataStructure);

    bool SQLDelete(void* _DBObj);
    bool SQLDelete(void* _DBObj, int ID, QString Name);
private:


signals:
    void ErrorMessageSignal(struct BransonMessageBox &MsgBox);
protected:
    InterfaceClass(QObject *parent = 0);
private:
    static InterfaceClass* _instance;
public:
    ~InterfaceClass();
};

#endif // INTERFACE_H
