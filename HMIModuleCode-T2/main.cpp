#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QDebug>
#include <QFile>

#include <QQuickView>
#include <QQmlEngine>
//  ↵
#include "Modules/Modstart.h"
#include "TestCase/databasetest.h"
#include "UI/alpainteditem.h"

int main(int argc, char *argv[])
{
    //qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    qmlRegisterType<ALPaintedItem>("ALPaintedItem", 1, 0, "ALPaintedItem");

    QGuiApplication app(argc, argv);
    QString locale = QLocale::system().name();
    QTranslator translator;
    bool success = translator.load("displayChinese_zh_CN.qm");
    app.installTranslator(&translator);

//    MODstart *_ModStart = MODstart::Instance();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/UI/main.qml")));
    ALPaintedItem *alpaint = new ALPaintedItem;
    engine.rootContext()->setContextProperty("alpaint",alpaint);

//    DataBaseTest *_TestPtr = new DataBaseTest();
//    _TestPtr->TestMapJsonToString();
//    _TestPtr->TestStringJsonToMap();
//    _TestPtr->TestInsertOneRecordIntoWorkOrderTable();
//    _TestPtr->TestInsertOneRecordIntoPresetTable();
//    _TestPtr->TestInsertOneRecordIntoWireTable();
//    _TestPtr->TestQueryEntireWireTable();
//    _TestPtr->TestQueryEntireSpliceTable();
//    _TestPtr->TestQueryEntirePartTable();
//    _TestPtr->TestQueryEntireWorkOrderTable();
//    _TestPtr->TestQueryOneWireTable();
    return app.exec();
}
