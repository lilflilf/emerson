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
    bool GlobalShrinkTubeModeEnable;
//    QString MaxmmTemp;
//    QString MinmmTemp;
//    QString MaxmmTime;
//    QString MinmmTime;
    bool EthernetModeEnable;
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
    void ShrinkTubeTesting();
public:
    DataCommunication();
};

#endif // DATACOMMUNICATION_H
