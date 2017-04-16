#include "M2010.h"
#include "M10INI.h"
#include "UtilityClass.h"
#include "SaveReplace.h"
#include "Statistics.h"
#include "M10runMode.h"
#include "ModRunSetup.h"
#include <QDir>
#include <QDataStream>
#include <QFile>
#include "Modules/UtilityClass.h"
#include "Interface/Interface.h"
#include "M102IA.h"
M2010* M2010::_instance = 0;
M2010* M2010::Instance()
{
    if(_instance == 0){
        _instance = new M2010();
    }
    return _instance;
}

M2010::M2010()
{
    ReceiveFlags.SETUPdata = false;
    ReceiveFlags.PRESETdata = false;
    ReceiveFlags.WELDdata = false;
    ReceiveFlags.PowerGraphData = false;
    ReceiveFlags.HeightGraphData = false;
    ReceiveFlags.SNdata = false;
    ReceiveFlags.IOdata = false;
    ReceiveFlags.SonicHitsData = false;
    ReceiveFlags.PressureData = false;
    ReceiveFlags.IOSWITCHdata = false;
    ReceiveFlags.WELDDOWNLOADPARAMETERdata = false;
    ReceiveFlags.WELDDOWNLOADdata = false;
    ReceiveFlags.HeightData = false;
    ReceiveFlags.WIDTHdata = false;
    ReceiveFlags.MEMORYdata = false;
    ReceiveFlags.POWERrating = false;
    ReceiveFlags.STARTsignal = false;
    ReceiveFlags.SEQUENCEtable = false;
    ReceiveFlags.HORNamplitude = false;
    ReceiveFlags.SYSTEMid = false;
    ReceiveFlags.MAINTENANCEcounters = false;
    ReceiveFlags.AVAILABLE = -1;
    ReceiveFlags.IAFOUNDGOOD = false;
    ReceiveFlags.TIMEOUTERROR = false;
    ReceiveFlags.BADCHECKSUM = false;
    ReceiveFlags.PresetTable = false;
    ReceiveFlags.WireData = false;
    ReceiveFlags.FootPadelDATA = false;
    ReceiveFlags.ControllerVersionData = false;
    ReceiveFlags.ControllerSerialNumData = false;
    ReceiveFlags.ControllerPartNumData = false;
    ReceiveFlags.CalibrationDone = false;
    ReceiveFlags.HostReadyData = false;
    ReceiveFlags.CalHeightMaxGaugeData = false;
    ReceiveFlags.ActuatorType = false;
    ReceiveFlags.ActuatorVersionData = false;
    ReceiveFlags.ActuatorSerialNumData = false;
    ReceiveFlags.ActuatorPartNumData= false;
    ReceiveFlags.HeightGraphData = false;
    ReceiveFlags.CutterResponseData = false;

    M10Run.Sequence_Done = false;
    M10Run.Pre_Hght_Error = false;
    M10Run.Alarm_found = false;
    M10Run.Save_Data = false;
    M10Run.Auto_Set_Mode = false;
    M10Run.BarcodeFlash = false;
    M10Run.SafetyFailed = false;
    M10Run.Sequence_Line = -1;
    M10Run.Part_Count = -1;
    M10Run.Run_Splice.clear();
    M10Run.Seq_File_Name.clear();
    M10Run.Select_Part_file = false;
    M10Run.Select_Seq_file = false;
    M10Run.Load_From_Lib = false;
    M10Run.Initial_Startup = false;
    M10Run.Run_Splice_Stat.clear();
    M10Run.GotoRun = false;
    M10Run.E_Stop_Signal = false;
    M10Run.Horn_Close = false;
    M10Run.Gather_Close = false;
    M10Run.Anvil_Clamped = false;
    M10Run.Aux3On = false;
    M10Run.Aux4On = false;
    M10Run.Aux5On = false;
    M10Run.CoolingOn = false;
    M10Run.ToolingCoolingOn = false;
}

//void M2010::LoadSequenceData(string sSeqName, bool bFailedLoad, bool bIgnoreParts)
//{

//}

void M2010::ConvertPowerGraphData(QStringList SourceGraphDataList, QList<int> *DestList)
{
    if(DestList == NULL)
        return;
    int StartData = 17;      //First data character
    QString GraphString = "";
    QString Str;
    for (int i = 0; i < (SourceGraphDataList.size() - 1);i++)
    {
        Str = SourceGraphDataList.at(i);
        GraphString += Str.mid(StartData, 32);
    }
    Str = SourceGraphDataList.last();
    GraphString += Str.mid(StartData, (Str.length() - 19));

    int WeldPoints, Points, LenString;
    LenString = GraphString.length();
    WeldPoints = (int)(LenString/2);
    Points = WeldPoints - 5;
    int j = 0;
    bool bResult;
    for(int i = 0; i < Points; i++)
    {
        Str = GraphString.mid(j, 2);
        int value = Str.toInt(&bResult, 16);
        DestList->insert(i, value);
        j += 2;
    }
}

void M2010::ConvertHeightGraphData(QStringList SourceGraphDataList, QList<int> *DestList)
{
    M102IA *_M102IA = M102IA::Instance();
    if(DestList == NULL)
        return;
    int StartData = 17;      //First data character
    QString GraphString = "";
    QString Str;
    for (int i = 0; i < (SourceGraphDataList.size() - 1);i++)
    {
        Str = SourceGraphDataList.at(i);
        GraphString += Str.mid(StartData, 64);
    }
    Str = SourceGraphDataList.last();
    GraphString += Str.mid(StartData, (Str.length() - 19));

    int WeldPoints, Points, LenString;
    LenString = GraphString.length();
    WeldPoints = (int)(LenString/4);
    Points = WeldPoints - 5;
    int j = 0;
//    bool bResult;
    for(int i = 0; i < Points; i++)
    {
        Str = GraphString.mid(j, 4);
        int value = _M102IA->MakeHexWordNumber(Str);
        DestList->insert(i, value);
        j += 4;
    }
}

QString M2010::ParseSerialNumber(QString SerialCode)
{
    int i, StringLen, temp2;
    QString temp1;
    QByteArray bufNumber;
    StringLen = SerialCode.length();
    i = 0;
    while (i< StringLen)
    {
        temp1 = SerialCode.mid(i,2);
        bool bResult;
        temp2 = temp1.toInt(&bResult,16);
        bufNumber.insert(i/2,(char)temp2);
        i += 2;
    }
    return bufNumber.data();
}

//string M2010::GetResString(long StringNo)
//{
//    string temp;
//    return temp;
//}

//void M2010::NumberOnly(int KeyAscii)
//{

//}

/**********************************************************************************/
/*This function loads temporary preset or the saved preset in the Splice structure*/
/*depending on whether the Preset is altered and saved or not.                    */
/**********************************************************************************/
void M2010::load_splice_file()
{
    SaveReplace *ptr_SaveReplace = SaveReplace::Instance();
    Statistics  *ptr_Statistics  = Statistics::Instance();
    M10runMode  *ptr_M10runMode  = M10runMode::Instance();
//    M10INI      *ptr_M10INI      = M10INI::Instance();
    ModRunSetup *ptr_ModRunSetup = ModRunSetup::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();


    //This function will load the splice file present in run record.
//    int i = 0;

    if (PresetChanged == true)
       Splice = TempPreset;

    if (M10Run.Run_Splice == "")                  //Create and/or use default preset.
    {
        ptr_SaveReplace->CalculateSpliceData();
        ptr_Statistics->ZeroM20DataEvents();
        M10Run.Run_Splice = Splice.PartNo;
    }
    InterfaceClass* _Interface = InterfaceClass::Instance();
    if (_Interface->StatusData.Soft_Settings.Teach_Mode != TEACHMODESETTING::AUTO)
    {
        if (M10Run.Auto_Set_Mode == true)          //In all teach mode screens
        {
        // Quality window to max, lock the data

            if ((Splice.FlagWord & WELDMMODEMASK) != 1)
            {
                Splice.Time.Minus = MINTIME;
                Splice.Time.Plus = MAXTIME;
            }
            Splice.Power.Minus = MINPOWER;
            Splice.Power.Plus = _Utility->Maxpower;
            Splice.Preheight.Minus = MINPREHEIGHT;
            Splice.Preheight.Plus = MAXPREHEIGHT;
            if ((Splice.FlagWord & WELDMMODEMASK) != 3)
                Splice.Height.Minus = MINHEIGHT;
            if (((Splice.FlagWord & WELDMMODEMASK) != 2) && ((Splice.FlagWord & WELDMMODEMASK) != 3))
                Splice.Height.Plus = MAXHEIGHT;

            // if Teach mode samples haven't finished then don't reset Splice_Stat
            if (ptr_ModRunSetup->TeachModeSamplesNotFinished != true)
                ptr_Statistics->ZeroM20DataEvents();
            else
                ptr_ModRunSetup->TeachModeSamplesNotFinished = false;

        }
    }
    _Utility->InitializeTextData();
    SpliceData2IA();
//    frmSetupScreen.UpdateTubeShrinker();
    ptr_M10runMode->InvalidWeldCounter = 0;

}

/*****************************************************************************/
/*this function is used to send the preset data to controller                */
/*this also send width calibration data ,trigpress,amplitude and pre burst.  */
/*Command for Sending Amplitude Step parameters is also added before         */
/* the Preset is sent to the controller                                      */
/*****************************************************************************/
void M2010::SpliceData2IA()
{

}

/********************************************************************************/
/*This function copies Splice data to preset structure to be send to controller.*/
/*Copy is done one by one item wise                                             */
/*AmplitudeStep parameters are also sent to the controller                      */
/********************************************************************************/
void M2010::UpdateIAfields()
{

}

void M2010::ReZeroSpliceData()
{
//    int i,j;
    //Kill the first wire in the default splice
    Splice.Area = 0;
    Splice.NoOfWires = 0;
    Splice.Energy = 0;
}
