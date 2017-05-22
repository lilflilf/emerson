#include "ShrinkTubeSerial.h"
#include "UtilityClass.h"
#include "Interface/interface.h"
ShrinkTubeSerial* ShrinkTubeSerial::_instance = NULL;
bool ShrinkTubeSerial::IsTest = false;
bool ShrinkTubeSerial::IsMutexLock = false;
QSerialPort* ShrinkTubeSerial::m_pShrinkTubeCom = NULL;
QMutex* ShrinkTubeSerial::m_pMutex = NULL;

ShrinkTubeSerial* ShrinkTubeSerial::Instance()
{
    if(_instance == 0){
        _instance = new ShrinkTubeSerial();
    }
    return _instance;
}

ShrinkTubeSerial::ShrinkTubeSerial(QObject *parent) : QObject(parent)
{
    m_pShrinkTubeCom = new QSerialPort();
    m_pMutex = new QMutex(QMutex::NonRecursive);
    IsTest = false;
    IsMutexLock = false;
}

ShrinkTubeSerial::~ShrinkTubeSerial()
{
    delete m_pShrinkTubeCom;
    delete m_pMutex;
}

void ShrinkTubeSerial::FormatShrinkTubeData(M10INI::ShrinkTubeIndex Index,
                                            float ShrinkTime, int Temperature)
{
    QString ShrinkTubeTime, ShrinkTubeName, ShrinkTubeTemp;
    QByteArray ShrinkTubeData;
    QString CommName;
    int i = 0;
    unsigned char CheckSum = 1;
    unsigned char Command = 0x00;
    InterfaceClass *pInterface = InterfaceClass::Instance();
    ShrinkTubeData.clear();
    ShrinkTubeTime.sprintf("%2.1f",ShrinkTime);
    for(i = ShrinkTubeTime.length(); i< 4; i++)
        ShrinkTubeTime = "0" + ShrinkTubeTime;
    ShrinkTubeData.append(ShrinkTubeTime);
    ShrinkTubeData.append(Command);
    if(Index < pInterface->StatusData.ShrinkTubeDefaults.size())
        ShrinkTubeName = pInterface->StatusData.ShrinkTubeDefaults[Index].Name.trimmed();
    else
        ShrinkTubeName = pInterface->StatusData.ShrinkTubeDefaults[0].Name.trimmed();
    ShrinkTubeData.append(ShrinkTubeName);
    ShrinkTubeData.append(Command);
    ShrinkTubeTemp.sprintf("%d", Temperature);
    for(i = ShrinkTubeTemp.length(); i < 3; i++)
        ShrinkTubeTemp = "0" + ShrinkTubeTemp;
    ShrinkTubeData.append(ShrinkTubeTemp);
    for(int i = 0; i < ShrinkTubeData.size(); i++)
        CheckSum += ShrinkTubeData.at(i);
    CheckSum &= 0xFF;
    if (CheckSum < 0x10)
        ShrinkTubeData.append(Command);
    ShrinkTubeData.append(CheckSum);
    Command = 0x01; //SOH
    ShrinkTubeData.prepend(Command);
    Command = 0x00; //Just to get its attention!
    ShrinkTubeData.prepend(Command);
    Command = 0x04; //EOT
    ShrinkTubeData.append(Command);
    connect(m_pShrinkTubeCom,SIGNAL(readyRead()),this,SLOT(comShrinkTubeReadEventSlot()));
    CommName = QString::number(pInterface->StatusData.ShrinkTubeComInfo.COMport, 10);
    CommName = "COM" + CommName;
    m_pShrinkTubeCom->setPortName(CommName);
    m_pShrinkTubeCom->setBaudRate(pInterface->StatusData.ShrinkTubeComInfo.BaudRate);
    m_pShrinkTubeCom->setParity(QSerialPort::NoParity);
    m_pShrinkTubeCom->setDataBits(QSerialPort::Data8);
    m_pShrinkTubeCom->setStopBits(QSerialPort::OneStop);
    m_pShrinkTubeCom->setFlowControl(QSerialPort::NoFlowControl);
    m_pShrinkTubeCom->clearError();
    m_pShrinkTubeCom->clear();
    if(m_pShrinkTubeCom->isOpen() == false)
        m_pShrinkTubeCom->open(QIODevice::ReadWrite);
    m_pShrinkTubeCom->write(ShrinkTubeData);
    m_pShrinkTubeCom->waitForBytesWritten(-1);
}

void ShrinkTubeSerial::comShrinkTubeReadEventSlot()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    QByteArray DataBuffer;
    bool bResult = false;
//    char Command;
    DataBuffer.clear();
    DataBuffer = m_pShrinkTubeCom->readAll();
    for(int i = 0; i < DataBuffer.size(); i++)
    {
        char InChar = DataBuffer.at(i);
        switch(InChar)
        {
        case 0x06: //ACK
            bResult = true;
            break;
        case 0x15: //NAK
            break;
        case 0x12: // ShrinkTube Mutex Lock ACK
            break;
        }
        if(bResult == true)
            break;
    }
    if(IsTest == true)
    {
        BransonMessageBox tmpMsgBox;
        if(bResult == true)
        {
            tmpMsgBox.MsgPrompt = QObject::tr("Tube Shrinker has accepted data ");
            tmpMsgBox.MsgTitle = QObject::tr("Information");
            tmpMsgBox.TipsMode = (OKOnly + Information);
        }else{
            tmpMsgBox.MsgPrompt = QObject::tr("Tube Shrinker has rejected ddata.\n"
                                              "Please check and retry");
            tmpMsgBox.MsgTitle = QObject::tr("Exclamation");
            tmpMsgBox.TipsMode = (OKOnly + Exclamation);
        }
        tmpMsgBox.func_ptr = NULL;
        tmpMsgBox._Object = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
    }
}

