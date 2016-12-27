#ifndef MODSTART_H
#define MODSTART_H
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include "Interface/Definition.h"
using namespace std;

struct HMISOFTWARE
{
    QString Major;
    QString Minor;
    QString Revision;
};

class MODstart
{
public:
    struct HMISOFTWARE App;
    //Private objDriveSystem As Object
    bool UnLoad_KeyPadFlag;
    static bool Checkmaintenancelimit_EaWeld;
    static bool ApplicationFirstStartFlag;
public:
    void Unload_Popups();
    void Update_from_StatusData_for_commands();
    void GlobalInitM10();
    void GetSpliceFiles();
    void GetSequenceFiles();
    int  CheckIOStatus();
    void GetAuxillaryNamesToAuxNameArray();
    void GetDefaultNamesInAuxNameFile();
    void ViewIPConfiguration();
    void SetDefaultIndicatorsForOperatorScreen();
    void StoreTopCoordinateCreateEditSpliceScreen();

    bool UpdateInfoWithController();
    static void OfflineInitialization(void*);
private:
    void CheckAWGAreaTable();
    void CheckVersionFile(VersionList CurrVersions);
public:
    static MODstart* Instance();
protected:
    MODstart();
private:
    static MODstart* _instance;
public:
    ~MODstart(){} //do-nothing destructor
};

#endif // MODSTART_H
