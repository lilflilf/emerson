#ifndef READYSTATEMACHINE_H
#define READYSTATEMACHINE_H

#include <QObject>

class ReadyStateMachine : public QObject
{
    Q_OBJECT
public:
    explicit ReadyStateMachine(QObject *parent = 0);

signals:

public slots:
};

#endif // READYSTATEMACHINE_H