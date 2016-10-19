#ifndef MODRUNSETUP_H
#define MODRUNSETUP_H
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include "m10definitions.h"
using namespace std;

class ModRunSetup
{
public:

    bool InitialStartFlag; //to indicate that software has just started
    bool PresetSeqChangedCreated;
    bool MenuNewPresetPressFlag;
    bool MenuCreateSeqPressFlag;
    bool InputBoxCancelFlag;
    M10EXIT_ACTION M10exitMode;
    bool EditSeqOrSpliceFlag;
    int LeftVerticalCoordinates[60];
    int RightVerticalCoordinates[60];
    int OperatorScreenTop[9];
    int OperatorScreenHeight[9];
    int OperatorScreenWidth[9];
    int CenterPointTop[9];
    int WireLabelTop_frmCreateEditSplice[3];
    bool FlagCheckPassword_Setup;
    bool LabelFlag;
    int BaseLineCoordinates[9];
    int WireNumberOfSplice[40]; // 1 to 20 for lblLeftWire ,rest for lblRightWire
    bool OfflineModeEnabled;
    bool GlobalOfflineModeEnabled;
    M10Part SpliceBackUp;      //structure comes in use when esc. button is pressed
    ShrnkTubeIndex PrSizeCode;
    float PrShrinkTime;
    int PrShrinkTemp;
    float NumkeyValue;
    string KeypadtextValue;
    bool cancelmode;
    bool numkey_cancel;
    bool Languageselection;    //tells if Language dialog box has been visited
    bool Seq_Created_Or_Edited_Recently;
    //the flag helps in not reseting contents of Splice_Stat, even if user hops among different screens
    bool TeachModeSamplesNotFinished;
    bool Seqchanged;

    enum OPERATOR_SCREEN_WELD_INDICATOR Operator_PreHeight_Indicator;
    enum OPERATOR_SCREEN_WELD_INDICATOR Operator_Height_Indicator;
    enum OPERATOR_SCREEN_WELD_INDICATOR Operator_Time_Indicator;
    enum OPERATOR_SCREEN_WELD_INDICATOR Operator_Power_Indicator;

    //these declarations moved from old run screen code
    long SplicePictureBackColor;
    //   Variables used when copy data to floppy for Error.Log file
    string ETyp;
    string EVal;
    //   Variable to check if the file column is shown
    bool FileShown;
    float Currentvalue;
    long NewValueEntered;
    bool SpliceShown;
    int tempWidthOffsetVal;
    int tempHeightOffsetval;
public:
    void End_Model_10(M10EXIT_ACTION Action);
    bool LoadNewProjectSelect();
    void SaveStatFiles();
    void DeleteStatTempFiles();
    void M10initiate(bool bLoadFail = false);
    void Start_Run(int ModeLabel, int Onlycolorchange);
private:
    //Variable to hold the Index Position for the Pop-Up Menu in the Setup_Mode
    int IndexSetting;
public:
    static ModRunSetup* Instance();
protected:
    ModRunSetup();
private:
    static ModRunSetup* _instance;
public:
    ~ModRunSetup(){} //do-nothing destructor
};

#endif // MODRUNSETUP_H
