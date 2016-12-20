#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
#include <QMap>
#include <QObject>
#include "Interface/Definition.h"
#include "UtilityDefine.h"

class UtilityClass
{  
public:
    DataShownStructure txtData[DIN_end];
    int Maxpower;
public:
    void SetTextData(enum ScreenShowDataType TypeIndex,int Data, int min, int max,
                     int incrementor, float factor, QString formater);
public:
    void InitializeTextData();
    QString FormatedDataToString(ScreenShowDataType TypeIndex, int Data);
    QString FormatedDataToString(enum ScreenShowDataType TypeIndex, long Data);
    QString FormatedDataToString(enum ScreenShowDataType TypeIndex, float Data);
    float FormatedDataToFloat(enum ScreenShowDataType TypeIndex, int Data);
    int FormatedDataToInteger(enum ScreenShowDataType TypeIndex, int Data);
    float StringToFormatedData(enum ScreenShowDataType TypeIndex, QString ShownData);

    bool ReadFromBinaryFile(QString SourcDirectory, void* DestStruct);
    bool WriteToBinaryFile(void* SourceStruct, QString DestDirectory);

    bool MapJsonToString(QMap<int, QString>* _SourceMap, QString &DestString);
    bool StringJsonToMap(QString SourceString, QMap<int, QString>* _DestMap);

    bool ListJsonToString(QList<int>* _SourceList, QString &DestString);
    bool StringJsonToList(QString SourceString, QList<int>* _DestList);

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
