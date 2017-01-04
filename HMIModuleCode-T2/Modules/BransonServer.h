#ifndef BRANSONSERVER_H
#define BRANSONSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "BransonSocket.h"
class BransonServer : public QObject
{
    Q_OBJECT
private:
    long ServerPort;
    long OldServerPort;
    QTcpServer *m_pTcpServer; //server tcp Socket
    QTcpSocket *m_pConnectSocket; //client connect socket
    QString HostAddress; //Host Address
    QList<unsigned long> SocketList;

private:
    void CloseServer();
    int NextOpenSocket();
    void GetServerPort();
    void HandleConnectionRequest();
    void ParseHostAddress();
public:
    QString GetHostAddress();
    void OpenEthernetServer();
    void SendDataToClients(QString Data);
//    QString SendGraphData();

public:
    static BransonServer* Instance();
private:
    static BransonServer* _instance;
protected:
    explicit BransonServer(QObject *parent = 0);

signals:

public slots:
    void ConnectClientSlot();
    void DisConnectedSlot();
};

#endif // BRANSONSERVER_H
