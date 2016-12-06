#ifndef OPERATEPROCESS_H
#define OPERATEPROCESS_H
#include "Interface/PresetElement.h"

class OperateProcess
{
public:
    PresetElement CurrentSplice;
//    OperatorElement CurrentOperator;
public:
    static OperateProcess* Instance();
private:
    OperateProcess();
private:
    static OperateProcess* _instance;
};

#endif // OPERATEPROCESS_H
