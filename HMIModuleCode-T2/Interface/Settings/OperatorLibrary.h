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
    OperatorElement operator=(const OperatorElement &OperatorObject) const
    {
        OperatorElement Obj;
        Obj.RevCode = OperatorObject.RevCode;
        Obj.OperatorID = OperatorObject.OperatorID;
        Obj.OperatorName = OperatorObject.OperatorName;
        Obj.CreatedDate = OperatorObject.CreatedDate;
        Obj.Password = OperatorObject.Password;
        Obj.PermissionLevel = OperatorObject.PermissionLevel;
        return Obj;
    }
    ~OperatorElement(){}
};

#endif // OPERATORLIBRARY_H
