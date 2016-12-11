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
#include "Interface/Maintenance/AdvancedMaintenance.h"
#include "Interface/Interface.h"
#include <QHash>

int main(int argc, char *argv[])
{

//    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    qmlRegisterType<ALPaintedItem>("ALPaintedItem", 1, 0, "ALPaintedItem");

    QGuiApplication app(argc, argv);
    QString locale = QLocale::system().name();
    QTranslator translator;
    bool success = translator.load("displayChinese_zh_CN.qm");
    app.installTranslator(&translator);

    MODstart *_ModStart = MODstart::Instance();

    QQmlApplicationEngine engine;
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
    ALPaintedItem *alpaint = new ALPaintedItem;
    engine.rootContext()->setContextProperty("alpaint",alpaint);





//    DataBaseTest *_TestPtr = new DataBaseTest();


//    _TestPtr->TestInsertOneRecordIntoWireTable();
//    _TestPtr->TestQueryOnlyUseFieldWeldResult();
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
//    Maintenance *_Maintenance = new AdvancedMaintenance();
//    _Maintenance->_start();
//    InterfaceClass* _Interface = InterfaceClass::Instance();
//    memset(_Interface->StatusData.Machineflags.Word,0,8);
//    _Interface->StatusData.Machineflags.Flag.WdthEncoderOff = 1;
//    unsigned short tmp = _Interface->StatusData.Machineflags.Word[0];
//    tmp = _Interface->StatusData.Machineflags.Word[3];
//    struct test{
//        int a = 0;
//        int b = 8;
//    }www;
//    QByteArray ba;
//    ba.resize(sizeof(www));
//    memcpy(ba.data(), &www, sizeof(www));
//    uint tmp = qHashBits(&www,sizeof(struct test), 0);
//    uint tmp1 = qHash(ba, 0);
//    qDebug()<<"Hash Code: "<<tmp<< "" <<tmp1;
    return app.exec();
}
