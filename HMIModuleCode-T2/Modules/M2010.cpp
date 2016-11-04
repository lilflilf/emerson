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
    ReceiveFlags.PowerData = false;
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
    ReceiveFlags.CalibrationDone = false;
    ReceiveFlags.HostReadyData = false;
    ReceiveFlags.CalHeightMaxGaugeData = false;
    ReceiveFlags.ActuatorType = false;
    ReceiveFlags.ActuatorVersionData = false;
    ReceiveFlags.ActuatorSerialNumData = false;
    ReceiveFlags.ActuatorPartNumData= false;
}

//void M2010::LoadSequenceData(string sSeqName, bool bFailedLoad, bool bIgnoreParts)
//{

//}
/******************************FIXED************************************/
void M2010::GetLastRunRecord()
{
    //This function reads the file mode(Preset/sequence) from run_dat file.
    QString sFilePath;
    QDir dir;
    M10INI  *ptr_M10INI  = M10INI::Instance();
    UtilityClass *ptr_Utility = UtilityClass::Instance();

    sFilePath = ptr_M10INI->ConfigFilesPath + Run_File_Name;

    if(ptr_Utility->ReadFromBinaryFile(sFilePath, &RunFileRecord) == false)
       RunFileRecord.LastMade = None_Made;
}

/*********************************Fixed*************************/
void M2010::PutLastRunRecord(int TypeMade, QString PartName)
{
    //This function writes the file mode(Preset/sequence) from run_dat file.
    QString sFilePath;
    M10INI  *ptr_M10INI  = M10INI::Instance();
    UtilityClass *ptr_Utility = UtilityClass::Instance();
    RunFileRecord.Last_file = PartName;
    RunFileRecord.LastMade = TypeMade;
    sFilePath = ptr_M10INI->ConfigFilesPath + Run_File_Name;
    ptr_Utility->WriteToBinaryFile(&RunFileRecord, sFilePath);
}

//void M2010::MakeNormalSplice(M10Part ThisSplice)
//{

//}

/****************************************************************************************************/
/*The first splice the system sees or used when the load files are a problem.                       */
/*It provides all the default values to the Splice made.                                            */
/*CustRev and RevDate have been removed and Step variables have been added from the Splice structure*/
/****************************************************************************************************/
void M2010::MakeDefaultSplice(M10Part SpliceName)
{

}

int M2010::DecPtrCircular(int ptr, int ptrMAX)
{
    /*These functions are designed for manipulating pointers with values 0 to ptrMAX*/
    int tmpPtr = 0;
    if(ptr > 0)
        tmpPtr = (ptr - 1);
    else
        tmpPtr = ptrMAX;
    return tmpPtr;
}

int M2010::IncPtrCircular(int ptr, int ptrMAX)
{
    return ((ptr + 1) % (ptrMAX + 1));
}

void M2010::ConvertGraphData(QString GraphData)
{

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
    else
        LoadSpliceFile(M10Run.Run_Splice, Splice);//On failure, sets M10Run.Run_Splice=""

    if (M10Run.Run_Splice == "")                  //Create and/or use default preset.
    {
        MakeDefaultSplice(Splice);                //Set Splice Part Structure to initial data in case there is no Run_file.dat
        ptr_SaveReplace->CalculateSpliceData();
        ptr_Statistics->ZeroM20DataEvents();
        M10Run.Run_Splice = Splice.PartNo;
        SaveSpliceFile(true);                     //Update run_file.dat
    }

    ptr_M10runMode->init_m20_data_events();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    if (_Interface->StatusData.Soft_Settings.Teach_Mode != AUTO)
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
    MakeDefaultSplice(Splice);
    //Kill the first wire in the default splice
    Splice.Area = 0;
    Splice.NoOfWires = 0;
    Splice.Energy = 0;
}

void M2010::UpdateSpliceData()
{
    UpdateThisSplice(Splice);
}

/***************************************************************************************************/
/*ThisSplice is always Splice, DO NOT CHANGE                                                       */
/*The Splice is updated with the related values from the data structure and stored in the .PRT file*/
/*Update Splice structure with the Amplitude Step related parameters                               */
/*It updates the .PRT file only when invoked on Teach Mode                                         */
/***************************************************************************************************/
void M2010::UpdateThisSplice(M10Part ThisSplice)
{
    int FileNumber;
}

//void M2010::SendNWmsgStruct(ErrMsgStruct MsgStruct[])
//{

//}

//void M2010::SendNWmsg(string sErrPart, string sErr)
//{

//}

/*************************************************************************************/
/* This routine replaces the many, many file accesses in the old program             */
/* Because of the variety of input possibilities the process must include checking to*/
/* see if it is a file, path, or part name submitted.                                */
/* The assumption is that it is either a part name or a legitimate part file name    */
/* The Splice structure is then updated from the .PRT file.                          */
/* RevCode of .PRT is compared and updated with the DEFINEDREVCODE(current RevCode)  */
/*************************************************************************************/
void M2010::LoadSpliceFile(QString sPartDescription, M10Part PartDest)
{

}

/****************************************************************/
/*This routine saves the Splice structure in the .PRT file only */
/* when the current preset is asked to save.                    */
/*Till that time it is in RAM and acts as the working Preset.   */
/****************************************************************/
void M2010::SaveSpliceFile(bool bUpdateRun, bool SaveOriginalSplice)
{

}

int M2010::MakeIntEven(int DataIn, bool RoundDown)
{
    return DataIn;
}

/***************************************************************************************/
/*This function compares the Revcode of the .PRT file and the Defined RevCode          */
/* and updates the PRT file in case the Revcode used is different from the current one.*/
/***************************************************************************************/
void M2010::UpdateRevCode(string sFilePath, M10Part PartDest, int PrtRevCode)
{
    int i;
    M10PartRevThree PartDestRevThree;
    M10PartRevTwo   PartDestRevTwo;
}

int M2010::GetTeachModeRunCount()
{
    int tmpRunCount;
    if (Splice.PresetTeachModeSetting == GLOBALS)
    {

    }
    return tmpRunCount;
}

void M2010::CopyPartRevThree(M10PartRevThree PartDestRevThree, M10Part PartDest)
{
//    PartDest.RevCode      = DEFINEDREVCODE;
//    PartDest.PartNo       = PartDestRevThree.PartNo;
//    PartDest.FlagField    = PartDestRevThree.FlagField;
//    PartDest.Amplitude2   = PartDestRevThree.Amplitude2;
//    PartDest.EnergyToStep = PartDestRevThree.EnergyToStep;
//    PartDest.Area         = PartDestRevThree.Area;
//    PartDest.PartsCnt     = PartDestRevThree.PartsCnt;
//    PartDest.TimeToStep   = PartDestRevThree.TimeToStep;
//    PartDest.PowerToStep  = PartDestRevThree.PowerToStep;
//    PartDest.Energy       = PartDestRevThree.Energy;
//    PartDest.Width        = PartDestRevThree.Width;
//    PartDest.Pressure     = PartDestRevThree.Pressure;
//    PartDest.Amplitude    = PartDestRevThree.Amplitude;
//    PartDest.Time         = PartDestRevThree.Time;
//    PartDest.Power        = PartDestRevThree.Power;
//    PartDest.Preheight    = PartDestRevThree.Preheight;
//    PartDest.Height       = PartDestRevThree.Height;
//    PartDest.Force        = PartDestRevThree.Force;
//    PartDest.NoOfWires    = PartDestRevThree.NoOfWires;
//    for(int i = 0; i< MAX_WIRE_ELEMENTS;i++)
//    {
//        PartDest.WireEl[i].PartName = PartDestRevThree.WireEl[i].PartName;
//        PartDest.WireEl[i].Area = PartDestRevThree.WireEl[i].Area;
//        for (int j = 0; j < 11; j++)
//        {
//            PartDest.WireEl[i].Color[j] = PartDestRevThree.WireEl[i].Color[j];
//        }
//    }
//    PartDest.RecData   = PartDestRevThree.RecData;
//    PartDest.TrigPres  = PartDestRevThree.TrigPres;
//    PartDest.SqzTime   = PartDestRevThree.SqzTime;
//    PartDest.FlagWord  = PartDestRevThree.FlagWord;
//    PartDest.StopCount = PartDestRevThree.StopCount;
//    PartDest.HoldTime  = PartDestRevThree.HoldTime;
//    PartDest.ABDelay   = PartDestRevThree.ABDelay;
//    PartDest.ABDur     = PartDestRevThree.ABDur;
//    PartDest.PreBurst = PartDestRevThree.PreBurst;
//    PartDest.WidthCorr = PartDestRevThree.WidthCorr;
//    PartDest.HeightCorr = PartDestRevThree.HeightCorr;
//    PartDest.ShrinkTubeIndex = PartDestRevThree.ShrinkTubeIndex;
//    PartDest.ShrinkTime = PartDestRevThree.ShrinkTime;
//    PartDest.ShrinkTemperature = PartDestRevThree.ShrinkTemperature;
//    PartDest.PreviousFileNumber = PartDestRevThree.PreviousFileNumber;
//    PartDest.PresetTeachModeSetting = PartDestRevThree.PresetTeachModeSetting;
//    for(int i = 0; i < ENERGY_ADJ; i++)
//    {
//         PartDest.TeachModequal_Window[i] = PartDestRevThree.TeachModequal_Window[i];
//    }
//    PartDest.StandardRunQuantity = PartDestRevThree.StandardRunQuantity;
//    PartDest.AutoRunQuantity = PartDestRevThree.AutoRunQuantity;
//    PartDest.SigmaRunQuantity = PartDestRevThree.SigmaRunQuantity;
//    PartDest.PresetPicName = PartDestRevThree.PresetPicName;
}

void M2010::CopyPartRevTwo(M10PartRevTwo PartDestRevTwo, M10Part PartDest)
{
//    PartDest.RevCode = DEFINEDREVCODE;
//    PartDest.PartNo = PartDestRevTwo.PartNo;
//    PartDest.FlagField = PartDestRevTwo.FlagField;
//    PartDest.Amplitude2 = PartDestRevTwo.Amplitude2;
//    PartDest.EnergyToStep = PartDestRevTwo.EnergyToStep;
//    PartDest.Area = PartDestRevTwo.Area;
//    PartDest.PartsCnt = PartDestRevTwo.PartsCnt;
//    PartDest.TimeToStep = PartDestRevTwo.TimeToStep;
//    PartDest.PowerToStep = PartDestRevTwo.PowerToStep;
//    PartDest.Energy = PartDestRevTwo.Energy;
//    PartDest.Width = PartDestRevTwo.Width;
//    PartDest.Pressure = PartDestRevTwo.Pressure;
//    PartDest.Amplitude = PartDestRevTwo.Amplitude;
//    PartDest.Time = PartDestRevTwo.Time;
//    PartDest.Power = PartDestRevTwo.Power;
//    PartDest.Preheight = PartDestRevTwo.Preheight;
//    PartDest.Height = PartDestRevTwo.Height;
//    PartDest.Force = PartDestRevTwo.Force;
//    PartDest.NoOfWires = PartDestRevTwo.NoOfWires;
//    for(int i = 0; i < MAX_WIRE_ELEMENTS; i++)
//    {
//        PartDest.WireEl[i].PartName = PartDestRevTwo.WireEl[i].PartName;
//        PartDest.WireEl[i].Area = PartDestRevTwo.WireEl[i].Area;
//        for(int j = 0; j < 11; j++)
//        {
//            PartDest.WireEl[i].Color[j] = PartDestRevTwo.WireEl[i].Color[j];
//        }
//        PartDest.WireEl[i].side = PartDestRevTwo.WireEl[i].side;
//    }
//    PartDest.RecData = PartDestRevTwo.RecData;
//    PartDest.TrigPres = PartDestRevTwo.TrigPres;
//    PartDest.SqzTime = PartDestRevTwo.SqzTime;
//    PartDest.FlagWord = PartDestRevTwo.FlagWord;
//    PartDest.StopCount = PartDestRevTwo.StopCount;
//    PartDest.HoldTime = PartDestRevTwo.HoldTime;
//    PartDest.ABDelay = PartDestRevTwo.ABDelay;
//    PartDest.ABDur = PartDestRevTwo.ABDur;
//    PartDest.PreBurst = PartDestRevTwo.PreBurst;
//    PartDest.WidthCorr = PartDestRevTwo.WidthCorr;
//    PartDest.HeightCorr = PartDestRevTwo.HeightCorr;
//    PartDest.ShrinkTubeIndex = PartDestRevTwo.ShrinkTubeIndex;
//    PartDest.ShrinkTime = PartDestRevTwo.ShrinkTime;
//    PartDest.ShrinkTemperature = PartDestRevTwo.ShrinkTemperature;
//    PartDest.PreviousFileNumber = PartDestRevTwo.PreviousFileNumber;
//    PartDest.PresetTeachModeSetting = PartDestRevTwo.PresetTeachModeSetting;
//    for(int i = 0; i < ENERGY_ADJ; i++)
//    {
//        PartDest.TeachModequal_Window[i] = PartDestRevTwo.TeachModequal_Window[i];
//    }
//    PartDest.StandardRunQuantity = PartDestRevTwo.StandardRunQuantity;
//    PartDest.AutoRunQuantity = PartDestRevTwo.AutoRunQuantity;
//    PartDest.SigmaRunQuantity = PartDestRevTwo.SigmaRunQuantity;
//    PartDest.PresetPicName = PartDestRevTwo.PresetPicName;
}
