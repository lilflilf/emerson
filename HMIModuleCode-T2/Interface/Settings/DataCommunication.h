#ifndef DATACOMMUNICATION_H
#define DATACOMMUNICATION_H
#include "Interface/Definition.h"
struct ShrinkTubeReference
{
    QString Name;
    QString Temp;
    QString Time;
};

struct DataCommunicationForScreen
{
    bool GlobalShrinkTubeMode;
    QList<struct ShrinkTubeReference> ShrinkTubeDefault;
    QString MaxmmTemp;
    QString MinmmTemp;
    QString MaxmmTime;
    QString MinmmTime;
    bool EthernetMode;
    BRANSONDATA ServerPort;
    QString IPConfiguration;
    bool RemoteDataLogging; //bool NetworkingEnabled;
    bool RemoteGraphData;
    bool ModularProduction;
};

class DataCommunication
{
public:
    struct DataCommunicationForScreen CurrentDataCommunication;
public:
    bool _Recall();
    bool _Set();
    void _Default();
    void _Cancel();
    void _Ok();
public:
    DataCommunication();
};

#endif // DATACOMMUNICATION_H
