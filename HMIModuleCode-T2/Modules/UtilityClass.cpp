#include "UtilityClass.h"
#include <QDir>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonParseError>
#include <QDebug>

UtilityClass* UtilityClass::_instance = 0;
UtilityClass* UtilityClass::Instance()
{
    if(_instance == 0){
        _instance = new UtilityClass();
    }
    return _instance;
}

UtilityClass::UtilityClass()
{

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
