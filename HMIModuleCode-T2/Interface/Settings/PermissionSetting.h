#ifndef PERMISSIONSETTING_H
#define PERMISSIONSETTING_H
#include <QString>
#include <QObject>
#include "Interface/Interface.h"
enum PWPMasks
{
//    PWPAdminOnly& = &H0&        'Used as a flag in the mask field
    PWPCreateNewMask        =     0x01,  //Bit 0
    PWPEditExistingMask     =     0x02,  //Bit 1
    PWPOperateMask          =     0x04,  //Bit 2
    PWPTestMask             =     0x08,  //Bit 3
    PWPTeachModeMask        =     0x10,  //Bit 4
    PWPCalibrateMask        =     0x20,  //Bit 5
    PWPToolChangeMask       =     0x40,  //Bit 6
    PWPAdvMaintMask         =     0x80,  //Bit 7
    PWPMaintCounterMask     =   0x0100,  //Bit 8
    PWPMaintLogMask         =   0x0200,  //Bit 9
    PWPWorkOrderHistoryMask =   0x0400,  //Bit 10
    PWPStatisticalTrendMask =   0x0800,  //Bit 11
    PWPErrAlarmLogMask      =   0x1000,  //Bit 12
    PWPLibraryMask          =   0x2000,  //Bit 13
    PWPVersionInfoMask      =   0x4000,  //Bit 14
    PWPPermissionSetMask    =   0x8000,  //Bit 15
    PWPWeldDefaultsMask     = 0x010000,  //Bit 16
    PWPOperatorLibMask      = 0x020000,  //Bit 17
    PWPDataCommMask         = 0x040000,  //Bit 18
    PWPLockOnAlarmMask      = 0x080000,  //Bit 19
};
const QString FunctionNameList[] = {
    QObject::tr("Create New"),                //Bit 0
    QObject::tr("Edit Existing"),             //Bit 1
    QObject::tr("Operate"),                   //Bit 2
    QObject::tr("Test"),                      //Bit 3
    QObject::tr("Teach Mode"),                //Bit 4
    QObject::tr("Calibration"),               //Bit 5
    QObject::tr("Tool Change"),               //Bit 6
    QObject::tr("Advanced Maintenance"),      //Bit 7
    QObject::tr("Maintenance Counter"),       //Bit 8
    QObject::tr("Maintenance Log"),           //Bit 9
    QObject::tr("Work Order History"),        //Bit 10
    QObject::tr("Statistical Trend"),         //Bit 11
    QObject::tr("Error/Alarm Log"),           //Bit 12
    QObject::tr("Library"),                   //Bit 13
    QObject::tr("Version Information"),       //Bit 14
    QObject::tr("Permission Setting"),        //Bit 15
    QObject::tr("Weld Defaults"),             //Bit 16
    QObject::tr("Operator Library"),          //Bit 17
    QObject::tr("Data/Communication"),        //Bit 18
    QObject::tr("Lock On Alarm"),             //Bit 19
};

enum PermissionLevel
{
    Level1 = 1,
    Level2 = 2,
    Level3 = 3,
    Level4 = 4,
};


class PermissionSetting : public QObject
{
    Q_OBJECT
public:
    void InitializeFRAM();
    void LockOnAlarm();
    //for example
//    void SetPermissionSetting(enum SCREEN_MODE currentScreen,
//                              enum PermissionLevel currentLevel)
//    {
//        InterfaceClass* _Interface = InterfaceClass::Instance();
//        _Interface->StatusData.PasswordData[currentLevel].PWPermissions
//                |= 2 ^ currentScreen;
//    }

public:
    explicit PermissionSetting(QObject *parent = 0);

signals:

public slots:
};

#endif // PERMISSIONSETTING_H
