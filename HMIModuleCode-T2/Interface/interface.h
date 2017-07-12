#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include <QObject>
#include <QDebug>
//#include "definition.h"
#include "PresetElement.h"
#include "SysConfiguration.h"
#include "Settings/OperatorLibrary.h"
#include "WorkOrderElement.h"
const QString HelpContent[] = {
    /* SpliceScreen 0*/
    QObject::tr("<WIRE BUILDER> build wires for specific splice\n"
                "<EDIT EXISTING SPLICE> edit existing splices built before\n"
                "<WIRE LIBRARY> go to wire library to select wires\n"
                "<ADD WIRE> add wires into splice\n"
                "<DELETE WIRE> delete wires from splice\n"
                "<SAVE SPLICE> save splice\n"
                "<Image> insert image for the splice\n"
                "<SPLICE NAME> input splice name"),
    /* SequenceScreen 1*/
    QObject::tr("<Up> move selected splice upward\n"
                "<Down> move selected splice downward\n"
                "<ADD NEW SPLICE> add new splice to a sequence\n"
                "<ADD EXISTING SPLICE> add existing splice to a sequence\n"
                "<EDIT EXISTING SEQUENCE> edit an exsting sequence\n"
                "<SAVE SEQUENCE> save a sequence\n"
                "<EDIT SPLICE> edit the selected splice\n"
                "<DELETE SPLICE> delete the selected splice"),
    /* HarnessScreen 2*/
    QObject::tr("<Up> move selected splice upward\n"
                "<Down> move selected splice downward\n"
                "<ADD NEW SPLICE> add new splice to a harness\n"
                "<ADD EXISTING SPLICE> add new splice to a harness\n"
                "<EDIT EXISTING HARNESS> edit an existing harness\n"
                "<SAVE HARNESS> save a harness\n"
                "<EDIT SPLICE> edit the selected splice\n"
                "<DELETE SPLICE> delete the selected splice"),
    /* WireScreen 3*/
    QObject::tr("<WIRE BUILDER> build wires for specific splice\n"
                "<SAVE TO WIRE LIBRARY> save selected wire into wire library\n"
                "<Color> edit color of selected wire\n"
                "<Stripe> edit stripe type of selected wire\n"
                "<Conductor> edit material of selected wire\n"
                "<Side> specify the side when insert the selected wire\n"
                "<Location> specify the location when lay the selected wire"),
    /* SetupScreen 4*/
    QObject::tr("<WELD SETTINGS> SET WELDING PARAMETERS AND\n"
                "                  QUALITY WINDOW\n"
                "<ADVANCED SETTING> go into advanced settings\n"
                "<Graph> display power graph and height graph\n"
                "<Cancel> cancel the change\n"
                "<SAVE SPLICE> save settings to specific splice"),
    /* AdvanceSettingScreen 5*/
    QObject::tr("<Weld Model> select welding mode\n"
                "<Insulation> enable/disable communications with downstream\n"
                "              Raychem shrink tube machine\n"
                "<Pre Burst> set pre-burst time\n"
                "<After Burst> set after burst duration time\n"
                "<Squeeze> set squeeze time\n"
                "<Hold> set hold time\n"
                "<Displayed> input actual width/height displayed on splicer machine\n"
                "<Actual> input actual width/height of work piece measured by meter\n"
                "<SAVE> save settings to specific splice"),
    /* HarnessSettingScreen 6*/
    QObject::tr("<Basic/Adv.> enter basic or advanced setting mode\n"
                "<Board/Splice> enter board or splice setting\n"
                "<WORKSTATION> input number of workstation and max splices\n"
                "              per workstation\n"
                "<BOARD LAYOUT> input number of row and column, as well as\n"
                "                  max splice per zone\n"
                "<EDIT SPLICE> edit the selected splice\n"
                "<DELETE SPLICE> delete the selected splice"),
    /* InsulationScreen 7*/
    QObject::tr("<Shrink tube ID> set shrink tube ID\n"
                "<Temp> set shrink temperature\n"
                "<Time> set shrink time\n"
                "<Mutex Lock> enable/disable Mutex function"),
    "", /* 8 */
    "", /* 9 */
    /* TestScreen  10*/
    QObject::tr("<OK> select a splice and click OK for confirm"),
    "", /* 11 */
    "", /* 12 */
    "", /* 13 */
    "", /* 14 */
    "", /* 15 */
    "", /* 16 */
    "", /* 17 */
    "", /* 18 */
    "", /* 19 */
    /* SpliceListScreen 20*/
    QObject::tr("<OK> select a splice and click OK for confirm"),
    /* SequenceListScreen 21*/
    QObject::tr("<OK> select a squence and click OK for confirm"),
    /* HarnessListScreen 22*/
    QObject::tr("<OK> select a harness and click OK for confirm"),
    /* OperateSpliceSettingScreen 23*/
    QObject::tr("<OK> select a splice and click OK for confirm\n"
                "<Sample Size> set sample size or unconstrained when teach mode off\n"
                "<Teach Mode> select teach mode standard/auto/sigma\n"
                "<Advanced Setting> enter advanced settings for teach mode\n"
                "<Start> start operation"),
    /* TeachModeAdvancedSettingScreen 24*/
    QObject::tr("<Upper> set allowable max deviation percentages\n"
                "<Lower> set allowable min deviation percentages\n"
                "<Quantity> set sample size\n"
                "<Default Setting> use default settings\n"
                "<Cancel> cancel changes\n"
                "<OK> confirm all changes"),
    /* OperateSpliceScreen 25*/
    QObject::tr("<EDIT SPLICE> edit current splice"),
    /* OperateSequenceScreen 26*/
    QObject::tr("<EDIT SPLICE> edit one splice of sequence"),
    /* OperateHarnessSettingScreen 27*/
    QObject::tr("<Batch Size> specify batch size or unconstrained batch size\n"
                "<START> start to operate harness\n"
                "<CANCEL> cancel selection of harness"),
    /* OperateHarnessScreen 28*/
    QObject::tr("<EDIT SPLICE> edit one splice of harness"),
    "", /* 29 */
    /* WeldResultHistoryScreen 30*/
    QObject::tr("<Sequence Name> specify sequence name to check associated weld\n"
                "                  result history\n"
                "<Harness Name> specify harness name to check associated weld\n"
                "                  result history\n"
                "<Splice Name> specify splice name to check associated weld\n"
                "              result history\n"
                "<Data and Time> specify starting and ending date and time to check\n"
                "                  associated weld result history\n"
                "<APPLY> apply search method\n"
                "<Back>\n"
                "<Export Data> export data to local PC or external memory"),
    /* StatisticalTrendScreen 31*/
    QObject::tr("<Splice Name> specify sequence name to check associated statistical trend\n"
                "<Date and Time> specify starting and ending date and time to check\n"
                "                  associated statistical trend\n"
                "<APPLY> apply search method\n"
                "<Export Data> export data to local PC or external memory\n"
                "<Time> display statistical trend in terms of welding time\n"
                "<Peak Power> display statistical trend in terms of peak power\n"
                "<Pre-Height> display statistical trend in terms of pre-height\n"
                "<Post Height> display statistical trend in terms of post height"),
    /* ErrorAlarmLogScreen 32*/
    QObject::tr("<Alarm/Error> specify alarm or error type to check associated log\n"
                "<Date and Time> specify starting and ending date and time to check\n"
                "                  associated log\n"
                "<APPLY> apply search method\n"
                "<Export Data> export data to local PC or external memory"),
    /* LibraryScreen 33*/
    QObject::tr("<Splice> enter into splice library\n"
                "<Sequence> enter into sequence library\n"
                "<Harness> enter into harness library\n"
                "<Wire> enter into wire library\n"
                "<Insulation> enter into insulation library\n"
                "<Edit> edit selected item\n"
                "<Delete> delete selected item\n"
                "<Export> export data to local PC or external memory\n"
                "<Import> import data from local PC or externam memory"),
    "", /* 34 */
    "", /* 35 */
    "", /* 36 */
    "", /* 37 */
    "", /* 38 */
    "", /* 39 */
    /* CalibrationScreen 40 */
    QObject::tr("<Start> start calibration\n"
                "<Cancel> cancel calibration"),
    /* ToolChangeScreen 41 */
    QObject::tr("<NEXT STEP> move forward to next step of tool change\n"
                "<BACK> move forward to previous step of tool change"),
    /* AdvancedMaintenanceScreen 42 */
    QObject::tr("<1-Anvil Arm> check status of anvil arm\n"
                             "<2-Gather> check status of gather\n"
                             "<3-Safety> check status of safety\n"
                             "<4-Cutter> check status of cutter\n"
                             "<5-Cooling Tooling> check status of cooling air for tooling\n"
                             "<6-Cooling Converter> check status of cooling air for converter\n"
                             "<7-Crash> check status of crash stopper\n"
                             "<Run Sonics> fire ultrasonic energy at the current amplitude setting\n"
                             "<Run Sonics 100%> fire ultrasonic energy at 100% amplitude\n"
                             "                  Used when calibrating amplitude\n"
                             "<Amplidude> set the amplitude value based on the gauge reading\n"
                             "<Reset> reset alarm"),
    /* MaintenanceCounterScreen 43 */
    QObject::tr("<Counter> increase after each weld cycle up to limits set by user\n"
                "<Limit> set the maintenance limits for the listed items in number of\n"
                "          weld cycle or in kilo-joule units\n"
                "<Reset> reset the counter to zero after maintenance or replacement\n"
                "<80% Alarm> enable or disable alarm trigger when counter increase up\n"
                "              to 80% of setting\n"
                "<100% Lock> enable or disable machine lock when counter increase up\n"
                "              to 100% of setting"),
    /* MaintenanceLogScreen 44 */
    QObject::tr("<Maintenance Type> select maintenance type to search associated\n "
                "                      maintenance log\n"
                "<Date and Time> specify starting and ending date and time to search\n"
                "                  associated maintenance log\n"
                "<APPLY> apply search method\n"
                "<Export Data> export data to local PC or external memory"),
    /* UserManual 45 */
    QObject::tr("<Search> input keyword for search\n"
                "<Previous> move backward to the previous matched keyword\n"
                "<Back> move forward to the next matched keyword"),
    "", /* 46 */
    "", /* 47 */
    "", /* 48 */
    "", /* 49 */
    /* PermissionSettingScreen 50 */
    QObject::tr("<Function Name> select functions linked to permission level\n"
                "<Level 1> input category name and check box of associated\n"
                "          functions permitted\n"
                "<Level 2> input category name and check box of associated\n"
                "          functions permitted\n"
                "<Level 3> input category name and check box of associated\n"
                "          functions permitted\n"
                "<Level 4> input category name and check box of associated\n"
                "          functions permitted\n"
                "<Default> back to default setting of function list\n"
                "<Cancel> cancel the new settings\n"
                "<OK> apply the new settings"),
    /* WeldDefault1Screen 51 */
    QObject::tr("<Width Encoder> enable or disable width encoder\n"
                "<Height Encoder> enable or disable height encoder\n"
                "<Foot Pedal Abort> enable or disable foot pedal abort\n"
                "<Seek> enable or disable frequency seek\n"
                "<Cooling> enable the setting of a predetermined amount of\n"
                "          time the cooling air will stay on after a splice\n"
                "<Cooling(1sec/100J)> automatically sets cooling duration \n"
                "                      after a splice to 1 second per 100J of energy applied\n"
                "<Cooling Tooling> set the delay period after a splice and \n"
                "                  before cooling is turned on\n"
                "<Graph Data Sampling> set sampling frequency(1/5/10/20ms) \n"
                "                      to generate a graph of power(Watts vs. Time)\n"
                "<Display> set display units\n"
                "<Formula> set three different splice area range and associated \n"
                "          offset & multiplier to formulate a recommended weld settings\n"
                "<Default> go back to system default settings\n"
                "<Cancel> cancel all changes\n"
                "<OK> apply all changes"),
    /* OperatorLibraryScreen 52 */
    QObject::tr("<Add New> add new operator\n"
                "<Operator Name> input operator’s name\n"
                "<Password> input operator’s password\n"
                "<permission level> select operator’s permission level\n"
                "<Cancel> cancel all the changes\n"
                "<OK> apply all the changes\n"
                "<Edit> edit existing operators\n"
                "<Delete> delete existing operators"),
    /* DataCommunicationScreen 53 */
    QObject::tr("<Network(Ethernet)> enable or disable Ethernet network communication\n"
                "<Remote Data Logging> enable or disable the controller to send weld\n"
                "                      results out the Ethernet port at the end of each weld cycle\n"
                "<Modular Production Mode> enable or disable KSK network communication\n"
                "<Graph Data> enable or disable the controller to send the power graph\n"
                "<Shrink Tube Test> test the communication with shrink tube machine\n"
                "<Server Port> set the server port that will be used to communicate\n"
                "              between the controller and user data logging application"),
    /* WeldDefault2Screen 54 */
    QObject::tr("<Anti-Side> enable or disable anti-side function\n"
                "<Unload> set the time the gather will be open for the operator to remove\n"
                "          a splice when it’s done\n"
                "<Cutter> enable or disable cutting function\n"
                "<Load> set the time the cutter will apply\n"
                "<Time> enable or disable cutting function according to time quality window\n"
                "<Peak Power> enable or disable cutting function according to\n"
                "              peak power quality window\n"
                "<Pre-Height> enable or disable cutting function according to pre-height\n"
                "              quality window\n"
                "<Post-Height> enable or disable cutting function according to post-height\n"
                "              quality window"),
    "", /* 55 */
    "", /* 56 */
    "", /* 57 */
    "", /* 58 */
    "" /* 59 */
};

enum TipsScreenMode{
    OKOnly      = 0x00, //only show Okay button
    OKCancel    = 0x01, //show Okay and cancel buttons
    RESETCancel = 0x02, //show Reset and cancel buttons
    ACCEPTReject = 0x04, //show Accept and Reject buttons
    Critical    = 0x10, //show Error sign
    Exclamation = 0x20, //show Warning sign
    Information = 0x40, //show Information sign
    Alarm       = 0x80, //show Alarm sign
    QualityAlarm = 0x100, //show Alarm Sign, and only for the lock on alarm.
    OFF_ON_LINE = 0x200,//show On Line and Off Line

};

struct BransonMessageBox{
    QString MsgTitle;
    QString MsgPrompt;
    int TipsMode;
    void* _Object;
    void (*OKfunc_ptr)(void*);
    void (*Cancelfunc_ptr)(void*);
};


class InterfaceClass:public QObject
{
         Q_OBJECT
public:

    enum SUBMENUOPTION{
        SpliceScreen = 0,
        SequenceScreen = 1,
        HarnessScreen = 2,
        WireScreen = 3,
        SetupScreen = 4,
        AdvanceSettingScreen = 5,
        HarnessSettingScreen = 6,
        InsulationScreen = 7,
        TestScreen = 10,
        SpliceListScreen = 20,
        SequenceListScreen = 21,
        HarnessListScreen = 22,
        OperateSpliceSettingScreen = 23,
        TeachModeAdvancedSettingScreen = 24,
        OperateSpliceScreen = 25,
        OperateSequenceScreen = 26,
        OperateHarnessSettingScreen = 27,
        OperateHarnessScreen = 28,
        WeldResultHistoryScreen = 30,
        StatisticalTrendScreen = 31,
        ErrorAlarmLogScreen = 32,
        LibraryScreen = 33,
        VersionInformationScreen = 34,
        CalibrationScreen = 40,
        ToolChangeScreen = 41,
        AdvancedMaintenanceScreen = 42,
        MaintenanceCounterScreen = 43,
        MaintenanceLogScreen = 44,
        UserManual = 45,
        PermissionSettingScreen = 50,
        WeldDefault1Screen = 51,
        OperatorLibraryScreen = 52,
        DataCommunicationScreen = 53,
        WeldDefault2Screen = 54,
    };

public:
    static InterfaceClass* Instance();
    //Following for the screen showing using signal
public:
    Status_Data StatusData;
    Status_Data tempStatusData;         //Used by routines before an OK or Save
    Status_Data DefaultStatusData;
    VersionList PreviousVersions;
    VersionList CurrentVersions;
    OperatorElement CurrentOperator;
    WorkOrderElement CurrentWorkOrder;
    bool FirstScreenComesUp;
    bool ApplicationFirstStartFlag;
public:
    void cMsgBox(struct BransonMessageBox* MsgBox);
    void DispearMsgBox();
    void ShownAlarmSign();
    void UpdateAlarmList();
//    void LockOnAlarm();
    static void HotRestartSys(void* _Obj);
private:
    void CheckBransonFolder();
signals:
    void EnableErrorMessageSignal(struct BransonMessageBox &MsgBox);
    void DisableErrorMessageSignal(struct BransonMessageBox &MsgBox);
    void ThereAreAlarmItemsSignal();
    void ThereAreSomeAlarmReseted();
public slots:
    void AnyAlarmEventSlot(bool &bResult);
protected:
    InterfaceClass(QObject *parent = 0);
private:
    BransonMessageBox MessageBox;
    static InterfaceClass* _instance;
    BransonMessageBox tmpMsgBox;
public:
    ~InterfaceClass();
};

#endif // INTERFACE_H
