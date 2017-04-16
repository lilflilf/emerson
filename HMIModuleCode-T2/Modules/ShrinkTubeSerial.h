#ifndef SHRINKTUBESERIAL_H
#define SHRINKTUBESERIAL_H

#include <QObject>

class ShrinkTubeSerial : public QObject
{
    Q_OBJECT
public:
    explicit ShrinkTubeSerial(QObject *parent = 0);

signals:

public slots:
};

#endif // SHRINKTUBESERIAL_H