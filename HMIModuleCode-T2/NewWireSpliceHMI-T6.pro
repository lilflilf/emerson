TEMPLATE = app

QT += qml quick
QT += serialport
QT += network
QT += sql axcontainer
CONFIG += c++11
RC_FILE = res.rc
static {
    QT += svg
    QTPLUGIN += qtvirtualkeyboardplugin
}
TRANSLATIONS = displayChinese_zh_CN.ts \
               displayFrench_zh_CN.ts\
               displayEnglish_zh_CN.ts

#lupdate_only{
#    SOURCES += UI/*.qml
#}
SOURCES += main.cpp \
    Modules/Modstart.cpp \
    Modules/MDefine.cpp \
    Modules/M10INI.cpp \
    Modules/M2010.cpp \
    Modules/Password.cpp \
    Modules/M102IA.cpp \
    Modules/ModRunSetup.cpp \
    Modules/Statistics.cpp \
    Modules/SaveReplace.cpp \
    Modules/M10RunMode.cpp \
    Modules/UtilityClass.cpp \
    Modules/BransonSerial.cpp \
    UI/hmiadaptor.cpp \
    TestCase/databasetest.cpp \
    UI/alpainteditem.cpp \
    DataBase/DBWireTable.cpp \
    DataBase/DBPresetTable.cpp \
    DataBase/DBPartTable.cpp \
    DataBase/DBWorkOrderTable.cpp \
    UI/tablemodel.cpp \
    DataBase/DBOperatorTable.cpp \
    TestCase/ScreenShowConvertTest.cpp \
    DataBase/DBWeldResultTable.cpp \
    DataBase/DBAlarmLogTable.cpp \
    Interface/Interface.cpp \
    Interface/Maintenance/ToolChange.cpp \
    Interface/Maintenance/AdvancedMaintenance.cpp \
    Interface/Maintenance/Calibration.cpp \
    Interface/Maintenance/MaintenanceCounter.cpp \
    DataBase/DBMaintenanceLogTable.cpp \
    Interface/Settings/WeldDefaults.cpp \
    Interface/Settings/DataCommunication.cpp \
    Interface/Settings/PermissionSetting.cpp \
    Interface/ViewData/StatisticalTrend.cpp \
    Interface/VariantToString.cpp \
    Interface/StringToVariant.cpp \
    Interface/WireElement.cpp \
    Interface/PresetElement.cpp \
    Interface/PartElement.cpp \
    Interface/WorkOrderElement.cpp \
    Interface/WeldResultElement.cpp \
    Interface/AlarmElement.cpp \
    Modules/AlarmMessage.cpp \
    Modules/StatisticalFunction.cpp \
    Modules/TimerClass.cpp \
    Modules/ThreadClass.cpp \
    Interface/MakeWeld/MakeWeldProcess.cpp \
    Interface/SysConfiguration.cpp \
    Modules/BransonServer.cpp \
    Modules/BransonSocket.cpp \
    Interface/UpperRightIcon/AlarmIcon.cpp




RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Modules/Modstart.h \
    Modules/MDefine.h \
    Modules/M10INI.h \
    Modules/M2010.h \
    Modules/Password.h \
    Modules/M102IA.h \
    Modules/ModRunSetup.h \
    Modules/Statistics.h \
    Modules/SaveReplace.h \
    Modules/M10definitions.h \
    Modules/M10runMode.h \
    Modules/UtilityClass.h\
    Modules/BransonSerial.h \
    DataBase/Sqlit3Class.h \
    Interface/Definition.h \
    UI/hmiadaptor.h \
    TestCase/databasetest.h \
    UI/alpainteditem.h \
    DataBase/DBWireTable.h \
    DataBase/DBPresetTable.h \
    DataBase/DBPartTable.h \
    DataBase/DBWorkOrderTable.h \
    UI/tablemodel.h \
    DataBase/DBOperatorTable.h \
    TestCase/ScreenShowConvertTest.h \
    DataBase/DBWeldResultTable.h \
    DataBase/DBAlarmLogTable.h \
    Interface/Interface.h \
    Interface/Maintenance/ToolChange.h \
    Interface/Maintenance/AdvancedMaintenance.h \
    Interface/Maintenance/Calibration.h \
    Interface/Maintenance/MaintenanceCounter.h \
    Interface/Maintenance/Maintenance.h \
    Interface/Maintenance/MaintenanceLog.h \
    DataBase/DBMaintenanceLogTable.h \
    Interface/Settings/WeldDefaults.h \
    Interface/Settings/OperatorLibrary.h \
    Interface/Settings/DataCommunication.h \
    Interface/Settings/PermissionSetting.h \
    Interface/ViewData/StatisticalTrend.h \
    Interface/VariantToString.h \
    Interface/StringToVariant.h \
    Interface/WireElement.h \
    Interface/PresetElement.h \
    Interface/PartElement.h \
    Interface/WorkOrderElement.h \
    Interface/WeldResultElement.h \
    Interface/AlarmElement.h \
    Modules/AlarmMessage.h \
#    UI/displayChinese_zh_CN.qm \
    Modules/StatisticalFunction.h \
    Modules/TimerClass.h \
    Modules/ThreadClass.h \
    Interface/MakeWeld/MakeWeldProcess.h \
    Interface/SysConfiguration.h \
    Modules/BransonServer.h \
    Modules/BransonSocket.h \
    Interface/UpperRightIcon/AlarmIcon.h \
    Modules/typedef.h

DISTFILES += \
#    UI/displayChinese_zh_CN.qm \
    cmake.exe.stackdump \
#    UI/displayChinese_zh_CN.ts \
#    UI/displayFrench_zh_CN.ts
