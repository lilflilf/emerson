#ifndef MODSTART_H
#define MODSTART_H
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include "M10definitions.h"
using namespace std;

struct HMISOFTWARE
{
    string Major;
    string Minor;
    string Revision;
};

#define HWND_TOPMOST   -1
#define HWND_NOTOPMOST -2

#define SWP_NOACTIVATE 0x10
#define SWP_SHOWWINDOW 0x40

#define FLAGS  (SWP_NOMOVE | SWP_NOSIZE)


class MODstart
{
public:
    struct HMISOFTWARE App;
    bool FirstScreenComesUp;
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
    void CheckVersionFile(VersionList CurrVersions);

    static void OfflineInitialization(void*);
private:
    void CheckBransonFolder();
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
