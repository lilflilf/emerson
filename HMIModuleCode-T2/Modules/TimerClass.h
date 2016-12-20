#ifndef TIMERCLASS_H
#define TIMERCLASS_H

#include <QObject>

class TimerClass : public QObject
{
    Q_OBJECT
public:
    explicit TimerClass(QObject *parent = 0);

signals:

public slots:
};

#endif // TIMERCLASS_H