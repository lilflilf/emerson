#ifndef BRANSONSERVER_H
#define BRANSONSERVER_H

#include <QObject>

class BransonServer : public QObject
{
    Q_OBJECT
public:
    explicit BransonServer(QObject *parent = 0);

signals:

public slots:
};

#endif // BRANSONSERVER_H