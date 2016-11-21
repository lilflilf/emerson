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

enum PermissionLevel
{
    Level1 = 1,
    Level2 = 2,
    Level3 = 3,
    Level4 = 4,
};
struct PermissionSettingForScreen
{
    QString Identifier;
    bool Level1;
    bool Level2;
    bool Level3;
    bool Level4;
};

class PermissionSetting : public QObject
{
    Q_OBJECT
private:
    QList<struct PermissionSettingForScreen> CurrentPermissionList;
public:
    static QStringList FunctionNameList;
    static QStringList LevelIdentifier;
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
    bool _Recall(void*);
    bool _Set();
    void _Default();
public:
    explicit PermissionSetting(QObject *parent = 0);

signals:

public slots:
};

#endif // PERMISSIONSETTING_H
