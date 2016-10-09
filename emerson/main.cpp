#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "hmiadaptor.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    HmiAdaptor * adaptor = new HmiAdaptor;
    engine.rootContext()->setContextProperty("adaptor",adaptor);

    return app.exec();
}
