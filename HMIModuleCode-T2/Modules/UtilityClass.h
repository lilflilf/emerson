#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
#include <QMap>
#include <QObject>
#include <QThread>
#include "Interface/Definition.h"
#include "UtilityDefine.h"

typedef void (*ptrCallbackFun)(void*); //define a the recall


class UtilityClass
{  
private:
    DataShownStructure txtData[DIN_end];
public:
    int Maxpower;
public:
    void SetTextData(enum ScreenShowDataType TypeIndex,int Data, int min, int max,
                     int incrementor, float factor, QString formater);
public:

    void InitializeTextData();
    QString FormatedDataToString(enum ScreenShowDataType TypeIndex, int Data);
    float FormatedDataToFloat(enum ScreenShowDataType TypeIndex, int Data);
    int FormatedDataToInteger(enum ScreenShowDataType TypeIndex, int Data);
    int StringToFormatedData(enum ScreenShowDataType TypeIndex, QString ShownData);

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

class ThreadClass : public QThread
{
    Q_OBJECT
private:
    bool m_stop;
    bool m_suspend;
    ptrCallbackFun m_callbackHandle;
    void* m_arg;
public:
    explicit ThreadClass(QObject *parent = 0, void* _funcn = NULL,
                         void* arg = NULL);
    ~ThreadClass();
    void run();
    void setStopEnabled(bool enabled = true);
    void setSuspendEnabled(bool enabled = true);

signals:

public slots:
};


#endif // UTILITY_H
