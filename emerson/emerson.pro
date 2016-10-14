TEMPLATE = app

QT += qml quick
CONFIG += c++11

CONFIG += localize_deployment

TRANSLATIONS = displayChinese_zh_CN.ts \
               displayFrench_zh_CN.ts

lupdate_only{
    SOURCES += *.qml
}
SOURCES += main.cpp \
    hmiadaptor.cpp


RESOURCES += qml.qrc
RC_FILE += test.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    hmiadaptor.h
