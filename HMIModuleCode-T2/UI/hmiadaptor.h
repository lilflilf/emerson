#ifndef HMIADAPTOR_H
#define HMIADAPTOR_H

#include<QMetaType>
#include <QObject>
#define HMI_PRINT (qDebug() <<"HMI adapter:" << __FILE__ << __FUNCTION__ << __LINE__ << ": ")

class HmiAdaptor : public QObject
{
    Q_OBJECT
public:
    explicit HmiAdaptor(QObject *parent = 0);
    Q_INVOKABLE void openFileDialog();
signals:

public slots:
};

#endif // HMIADAPTOR_H
