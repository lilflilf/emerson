#ifndef SHRINKTUBESERIAL_H
#define SHRINKTUBESERIAL_H

#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QMutex>
#include "M10INI.h"
class ShrinkTubeSerial : public QObject
{
    Q_OBJECT
private:
    static QMutex* m_pMutex;
public:
    static QSerialPort *m_pShrinkTubeCom;
    static bool IsTest;
    static bool IsMutexLock;
public:
    void FormatShrinkTubeData(M10INI::ShrinkTubeIndex Index,
                              float ShrinkTime, int Temperature);

signals:

public slots:
    static void comShrinkTubeReadEventSlot();

public:
    static ShrinkTubeSerial* Instance();
protected:
    explicit ShrinkTubeSerial(QObject *parent = 0);
private:
    static ShrinkTubeSerial* _instance;
public:
    ~ShrinkTubeSerial();
};

#endif // SHRINKTUBESERIAL_H
