#ifndef M10RUNMODE_H
#define M10RUNMODE_H
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include "m10definitions.h"
#include "Interface/PresetElement.h"
using namespace std;
#define MAX_CYCLE_COUNTER               65000
#define MAX_HOSTNAME_LEN                132
#define MAX_DOMAIN_NAME_LEN             132
#define MAX_SCOPE_ID_LEN                260
#define MAX_ADAPTER_NAME_LENGTH         260
#define MAX_ADAPTER_ADDRESS_LENGTH      8
#define MAX_ADAPTER_DESCRIPTION_LENGTH  132
#define ERROR_BUFFER_OVERFLOW           111
#define MIB_IF_TYPE_ETHERNET            6
#define MIB_IF_TYPE_TOKENRING           9
#define MIB_IF_TYPE_FDDI                15
#define MIB_IF_TYPE_PPP                 23
#define MIB_IF_TYPE_LOOPBACK            24
#define MIB_IF_TYPE_SLIP                28

struct IP_ADDR_STRING
{
    long Next;
    string IpAddress;
    string IpMask;
    long Context;
};

struct IP_ADAPTER_INFO
{
    long Next;
    long ComboIndex;
    string AdapterName;
    string Description;
    long AddressLength;
    unsigned char Address[MAX_ADAPTER_ADDRESS_LENGTH - 1];
    long Index;
    long Type;
    long DhcpEnabled;
    long CurrentIpAddress;
    IP_ADDR_STRING IpAddressList;
    IP_ADDR_STRING GatewayList;
    IP_ADDR_STRING DhcpServer;
    unsigned char HaveWins;
    IP_ADDR_STRING PrimaryWinsServer;
    IP_ADDR_STRING SecondaryWinsServer;
    long LeaseObtained;
    long LeaseExpires;
};

struct FIXED_INFO
{
    string HostName;
    string DomainName;
    long CurrentDnsServer;
    IP_ADDR_STRING DnsServerList;
    long NodeType;
    string ScopeId;
    long EnableRouting;
    long EnableProxy;
    long EnableDns;
};

class M10runMode
{
private:
    int WeldResultID;
public:
    bool PreviousWeldValid;
    bool Teach_Auto_Stage2;
    int InvalidWeldCounter;   //significant in Auto Teach mode only
    QString tempStatFile;


//    Timer tmrM10runMode;
    bool WidthError;
    int valueReturned_fromEndCount;
    bool ESTOPMessage;

//    Object objDriveSystem; //File System Object
public:
    void SlowDown(long iCnt);
    void run_setup();
    void next_splice_in();
    void get_weld();
    void init_m20_data_events(PresetElement *_Splice);

    int GetPressureFromString(string InString, int ShowPressureUnit);
    string MakePressureToString(int PressureData, int ShowPressureUnit);

    bool CheckWeldData(int weldresult = -1);

    void CalculateTeachMode(PresetElement* _Splice);

    void SafetyAlertMsg(unsigned long IOStatus);
    void FootPedalMsg(unsigned long IOStatus);
    void Run_E_Stop_Screen(unsigned long LastIOStatus);
    void LockAlertMsg(unsigned long IOStatus);

    void Save_Data_Events();
    void CycleAbortMsg();

    void SetAllTxtDataTemp();
    void SetTextData2Temp();


    void InitTextFromSplice(M10Part SpliceData);
    void PostWeld_Indicators_Update(); // called in check weld data
    void UpdateMaintenanceData();
    void TeachModeFinished(PresetElement* _Splice);
    void RemoteReset();
private:
    void Escape_Teach_Auto_Invalid_Welds(bool Alarm_found);
    void RestartSeqOnAlarm();
    void TeachModeProcess();
    bool CheckForOverLoad(bool ShowAlarm);
    void Update_Counter();

public:
    static M10runMode* Instance();
protected:
    M10runMode();
private:
    static M10runMode* _instance;
public:
    ~M10runMode(){} //do-nothing destructor
};

#endif // M10RUNMODE_H
