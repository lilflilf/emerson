#include "UtilityClass.h"
#include <QDir>
#include <QDataStream>

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
