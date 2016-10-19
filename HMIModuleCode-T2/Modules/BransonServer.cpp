#include "BransonServer.h"
#include "Interface/interface.h"
#include <QException>
BransonServer* BransonServer::_instance = 0;
//BransonServer* BransonServer::comIAport = 0;
BransonServer* BransonServer::Instance()
{
    if(_instance == 0){
        _instance = new BransonServer();
    }
    return _instance;
}

BransonServer::BransonServer(QObject *parent)
    :QObject(parent)
{
    ListenSocket = NULL;
    ReadWriteSocket = NULL;
}

BransonServer::~BransonServer()
{
//    delete comIAport;
}

/*---------------------------------------------------------------------*/
/* Open Ethernet Server on a port defined in PortNumber.txt file.      */
/* If File doesn't exist then create the file with default port number.*/
/*---------------------------------------------------------------------*/
void BransonServer::OpenEthernetServer()
{
    InterfaceClass* ptr_InterfaceClass = InterfaceClass::Instance();
    try{
        //Close server first.
        CloseServer();
        //Get the server port number
        GetServerPort();
        OldServerPort = ServerPort;
        //Check if Port number is Zero
        if (ServerPort != 0)
        {
            //Now open server

//                .AmtechServersock(0).Close
//                .AmtechServersock(0).LocalPort = ServerPort
//                .AmtechServersock(0).Listen 'Opens the winsock control.
//            End With
            if(this->ListenSocket != NULL)
            {
                this->ListenSocket->disconnect();
                delete this->ListenSocket;
                this->ListenSocket = NULL;
            }else{
                this->ListenSocket =new QTcpServer;
                this->ListenSocket->listen(QHostAddress::Any,ServerPort);
                QObject::connect(this->ListenSocket,SIGNAL(newConnection()),this,SLOT(processConnection()));
            }
        }
    }
    catch(QException &e)
    {
        BransonMessageBox tmpMsgBox;
        tmpMsgBox.MsgPrompt = QString::fromStdString(e.what());
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.func_ptr = NULL;
        ptr_InterfaceClass->cMsgBox(&tmpMsgBox);
    }
}

void BransonServer::HandleConnectionRequest(int Index, long requestID)
{

}

void BransonServer::CloseServer()
{

}

int BransonServer::NextOpenSocket()
{

}

void BransonServer::SendDataToClients(QString Data)
{

}

void BransonServer::GetServerPort()
{

}

void BransonServer::SetDefaultServerPort()
{

}

void BransonServer::StoreServerPortToTextFile()
{

}

QString BransonServer::SendGraphData()
{

}
