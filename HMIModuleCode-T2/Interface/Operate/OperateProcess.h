#ifndef OPERATEPROCESS_H
#define OPERATEPROCESS_H
#include <QObject>
#include "Interface/PresetElement.h"

class OperateProcess : public QObject
{
public:
    PresetElement CurrentSplice;
//    OperatorElement CurrentOperator;
private:
    void UpdateIAFields();
public:
    void _start();
    void _stop();
    void _execute();
signals:

public slots:

public:
    static OperateProcess* Instance();
private:
    explicit OperateProcess(QObject *parent = 0);
private:
    static OperateProcess* _instance;
};

#endif // OPERATEPROCESS_H
