#include "Password.h"


Password* Password::_instance = 0;
Password* Password::Instance()
{
    if(_instance == 0){
        _instance = new Password();
    }
    return _instance;
}

Password::Password()
{

}

int Password::CheckPasswordDataEntries(PWPMasks PWPMask)
{
    return 0;
}

void Password::SetPWPIMasks()
{
    PWPIMasks[PWPIMaintenance] = PWPMaintMask;
    PWPIMasks[PWPISetup]       = PWPSetupMask;
    PWPIMasks[PWPIOptions]     = PWPOptionsMask;
    PWPIMasks[PWPIBuild]       = PWPBuildMask;
    PWPIMasks[PWPIRecall]      = PWPRecallMask;
    PWPIMasks[PWPITeach]       = PWPTeachMask;
}
