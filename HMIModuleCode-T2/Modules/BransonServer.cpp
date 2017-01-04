#include "BransonServer.h"
#include "BransonSocket.h"
#include "Interface/interface.h"
#include "Statistics.h"
#include <QNetworkInterface>
#include <QDateTime>
#include <QDebug>
BransonServer* BransonServer::_instance = NULL;
BransonServer* BransonServer::Instance()
{
    if(_instance == 0){
        _instance = new BransonServer();
    }
    return _instance;
}

BransonServer::BransonServer(QObject *parent) : QObject(parent)
{
    m_pConnectSocket = NULL;
    m_pTcpServer = NULL;
    SocketList.clear();
    ParseHostAddress();
}

/*---------------------------------------------------------------------*/
/*One main sub that closes the server.                                 */
/*Should be called before opening the server.                          */
/*---------------------------------------------------------------------*/
void BransonServer::CloseServer()
{
    //1. Unload & close all winsock controls
    BransonSocket* tmpSocket;
    for(int i= 0; i < SocketList.count(); i++)
    {
        tmpSocket = (BransonSocket*)(SocketList.at(i));
        delete tmpSocket;
    }
    SocketList.clear();
    if(m_pTcpServer != NULL)
        delete m_pTcpServer;
    m_pTcpServer = NULL;

}

/*---------------------------------------------------------------------*/
/* Checks for PortNumber.txt file if not present create one            */
/* and writes default port strings in it.                              */
/*---------------------------------------------------------------------*/
void BransonServer::GetServerPort()
{
    InterfaceClass *_Interface = InterfaceClass::Instance();
    ServerPort = _Interface->StatusData.ServerPort;
}

void BransonServer::ParseHostAddress()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach(QHostAddress address, list)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            HostAddress = address.toString();
            break;
        }
    }
}

/*---------------------------------------------------------------------*/
/* Open Ethernet Server on a port defined in PortNumber.txt file.      */
/* If File doesn't exist then create the file with default port number.*/
/*---------------------------------------------------------------------*/
void BransonServer::OpenEthernetServer()
{
    InterfaceClass *_pInterface = InterfaceClass::Instance();
    //Close Server first.
    CloseServer();
    //Get the server port number
    GetServerPort();
    OldServerPort = ServerPort;
    //Check if Port number is Zero
    if (ServerPort != 0)
    {
        //Now open server
        m_pTcpServer = new QTcpServer(this);
        if(!m_pTcpServer->listen(QHostAddress::Any, ServerPort))
        {
            //listen fail
            qDebug()<<"m_pTcpServer Error: "<<m_pTcpServer->errorString();
            BransonMessageBox tmpMsgBox;
            tmpMsgBox.MsgPrompt = QObject::tr("Listen Fail") +
                    m_pTcpServer->errorString();
            tmpMsgBox.MsgTitle = QObject::tr("Information");
            tmpMsgBox.TipsMode = Information;
            tmpMsgBox.func_ptr = NULL;
            tmpMsgBox._Object = NULL;
            _pInterface->cMsgBox(&tmpMsgBox);

        }else{
            connect(m_pTcpServer, SIGNAL(newConnection()),
                    this, SLOT(ConnectClientSlot()));
        }
    }
}

void BransonServer::HandleConnectionRequest()
{
    Statistics* _Statistics = Statistics::Instance();
    QString sColumnHeader, sHeader;
    BransonSocket* tmpSocket;
    qDebug()<<"SocketList :"<< SocketList.count();
    if(SocketList.count() != 0)
    {
        sColumnHeader = _Statistics->HeaderString() + "\r\n";
        sHeader = QObject::tr("HMI Daily Log ") + QDateTime::currentDateTime().toString("MM/dd/yyyy hh:mm:ss") + "\r\n";
        tmpSocket = (BransonSocket*)(SocketList.last());
        tmpSocket->SocketSendData(sHeader);
        tmpSocket->SocketSendData(sColumnHeader);
    }
}

//Slots:
void BransonServer::ConnectClientSlot()
{
    if(m_pTcpServer == NULL)
        return;
    m_pConnectSocket = m_pTcpServer->nextPendingConnection();
    BransonSocket *_Socket = new BransonSocket(m_pConnectSocket);
    SocketList.append((unsigned long)_Socket);
    qDebug()<<"Socket Connected:" << _Socket;
    connect(m_pConnectSocket, SIGNAL(readyRead()), _Socket, SLOT(ReadTcpDataSlot()));
//    connect(m_pConnectSocket, SIGNAL(disconnected()), m_pConnectSocket, SLOT(deleteLater()));

    connect(m_pConnectSocket, SIGNAL(disconnected()), this, SLOT(DisConnectedSlot()));
    HandleConnectionRequest();
}

void BransonServer::DisConnectedSlot()
{
    BransonSocket *_Socket = NULL;
    for(int i = 0; i< SocketList.count(); i++)
    {
        _Socket = ((BransonSocket*)(SocketList.at(i)));
        if(_Socket->m_pConnectSocket == this->sender())
        {
            _Socket->deleteLater();
            SocketList.removeAt(i);
            break;
        }
    }
//    connect(m_pConnectSocket, SIGNAL(disconnected()),_Socket, SLOT(deleteLater()));
}

void BransonServer::SendDataToClients(QString Data)
{
    BransonSocket* tmpSocket;
    if(SocketList.count() != 0)
    {
        for(int i = 0; i< SocketList.count(); i++)
        {
            tmpSocket = (BransonSocket*)(SocketList.at(i));
            tmpSocket->SocketSendData(Data);
        }
    }
}

QString BransonServer::GetHostAddress()
{
    return HostAddress;
}
