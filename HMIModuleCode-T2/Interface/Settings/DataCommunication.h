#ifndef DATACOMMUNICATION_H
#define DATACOMMUNICATION_H
#include "Interface/Definition.h"
struct ShrinkTubeReference
{
    QString Name;
    BRANSONDATA Temp;
    BRANSONDATA Time;
};

struct DataCommunicationForScreen
{
    bool GlobalShrinkTubeMode;
    struct ShrinkTubeReference ShrinkTubeDefault[4];
    bool EthernetMode;
    QString ServerPort;
    QString IPConfiguration;
    bool RemoteDataLogging; //bool NetworkingEnabled;
    bool RemoteGraphData;
    bool ModularProduction;
};

class DataCommunication
{
public:
    void _Recall(void*);
    void _Set(void*);
    void _Default();
public:
    DataCommunication();
};

#endif // DATACOMMUNICATION_H
