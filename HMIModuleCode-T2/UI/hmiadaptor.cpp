#include "hmiadaptor.h"
#include <qdebug.h>
#include <QSqlQuery>
#include <QSqlError>

HmiAdaptor::HmiAdaptor(QObject *parent) : QObject(parent)
{
    workOrderModel = new WorkOrderModel(this);
//    listModel.append({"name":"work order id111111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
    QStringList list;
    list << "name" << "date" << "middle" << "count";
    workOrderModel->setRoles(list);
    workOrderModel->setModelList();

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", "hmiconnect");
    db.setDatabaseName("./hmi.db");
    if (!db.open())
    {
        qDebug() << "Cannot open contact database" << db.lastError().text();
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
    db.close();
}

void HmiAdaptor::openFileDialog()
{
    qDebug() << tr("openFileDialog");
    //QString fileName = QFileDialog::getOpenFileName(NULL, tr("Open File"),"C:",tr("Images (*.png *.xpm *.jpg)"));
}
