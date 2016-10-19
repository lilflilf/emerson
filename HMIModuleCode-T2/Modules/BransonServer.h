#ifndef BRANSONSERVER_H
#define BRANSONSERVER_H
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>
using namespace std;

//Max Client connections on a server.
#define MAX_CLIENT 32767

//Define Server port
#define DEFAULT_SERVER_PORT 4200

#define MAXSERVER_PORT_NUMBER 65535
#define MINSERVER_PORT_NUMBER 1

//ALARMS BITS
enum ALARMBITS{
    POWEROVERLOAD_ALARM = 0x01,
    WELDTIME_ALARM = 0x20,
    POWER_ALARM = 0x40,
    HEIGHT_ALARM = 0x80,
    WIDTH_ALARM = 0x800,
    WELD_ALARMS = (POWEROVERLOAD_ALARM |
                    WELDTIME_ALARM |
                    POWER_ALARM |
                    HEIGHT_ALARM | WIDTH_ALARM)
};

class BransonServer : public QObject
{
    Q_OBJECT
public:
    long ServerPort;
    long OldServerPort;

public:
    void OpenEthernetServer();
    void HandleConnectionRequest(int Index, long requestID);
    void CloseServer();
    int NextOpenSocket();
    void SendDataToClients(QString Data);
    void GetServerPort();
    void SetDefaultServerPort();
    void StoreServerPortToTextFile();
    QString SendGraphData();

private:
    QTcpServer   *ListenSocket;  // 侦听套接字
    QTcpSocket   *ReadWriteSocket;//读写套接字
private slots:
    void  processConnection();
    void  processText();

public:
    static BransonServer* Instance();
protected:
    BransonServer(QObject *parent = 0);
    void timerEvent(QTimerEvent *event);
private:
    static BransonServer* _instance;
public:
    ~BransonServer();
};

#endif // BRANSONSERVER_H
