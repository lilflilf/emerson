#ifndef BRANSONSERIAL_H
#define BRANSONSERIAL_H
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QMutex>
//#include "m10definitions.h"
using namespace std;

class BransonSerial:public QObject
{
     Q_OBJECT
private:
    static QMutex* _Mutex;
public:
    static QSerialPort *comIAport;
public:
    int CheckIAportSet(long iBaudRate, long iComm);
    void FindIAport();

public slots:
    static void comIAportReadEventSlot();
public:
    static bool IAportSend(char data);
    static bool IAportSend(QByteArray data);
public:
    static BransonSerial* Instance();
protected:
    BransonSerial(QObject *parent = 0);
private:
    static BransonSerial* _instance;
public:
    ~BransonSerial();
};

#endif // BRANSONSERIAL_H
