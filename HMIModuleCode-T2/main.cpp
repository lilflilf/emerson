#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QDebug>
#include <QFile>
#include "Modules/Modstart.h"
#include <QQuickView>
#include <QQmlEngine>
//  ↵
#include "TestCase/databasetest.h"
#include "UI/alpainteditem.h"
#include "UI/hmiadaptor.h"
#include "Interface/Maintenance/AdvancedMaintenance.h"
#include "Interface/Interface.h"
#include <QHash>
#include <QDateTime>

int main(int argc, char *argv[])
{

    HWND hWnd = ::FindWindow(TEXT("Shell_traywnd"),TEXT(""));
    ::SetWindowPos(hWnd,0,0,0,0,0,SWP_HIDEWINDOW);

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    qmlRegisterType<ALPaintedItem>("ALPaintedItem", 1, 0, "ALPaintedItem");

    QGuiApplication app(argc, argv);
    QString locale = QLocale::system().name();
    QTranslator translator;
    bool success = translator.load("displayChinese_zh_CN.qm");
    app.installTranslator(&translator);
    QQmlApplicationEngine engine;
    MODstart* _ModStart = MODstart::Instance();
    HmiAdaptor *hmiAdaptor = new HmiAdaptor;
    engine.rootContext()->setContextProperty("hmiAdaptor",hmiAdaptor);
    engine.rootContext()->setContextProperty("workOrderModel",hmiAdaptor->workOrderModel);
    engine.rootContext()->setContextProperty("spliceModel",hmiAdaptor->spliceModel);
    engine.rootContext()->setContextProperty("partModel",hmiAdaptor->partModel);
    engine.rootContext()->setContextProperty("operatorModel",hmiAdaptor->operatorModel);
    engine.rootContext()->setContextProperty("wireModel",hmiAdaptor->wireModel);
    engine.rootContext()->setContextProperty("weldHistoryModel",hmiAdaptor->weldHistoryModel);
    engine.rootContext()->setContextProperty("alarmModel",hmiAdaptor->alarmModel);
    engine.rootContext()->setContextProperty("maintenanceLogModel",hmiAdaptor->maintenanceLogModel);
    engine.load(QUrl(QStringLiteral("qrc:/UI/main.qml")));
    return app.exec();
}
