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
        int tmp = ((struct PARTATTRIBUTE)i.value()).SpliceID;
        QString value = QString::number(tmp, 10) + ";";
        QString str = ((struct PARTATTRIBUTE)i.value()).SpliceName + ";";
        value += str;
        tmp = ((struct PARTATTRIBUTE)i.value()).CurrentWorkstation;
        str = QString::number(tmp, 10) + ";";
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
                PartAttribute.SpliceID = ((QString)strList.at(0)).toInt();
                PartAttribute.SpliceName = strList.at(1);
                PartAttribute.CurrentWorkstation = ((QString)strList.at(2)).toInt();
                PartAttribute.CurrentBoardLayoutZone = ((QString)strList.at(3)).toInt();
                _DestMap->insert(i.key().toInt(), PartAttribute);
                ++i;
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
            QJsonObject::const_iterator i = obj.constBegin();
            for (int i = 0; i < obj.count();i++)
            {
               _DestList->append(obj.constFind(QString("%1").arg(i)).value().toVariant().toInt());
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
    SetTextData(DINGauge, 0, MINEDITWIRE, MAXEDITWIRE, 1, 0.01, "%.2fmm²");
    SetTextData(DINGaugeAWG, 0, MINWIREAREA_AWG, MAXWIREAREA_AWG, 1, 1, "%dAWG");
    SetTextData(DINCrossSection, 0, MINWIREAREA, MAXWIREAREA, 1, 0.01, "%.2fmm²");
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
    SetTextData(DINActTime, 0, MINTIME, MAXTIME, 2, 0.005, "%.2fs");
    SetTextData(DINTimePl, 0, MINTIME, MAXTIME, 2, 0.005, "%.2fs");
    SetTextData(DINTimeMs, 0, MINTIME, MAXTIME, 2, 0.005, "%.2fs");
    SetTextData(DINActPower, 0, MINPOWER, Maxpower, 100, 1, "%dW");
    SetTextData(DINPowerPl, 0, MINPOWER, Maxpower, 100, 1, "%dW");
    SetTextData(DINPowerMs, 0, MINPOWER,
                _Interface->StatusData.Soft_Settings.SonicGenWatts, 100, 1, "%dW");
    SetTextData(DINActPreHgt, 0, MINHEIGHT, MAXHEIGHT, 2, 0.01, "%.2fmm");
    SetTextData(DINPre_HgtPl, 0, MINHEIGHT, MAXHEIGHT, 2, 0.01, "%.2fmm");
    SetTextData(DINPre_HgtMs, 0, MINHEIGHT, MAXHEIGHT, 2, 0.01, "%.2fmm");
    SetTextData(DINActHgt, 0, MINHEIGHT, MAXHEIGHT, 2, 0.01, "%.2fmm");
    SetTextData(DINHeightPl, 0, MINHEIGHT, MAXHEIGHT, 2, 0.01, "%.2fmm");
    SetTextData(DINHeightMs, 0, MINHEIGHT, MAXHEIGHT, 2, 0.01, "%.2fmm");

    SetTextData(DINABDelay, 0, MINABDELAY, MAXABDELAY, 2, 0.01, "%.2fs");
    SetTextData(DINABDuration, 0, MINABDURATION, MAXABDURATION, 2, 0.01, "%.2fs");
    SetTextData(DINPartCounter, 0, MINPARTCOUNT, MAXPARTCOUNT, 0, 1, "%dPcs");
    SetTextData(DINStopCounter, 0, MINSTOPCOUNT, MAXSTOPCOUNT, 2, 1, "%dPcs");
    SetTextData(DINSqueezeTime, 0, MINSQUEEZETIME, MAXSQUEEZETIME, 2, 0.01, "%.2fs");
    SetTextData(DINHoldTime, 0, MINHOLDTIME, MAXHOLDTIME, 2, 0.01, "%.2fs");

    SetTextData(DINAntiSpliceTime, 0, MINANTISIDETIME, MAXANTISIDETIME, 2, 0.005, "%.1fs" );
    SetTextData(DINCutOffTime, 0, MINCUTOFFTIME, MAXCUTOFFTIME, 2, 0.005, "%.1fs");

    // Flag word is a bit field and must have all bits active
    SetTextData(DINFlagBits, 0, 0x8000, 0x7FFF, 0, 1, "");

    SetTextData(DINPreBurst, 0, MINPREBURST, MAXPREBURST, 10, 0.01, "%.2fs");
    SetTextData(DINWeldMode, 0, 0, 2, 1, 1, "");

    SetTextData(DINAmplitude2, 0, MINAMPLITUDE,
       _Interface->StatusData.Soft_Settings.Horn_Calibrate, 1, 1, "%dμm");
    SetTextData(DINEnergy2Step, 0, MINSTEPENERGY, MAXENERGY, 2, 1, "%dJ");
    SetTextData(DINPower2Step, 0, MINPOWER, Maxpower, 100, 1, "%dW");
    SetTextData(DINTime2Step, 0, MINTIME, MAXSTEPTIME, 2, 0.001, "%.2fs");
    SetTextData(DINCoolDur, 0, MINCOOLDUR, MAXCOOLDUR, 1, 0.01, "%.2fs");
    SetTextData(DINCoolDel, 0, MINCOOLDEL, MAXCOOLDEL, 1, 0.01, "%.2fs");
    SetTextData(DINFormulaArea, 0, MINFORMULAAREA, MAXFORMULAAREA, 1, 1, "%.2fmm²");
    SetTextData(DINFormulaEnergyOffset, 0, Minmm2EnergyOffset, Maxmm2EnergyOffset, 1, 1, "%.2fJ");
    SetTextData(DINFormulaEnergyMult, 0, Minmm2EnergyMult, Maxmm2EnergyMult, 1, 1, "%.2fJ" );
    SetTextData(DINFormulaWidthOffset, 0, 0, 0, 1, 1, "%dmm");
    SetTextData(DINFormulaWidthMult, 0, Minmm2WidthAreaRatio, Maxmm2WidthAreaRatio, 1, 1, "%.2f");
    if (_Interface->StatusData.Soft_Settings.Pressure2Unit == ToBar)
    {
        SetTextData(DINFormulaPressureOffset, 0, Minmm2PressOffset, Maxmm2PressOffset, 1, PSItoBARfactor, "%.2fB");
        SetTextData(DINFormulaPressureMult, 0, Minmm2PressMult, Maxmm2PressMult, 1, PSItoBARfactor, "%.2f");
    }
    else if (_Interface->StatusData.Soft_Settings.Pressure2Unit == TokPa)
    {
        SetTextData(DINFormulaPressureOffset, 0, Minmm2PressOffset, Maxmm2PressOffset, 1, PSItoKPAfactor, "%dkPa");
        SetTextData(DINFormulaPressureMult, 0, Minmm2PressMult, Maxmm2PressMult, 1, PSItoKPAfactor, "%d");
    }else{
        SetTextData(DINFormulaPressureOffset, 0, Minmm2PressOffset, Maxmm2PressOffset, 1, 1, "%.1fPSI");
        SetTextData(DINFormulaPressureMult, 0, Minmm2PressMult, Maxmm2PressMult, 1, 1, "%.2f");
    }
    SetTextData(DINFormulaAmplitudeOffset, 0, Minmm2AmplitudeOffset, Maxmm2AmplitudeOffset, 1, 1, "%.2fμm");
    SetTextData(DINFormulaAmplitudeMult, 0, Minmm2AmplitudeMult, Maxmm2AmplitudeMult, 1, 1, "%.2f");

    SetTextData(DINShrinkTubeTemperature, 0, ShrinkTubeMinTemp, ShrinkTubeMaxTemp, 1, 1, "%d℃");
    SetTextData(DINShrinkTubeTime, 0, ShrinkTubeMinTime, ShrinkTubeMaxTime, 1, 1, "%.1fs");
    SetTextData(DINServerPortNumber, 0, MINSERVER_PORT_NUMBER, MAXSERVER_PORT_NUMBER, 1, 1, "%d");
    SetTextData(DINHornLimit, 0, MINHORNLIMIT, MAXHORNLIMIT, 1, 1, "%d");
    SetTextData(DINAnvilTipLimit, 0, MINANVILTIPLIMIT, MAXANVILTIPLIMIT, 1, 1, "%d");
    SetTextData(DINGatherLimit, 0, MINGATHERLIMIT, MAXGATHERLIMIT, 1, 1, "%d");
    SetTextData(DINAnvilGuideLimit, 0, MINANVILGUIDELIMIT, MAXANVILGUIDELIMIT, 1, 1, "%d");
    SetTextData(DINConverterLimit, 0, MINCONVERTERLIMIT, MAXCONVERTERLIMIT, 1, 1, "%d");
    SetTextData(DINPercentTeachMode, 0, MINPERCENTTEACHMODE, MAXPERCENTTEACHMODE, 1, 1, "%d%");
    SetTextData(DINSigmaTeachMode, 0, MINSIGMATEACHMODE, MAXSIGMATEACHMODE, 1, 1, "%d");
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

float UtilityClass::StringToFormatedData(ScreenShowDataType TypeIndex, QString ShownData)
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
    return (float)tmpValue;
}


