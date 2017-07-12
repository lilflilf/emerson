#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QDebug>
#include <QFile>
#include "Modules/Modstart.h"
#include "Modules/M10INI.h"
#include <QQuickView>
#include <QQmlEngine>
#include "UI/alpainteditem.h"
#include "UI/hmiadaptor.h"
#include "Interface/Maintenance/AdvancedMaintenance.h"
#include "Interface/Interface.h"
#include <QHash>
#include <QDateTime>
#include <QDesktopWidget>
#include <QtWebView/QtWebView>
#include <QtWebEngine/QtWebEngine>
#include <QtWebEngineWidgets>
#include <QWebEngineHistory>
#include <QWebEngineHistoryItem>
#include <QWebEnginePage>
#include <QWebEngineView>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
int main(int argc, char *argv[])
{
    RECT rt = {0, 0, 0, 0};
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);
    int axisy = GetSystemMetrics(SM_CYSCREEN) - rt.bottom;

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    RECT rc = {0,0,width,height};
    SystemParametersInfo(SPI_SETWORKAREA, 0, &rc, 0);

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    qmlRegisterType<ALPaintedItem>("ALPaintedItem", 1, 0, "ALPaintedItem");

    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/images/vg02.ico"));
//    QtWebView::initialize();
    QtWebEngine::initialize();
    QString locale = QLocale::system().name();

    M10INI *pM10INI = M10INI::Instance();
    pM10INI->CheckBransonFolder();
    pM10INI->Get_INI_File();
    QTranslator* translator = pM10INI->TranslationInitial();
    app.installTranslator(translator);
    QQmlApplicationEngine engine;

    HmiAdaptor *hmiAdaptor = new HmiAdaptor();
    hmiAdaptor->taskBarHeight = axisy;
    engine.rootContext()->setContextProperty("hmiAdaptor", hmiAdaptor);
    engine.rootContext()->setContextProperty("workOrderModel", hmiAdaptor->workOrderModel);
    engine.rootContext()->setContextProperty("spliceModel", hmiAdaptor->spliceModel);
    engine.rootContext()->setContextProperty("partModel", hmiAdaptor->harnessModel);
    engine.rootContext()->setContextProperty("operatorModel", hmiAdaptor->operatorModel);
    engine.rootContext()->setContextProperty("wireModel", hmiAdaptor->wireModel);
    engine.rootContext()->setContextProperty("weldHistoryModel", hmiAdaptor->weldHistoryModel);
    engine.rootContext()->setContextProperty("alarmModel", hmiAdaptor->alarmModel);
    engine.rootContext()->setContextProperty("maintenanceLogModel", hmiAdaptor->maintenanceLogModel);
    engine.rootContext()->setContextProperty("sequenceModel", hmiAdaptor->sequenceModel);

    engine.load(QUrl(QStringLiteral("qrc:/UI/main.qml")));
    MODstart::Instance();
    return app.exec();
}
