#include "PermissionSetting.h"
#include "Interface/Interface.h"
QStringList PermissionSetting::FunctionNameList;
QStringList PermissionSetting::LevelIdentifier;
PermissionSetting::PermissionSetting(QObject *parent) : QObject(parent)
{
    FunctionNameList.clear();
    LevelIdentifier.clear();
    int i = 0;
    FunctionNameList.insert(i++, QObject::tr("Create New"));          //Bit 0
    FunctionNameList.insert(i++, QObject::tr("Edit Existing"));       //Bit 1
    FunctionNameList.insert(i++, QObject::tr("Operate"));             //Bit 2
    FunctionNameList.insert(i++, QObject::tr("Test"));                //Bit 3
    FunctionNameList.insert(i++, QObject::tr("Teach Mode"));           //Bit 4
    FunctionNameList.insert(i++, QObject::tr("Calibration"));         //Bit 5
    FunctionNameList.insert(i++, QObject::tr("Tool Change"));         //Bit 6
    FunctionNameList.insert(i++, QObject::tr("Advanced Maintenance"));//Bit 7
    FunctionNameList.insert(i++, QObject::tr("Maintenance Counter")); //Bit 8
    FunctionNameList.insert(i++, QObject::tr("Maintenance Log"));     //Bit 9
    FunctionNameList.insert(i++, QObject::tr("Work Order History"));  //Bit 10
    FunctionNameList.insert(i++, QObject::tr("Statistical Trend"));   //Bit 11
    FunctionNameList.insert(i++, QObject::tr("Error/Alarm Log"));     //Bit 12
    FunctionNameList.insert(i++, QObject::tr("Library"));             //Bit 13
    FunctionNameList.insert(i++, QObject::tr("Version Information")); //Bit 14
    FunctionNameList.insert(i++, QObject::tr("Permission Setting"));  //Bit 15
    FunctionNameList.insert(i++, QObject::tr("Weld Defaults"));       //Bit 16
    FunctionNameList.insert(i++, QObject::tr("Operator Library"));    //Bit 17
    FunctionNameList.insert(i++, QObject::tr("Data/Communication"));  //Bit 18
    FunctionNameList.insert(i++, QObject::tr("Lock On Alarm"));       //Bit 19
}

void PermissionSetting::InitializeFRAM()
{

}

void PermissionSetting::_Default()
{

}

bool PermissionSetting::_Recall(void* PermissionList)
{
    if(PermissionList == NULL)
        return false;
    ((QList<struct PermissionSettingForScreen>*)(PermissionList))->clear();

}

bool PermissionSetting::_Set()
{
    InterfaceClass* _interface = InterfaceClass::Instance();
    if(CurrentPermissionList.empty() == true)
        return false;
    //deep Copy
    for(int i = 1; i < 5; i++)
    {
        _interface->tempStatusData.PasswordData[i].Identifier
                = LevelIdentifier.at(i-1);
    }
    for(int i = 0; i< CurrentPermissionList.size();i++)
    {
        QString str = CurrentPermissionList.at(i).Identifier;
        int FunIndex = FunctionNameList.indexOf(str);
        if(CurrentPermissionList.at(i).Level1 == true)
            _interface->tempStatusData.PasswordData[1].PWPermissions
                    |= (2 ^ FunIndex);
        else
            _interface->tempStatusData.PasswordData[1].PWPermissions
                    &= ~(2 ^ FunIndex);
        if(CurrentPermissionList.at(i).Level2 == true)
            _interface->tempStatusData.PasswordData[2].PWPermissions
                    |= (2 ^ FunIndex);
        else
            _interface->tempStatusData.PasswordData[2].PWPermissions
                    &= ~(2 ^ FunIndex);
        if(CurrentPermissionList.at(i).Level3 == true)
            _interface->tempStatusData.PasswordData[3].PWPermissions
                    |= (2 ^ FunIndex);
        else
            _interface->tempStatusData.PasswordData[3].PWPermissions
                    &= ~(2 ^ FunIndex);
        if(CurrentPermissionList.at(i).Level4 == true)
            _interface->tempStatusData.PasswordData[4].PWPermissions
                    |= (2 ^ FunIndex);
        else
            _interface->tempStatusData.PasswordData[4].PWPermissions
                    &= ~(2 ^ FunIndex);

    }
    return true;
}
