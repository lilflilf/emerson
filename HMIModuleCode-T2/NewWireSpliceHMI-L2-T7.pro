TEMPLATE = app

QT += qml quick
QT += serialport
QT += network
QT += sql axcontainer
#QT += webview
QT += webengine
QT += webenginewidgets webchannel
CONFIG += c++11
RC_FILE = res.rc
static {
    QT += svg
    QTPLUGIN += qtvirtualkeyboardplugin
}
TRANSLATIONS =  displayEnglish_zh_CN.ts \
                displayJapanese_zh_CN.ts \
                displaySimplifiedChinese_zh_CN.ts \
                displayTraditionalChinese_zh_CN.ts \
                displayIndonesian_zh_CN.ts \
                displaySpanish_zh_CN.ts \
                displayVietnam_zh_CN.ts \
                displayTurkish_zh_CN.ts \
                displayThai_zh_CN.ts \
                displayPortuguese_zh_CN.ts \
                displayGerman_zh_CN.ts \
                displayFrench_zh_CN.ts \
                displayRussian_zh_CN.ts \
                displayPolish_zh_CN.ts \
                displayKorean_zh_CN.ts \
                displayItalian_zh_CN.ts \
                displaySlovak_zh_CN.ts \
                displayRomanian_zh_CN.ts \
                displayHungarian_zh_CN.ts \
                displayDutch_zh_CN.ts \
                displayCzech_zh_CN.ts \
                displayMalaysian_zh_CN.ts \
                displayArabic_zh_CN.ts \
                displayHindi_zh_CN.ts


lupdate_only{
    SOURCES += UI/*.qml
}
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
    Interface/UpperRightIcon/AlarmIcon.cpp \
    DataBase/DBHarnessTable.cpp \
    Interface/HarnessElement.cpp \
    Interface/SequenceElement.cpp \
    DataBase/DBSequenceTable.cpp \
    Interface/MakeWeld/ReadyStateMachine.cpp \
    Modules/ShrinkTubeSerial.cpp \
    Interface/TeachModeAdvance/TeachModeAdvance.cpp \
    DataExport_Import/CSVWireData.cpp \
    DataExport_Import/CSVPresetData.cpp \
    DataExport_Import/CSVHarnessData.cpp \
    DataExport_Import/CSVSequenceData.cpp \
    DataExport_Import/CSVWeldResultData.cpp \
    DataExport_Import/CSVMaintenanceLogData.cpp \
    DataExport_Import/CSVAlarmLogData.cpp




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
    Modules/typedef.h \
    DataBase/DBHarnessTable.h \
    Interface/HarnessElement.h \
    Interface/SequenceElement.h \
    DataBase/DBSequenceTable.h \
    Interface/MakeWeld/ReadyStateMachine.h \
    Modules/ShrinkTubeSerial.h \
    Interface/TeachModeAdvance/TeachModeAdvance.h \
    DataExport_Import/DataClass.h \
    DataExport_Import/CSVPresetData.h \
    DataExport_Import/CSVWireData.h \
    DataExport_Import/CSVHarnessData.h \
    DataExport_Import/CSVSequenceData.h \
    DataExport_Import/CSVWeldResultData.h \
    DataExport_Import/CSVMaintenanceLogData.h \
    DataExport_Import/CSVAlarmLogData.h

DISTFILES += \
#    UI/displayChinese_zh_CN.qm \
    cmake.exe.stackdump \
#    UI/displayChinese_zh_CN.ts \
#    UI/displayFrench_zh_CN.ts
