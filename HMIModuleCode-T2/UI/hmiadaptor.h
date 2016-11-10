#ifndef HMIADAPTOR_H
#define HMIADAPTOR_H

#include <QMetaType>
#include <QObject>
#include "tablemodel.h"
#include "Interface/definition.h"

#define HMI_PRINT (qDebug() <<"HMI adapter:" << __FILE__ << __FUNCTION__ << __LINE__ << ": ")

class HmiAdaptor : public QObject
{
    Q_OBJECT
    Q_ENUMS(StripeType)
    Q_ENUMS(MetalType)
    Q_ENUMS(HorizontalLocation)
    Q_ENUMS(VerticalLocation)
    Q_ENUMS(VerticalPosition)
public:
    explicit HmiAdaptor(QObject *parent = 0);
    Q_INVOKABLE void openFileDialog();

    WorkOrderModel *workOrderModel;
    SpliceModel *spliceModel;
    PartModel *partModel;
    OperatorModel *operatorModel;
    WireModel *wireModel;
    WeldHistoryModel *weldHistoryModel;
    AlarmModel *alarmModel;

signals:

public slots:
};

#endif // HMIADAPTOR_H
