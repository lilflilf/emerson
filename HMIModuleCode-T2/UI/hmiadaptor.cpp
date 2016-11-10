#include "hmiadaptor.h"
#include <qdebug.h>
#include <QSqlQuery>
#include <QSqlError>
HmiAdaptor::HmiAdaptor(QObject *parent) : QObject(parent)
{
    workOrderModel = new WorkOrderModel(this);
    QStringList list;
    list << "workOrderId" << "name" << "date" << "middle" << "count";
    workOrderModel->setRoles(list);
    workOrderModel->setModelList();

    spliceModel = new SpliceModel(this);
    list.clear();
    list << "spliceId" << "name" << "date" << "middle" << "count" << "SpliceName" << "DateCreated" << "OperatorName" << "CrossSection" << "TotalWires" << "Verified" << "WeldMode" << "Energy" << "Amplitude"
         << "Width" << "TriggerPressure" << "WeldPressure" << "Time+" << "Time-" << "Power+" << "Power-" << "Pre-Height+" << "Pre-Height-" << "Height+" << "Height-";
    spliceModel->setRoles(list);
    spliceModel->setModelList();

    partModel = new PartModel(this);
    list.clear();
    list << "PartId" << "PartName" << "DateCreated" << "OperatorName" << "TotalSplices" << "ProcessMode" << "#ofWorkstation" << "#ofSplicesperWorkstation" << "Rows" << "Columns" << "MaxSplicesPerZone";
    partModel->setRoles(list);
    partModel->setModelList();

    wireModel = new WireModel(this);
    list.clear();
    list <<"WireId"<< "WireName" << "DateCreated" << "OperatorName" << "Color" << "StripeType" << "StripeColor" << "Gauge" << "MetalType" << "HorizontalLocation" << "VerticalLocation" << "VerticalPosition";
    wireModel->setRoles(list);
    wireModel->setModelList();

    operatorModel = new OperatorModel(this);
    list.clear();;
    list << "operatorId" << "name" << "date" << "middle" << "count";
    operatorModel->setRoles(list);
    operatorModel->setModelList();

    weldHistoryModel = new WeldHistoryModel(this);
    list.clear();
    list << "WeldHistoryId" << "WorkOrderName" << "PartName" << "SpliceName" << "OperatorName" << "DateCreated"
         << "CrossSection" << "WeldMode" << "Energy" << "Amplitude" << "Width" << "TriggerPressure" << "WeldPressure"
         << "Time+" << "Timer-" << "Time" << "Power+" << "Power-" << "Power" << "Pre-Height+" << "Pre-Height-"
         << "Pre-Height" << "Height+" << "Height-" << "Height" << "Alarm" << "SampleRatio" <<"GraphData";

    weldHistoryModel->setRoles(list);
    weldHistoryModel->setModelList();

    alarmModel = new AlarmModel(this);
    list.clear();
    list << "CreatedDate" << "Alarm/ErrorType" << "Alarm/ErrorLevel" << "Message" << "SpliceName";
    alarmModel->setRoles(list);
    alarmModel->setModelList();

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

