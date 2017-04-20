#include "PermissionSetting.h"
#include "Interface/Interface.h"
#include <QDebug>
#include <QtMath>
QStringList PermissionSetting::AllFunctionNameList;
QStringList PermissionSetting::FiveLevelIdentifier;
PermissionSetting::PermissionSetting(QObject *parent) : QObject(parent)
{
    AllFunctionNameList.clear();
    FiveLevelIdentifier.clear();
    int i = 0;
    AllFunctionNameList.insert(i++, QObject::tr("Create New"));          //Bit 0
    AllFunctionNameList.insert(i++, QObject::tr("Edit Existing"));       //Bit 1
    AllFunctionNameList.insert(i++, QObject::tr("Operate"));             //Bit 2
    AllFunctionNameList.insert(i++, QObject::tr("Test"));                //Bit 3
    AllFunctionNameList.insert(i++, QObject::tr("Teach Mode"));          //Bit 4
    AllFunctionNameList.insert(i++, QObject::tr("Calibration"));         //Bit 5
    AllFunctionNameList.insert(i++, QObject::tr("Tool Change"));         //Bit 6
    AllFunctionNameList.insert(i++, QObject::tr("Advanced Maintenance"));//Bit 7
    AllFunctionNameList.insert(i++, QObject::tr("Maintenance Counter")); //Bit 8
    AllFunctionNameList.insert(i++, QObject::tr("Maintenance Log"));     //Bit 9
    AllFunctionNameList.insert(i++, QObject::tr("Weld History"));        //Bit 10
    AllFunctionNameList.insert(i++, QObject::tr("Statistical Trend"));   //Bit 11
    AllFunctionNameList.insert(i++, QObject::tr("Error/Alarm Log"));     //Bit 12
    AllFunctionNameList.insert(i++, QObject::tr("Library"));             //Bit 13
    AllFunctionNameList.insert(i++, QObject::tr("Version Information")); //Bit 14
    AllFunctionNameList.insert(i++, QObject::tr("Permission Setting"));  //Bit 15
    AllFunctionNameList.insert(i++, QObject::tr("Weld Defaults"));       //Bit 16
    AllFunctionNameList.insert(i++, QObject::tr("Operator Library"));    //Bit 17
    AllFunctionNameList.insert(i++, QObject::tr("Data/Communication"));  //Bit 18
    AllFunctionNameList.insert(i++, QObject::tr("Lock On Alarm"));       //Bit 19
}

void PermissionSetting::InitializeFRAM()
{
    HMI_PRINT;
}

void PermissionSetting::_Default()
{
    HMI_PRINT;
}

void PermissionSetting::LockOnAlarm()
{
    HMI_PRINT;
}

bool PermissionSetting::_Recall()
{
    InterfaceClass* _interface = InterfaceClass::Instance();
    CurrentPermissionList.clear();
    FiveLevelIdentifier.clear();
    for(int i = 0; i < 5; i++)
        FiveLevelIdentifier.insert(i,_interface->StatusData.PasswordData[i].Identifier);
    struct PermissionSettingForScreen tmpStruct;
    for(int i = 0; i < _interface->StatusData.CurrentFunIndex.size();i++)
    {
        unsigned int FunIndex = _interface->StatusData.CurrentFunIndex.at(i);
        tmpStruct.Identifier = AllFunctionNameList.at(FunIndex);
        unsigned long Comparison = (0x01 << FunIndex);
        if((_interface->StatusData.PasswordData[0].PWPermissions & Comparison) ==
                Comparison)
            tmpStruct.PhyKey = true;
        else
            tmpStruct.PhyKey = false;
        if((_interface->StatusData.PasswordData[1].PWPermissions & Comparison) ==
                Comparison)
            tmpStruct.Level1 = true;
        else
            tmpStruct.Level1 = false;
        if((_interface->StatusData.PasswordData[2].PWPermissions & Comparison) ==
                Comparison)
            tmpStruct.Level2 = true;
        else
            tmpStruct.Level2 = false;
        if((_interface->StatusData.PasswordData[3].PWPermissions & Comparison) ==
                Comparison)
            tmpStruct.Level3 = true;
        else
            tmpStruct.Level3 = false;
        if((_interface->StatusData.PasswordData[4].PWPermissions & Comparison) ==
                Comparison)
            tmpStruct.Level4 = true;
        else
            tmpStruct.Level4 = false;
        CurrentPermissionList.insert(i,tmpStruct);
    }
//    for(int i = 0; i< CurrentPermissionList.size();i++)
//    {
//        qDebug() << "xxxxxxxxxxxxx " << CurrentPermissionList.at(i).Level1 << CurrentPermissionList.at(i).Level2 <<CurrentPermissionList.at(i).Level3 << CurrentPermissionList.at(i).Level4;
//    }
    return true;
}

bool PermissionSetting::_Set()
{
    InterfaceClass* _interface = InterfaceClass::Instance();
//    if(CurrentPermissionList.empty() == true)
//        return false;
    _interface->StatusData.CurrentFunIndex.clear();
    for(int i = 0; i < 5; i++)
    {
        _interface->StatusData.PasswordData[i].Identifier
                = FiveLevelIdentifier.at(i);
    }
    for(int i = 0; i< CurrentPermissionList.size();i++)
    {
        QString str = CurrentPermissionList.at(i).Identifier;
        int FunIndex = AllFunctionNameList.indexOf(str);
        _interface->StatusData.CurrentFunIndex.insert(i, FunIndex);
        unsigned long Comparison = (0x01 << FunIndex);
        if(CurrentPermissionList.at(i).PhyKey == true)
            _interface->StatusData.PasswordData[0].PWPermissions
                    |= Comparison;
        else
            _interface->StatusData.PasswordData[0].PWPermissions
                    &= ~Comparison;
        if(CurrentPermissionList.at(i).Level1 == true)
            _interface->StatusData.PasswordData[1].PWPermissions
                    |= Comparison;
        else
            _interface->StatusData.PasswordData[1].PWPermissions
                    &= ~Comparison;
        if(CurrentPermissionList.at(i).Level2 == true)
            _interface->StatusData.PasswordData[2].PWPermissions
                    |= Comparison;
        else
            _interface->StatusData.PasswordData[2].PWPermissions
                    &= ~Comparison;
        if(CurrentPermissionList.at(i).Level3 == true)
            _interface->StatusData.PasswordData[3].PWPermissions
                    |= Comparison;
        else
            _interface->StatusData.PasswordData[3].PWPermissions
                    &= ~Comparison;
        if(CurrentPermissionList.at(i).Level4 == true)
            _interface->StatusData.PasswordData[4].PWPermissions
                    |= Comparison;
        else
            _interface->StatusData.PasswordData[4].PWPermissions
                    &= ~Comparison;

        qDebug()<<_interface->StatusData.PasswordData[1].PWPermissions<<
                  _interface->StatusData.PasswordData[2].PWPermissions<<
                  _interface->StatusData.PasswordData[3].PWPermissions<<
                  _interface->StatusData.PasswordData[4].PWPermissions;


    }
    _interface->StatusData.WriteStatusDataToQSetting();
    return true;
}
