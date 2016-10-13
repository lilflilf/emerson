#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "hmiadaptor.h"
#include <QDebug>
#include <QFile>
#include "hmiadaptor.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QString locale = QLocale::system().name();

    QTranslator translator;
    bool success = translator.load("displayChinese_zh_CN.qm");
    app.installTranslator(&translator);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



    return app.exec();
}
