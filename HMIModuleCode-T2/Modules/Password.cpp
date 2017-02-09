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
