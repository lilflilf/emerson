#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
#include <QMap>
#include "Interface/definition.h"

class UtilityClass
{  
public:
    bool ReadFromBinaryFile(QString SourcDirectory, void* DestStruct);
    bool WriteToBinaryFile(void* SourceStruct, QString DestDirectory);

    bool MapJsonToString(QMap<int, QString>* _SourceMap, QString &DestString);
    bool StringJsonToMap(QString SourceString, QMap<int, QString>* _DestMap);

    bool MapJsonToString(QMap<int, struct PARTATTRIBUTE> *_SourceMap, QString &DestString);
    bool StringJsonToMap(QString SourceString, QMap<int, struct PARTATTRIBUTE> *_DestMap);

public:
    static UtilityClass* Instance();
protected:
    UtilityClass();
private:
    static UtilityClass* _instance;
public:
    ~UtilityClass(){} //do-nothing destructor
};

#endif // UTILITY_H
