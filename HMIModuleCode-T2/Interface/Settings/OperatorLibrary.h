#ifndef OPERATORLIBRARY_H
#define OPERATORLIBRARY_H
#include <QString>
#include "Interface/Definition.h"
//default has two records in user log.
class OperatorElement
{
public:
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
        PermissionLevel = OPEN;
    }
    OperatorElement * operator = (OperatorElement const &OperatorObject)
    {
        this->RevCode = OperatorObject.RevCode;
        this->OperatorID = OperatorObject.OperatorID;
        this->OperatorName = OperatorObject.OperatorName;
        this->CreatedDate = OperatorObject.CreatedDate;
        this->Password = OperatorObject.Password;
        this->PermissionLevel = OperatorObject.PermissionLevel;
        return this;
    }
    ~OperatorElement(){}
};

#endif // OPERATORLIBRARY_H
