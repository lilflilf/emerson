#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
//    engine.rootContext()->setContextProperty();

    return app.exec();
}
