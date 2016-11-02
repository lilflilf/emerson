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
#include "UI/hmiadaptor.h"

int main(int argc, char *argv[])
{
    //qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    qmlRegisterType<ALPaintedItem>("ALPaintedItem", 1, 0, "ALPaintedItem");

    QGuiApplication app(argc, argv);
    QString locale = QLocale::system().name();
    QTranslator translator;
    bool success = translator.load("displayChinese_zh_CN.qm");
    app.installTranslator(&translator);

    MODstart *_ModStart = MODstart::Instance();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/UI/main.qml")));
    ALPaintedItem *alpaint = new ALPaintedItem;
    engine.rootContext()->setContextProperty("alpaint",alpaint);
    HmiAdaptor *hmiAdaptor = new HmiAdaptor;
    engine.rootContext()->setContextProperty("hmiAdaptor",hmiAdaptor);
    engine.rootContext()->setContextProperty("workOrderModel",hmiAdaptor->workOrderModel);
    engine.rootContext()->setContextProperty("spliceModel",hmiAdaptor->spliceModel);
    engine.rootContext()->setContextProperty("partModel",hmiAdaptor->partModel);

//    DataBaseTest *_TestPtr = new DataBaseTest();
//    _TestPtr->TestMapJsonToString();
//    _TestPtr->TestStringJsonToMap();
//    _TestPtr->TestInsertOneRecordIntoWorkOrderTable();
//    _TestPtr->TestInsertOneRecordIntoPartTable();
//    _TestPtr->TestInsertOneRecordIntoPresetTable();
//    _TestPtr->TestInsertOneRecordIntoWireTable();
//    _TestPtr->TestInsertOneRecordIntoOperatorTable();
//    _TestPtr->TestQueryEntireWireTable();
//    _TestPtr->TestQueryEntireSpliceTable();
//    _TestPtr->TestQueryEntirePartTable();
//    _TestPtr->TestQueryEntireWorkOrderTable();
//    _TestPtr->TestQueryEntireOpertorTable();
//    _TestPtr->TestQueryOneOperatorTable();
//    _TestPtr->TestQueryOneWireTable();
//    _TestPtr->TestDeleteEntireWireTable();
//    _TestPtr->TestDeleteEntirePresetTable();
//    _TestPtr->TestDeleteEntirePartTable();
//    _TestPtr->TestDeleteEntireWorkOrderTable();
//    _TestPtr->TestDeleteEntireOperator();
//    _TestPtr->TestDeleteOneWireTable();
//    _TestPtr->TestDeleteOnePresetTable();
//    _TestPtr->TestDeleteOnePartTable();
//    _TestPtr->TestDeleteOneWorkOrderTable();
//    _TestPtr->TestDeleteOneOperatorTable();
//    _TestPtr->TestUpdateOneRecordIntoWireTable();
//    _TestPtr->TestUpdateOneRecordIntoPresetTable();
//    _TestPtr->TestUpdateOneRecordIntoPartTable();
//    _TestPtr->TestUpdateOneRecordIntoWorkOrderTable();
//    _TestPtr->TestUpdateOneRecordIntoOperatorTable();
//    _TestPtr->TestQueryOnlyTimeWireTable();

    return app.exec();
}
