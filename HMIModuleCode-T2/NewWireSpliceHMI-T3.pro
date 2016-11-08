TEMPLATE = app

QT += qml quick
QT += serialport
QT += sql
CONFIG += c++11

SOURCES += main.cpp \
    UI/Utility.cpp \
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
    Interface/SysConfiguration.cpp \
    Interface/Interface.cpp \
    Interface/Maintenance.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    UI/Utility.h \
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
    DataBase/SqlSentence.h \
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
    Interface/SysConfiguration.h \
    Interface/Interface.h \
    Interface/Maintenance.h

DISTFILES += \
    UI/displayChinese_zh_CN.qm \
    cmake.exe.stackdump \
    UI/displayChinese_zh_CN.ts \
    UI/displayFrench_zh_CN.ts \
    mainba.qml
