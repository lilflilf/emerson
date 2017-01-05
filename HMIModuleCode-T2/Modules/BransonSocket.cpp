#include "BransonSocket.h"
#include <QDebug>
BransonSocket::BransonSocket(QObject *parent) : QObject(parent)
{
    m_pConnectSocket = (QTcpSocket*)parent;
    IsActivated = true;
}

BransonSocket::~BransonSocket()
{
    qDebug()<<"Delete Socket:" <<this;
    m_pConnectSocket = NULL;
    IsActivated = false;
}

//void BransonSocket::DisConnectedSlot()
//{
//    IsActivated = false;
//    qDebug()<<"Disconnect Socket Point: "<< this;
//}

void BransonSocket::ReadTcpDataSlot()
{
    QByteArray byteArray;
    byteArray = m_pConnectSocket->readAll();
    //data parse
    //processPakcet(byteArray);
}

bool BransonSocket::IsAvailableSocket()
{
    return IsActivated;
}

void BransonSocket::SocketSendData(QString data)
{
    if(m_pConnectSocket == NULL)
        return;
    QByteArray Buffer = data.toLatin1();
    m_pConnectSocket->write(Buffer);
//    m_pConnectSocket->waitForBytesWritten(-1);
}
