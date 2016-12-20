#ifndef THREADCLASS_H
#define THREADCLASS_H

#include <QObject>

class ThreadClass : public QObject
{
    Q_OBJECT
public:
    explicit ThreadClass(QObject *parent = 0);

signals:

public slots:
};

#endif // THREADCLASS_H