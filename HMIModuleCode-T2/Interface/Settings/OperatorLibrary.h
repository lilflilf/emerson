#ifndef OPERATORLIBRARY_H
#define OPERATORLIBRARY_H
#include <QString>
//#include "Interface/Definition.h"
//default has two records in user log.
class OperatorElement
{
public:
    enum PASSWORDCONTROL
    {
        PHYKEY,
        LEVEL1,
        LEVEL2,
        LEVEL3,
        LEVEL4,
        INITIAL,
        BRANSON,
    };
    int RevCode;
    int OperatorID;
    QString OperatorName;
    int WhoCreatedNewID;
    unsigned int CreatedDate;
    QString Password;
    enum PASSWORDCONTROL PermissionLevel;
public:
    OperatorElement()
    {
        RevCode = -1;
        OperatorID = -1;
        OperatorName.clear();
        WhoCreatedNewID = -1;
        CreatedDate = 0;
        Password.clear();
        PermissionLevel = LEVEL1;
    }
    OperatorElement operator=(const OperatorElement &OperatorObject)
    {
        if(this == &OperatorObject)
            return *this;
        this->RevCode = OperatorObject.RevCode;
        this->OperatorID = OperatorObject.OperatorID;
        this->OperatorName = OperatorObject.OperatorName;
        this->CreatedDate = OperatorObject.CreatedDate;
        this->Password = OperatorObject.Password;
        this->PermissionLevel = OperatorObject.PermissionLevel;
        return *this;
    }
    ~OperatorElement(){}
};

#endif // OPERATORLIBRARY_H
