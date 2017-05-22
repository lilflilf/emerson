#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QDebug>
#include <QFile>
#include "Modules/Modstart.h"
#include "Modules/M10INI.h"
#include <QQuickView>
#include <QQmlEngine>
#include "TestCase/databasetest.h"
#include "UI/alpainteditem.h"
#include "UI/hmiadaptor.h"
#include "Interface/Maintenance/AdvancedMaintenance.h"
#include "Interface/Interface.h"
#include <QHash>
#include <QDateTime>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    RECT rt = {0,0,0,0};
    SystemParametersInfo(SPI_GETWORKAREA,0,&rt,0);
    int y = GetSystemMetrics(SM_CYSCREEN)-rt.bottom;

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    RECT rc = {0,0,width,height};
    SystemParametersInfo(SPI_SETWORKAREA, 0, &rc, 0);

//    HWND hWnd = ::FindWindow(TEXT("Shell_traywnd"),TEXT(""));
//    ::SetWindowPos(hWnd,0,0,0,0,0,SWP_HIDEWINDOW);

//    HWND WndHandle;
//    // 获取任务栏的窗口句柄，并显示
//    WndHandle = FindWindow(TEXT("Shell_TrayWnd"), NULL);
//    ShowWindow(WndHandle, SW_HIDE);
//    HWND WndHandle2;
//    // 获取开始按钮句柄,并显示
//    WndHandle2 = FindWindow(TEXT("Button"), NULL);
//    ShowWindow(WndHandle2, SW_HIDE);

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    qmlRegisterType<ALPaintedItem>("ALPaintedItem", 1, 0, "ALPaintedItem");

    QGuiApplication app(argc, argv);
    QString locale = QLocale::system().name();
    QTranslator translator;
//    bool success = translator.load("displayChinese_zh_CN.qm");
    translator.load("displayChinese_zh_CN.qm");
    app.installTranslator(&translator);
    QQmlApplicationEngine engine;

    M10INI *pM10INI = M10INI::Instance();
    pM10INI->CheckBransonFolder();
    pM10INI->Init_AWGToMMTable();
    pM10INI->Get_INI_File();

    HmiAdaptor *hmiAdaptor = new HmiAdaptor();
    hmiAdaptor->taskBarHeight = y;
    engine.rootContext()->setContextProperty("hmiAdaptor",hmiAdaptor);
    engine.rootContext()->setContextProperty("workOrderModel",hmiAdaptor->workOrderModel);
    engine.rootContext()->setContextProperty("spliceModel",hmiAdaptor->spliceModel);
    engine.rootContext()->setContextProperty("partModel",hmiAdaptor->harnessModel);
    engine.rootContext()->setContextProperty("operatorModel",hmiAdaptor->operatorModel);
    engine.rootContext()->setContextProperty("wireModel",hmiAdaptor->wireModel);
    engine.rootContext()->setContextProperty("weldHistoryModel",hmiAdaptor->weldHistoryModel);
    engine.rootContext()->setContextProperty("alarmModel",hmiAdaptor->alarmModel);
    engine.rootContext()->setContextProperty("maintenanceLogModel",hmiAdaptor->maintenanceLogModel);
    engine.rootContext()->setContextProperty("sequenceModel",hmiAdaptor->sequenceModel);
    engine.load(QUrl(QStringLiteral("qrc:/UI/main.qml")));
    MODstart::Instance();
    return app.exec();
}
