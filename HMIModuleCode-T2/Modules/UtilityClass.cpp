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
    int i = 0;
    QString str = "";
    if(_SourceMap == NULL)
        return false;
    QMap<int, QString>::const_iterator iterator = _SourceMap->constBegin();
    while (iterator != _SourceMap->constEnd()) {
        QString value = QString::number(iterator.key(), 10) + ";";
        value += (iterator.value() + ";");
        json.insert(QString::number(i, 10),value);
        ++iterator;
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
            QJsonObject::const_iterator iterator = obj.constBegin();
            for(int i = 0; i< obj.count(); i++)
            {
                iterator = obj.constFind(QString::number(i, 10));
                if(iterator != obj.constEnd())
                {
                    QString value = iterator.value().toString();
                    QStringList strList = value.split(";");
                    _DestMap->insert(((QString)strList.at(0)).toInt(), strList.at(1));
                }
            }
            bResult = true;

        }
    }
    return bResult;
}

bool UtilityClass::MapJsonToString(QMap<int, struct HARNESSATTRIBUTE> *_SourceMap, QString &DestString)
{
    QJsonObject json;
    int i = 0;
    if(_SourceMap == NULL)
        return false;
    QMap<int, struct HARNESSATTRIBUTE>::const_iterator iterator = _SourceMap->constBegin();
    while (iterator != _SourceMap->constEnd()) {
        QString key = QString::number(i, 10);

        QString str = QString::number(iterator.key(), 10) + ";";
        QString value = str;
        int tmp = ((struct HARNESSATTRIBUTE)iterator.value()).SpliceID;
        str = QString::number(tmp, 10) + ";";
        value += str;
        str = ((struct HARNESSATTRIBUTE)iterator.value()).SpliceName + ";";
        value += str;
        tmp = ((struct HARNESSATTRIBUTE)iterator.value()).CurrentWorkstation;
        str = QString::number(tmp, 10) + ";";
        value += str;
        tmp = ((struct HARNESSATTRIBUTE)iterator.value()).CurrentBoardLayoutZone;
        str = QString::number(tmp, 10) + ";";
        value += str;
        json.insert(key,value);
        ++iterator;
        ++i;
    }
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    DestString = byte_array.data();
    return true;
}

bool UtilityClass::StringJsonToMap(QString SourceString, QMap<int, struct HARNESSATTRIBUTE> *_DestMap)
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
            QJsonObject::const_iterator iterator = obj.constBegin();
            for(int i = 0; i< obj.count(); i++){
                iterator = obj.constFind(QString::number(i, 10));
                if(iterator != obj.constEnd())
                {
                    QString value = iterator.value().toString();
                    struct HARNESSATTRIBUTE HarnessAttribute;
                    QStringList strList = value.split(";");
                    int key = ((QString)strList.at(0)).toInt();
                    HarnessAttribute.SpliceID = ((QString)strList.at(1)).toInt();
                    HarnessAttribute.SpliceName = strList.at(2);
                    HarnessAttribute.CurrentWorkstation = ((QString)strList.at(3)).toInt();
                    HarnessAttribute.CurrentBoardLayoutZone = ((QString)strList.at(4)).toInt();
                    _DestMap->insert(key, HarnessAttribute);
                }
            }
            bResult = true;

        }
    }
    return bResult;
}

bool UtilityClass::MapJsonToString(QMap<int, struct SEQUENCEATTRIBUTE> *_SourceMap, QString &DestString)
{
    QJsonObject json;
    int i = 0;
    if(_SourceMap == NULL)
        return false;
    QMap<int, struct SEQUENCEATTRIBUTE>::const_iterator iterator = _SourceMap->constBegin();
    while (iterator != _SourceMap->constEnd()) {
        QString key = QString::number(i, 10);

        QString str = QString::number(iterator.key(), 10) + ";";
        QString value = str;
        int tmp = ((struct SEQUENCEATTRIBUTE)iterator.value()).SpliceID;
        str = QString::number(tmp, 10) + ";";
        value += str;
        str = ((struct SEQUENCEATTRIBUTE)iterator.value()).SpliceName + ";";
        value += str;
        tmp = ((struct SEQUENCEATTRIBUTE)iterator.value()).Quantity;
        str = QString::number(tmp, 10) + ";";
        value += str;
        json.insert(key,value);
        ++iterator;
        ++i;
    }
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    DestString = byte_array.data();
    return true;
}

bool UtilityClass::StringJsonToMap(QString SourceString, QMap<int, struct SEQUENCEATTRIBUTE> *_DestMap)
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
            QJsonObject::const_iterator iterator = obj.constBegin();
            for(int i = 0; i< obj.count(); i++){
                iterator = obj.constFind(QString::number(i, 10));
                if(iterator != obj.constEnd())
                {
                    QString value = iterator.value().toString();
                    struct SEQUENCEATTRIBUTE SequenceAttribute;
                    QStringList strList = value.split(";");
                    int key = ((QString)strList.at(0)).toInt();
                    SequenceAttribute.SpliceID = ((QString)strList.at(1)).toInt();
                    SequenceAttribute.SpliceName = strList.at(2);
                    SequenceAttribute.Quantity = ((QString)strList.at(3)).toInt();
                    _DestMap->insert(key, SequenceAttribute);
                }
            }
            bResult = true;

        }
    }
    return bResult;
}

bool UtilityClass::MapJsonToString(QMap<int, int> *_SourceMap, QString &DestString)
{
    QJsonObject json;
    int i = 0;
    QString str = "";
    QString value = "";
    if(_SourceMap == NULL)
        return false;
    QMap<int, int>::const_iterator iterator = _SourceMap->constBegin();
    while (iterator != _SourceMap->constEnd()) {
        str = QString::number(iterator.key(),10) + ";";
        value += str;
        str = QString::number(iterator.value(), 10) + ";";
        value += str;
        json.insert(QString::number(i, 10), value);
        ++iterator;
        ++i;
    }
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    DestString = byte_array.data();
    return true;
}

bool UtilityClass::StringJsonToMap(QString SourceString, QMap<int, int> *_DestMap)
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
            QJsonObject::const_iterator iterator = obj.constBegin();
            for(int i = 0; i < obj.count(); i++)
            {
                iterator = obj.constFind(QString::number(i, 10));
                if(iterator != obj.constEnd())
                {
                    QStringList StringList = iterator.value().toString().split(";");
                    _DestMap->insert(((QString)StringList.at(0)).toInt(), ((QString)StringList.at(1)).toInt());
                }
            }
            bResult = true;
        }
    }
    return bResult;
}

bool UtilityClass::ListJsonToString(QList<int>* _SourceList, QString &DestString)
{
    QJsonObject json;
    if(_SourceList == NULL)
        return false;
    for(int i = 0; i < _SourceList->size(); i++)
        json.insert(QString::number(i,10),  QString::number(_SourceList->at(i), 10));
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    DestString = byte_array.data();
    return true;
}

bool UtilityClass::StringJsonToList(QString SourceString, QList<int> *_DestList)
{
    bool bResult = false;
    if(_DestList == NULL)
        return false;
    QByteArray byte_array = SourceString.toLatin1();
    QJsonParseError json_error;
    QJsonDocument parse_document = QJsonDocument::fromJson(byte_array, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_document.isObject())
        {
            QJsonObject obj = parse_document.object();
            if(_DestList->isEmpty() == false)
                _DestList->clear();
            QJsonObject::const_iterator tmp;
            for (int i = 0; i < obj.count();i++)
            {
                tmp = obj.constFind(QString("%1").arg(i));
                if(tmp != obj.constEnd())
                    _DestList->append(tmp.value().toVariant().toInt());
            }
            bResult = true;

        }
    }
    return bResult;
}

bool UtilityClass::ListJsonToString(QList<struct ShrinkTubeData>* _SourceList, QString &DestString)
{
    QJsonObject json;
    QString str = "";
    int i_tmp = 0;
    float f_tmp = 0;
    if(_SourceList == NULL)
        return false;
    for(int i = 0; i < _SourceList->size(); i++)
    {   str = _SourceList->at(i).Name + ";";
        i_tmp = _SourceList->at(i).temp;
        str += (QString::number(i_tmp, 10) + ";");
        f_tmp = _SourceList->at(i).Time;
        str += QString("%1").arg(f_tmp);;
        json.insert(QString::number(i,10),  str);
    }
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    DestString = byte_array.data();
    return true;
}

bool UtilityClass::StringJsonToList(QString SourceString, QList<struct ShrinkTubeData> *_DestList)
{
    bool bResult = false;
    if(_DestList == NULL)
        return false;
    QByteArray byte_array = SourceString.toLatin1();
    QJsonParseError json_error;
    QJsonDocument parse_document = QJsonDocument::fromJson(byte_array, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_document.isObject())
        {
            QJsonObject obj = parse_document.object();
            if (_DestList->isEmpty() == false)
                _DestList->clear();
            QJsonObject::const_iterator tmp;
            for(int i = 0; i < obj.count(); i++)
            {
                tmp = obj.constFind(QString::number(i, 10));
                if(tmp != obj.constEnd())
                {
                    QString value = tmp.value().toString();
                    struct ShrinkTubeData ShrinkTubeAttribute;
                    QStringList strList = value.split(";");
                    ShrinkTubeAttribute.Name = strList.at(0);
                    ShrinkTubeAttribute.temp = ((QString)strList.at(1)).toInt();
                    ShrinkTubeAttribute.Time = ((QString)strList.at(2)).toFloat();
                    _DestList->append(ShrinkTubeAttribute);
                }
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
    SetTextData(DINGauge, 0, MINEDITWIRE, MAXEDITWIRE, 1, (float)0.01, QString("%.2fmm").append(QChar(0xB2)));//"%.2fmm²"
    SetTextData(DINGaugeAWG, 0, MINWIREAREA_AWG, MAXWIREAREA_AWG, 1, 1, "%dAWG");
    SetTextData(DINCrossSection, 0, MINWIREAREA, MAXWIREAREA, 1, (float)0.01, QString("%.2fmm").append(QChar(0xB2)));//"%.2fmm²"
    SetTextData(DINEnergy, 0, MINENERGY, MAXENERGY, 2, 1, "%dJ");
    if(_Interface->StatusData.Soft_Settings.Length2Unit == BRANSON_INI_STRUCT::ToMM)
    {
        if (_Interface->StatusData.MachineType != ACT2032)
            SetTextData(DINWidth, 0, MINWIDTH, MAXWIDTH, 2, (float)0.01, "%.2fmm");
        else
            SetTextData(DINWidth, 0, MINWIDTH, MAXWIDTH2032, 2, (float)0.01, "%.2fmm");
    }else
    {
        if (_Interface->StatusData.MachineType != ACT2032)
            SetTextData(DINWidth, 0, MINWIDTH, MAXWIDTH, 2, (float)LENGTH2INCHFACTOR, "%.2fin");
        else
            SetTextData(DINWidth, 0, MINWIDTH, MAXWIDTH2032, 2, (float)LENGTH2INCHFACTOR, "%.2fin");
    }
    if (_Interface->StatusData.Soft_Settings.Pressure2Unit == BRANSON_INI_STRUCT::ToBar)
    {
        SetTextData(DINPressure,        0, MINWELDPRESSURE, MAXWELDPRESSURE, 1, (float)PRESS2BARFACTOR, "%.2fB");
        SetTextData(DINTriggerPressure, 0, MINTRIGPRESSURE, MAXTRIGPRESSURE, 1, (float)PRESS2BARFACTOR, "%.2fB");
        // Force is actually not displayed anywhere
        SetTextData(DINForcePl,         0, MINFORCE,        MAXFORCE,        2, (float)PRESS2BARFACTOR, "%.2fB");
        SetTextData(DINForceMs,         0, MINFORCE,        MAXFORCE,        2, (float)PRESS2BARFACTOR, "%.2fB");
    }
    else if (_Interface->StatusData.Soft_Settings.Pressure2Unit == BRANSON_INI_STRUCT::TokPa)
    {
        SetTextData(DINPressure, 0, MINWELDPRESSURE, MAXWELDPRESSURE, 1, (float)PRESS2KPAFACTOR, "%dkPa");
        SetTextData(DINTriggerPressure, 0, MINTRIGPRESSURE, MAXTRIGPRESSURE, 1, (float)PRESS2KPAFACTOR,  "%dkPa");
        // Force is actually not displayed anywhere
        SetTextData(DINForcePl, 0, MINFORCE, MAXFORCE, 2, (float)PRESS2KPAFACTOR, "%dkPa");
        SetTextData(DINForceMs, 0, MINFORCE, MAXFORCE, 2, (float)PRESS2KPAFACTOR, "%dkPa");
    }
    else
    {
        SetTextData(DINPressure, 0, MINWELDPRESSURE, MAXWELDPRESSURE, 2, (float)0.1, "%.1fpsi");
        SetTextData(DINTriggerPressure, 0, MINTRIGPRESSURE, MAXTRIGPRESSURE, 2, (float)0.1,  "%.1fpsi");
        // Force is actually not displayed anywhere
        SetTextData(DINForcePl, 0, MINFORCE, MAXFORCE, 2, (float)0.1, "%.1fpsi");
        SetTextData(DINForceMs, 0, MINFORCE, MAXFORCE, 2, (float)0.1, "%.1fpsi");
    }

    QString str = QString("%d%1%2").arg(QString(QChar(0x03BC))).arg("m");
    SetTextData(DINAmplitude,0, MINAMPLITUDE,
                _Interface->StatusData.Soft_Settings.Horn_Calibrate, 1, 1, str);//"%dμm"

    SetTextData(DINActTime, 0, MINTIME, MAXTIME, 2, (float)0.01, "%.2fs");
    SetTextData(DINTimePl, 0, MINTIME, MAXTIME, 2, (float)0.01, "%.2fs");
    SetTextData(DINTimeMs, 0, MINTIME, MAXTIME, 2, (float)0.01, "%.2fs");
    SetTextData(DINActPower, 0, MINPOWER, Maxpower, 100, 1, "%dW");
    SetTextData(DINPowerPl, 0, MINPOWER, Maxpower, 100, 1, "%dW");
//    SetTextData(DINPowerMs, 0, MINPOWER,
//                _Interface->StatusData.Soft_Settings.SonicGenWatts, 100, 1, "%dW");
    SetTextData(DINPowerMs, 0, MINPOWER, Maxpower, 100, 1, "%dW");
    SetTextData(DINPowerSupply, 0, MINPOWERSUPPLY, MAXPOWERSUPPLY, 100, 1, "%dw");
    if(_Interface->StatusData.Soft_Settings.Length2Unit == BRANSON_INI_STRUCT::ToMM)
    {
        SetTextData(DINActPreHgt, 0, MINHEIGHT, MAXHEIGHT, 2, (float)0.01, "%.2fmm");
        SetTextData(DINPre_HgtPl, 0, MINHEIGHT, MAXHEIGHT, 2, (float)0.01, "%.2fmm");
        SetTextData(DINPre_HgtMs, 0, MINHEIGHT, MAXHEIGHT, 2, (float)0.01, "%.2fmm");
        SetTextData(DINActHgt, 0, MINHEIGHT, MAXHEIGHT, 2, (float)0.01, "%.2fmm");
        SetTextData(DINHeightPl, 0, MINHEIGHT, MAXHEIGHT, 2, (float)0.01, "%.2fmm");
        SetTextData(DINHeightMs, 0, MINHEIGHT, MAXHEIGHT, 2, (float)0.01, "%.2fmm");
    }
    else
    {
        SetTextData(DINActPreHgt, 0, MINHEIGHT, MAXHEIGHT, 2, (float)LENGTH2INCHFACTOR, "%.2fin");
        SetTextData(DINPre_HgtPl, 0, MINHEIGHT, MAXHEIGHT, 2, (float)LENGTH2INCHFACTOR, "%.2fin");
        SetTextData(DINPre_HgtMs, 0, MINHEIGHT, MAXHEIGHT, 2, (float)LENGTH2INCHFACTOR, "%.2fin");
        SetTextData(DINActHgt, 0, MINHEIGHT, MAXHEIGHT, 2, (float)LENGTH2INCHFACTOR, "%.2fin");
        SetTextData(DINHeightPl, 0, MINHEIGHT, MAXHEIGHT, 2, (float)LENGTH2INCHFACTOR, "%.2fin");
        SetTextData(DINHeightMs, 0, MINHEIGHT, MAXHEIGHT, 2, (float)LENGTH2INCHFACTOR, "%.2fin");
    }

    SetTextData(DINABDelay, 0, MINABDELAY, MAXABDELAY, 2, (float)0.01, "%.2fs");
    SetTextData(DINABDuration, 0, MINABDURATION, MAXABDURATION, 2, (float)0.01, "%.2fs");
    SetTextData(DINPartCounter, 0, MINPARTCOUNT, MAXPARTCOUNT, 0, 1, "%dPcs");
    SetTextData(DINStopCounter, 0, MINSTOPCOUNT, MAXSTOPCOUNT, 2, 1, "%dPcs");
    SetTextData(DINSqueezeTime, 0, MINSQUEEZETIME, MAXSQUEEZETIME, 2, (float)0.01, "%.2fs");
    SetTextData(DINHoldTime, 0, MINHOLDTIME, MAXHOLDTIME, 2, (float)0.01, "%.2fs");

    SetTextData(DINAntiSpliceTime, 0, MINANTISIDETIME, MAXANTISIDETIME, 2, (float)0.005, "%.1fs" );
    SetTextData(DINCutOffTime, 0, MINCUTOFFTIME, MAXCUTOFFTIME, 2, (float)0.005, "%.1fs");

    // Flag word is a bit field and must have all bits active
    SetTextData(DINFlagBits, 0, 0x8000, 0x7FFF, 0, 1, "");

    SetTextData(DINPreBurst, 0, MINPREBURST, MAXPREBURST, 10, (float)0.01, "%.2fs");
    SetTextData(DINWeldMode, 0, 0, 2, 1, 1, "");

    str = QString("%d%1%2").arg(QString(QChar(0x03BC))).arg("m");
    SetTextData(DINAmplitude2, 0, MINAMPLITUDE,
       _Interface->StatusData.Soft_Settings.Horn_Calibrate, 1, 1, str);//"%dμm"
    SetTextData(DINEnergy2Step, 0, MINSTEPENERGY, MAXENERGY, 2, 1, "%dJ");
    SetTextData(DINPower2Step, 0, MINPOWER, Maxpower, 100, 1, "%dW");
    SetTextData(DINTime2Step, 0, MINTIME, MAXSTEPTIME, 2, (float)0.001, "%.2fs");
    SetTextData(DINCoolDur, 0, MINCOOLDUR, MAXCOOLDUR, 1, (float)0.01, "%.2fs");
    SetTextData(DINCoolDel, 0, MINCOOLDEL, MAXCOOLDEL, 1, (float)0.01, "%.2fs");
    SetTextData(DINFormulaArea, 0, MINFORMULAAREA, MAXFORMULAAREA, 1, 1, QString("%.2fmm").append(QChar(0xB2)));//"%.2fmm²"
    SetTextData(DINFormulaEnergyOffset, 0, Minmm2EnergyOffset, Maxmm2EnergyOffset, 1, 1, "%.2fJ");
    SetTextData(DINFormulaEnergyMult, 0, Minmm2EnergyMult, Maxmm2EnergyMult, 1, 1, "%.2f" );
    SetTextData(DINFormulaWidthOffset, 0, 0, 0, 1, 1, "%dmm");
    SetTextData(DINFormulaWidthMult, 0, Minmm2WidthAreaRatio, Maxmm2WidthAreaRatio, 1, 1, "%.2f");
    if (_Interface->StatusData.Soft_Settings.Pressure2Unit == BRANSON_INI_STRUCT::ToBar)
    {
        SetTextData(DINFormulaPressureOffset, 0, Minmm2PressOffset, Maxmm2PressOffset, 1, (float)PSItoBARfactor, "%.2fB");
        SetTextData(DINFormulaPressureMult, 0, Minmm2PressMult, Maxmm2PressMult, 1, (float)PSItoBARfactor, "%.2f");
    }
    else if (_Interface->StatusData.Soft_Settings.Pressure2Unit == BRANSON_INI_STRUCT::TokPa)
    {
        SetTextData(DINFormulaPressureOffset, 0, Minmm2PressOffset, Maxmm2PressOffset, 1, (float)PSItoKPAfactor, "%dkPa");
        SetTextData(DINFormulaPressureMult, 0, Minmm2PressMult, Maxmm2PressMult, 1, (float)PSItoKPAfactor, "%d");
    }else{
        SetTextData(DINFormulaPressureOffset, 0, Minmm2PressOffset, Maxmm2PressOffset, 1, 1, "%.1fPSI");
        SetTextData(DINFormulaPressureMult, 0, Minmm2PressMult, Maxmm2PressMult, 1, 1, "%.2f");
    }
    str = QString("%.2f%1%2").arg(QString(QChar(0x03BC))).arg("m");
    SetTextData(DINFormulaAmplitudeOffset, 0, Minmm2AmplitudeOffset, Maxmm2AmplitudeOffset, 1, 1, str);//"%.2fμm"
    SetTextData(DINFormulaAmplitudeMult, 0, Minmm2AmplitudeMult, Maxmm2AmplitudeMult, 1, 1, "%.2f");
    SetTextData(DINShrinkTubeTemperature, 0, ShrinkTubeMinTemp, ShrinkTubeMaxTemp, 1, 1, QString("%d").append(QChar(0x2103))); //"%d℃"
    SetTextData(DINShrinkTubeTime, 0, ShrinkTubeMinTime, ShrinkTubeMaxTime, 1, (float)0.1, "%.1fs");
    SetTextData(DINServerPortNumber, 0, MINSERVER_PORT_NUMBER, MAXSERVER_PORT_NUMBER, 1, 1, "%d");
    SetTextData(DINHornCountLimit, 0, MINHORNCOUNTLIMIT, MAXHORNCOUNTLIMIT, 1, 1, "%d");
    SetTextData(DINHornEnergyLimit, 0, MINHORNENERGYLIMIT, MAXHORNENERGYLIMIT, 1, 1, "%.1fKJ");
    SetTextData(DINAnvilCountLimit, 0, MINANVILCOUNTLIMIT, MAXANVILCOUNTLIMIT, 1, 1, "%d");
    SetTextData(DINAnvilEnergyLimit, 0, MINANVILENERGYLIMIT, MAXANVILENERGYLIMIT, 1, 1, "%.1fKJ");
    SetTextData(DINGatherCountLimit, 0, MINGATHERCOUNTLIMIT, MAXGATHERCOUNTLIMIT, 1, 1, "%d");
    SetTextData(DINGatherEnergyLimit, 0, MINGATHERENERGYLIMIT, MAXGATHERENERGYLIMIT, 1, 1, "%.1fKJ");
    SetTextData(DINGuideCountLimit, 0, MINGUIDECOUNTLIMIT, MAXGUIDECOUNTLIMIT, 1, 1, "%d");
    SetTextData(DINGuideEnergyLimit, 0, MINGUIDEENERGYLIMIT, MAXGUIDEENERGYLIMIT, 1, 1, "%.1fKJ");
    SetTextData(DINConverterLimit, 0, MINCONVERTERLIMIT, MAXCONVERTERLIMIT, 1, 1, "%d");
    SetTextData(DINPercentTeachMode, 0, MINPERCENTTEACHMODE, MAXPERCENTTEACHMODE, 1, 1, "%d%");
    SetTextData(DINSigmaTeachMode, 0, MINSIGMATEACHMODE, MAXSIGMATEACHMODE, 1, 1, "%d");
    SetTextData(DINGraphTimeMS, 0, MINTIME, MAXTIME, 2, 1, "%d");
    SetTextData(DINGraphPower, 0, MINPOWER, Maxpower, 100, 1, "%d");
    SetTextData(DINGraphHeight, 0, MINHEIGHT, MAXHEIGHT, 2, (float)0.01, "%.2f");
    SetTextData(DINTestQuantity, 0, MINTESTQUANTITY, MAXTESTQUANTITY, 1, 1, "%d");
    SetTextData(DINSequenceQuantity, 0, MINSEQUENCEQUANTITY, MAXSEQUENCEQUANTITY, 1, 1, "%d");
    str = QString("%d%1%2").arg(QString(QChar(0x03BC))).arg("m");
    SetTextData(DINDefaultAmplitude, 0, MINAMPLITUDE, MAXAMPLITUDE, 1, 1, str);//"%dμm"
    SetTextData(DINTeachModeQuantity, 0, MINTEACHMODEQUANTITY, MAXTEACHMODEQUANTITY,1, 1, "%d");
    SetTextData(DINTuneFrequence, 0, MINTUNEFREQUENCE, MAXTUNEFREQUENCE, 100, 1, "%dHz");
    SetTextData(DINFreqOffset, 0, MINFREQOFFSET, MAXFREQOFFSET, 100, 1, "%dHz");
    SetTextData(DINActualFrequence, 0, MINFREQUENCE, MAXFREQUENCE, 100, 1, "%dHz");
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
        tmpStr.sprintf(txtData[TypeIndex].Format.toStdString().c_str(),(int)(Data * txtData[TypeIndex].Factor));
    else if(txtData[TypeIndex].Format.contains("f") == true)
        tmpStr.sprintf(txtData[TypeIndex].Format.toStdString().c_str(),(float)(Data * txtData[TypeIndex].Factor));
    else
        tmpStr.clear();
    return tmpStr;
}

QString UtilityClass::FormatedDataToString(ScreenShowDataType TypeIndex, long Data)
{
    QString tmpStr;
    if(txtData[TypeIndex].Format.contains("d") == true)
        tmpStr.sprintf(txtData[TypeIndex].Format.toStdString().c_str(),(long)(Data * txtData[TypeIndex].Factor));
    else if(txtData[TypeIndex].Format.contains("f") == true)
        tmpStr.sprintf(txtData[TypeIndex].Format.toStdString().c_str(),(float)(Data * txtData[TypeIndex].Factor));
    else
        tmpStr.clear();
    return tmpStr;
}

QString UtilityClass::FormatedDataToString(ScreenShowDataType TypeIndex, float Data)
{
    QString tmpStr;
    if(txtData[TypeIndex].Format.contains("d") == true)
        tmpStr.sprintf(txtData[TypeIndex].Format.toStdString().c_str(),(float)(Data * txtData[TypeIndex].Factor));
    else if(txtData[TypeIndex].Format.contains("f") == true)
        tmpStr.sprintf(txtData[TypeIndex].Format.toStdString().c_str(),(float)(Data * txtData[TypeIndex].Factor));
    else
        tmpStr.clear();
    return tmpStr;
}

QString UtilityClass::FormatedDataToString(ScreenShowDataType TypeIndex, double Data)
{
    QString tmpStr;
    if(txtData[TypeIndex].Format.contains("d") == true)
        tmpStr.sprintf(txtData[TypeIndex].Format.toStdString().c_str(),(double)(Data * txtData[TypeIndex].Factor));
    else if(txtData[TypeIndex].Format.contains("f") == true)
        tmpStr.sprintf(txtData[TypeIndex].Format.toStdString().c_str(),(double)(Data * txtData[TypeIndex].Factor));
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

double UtilityClass::StringToFormatedData(ScreenShowDataType TypeIndex, QString ShownData)
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
    return tmpValue;
}

