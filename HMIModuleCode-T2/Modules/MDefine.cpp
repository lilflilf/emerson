#include "MDefine.h"

MDefine* MDefine::_instance = 0;
MDefine* MDefine::Instance()
{
    if(_instance == 0){
        _instance = new MDefine();
    }
    return _instance;
}

MDefine::MDefine()
{
    ModularSequenceDone = false;
    FlagModularProduction = false;

}
