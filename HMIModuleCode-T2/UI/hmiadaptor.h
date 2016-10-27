#ifndef HMIADAPTOR_H
#define HMIADAPTOR_H

#include<QMetaType>
#include <QObject>
#include "tablemodel.h"

#define HMI_PRINT (qDebug() <<"HMI adapter:" << __FILE__ << __FUNCTION__ << __LINE__ << ": ")

class HmiAdaptor : public QObject
{
    Q_OBJECT
public:
    explicit HmiAdaptor(QObject *parent = 0);
    Q_INVOKABLE void openFileDialog();
//    Q_INVOKABLE QVariant getWorkOrderValue(int index, QString key);

    WorkOrderModel *workOrderModel;
signals:

public slots:
};

#endif // HMIADAPTOR_H
