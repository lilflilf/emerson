#include "hmiadaptor.h"
#include <qdebug.h>
#include <QSqlQuery>
#include <QSqlError>

HmiAdaptor::HmiAdaptor(QObject *parent) : QObject(parent)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", "hmiconnect");
    db.setDatabaseName("./hmi.db");
    if (!db.open())
    {
        qDebug() << "Cannot open contact database" << db.lastError().text();
    }

    QSqlDatabase seconddb;
    seconddb = QSqlDatabase::addDatabase("QSQLITE", "hmiconnectsecond");
    seconddb.setDatabaseName("./hmisecond.db");
    if (!seconddb.open())
    {
        qDebug() << "Cannot open contact database" << seconddb.lastError().text();
    }


    QSqlQuery query(db);
    if(!db.tables().contains("wire"))
    {
        query.exec("create table wire (id INTEGER PRIMARY KEY AUTOINCREMENT, surname varchar(20))");
    }
    qDebug() << query.lastError();

    query.prepare("INSERT INTO wire (surname) VALUES (?)");
    query.addBindValue("zhangjy");
    query.exec();
    qDebug() << query.lastError();


    QSqlQuery querySecond(seconddb);
    if(!seconddb.tables().contains("wire"))
    {
        querySecond.exec("create table wire (id INTEGER PRIMARY KEY AUTOINCREMENT, surname varchar(20))");
    }
    qDebug() << query.lastError();

    querySecond.prepare("INSERT INTO wire (surname) VALUES (?)");
    querySecond.addBindValue("zhangjylfffffffff");
    querySecond.exec();
    qDebug() << querySecond.lastError();

    querySecond.prepare("select id,surname from wire where surname=?");
    querySecond.addBindValue("zhangjylfffffffff");
    qDebug() << "result = " << querySecond.exec();

    //qDebug() << "return ==" << querySecond.next();
    querySecond.next();
    qDebug() << "count ==" << querySecond.value(0).toInt();
    while (querySecond.next()) {
        qDebug() << querySecond.value(0).toInt();
    }

    db.close();
    seconddb.close();

    if (!db.open())
    {
        qDebug() << "Cannot open contact databaseaaa" << db.lastError().text();
    }

    query.prepare("INSERT INTO wire (surname) VALUES (?)");
    query.addBindValue("zhangjyaaaaaaaaaaaaaaaaaaaaaaaaaa");
    query.exec();
    qDebug() << query.lastError();

    query.prepare("delete from wire");
    query.exec();
    qDebug() << "TRUNCATE table" << query.lastError();

    db.close();

}

void HmiAdaptor::openFileDialog()
{
    qDebug() << tr("openFileDialog");
    //QString fileName = QFileDialog::getOpenFileName(NULL, tr("Open File"),"C:",tr("Images (*.png *.xpm *.jpg)"));
}
