#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QDebug>
#include <QFile>

#include <QQuickView>
#include <QQmlEngine>
//  ↵
int main(int argc, char *argv[])
{
    //qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);
    QString locale = QLocale::system().name();
    QTranslator translator;
    bool success = translator.load("displayChinese_zh_CN.qm");
    app.installTranslator(&translator);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/UI/main.qml")));

    return app.exec();
}
