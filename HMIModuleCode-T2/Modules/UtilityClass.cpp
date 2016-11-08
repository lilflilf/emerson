#include "UtilityClass.h"
#include <QDir>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonParseError>
#include <QDebug>
#include "Interface/Interface.h"
UtilityClass* UtilityClass::_instance = NULL;
UtilityClass* UtilityClass::Instance()
{
    if(_instance == NULL){
        _instance = new UtilityClass();
    }
    return _instance;
}

UtilityClass::UtilityClass()
{
    InitializeTextData();
}

bool UtilityClass::ReadFromBinaryFile(QString SourcDirectory, void *DestStruct)
{
    QDir dir;
    bool ResultFlag = false;
    if (dir.exists(SourcDirectory) == true)
    {
        QFile file(SourcDirectory);
        file.open(QIODevice::ReadOnly);
        QDataStream Out(&file);    // read the data serialized from the file
        char* buffer = (char*)DestStruct;
        Out >> buffer;           // extract "the answer is" and 42
        file.close();
        ResultFlag = true;
    }
    return ResultFlag;
}

bool UtilityClass::WriteToBinaryFile(void *SourceStruct, QString DestDirectory)
{
    QDir dir;
    bool ResultFlag = false;
    if (dir.exists(DestDirectory) == true)
    {
        QFile file(DestDirectory);
        file.open(QIODevice::ReadWrite);
        QDataStream in(&file);    // read the data serialized from the file
        char* buffer = (char*)SourceStruct;
        in << buffer;           // extract "the answer is" and 42
        file.close();
        ResultFlag = true;
    }
    return ResultFlag;
}

bool UtilityClass::MapJsonToString(QMap<int, QString>* _SourceMap, QString &DestString)
{
    QJsonObject json;
    if(_SourceMap == NULL)
        return false;
    QMap<int, QString>::const_iterator i = _SourceMap->constBegin();
    while (i != _SourceMap->constEnd()) {
        json.insert(QString::number(i.key(),10),i.value());
        ++i;
    }
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    DestString = byte_array.data();
    return true;
}

bool UtilityClass::StringJsonToMap(QString SourceString, QMap<int, QString>* _DestMap)
{
    bool bResult = false;
    if(_DestMap == NULL)
        return false;
    QByteArray byte_array = SourceString.toLatin1();
    QJsonParseError json_error;
    QJsonDocument parse_document = QJsonDocument::fromJson(byte_array, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_document.isObject())
        {
            QJsonObject obj = parse_document.object();
            if(_DestMap->isEmpty() == false)
                _DestMap->clear();
            QJsonObject::const_iterator i = obj.constBegin();
            while(i != obj.constEnd()){
                _DestMap->insert(i.key().toInt(), i.value().toString());
                ++i;
            }
            bResult = true;

        }
    }
    return bResult;
}

bool UtilityClass::MapJsonToString(QMap<int, struct PARTATTRIBUTE> *_SourceMap, QString &DestString)
{
    QJsonObject json;
    if(_SourceMap == NULL)
        return false;
    QMap<int, struct PARTATTRIBUTE>::const_iterator i = _SourceMap->constBegin();
    while (i != _SourceMap->constEnd()) {
        QString key = QString::number(i.key(),10);
        QString value = ((struct PARTATTRIBUTE)i.value()).SpliceName + ";";
        int tmp = ((struct PARTATTRIBUTE)i.value()).CurrentWorkstation;
        QString str = QString::number(tmp, 10) + ";";
        value += str;
        tmp = ((struct PARTATTRIBUTE)i.value()).CurrentBoardLayoutZone;
        str = QString::number(tmp, 10) + ";";
        value += str;
        json.insert(key,value);
        ++i;
    }
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    DestString = byte_array.data();
    return true;
}

bool UtilityClass::StringJsonToMap(QString SourceString, QMap<int, struct PARTATTRIBUTE> *_DestMap)
{
    bool bResult = false;
    if(_DestMap == NULL)
        return false;
    QByteArray byte_array = SourceString.toLatin1();
    QJsonParseError json_error;
    QJsonDocument parse_document = QJsonDocument::fromJson(byte_array, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_document.isObject())
        {
            QJsonObject obj = parse_document.object();
            if (_DestMap->isEmpty() == false)
                _DestMap->clear();
            QJsonObject::const_iterator i = obj.constBegin();
            while(i != obj.constEnd()){
                QString value = i.value().toString();
                struct PARTATTRIBUTE PartAttribute;
                QStringList strList = value.split(";");
                PartAttribute.SpliceName = strList.at(0);
                PartAttribute.CurrentWorkstation = ((QString)strList.at(1)).toInt();
                PartAttribute.CurrentBoardLayoutZone = ((QString)strList.at(2)).toInt();
                _DestMap->insert(i.key().toInt(), PartAttribute);
                ++i;
            }
            bResult = true;

        }
    }
    return bResult;
}

/**************************************************************************************/
/* This is the central point for keeping track of all data, mins, maxs, and formatters*/
/* It receives Splice data and stores in the corresponding data structure.            */
/* The values related to Amplitude Stepping have been extracted to the data structure */
/**************************************************************************************/
void UtilityClass::InitializeTextData()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    SetTextData(DINEnergy, 0, MINENERGY, MAXENERGY, 2, 1, "%dJ");
    if (_Interface->StatusData.MachineType != ACT2032)
        SetTextData(DINWidth, 0, MINWIDTH, MAXWIDTH, 2, 0.01, "%.2fmm");
    else
        SetTextData(DINWidth, 0, MINWIDTH, MAXWIDTH2032, 2, 0.01, "%.2fmm");
    if (_Interface->StatusData.Soft_Settings.Pressure2Unit == ToBar)
    {
        SetTextData(DINPressure,        0, MINWELDPRESSURE, MAXWELDPRESSURE, 1, PRESS2BARFACTOR, "%.2fB");
        SetTextData(DINTriggerPressure, 0, MINTRIGPRESSURE, MAXTRIGPRESSURE, 1, PRESS2BARFACTOR, "%.2fB");
        // Force is actually not displayed anywhere
        SetTextData(DINForcePl,         0, MINFORCE,        MAXFORCE,        2, PRESS2BARFACTOR, "%.2fB");
        SetTextData(DINForceMs,         0, MINFORCE,        MAXFORCE,        2, PRESS2BARFACTOR, "%.2fB");
    }
    else if (_Interface->StatusData.Soft_Settings.Pressure2Unit == TokPa)
    {
        SetTextData(DINPressure, 0, MINWELDPRESSURE, MAXWELDPRESSURE, 1, PRESS2KPAFACTOR, "%dkPa");
        SetTextData(DINTriggerPressure, 0, MINTRIGPRESSURE, MAXTRIGPRESSURE, 1, PRESS2KPAFACTOR,  "%dkPa");
        // Force is actually not displayed anywhere
        SetTextData(DINForcePl, 0, MINFORCE, MAXFORCE, 2, PRESS2KPAFACTOR, "%dkPa");
        SetTextData(DINForceMs, 0, MINFORCE, MAXFORCE, 2, PRESS2KPAFACTOR, "%dkPa");
    }
    else
    {
        SetTextData(DINPressure, 0, MINWELDPRESSURE, MAXWELDPRESSURE, 2, 0.1, "%.1fPsi");
        SetTextData(DINTriggerPressure, 0, MINTRIGPRESSURE, MAXTRIGPRESSURE, 2, 0.1,  "%.1fPsi");
        // Force is actually not displayed anywhere
        SetTextData(DINForcePl, 0, MINFORCE, MAXFORCE, 2, 0.1, "%.1fPsi");
        SetTextData(DINForceMs, 0, MINFORCE, MAXFORCE, 2, 0.1, "%.1fPsi");
    }

    SetTextData(DINAmplitude,0, MINAMPLITUDE,
                _Interface->StatusData.Soft_Settings.Horn_Calibrate, 1, 1, "%dμm");
    SetTextData(DINTimePl, 0, MINTIME, MAXTIME, 2, 0.005, "%.2fs");
    SetTextData(DINTimeMs, 0, MINTIME, MAXTIME, 2, 0.005, "%.2fs");
    SetTextData(DINPowerPl, 0, MINPOWER, Maxpower, 100, 1, "%dW");
    SetTextData(DINPowerMs, 0, MINPOWER,
                _Interface->StatusData.Soft_Settings.SonicGenWatts, 100, 1, "%dW");
    SetTextData(DINPre_HgtPl, 0, MINHEIGHT, MAXHEIGHT, 2, 0.01, "%.2fmm");
    SetTextData(DINPre_HgtMs, 0, MINHEIGHT, MAXHEIGHT, 2, 0.01, "%.2fmm");
    SetTextData(DINHeightPl, 0, MINHEIGHT, MAXHEIGHT, 2, 0.01, "%.2fmm");
    SetTextData(DINHeightMs, 0, MINHEIGHT, MAXHEIGHT, 2, 0.01, "%.2fmm");

    SetTextData(DINABDelay, 0, MINABDELAY, MAXABDELAY, 2, 0.01, "%.2fs");
    SetTextData(DINABDuration, 0, MINABDURATION, MAXABDURATION, 2, 0.01, "%.2fs");
    SetTextData(DINPartCounter, 0, MINPARTCOUNT, MAXPARTCOUNT, 0, 1, "%dPcs");
    SetTextData(DINStopCounter, 0, MINSTOPCOUNT, MAXSTOPCOUNT, 2, 1, "%dPcs");
    SetTextData(DINSqueezeTime, 0, MINSQUEEZETIME, MAXSQUEEZETIME, 2, 0.01, "%.2fs");
    SetTextData(DINHoldTime, 0, MINHOLDTIME, MAXHOLDTIME, 2, 0.01, "%.2fs");

    // Flag word is a bit field and must have all bits active
    SetTextData(DINFlagBits, 0, 0x8000, 0x7FFF, 0, 1, "");

    SetTextData(DINPreBurst, 0, MINPREBURST, MAXPREBURST, 10, 0.01, "%.2fs");
    SetTextData(DINWeldMode, 0, 0, 2, 1, 1, "");

    SetTextData(DINAmplitude2, 0, MINAMPLITUDE,
       _Interface->StatusData.Soft_Settings.Horn_Calibrate, 1, 1, "%dμm");
    SetTextData(DINEnergy2Step, 0, MINSTEPENERGY, MAXENERGY, 2, 1, "%dJ");
    SetTextData(DINPower2Step, 0, MINPOWER, Maxpower, 100, 1, "%dW");
    SetTextData(DINTime2Step, 0, MINTIME, MAXSTEPTIME, 2, 0.001, "%.2fs");

}

void UtilityClass::SetTextData(ScreenShowDataType TypeIndex,int Data,int min, int max,
                               int incrementor,float factor, QString formater)
{
    txtData[TypeIndex].Data = Data;
    txtData[TypeIndex].min  = min;
    txtData[TypeIndex].max  = max;
    txtData[TypeIndex].Incrementor = incrementor;
    txtData[TypeIndex].Factor = factor;
    txtData[TypeIndex].Format = formater;
}

QString UtilityClass::FormatedDataToString(ScreenShowDataType TypeIndex, int Data)
{
    QString tmpStr;
    if(txtData[TypeIndex].Format.contains("d") == true)
        tmpStr.sprintf(txtData[TypeIndex].Format.toLatin1().data(),(int)(Data * txtData[TypeIndex].Factor));
    else if(txtData[TypeIndex].Format.contains("f") == true)
        tmpStr.sprintf(txtData[TypeIndex].Format.toLatin1().data(),(float)(Data * txtData[TypeIndex].Factor));
    else
        tmpStr.clear();
    return tmpStr;
}

float UtilityClass::FormatedDataToFloat(ScreenShowDataType TypeIndex, int Data)
{
    if(txtData[TypeIndex].Format.contains("f") == true)
        return (Data * txtData[TypeIndex].Factor);
    else
        return -1;
}

int UtilityClass::FormatedDataToInteger(ScreenShowDataType TypeIndex, int Data)
{
    if(txtData[TypeIndex].Format.contains("d") == true)
        return (Data * txtData[TypeIndex].Factor);
    else
        return -1;
}

int UtilityClass::StringToFormatedData(ScreenShowDataType TypeIndex, QString ShownData)
{
    ShownData.trimmed();
    if(ShownData.isEmpty() == true)
        return -1;

    QByteArray tmpArray = ShownData.toLatin1();
    const char *s = tmpArray.data();
    int i = 0;
    while(((*s >= '0') && (*s <= '9')) || (*s == '.'))
    {
        s++;
        i++;
    }
    ShownData.remove(i, ShownData.size() - i);

    double tmpValue = ShownData.toDouble();
    tmpValue /= txtData[TypeIndex].Factor;
    return (int)tmpValue;
}


ThreadClass::ThreadClass(QObject *parent, void* _func,
                         void* arg) : QThread(parent)
{
    m_stop = false;
    m_suspend = false;
    m_callbackHandle = (ptrCallbackFun)_func;
    m_arg = arg;
}

ThreadClass::~ThreadClass()
{
    m_stop = false;
    m_suspend = false;
    m_callbackHandle = NULL;
    m_arg = NULL;
}

void ThreadClass::run()
{
    if(m_callbackHandle != NULL)
    {
        while(1)
        {
            if(m_stop == true)
                break;
            if(m_suspend == false)
            {
                m_callbackHandle(m_arg);
                qDebug()<<"Thread process";
            }else
            {
                qDebug()<<"Thread suspend";
            }
            QThread::msleep(500);
        }
    }else{
        qDebug()<<"No function need to be executed";
    }
}

void ThreadClass::setStopEnabled(bool enabled)
{
    m_stop = enabled;
}

void ThreadClass::setSuspendEnabled(bool enabled)
{
    m_suspend = enabled;
}

