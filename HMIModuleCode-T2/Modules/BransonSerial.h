#ifndef BRANSONSERIAL_H
#define BRANSONSERIAL_H
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include <QObject>
#include <QtSerialPort/QSerialPort>
//#include "m10definitions.h"
using namespace std;

class BransonSerial:public QObject
{
     Q_OBJECT
private:
    int m_nCurrentTimer;
    bool b_Timeout;
public:
    static QSerialPort *comIAport;
public:
public:
    int CheckIAportSet(long iBaudRate, long iComm);
    void FindIAport();

    void SetCommandTimer(int Time = 3000);
    void ResetCommandTimer();
    bool IsCommandTimeout();

public slots:
    static void comIAportReadEventSlot();

public:
    static BransonSerial* Instance();
protected:
    BransonSerial(QObject *parent = 0);
    void timerEvent(QTimerEvent *event);
private:
    static BransonSerial* _instance;
public:
    ~BransonSerial();
};

#endif // BRANSONSERIAL_H
