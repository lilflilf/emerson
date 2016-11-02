#include "BransonSerial.h"
#include "M2010.h"
#include "M102IA.h"
#include "ModRunSetup.h"
#include "Interface/Interface.h"
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QTimerEvent>
#include <QDateTime>
#include <QCoreApplication>
BransonSerial* BransonSerial::_instance = 0;
QSerialPort* BransonSerial::comIAport = 0;
BransonSerial* BransonSerial::Instance()
{
    if(_instance == 0){
        _instance = new BransonSerial();
    }
    return _instance;
}

BransonSerial::BransonSerial(QObject *parent)
    :QObject(parent)
{
    comIAport = new QSerialPort();
    ResetCommandTimer();
}

BransonSerial::~BransonSerial()
{
    delete comIAport;
    ResetCommandTimer();
}

void BransonSerial::FindIAport()
{
    InterfaceClass *_Interface = InterfaceClass::Instance();
    CheckIAportSet((100 * _Interface->StatusData.ComInfo.BaudRate),
                             _Interface->StatusData.ComInfo.COMport);
}

int BransonSerial::CheckIAportSet(long iBaudRate, long iComm)
{
    int iResult = -1;
    QString CommName;
    M2010 *_M2010 = M2010::Instance();
    ModRunSetup *_ModRunSetup = ModRunSetup::Instance();
    char strCommand;
//    Required to keep computers with different or fewer ports from shutting down program
    CommName = QString::number(iComm, 10);
    CommName = "COM" + CommName;
    comIAport->setPortName(CommName);
    if (comIAport->isOpen() == true)
        comIAport->close();
    _M2010->ReceiveFlags.IAFOUNDGOOD = false;
    comIAport->setBaudRate(iBaudRate);
    comIAport->setParity(QSerialPort::NoParity);
    comIAport->setDataBits(QSerialPort::Data8);
    comIAport->setStopBits(QSerialPort::OneStop);
    comIAport->setFlowControl(QSerialPort::NoFlowControl);
    comIAport->clearError();
    comIAport->clear();
    connect(comIAport,SIGNAL(readyRead()),this,SLOT(comIAportReadEventSlot()));
    comIAport->open(QIODevice::ReadWrite);


    strCommand = 0x11;
    comIAport->write(&strCommand,1); //XON
    comIAport->waitForBytesWritten(-1);
    //ENQuirey, IA sends back "U"
    strCommand = IAcomfunctionENQ;
    comIAport->write(&strCommand,1);
    comIAport->waitForBytesWritten(-1);
    SetCommandTimer(2);
    while (IsCommandTimeout() == false)
    {
        QCoreApplication::processEvents(); // Wait for response
        if (_M2010->ReceiveFlags.IAFOUNDGOOD == true)
        {
            iResult = 1;  //means port was found
            _ModRunSetup->GlobalOfflineModeEnabled = false;
            break;
        }
    }
    ResetCommandTimer();
    if(iResult == 1)
        return iResult;

    strCommand = 0x11;
    comIAport->write(&strCommand,1); //XON
    comIAport->waitForBytesWritten(-1);
    //ENQuirey, IA sends back "U"
    strCommand = IAcomfunctionENQ;
    comIAport->write(&strCommand,1);
    comIAport->waitForBytesWritten(-1);
    SetCommandTimer(2);
    while (IsCommandTimeout() == false)
    {
        QCoreApplication::processEvents(); // Wait for response
        if (_M2010->ReceiveFlags.IAFOUNDGOOD == true)
        {
            iResult = 1;  //means port was found
            _ModRunSetup->GlobalOfflineModeEnabled = false;
            break;
        }
    }
    ResetCommandTimer();
    if(iResult == -1)
    {
        comIAport->close();
    }
    return iResult;
}

void BransonSerial::comIAportReadEventSlot()
{
    qDebug()<< "x";
    M2010 *ptr_M2010 = M2010::Instance();
    M102IA *ptr_M102IA = M102IA::Instance();
    int iPos = 0;
    QByteArray DataBuffer;
    QString strBuffer;
    char Command;
    DataBuffer.clear();
    static QString NextLine;
    DataBuffer = comIAport->readAll();
    strBuffer = DataBuffer.data();

    iPos = strBuffer.indexOf('U', 0);
    if (iPos >= 0)
        ptr_M2010->ReceiveFlags.IAFOUNDGOOD = true;

    if(strBuffer.length() > (iPos + 1))
        strBuffer = strBuffer.mid(iPos + 1, strBuffer.length() - iPos -1);
    else
        return;
    DataBuffer = strBuffer.toLatin1();
    for(int i = 0; i< DataBuffer.length(); i++)
    {
        char InChar = DataBuffer.at(i);
        switch(InChar)
        {
        case 13:  //End of a line or blank line
            if (NextLine.isEmpty() == false)
            {
                ptr_M102IA->HexLineBufferCheck(NextLine);
                Command = 0x13;
                comIAport->write(&Command,1); //XOFF
                comIAport->waitForBytesWritten(-1);
                NextLine.clear();
                Command = 0x11;
                comIAport->write(&Command,1); //XON
                comIAport->waitForBytesWritten(-1);
                Command = 0x06;
                comIAport->write(&Command,1); //ACK
                comIAport->waitForBytesWritten(-1);
            }
            break;
        case 10:
//            --Line feed: discard
            break;
        case ':': //Start a new line
            NextLine = InChar;
//            If Prog_Mode = Run_SCREEN Then _
//                frmRunScreen.shpComStatus.FillColor = &HC000&
            break;
        default:
            if ((InChar >= '0') && (InChar <= '9'))
            {
                NextLine = NextLine + InChar;
            }else if((InChar >= 'A') && (InChar <= 'F'))
            {
                NextLine = NextLine + InChar;
            }else
            {
//                If Prog_Mode = Run_SCREEN Then _
//                    frmRunScreen.shpComStatus.FillColor = &HFF&
            }
            break;
        }
    }


}


void BransonSerial::SetCommandTimer(int Time)
{
    if(m_nCurrentTimer != 0){
        killTimer(m_nCurrentTimer);
        m_nCurrentTimer = 0;
    }
    qDebug()<<"Utility::start() called";
    m_nCurrentTimer = startTimer(Time);
    b_Timeout = false;
}

void BransonSerial::ResetCommandTimer()
{
    if(m_nCurrentTimer > 0)
    {
        killTimer(m_nCurrentTimer);
        m_nCurrentTimer = 0;
        b_Timeout = false;
    }
}

bool BransonSerial::IsCommandTimeout()
{
    return b_Timeout;
}

void BransonSerial::timerEvent(QTimerEvent *event)
{
    if(event->timerId() >= m_nCurrentTimer)
    {
        b_Timeout = true;
    }
    else
    {
        QObject::timerEvent(event);
    }
}
