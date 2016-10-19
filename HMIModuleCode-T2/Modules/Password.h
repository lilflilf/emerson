#ifndef PASSWORD_H
#define PASSWORD_H

#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include "m10definitions.h"
using namespace std;

enum PasswordSecurityLevel{
    PWSLNoEntry = -1,
    PWSLNoneRequired,
    PWSLMatchedRequest,
};

enum PasswordReq{
   NoPasswordReq,
   OnlyAdminReq,
   BothPasswordReq,
};

enum PasswordQueryTasks{
    PWQTsGetNewUser,         //Get new ID and confirmed password
    PWQTsGetNewPassword,     //Get new confirmed password, ID is supplied
    PWQTsGetAdministrator,   //Initialize the system to allow Aministrator functions
    PWQTsGetPassword,        //Get an ID and its password
    PWQTsGetPasswordOnly,    //Get password, ID is supplied
    PWQTsLogAdministrator,   //Get the administrator
};

//Password permission constants, uses pairs of bit flags
enum PWPIndexers{
    PWPIMaintenance,
    PWPISetup,
    PWPIOptions,
    PWPIBuild,
    PWPIRecall,
    PWPITeach,
    PWPIEnd,
};

//Password Permission Masks, two bits per field
const long PWPTechMask = 0x55555555;  //Alternating ones beginning with 1
const long PWPAdminMask = 0xAAAAAAAA; //Alternating ones begining with 2

enum PWPMasks{
    PWPAdminOnly = 0x00,        //Used as a flag in the mask field
    PWPMaintMask = 0x03,        //Bits 0 and 1
    PWPSetupMask = 0x0C,        //Bits 2 and 3
    PWPOptionsMask = 0x30,      //Etc., etc., etc.
    PWPBuildMask = 0xC0,
    PWPRecallMask = 0x300,
    PWPTeachMask = 0xC00,
};

const string UNIVERSALPWKEY = "OLD GRUMPY MAN";

class Password
{
public:
    //--PWEntry is a constant string Variable 40 characters long!
    //PWEntry String  = "old,grumpyAmanBZYXWVUTSRQPONMLKJIHGFEDC" & Chr$(0)
    bool bErasePasswords;
    string PWIdentifierEntry;
    string PWPasswordEntry;
    int MinPermissionReq;
    long PWPIMasks[PWPIEnd - 1];
    PasswordQueryTasks PasswordQueryTask;
public:
    int CheckPasswordDataEntries(PWPMasks PWPMask = PWPAdminOnly);
    void SetPWPIMasks();
public:
    static Password* Instance();
protected:
    Password();
private:
    static Password* _instance;
public:
    ~Password(){} //do-nothing destructor
};

#endif // PASSWORD_H
