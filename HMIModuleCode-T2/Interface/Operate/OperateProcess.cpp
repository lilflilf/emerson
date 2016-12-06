#include "OperateProcess.h"
OperateProcess* OperateProcess::_instance = NULL;
OperateProcess* OperateProcess::Instance()
{
    if(_instance == NULL){
        _instance = new OperateProcess();
    }
    return _instance;
}

OperateProcess::OperateProcess()
{

}
