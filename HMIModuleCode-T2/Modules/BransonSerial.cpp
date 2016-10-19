#include "BransonSerial.h"
#include "M2010.h"
#include "M102IA.h"
#include <sstream>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QTimerEvent>
#include <QDateTime>
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
}

BransonSerial::~BransonSerial()
{
    delete comIAport;
}

void BransonSerial::FindIAport()
{
    int iResult;
    long BitRate;
    b_Timeout = false;
//    iResult =
}

int BransonSerial::CheckIAportSet(long iBaudRate, long iComm)
{
    long Timeout;
    int FeedbackResult = 0;
    stringstream tmpStr;
    string CommName;
    M2010 *ptr_M2010 = M2010::Instance();
    char strCommand;
//    Required to keep computers with different or fewer ports from shutting down program
    tmpStr << iComm;
    tmpStr >> CommName;
    CommName = "COM" + CommName;
    comIAport->setPortName(QString::fromStdString(CommName));
    if (comIAport->isOpen() == true)
        comIAport->close();
    ptr_M2010->ReceiveFlags.IAFOUNDGOOD = false;
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

    return FeedbackResult;
}

void BransonSerial::comIAportReadEventSlot()
{
    qDebug()<< "x";
    M2010 *ptr_M2010 = M2010::Instance();
    M102IA *ptr_M102IA = M102IA::Instance();
    int iPos = 0;
    QByteArray arr;
    string strBuffer;
    char Command;
    arr.clear();
    static string NextLine;
    arr = comIAport->readAll();
    strBuffer = arr.toStdString();
    iPos = strBuffer.find('U');
    if (iPos > 0){
        ptr_M2010->ReceiveFlags.IAFOUNDGOOD = true;
        strBuffer = strBuffer.substr(iPos + 1, strBuffer.length() - iPos -1);
//        return;
    }

    for(unsigned int i = 0; i< strBuffer.length(); i++)
    {
        char InChar = strBuffer[i];
        switch(InChar)
        {
        case 13:  //End of a line or blank line
            if (!NextLine.empty())
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
    if(m_nCurrentTimer == 0){
        qDebug()<<"Utility::start() called";
        m_nCurrentTimer = startTimer(Time);
        b_Timeout = false;
    }
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
    if(event->timerId() == m_nCurrentTimer)
    {
        b_Timeout = true;
    }
    else
    {
        QObject::timerEvent(event);
    }
}
