QT += qml quick

CONFIG += c++11

CONFIG += localize_deployment

TRANSLATIONS = displayChinese_zh_CN.ts

SOURCES += main.cpp \
    hmiadaptor.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    hmiadaptor.h
