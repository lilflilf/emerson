#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qtqml>
#include "UI\Utility.h"
#include "Modules\MODstart.h"
#include "Modules\BransonSerial.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "DataBase/Sqlit3Class.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<Utility>("UI.Utility", 1, 0, "Utility");

    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QQmlComponent component(&engine,QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *object = component.create();

    MODstart *m_ModStart = MODstart::Instance();
    BransonSerial *ptr_BransonSerial = BransonSerial::Instance();
    ptr_BransonSerial->CheckIAportSet(9600,1);

    SQLITCLASS *ptr_SQLITCLASS = SQLITCLASS::Instance();
//    ptr_SQLITCLASS->CreateNewDatabase();

    return app.exec();
}
