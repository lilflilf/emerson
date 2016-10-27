#include "M102IA.h"
#include "M10INI.h"
#include "M2010.h"
#include "MDefine.h"
#include "ModRunSetup.h"
#include "BransonSerial.h"
#include "Statistics.h"
#include "ModRunSetup.h"
#include <QCoreApplication>
#include "UtilityClass.h"

M102IA* M102IA::_instance = 0;
M102IA* M102IA::Instance()
{
    if(_instance == 0){
        _instance = new M102IA();
    }
    return _instance;
}

M102IA::M102IA()
{
    RawDataGraph = 0;
}
//Following Private Functions
void M102IA::PackHexRecord()
{
    if(RawDataGraph != 0)
        delete []RawDataGraph;
}

void M102IA::SetHighByte(int ByteNo, unsigned short Data)
{

}

void M102IA::SetLowByte(int ByteNo, unsigned short Data)
{

}

void M102IA::LittleEndianWord(int HighByte, unsigned short Data)
{

}

void M102IA::sndPreset2IA(int PresetNo)
{

}


//Following is the Public Functions
void M102IA::Generate_Beep(int BeepTime)
{
    //Send command to beep on controler side.
    //If BeepTime is zero then it will silence the beep during lock on Alarm.
    SendIACommand(IAComBeep, BeepTime);
}

void M102IA::HexLineCheck(string HexLineData, bool &HexLineCheckOK)
{
//    this function will check for the error of receiving data.
//    If any data lost or corrupted then it will be detected by this function.
    unsigned long DataSum, LengthCheck;
    unsigned int datalength;
    int SumCount;
    int i;
    string strTemp;
    HexLineCheckOK = true;
    if (HexLineData.substr(0,1) != ":")
    {
        HexLineCheckOK = false;
        return;
    }
    SumCount = (HexLineData.length() - 3) / 2;      //Count for sum check (from 0)
    LengthCheck = SumCount - 4;                     //Data count in string
    sscanf(HexLineData.substr(2,2).c_str(), "%x", &datalength);

    if (LengthCheck != datalength)
    {
        HexLineCheckOK = false;
        return;
    }
    DataSum = 0;
    for(i = 0; i < SumCount; i++)
    {
       strTemp = HexLineData.substr(2 * i + 2, 2);
       int tmpInt = 0;
       sscanf(strTemp.c_str(), "%x", &tmpInt);
       DataSum = DataSum + tmpInt;
    }
    if ((DataSum & 0xFF) != 0){
        HexLineCheckOK = false;
        return;
    }
}

void M102IA::HexLineBufferCheck(string InputLine)
{
//    This function is to force a buffer on the incoming data so it can't be overwritten
    static int DataSignature;          //Needs to be almost global in scope
    static bool HexLineCheckOK;        //Same here
    string tmpRecord = InputLine.substr(8, 2);
    if (tmpRecord == "00") //Data record: add to data structure
    {
        if (HexLineCheckOK == true)
        {
            HexLineCheck(InputLine, HexLineCheckOK);
            IAstructure = IAstructure + InputLine;
        }
    }
    else if(tmpRecord == "01")   //End Record
    {
        if (HexLineCheckOK == true)
        {
            HexLineCheck(InputLine, HexLineCheckOK);
            if (HexLineCheckOK == true)
            {
                ParseHexStructure(IAstructure, DataSignature);
            }
        }
    }
    else if ((tmpRecord == "02") ||   //Not used in our system (extended address record)
        (tmpRecord == "03"))   //Header Record, Initialize the data
    {
        IAstructure = "";
        HexLineCheck(InputLine, HexLineCheckOK);
        if (HexLineCheckOK == true){
            string tmpStr = InputLine.substr(12, 2) + InputLine.substr(10, 2);
            sscanf(tmpStr.c_str(), "%x", &DataSignature);
        }
    }
}

int M102IA::MakeHexNibble(int InNumber)
{
    //This function will break the integer to nibbles.
    int Result = -1;
    if ((InNumber < 0) || (InNumber > 15))
    {
       Result = -1;
       return Result;
    }
    if (InNumber < 10)
       Result = '0' + InNumber;
    else
       Result = 'A' + InNumber - 10;
    return Result;
}

string M102IA::MakeHexByte(int InNumber)
{
    string ResultStr = "";
    InNumber = InNumber & 0xFF;
    char InChar[2];
    InChar[0] = MakeHexNibble(InNumber/16);
    InChar[1] = MakeHexNibble(InNumber % 16);
    stringstream Stream;
    Stream << InChar;
    ResultStr = Stream.str();
    return ResultStr;
}

string M102IA::MakeHexWord(int InNumber)
{
    //Returns "little endian" string from number, Caution: Must be less than 0x10000
    //Handles all numbers as unsigned
    string ResultStr = "";
    unsigned short BigFlag, TopByte, BotByte;
    BigFlag = InNumber & 0x8000;     //Check for top bit
    TopByte = (InNumber & 0x7FFF) / 256;
    if (BigFlag != 0) TopByte = TopByte | 0x80;
    BotByte = (InNumber & 0xFF);
    ResultStr = MakeHexByte(BotByte) + MakeHexByte(TopByte);
    return ResultStr;
}

void M102IA::IACommand(IACommands CommandNumber, int SimNo)
{
    //Same as SendIACommand with zero data
    M2010   *ptr_M2010 = M2010::Instance();
    MDefine *ptr_MDefine = MDefine::Instance();
    if ((CommandNumber == IAComHostReady) && (ptr_M2010->M10Run.Alarm_found == true)) return;
    if ((CommandNumber = IAComHostReady) &&
        (ptr_MDefine->FlagModularProduction == true) &&
            (ptr_MDefine->ModularSequenceDone == true)) return;
    if (CommandNumber == IAComHostReady)
         SendCommandData(SimNo);
    else
         SendIACommand(CommandNumber, SimNo);

}

//This function contructs the out put charecter string to be send to controller.
//This will also calculate the checksum and apend the same in right position.
//New Command has also been implemented which sends parameters related to Amplitude Step
void M102IA::SendIACommand(IACommands CommandNumber, int CommandData)
{
    int SumCheck, datalength, InChar;
    unsigned int i, length;
    string strTemp, OutStr;
    MDefine *ptr_MDefine = MDefine::Instance();
    M2010   *ptr_M2010   = M2010  ::Instance();
    M10INI  *ptr_M10INI  = M10INI ::Instance();
    ModRunSetup *ptr_ModRunSetup = ModRunSetup::Instance();
    IACommandError = 0;
    if ((CommandNumber > IAComEnd) || (CommandNumber < 2))
    {
        IACommandError = -1;
        return;
    }
    //If OfflineModeEnabled = True Then Exit Sub
    if ((CommandNumber == IAComSetRunMode) && (CommandData = 0))  EnableAbortButton1 = false;
    if ((CommandNumber = IAComSetRunMode) && (CommandData = 1) &&
            (ptr_MDefine->ModularSequenceDone == true) &&
            (ptr_MDefine->FlagModularProduction == true))
    {
         ptr_M2010->ReceiveFlags.FootPadelDATA = true;
         return;
    }

    int Data[256];
    length = 2;
    switch (CommandNumber)
    {
        case IAComGetRunModeNew:       /* 0x63 */
            length = 0;
            Data[0] = 0;
        break;
        case IAComSetActuator:         /* 0x64 */
             length = 6;
             Data[0] = ptr_M2010->TempActuatorInfo.CurrentActuatorType;
             Data[1] = ptr_M2010->TempActuatorInfo.CurrentActuatorMode;
             Data[2] = ptr_M2010->TempActuatorInfo.CurrentAntisideSpliceTime;
        break;
        case IAComgetActuator:         /* 0x65 */
             length = 0;
             Data[0] = 0;
        break;
        case IAComSetCooling:
            length = 4;
            switch (ptr_M10INI->TempSysConfig.CoolingMode)
            {
                case ENERGYMODE:
                   Data[0] = -1;
                   Data[1] = ptr_M10INI->TempSysConfig.CoolingDel;
                break;
                case OFF:
                   Data[0] = 0;
                   Data[1] = ptr_M10INI->TempSysConfig.CoolingDel;
                break;
                default:
                   Data[0] = ptr_M10INI->TempSysConfig.CoolingDur;
                   Data[1] = ptr_M10INI->TempSysConfig.CoolingDel;
                break;

             }
        break;
        case IAComGetCooling:
             length = 0;
             Data[0] = 0;
        break;
        case IAComGetLockonAlarm:
             length = 0;
             Data[0] = 0;
        break;
        case IAComGetCutoff:
             length = 0;
             Data[0] = 0;
        break;
        case IAComGetMachineFlags:
             length = 2;
             Data[0] = 0;
        break;
        case IAComSetMachineFlags:
             length = 8;
             Data[0] = ptr_M10INI->TempSysConfig.Machineflags[0];
             Data[1] = ptr_M10INI->TempSysConfig.Machineflags[1];
             Data[2] = ptr_M10INI->TempSysConfig.Machineflags[2];
             Data[3] = ptr_M10INI->TempSysConfig.Machineflags[3];
        break;
        case IAAmpStepParameters:
             length = 8;
             Data[0] = IAsetup.Amplitude2;
             Data[1] = IAsetup.EnergyToStep;
             Data[2] = IAsetup.TimeToStep;
             Data[3] = IAsetup.PowerToStep;
        break;
        case IAComCalWidth:
             length = 6;
             Data[0] = CommandData;
             Data[1] = ptr_M2010->Shim1Val;
             Data[2] = ptr_M2010->Shim2Val;
        break;
        case IAComSetMaximumGauge:
             length = 2;
             Data[0] = (int)ptr_M10INI->StatusData.CalHightMaximumGauge;
        break;
        default:
            length = 2;
            Data[0] = CommandData;
        break;
    }


    //Construct a string from command information
    OutStr = ":";
    OutStr = OutStr + MakeHexWord(length);
    OutStr = OutStr + MakeHexByte(CommandNumber);
    OutStr = OutStr + "0B";

    for (datalength = 1; i <= (length / 2); i++)
        OutStr = OutStr + MakeHexWord(Data[datalength - 1]);


    for (i = 0; i < (OutStr.length() / 2); i++)
    {
          strTemp = OutStr.substr(2 * i + 2, 2);
          sscanf(strTemp.c_str(),"%x",&InChar);
          SumCheck = SumCheck + InChar;
    }
    SumCheck = (0 - SumCheck) & 0xFF;
    OutStr = OutStr + MakeHexByte(SumCheck) + "\n";

    #ifdef IA98System
        BransonSerial::comIA98->write(OutStr.c_str(), OutStr.length());
        BransonSerial::comIA98->waitForBytesWritten(-1);
    #else
        if (ptr_ModRunSetup->OfflineModeEnabled == false)
        {
            BransonSerial::comIAport->write(OutStr.c_str(), OutStr.length());
            BransonSerial::comIAport->waitForBytesWritten(-1);
            char Command = 0x11;
            BransonSerial::comIAport->write(&Command,1);
            BransonSerial::comIAport->waitForBytesWritten(-1);
        }
    #endif
}

bool M102IA::WaitForResponseAfterSent(int TimeOut, bool *CheckResponseFlag)
{
    BransonSerial *ptr_Serial = BransonSerial::Instance();
    ModRunSetup *ptr_ModRunSetup = ModRunSetup::Instance();
    ptr_Serial->SetCommandTimer(TimeOut);
    while ((*CheckResponseFlag == false) || (ptr_Serial->IsCommandTimeout() == false))
    {
        QCoreApplication::processEvents(); // Wait for response
        if ((ptr_ModRunSetup->OfflineModeEnabled == true) || (ptr_Serial->IsCommandTimeout() == false))
            break;
    };
    ptr_Serial->ResetCommandTimer();
    return *CheckResponseFlag;
}

int M102IA::MakeHexNibbleNumber(char HexNibble)
{
    int Result = 0;
    if((HexNibble >= '0') && (HexNibble <= '9'))
        Result = HexNibble - '0';
    else if ((HexNibble >= 'A') && (HexNibble <= 'F'))
        Result = 10 + HexNibble - 'A';
    else
        Result = 0;
    return Result;
}

int M102IA::MakeHexByteNumber(string HexByte)
{
    int Result = 0;
    Result = 16 * MakeHexNibbleNumber(HexByte[0]) +
            MakeHexNibbleNumber(HexByte[1]);
    return Result;
}

int M102IA::MakeHexWordNumber(string HexWord)
{
    //Makes the first four hex characters into number (input is little endian)
    int temp1, IntReturn;
    temp1 = MakeHexByteNumber(HexWord.substr(0, 2)) +
            256 * MakeHexByteNumber(HexWord.substr(2, 2));
    temp1 = temp1 & 0xFFFF;
    if ((temp1 & 0x8000) != 0)
    {
        temp1 = (temp1 & 0x7FFF);
        IntReturn = temp1;
        IntReturn = IntReturn | 0x8000;
    }
    else
        IntReturn = temp1;
    return IntReturn;
}

long M102IA::MakeHexWordNumberLong(string HexWord)
{
    //Make the first eight characters into a signed long number.
    //Little Endian "67452301" = 0x01234567
    long LSBs, MSBs, Result;

    //Collect Least Significant Bytes
    LSBs = MakeHexByteNumber(HexWord.substr(0,2)) + 0x100 * MakeHexByteNumber(HexWord.substr(2,2));
    //Collect Most Significant Bytes
    MSBs = MakeHexByteNumber(HexWord.substr(4,2)) + 0x100 * MakeHexByteNumber(HexWord.substr(6,2));
    //Test for negative numbers
    if ((MSBs & 0x8000) != 0) // Number is negative
    {
          MSBs = (MSBs & 0x7FFF); //Remove sign bit
          Result = (MSBs * 0x10000) + LSBs; //shift and add
          Result = (Result | 0x80000000);  //Replace sign bit
    }
    else // Number is positive
          Result = (MSBs * 0x10000) + LSBs; //shift and add
    return Result;
}

void M102IA::MakeMemoryString(string InputHexString, string &OutputHexString)
{
    //Parses an Intel hex string into memory data by removing overhead data
    //Output is all data, packed as it was sent
    int ByteCount, Position;

    Position = 1;    //Should be the first colon
    OutputHexString = "";

    while (Position > 0)
    {
        //Pack OutputHexString with data bytes:
//        ByteCount = CLng("&h" & Mid(InputHexString, Position + 1, 2))
        sscanf(InputHexString.substr(Position + 1, 2).c_str(),"%x",&ByteCount);
        OutputHexString = OutputHexString +
            InputHexString.substr(Position + 9, 2 * ByteCount);
        Position = InputHexString.find(':');
//        Position = InStr(Position + 1, InputHexString, ":", vbTextCompare)
    };
}

void M102IA::GetCstringFromHex(string InputString, string &OutputString,
                               int Start, int CharCount)
{
    //Caution: CharCount is the number of output characters, input counter is double
    //Input string is a memory hex string not an Intel hex string (contiguous bytes)
    long i; int NewChar;
    OutputString = "";
    stringstream ss;
    for (i = Start; i <(Start + 2 * CharCount); i+=2)
    {
        sscanf(InputString.substr(i,2).c_str(), "%x", &NewChar);
        if (NewChar == 0) break;
        ss << NewChar;
        OutputString = OutputString + ss.str();
    }
}

long M102IA::GetLongValue(string InputString, int Ref)
{
   return MakeHexWordNumberLong(InputString.substr(Ref, 8));
}

//Retrieves data from the input strings sent by the controller.
//Depending on the DataSignature respective values are extracted from the received HexString.
//Amplitude2 value required for Amplitude Stepping is also added
int M102IA::ParseHexStructure(string HexString, int DataSignature)
{
    M10INI *ptr_M10INI   = M10INI::Instance();
    M2010  *ptr_M2010    = M2010 ::Instance();
    MDefine *ptr_MDefine = MDefine::Instance();
    Statistics *ptr_Statistics = Statistics::Instance();
    ModRunSetup *ptr_ModRunSetup = ModRunSetup::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    const string Colon = ":";

    int i;
    int Index, temp, Div;
    string TempString = "";
    string PowerString;
    ptr_M10INI->GlobalSignature = DataSignature;
    switch(DataSignature)
    {
    case IASigSetup:
    case IASigPresetTable:
    case IASigPresetData:   //"14"
    case IASigWeld:
        //Last Weld Data - Data Signature = "03"
        //Need a Variable to put the Peak Power Value together.

        //A sample weld data structure as sent by IA after a weld is complete
        //   :02 0000 03 0300 F8 Header
        //                   25                          41             49
        //                      Reserved Data         En    Wd   Time PP Pp
        //   :10 9968 00 601700007E170000 C201 1701 8400 3A 66 E7
        //                      68           74    78                       90
        //                      Pp PreH Ampl WldH Resv PPHt Forc AlFg
        //   :0F 9978 00 03 OD01 2500 D300 FAFF 0D01 7301 0000 5C
        //   :01 0000 01 00 FE
        //--First data record
        IAactual.Energy = MakeHexWordNumber(HexString.substr(25, 4));
        IAactual.Width = MakeHexWordNumber(HexString.substr(29, 4)); //+ Splice.WidthCorr
        IAactual.Time = MakeHexWordNumber(HexString.substr(34, 4));
        // This Time value has been divided by 5 in firmware, so we only need to divided it by 2 again.
        // So, this time value is able to reduced 10 times.
        IAactual.Time = IAactual.Time / 2;
        //--Need to piece a together to parts here because of Jim's string
        TempString = HexString.substr(39, 2) + HexString.substr(52, 2);
        IAactual.Power = MakeHexWordNumber(TempString);
        //--Need to use the raw peakpower to do calculation
        Div = (ptr_M10INI->StatusData.Soft_Settings.SonicGenWatts / 200);
        IAactual.Power = MakeHexByteNumber(HexString.substr(37, 2));
        if (ptr_M10INI->StatusData.Soft_Settings.SonicGenWatts > 200)
           IAactual.Power = IAactual.Power * Div;
        else
           IAactual.Power = IAactual.Power * (ptr_M10INI->StatusData.Soft_Settings.SonicGenWatts / 200);
        //--Second data record
        IAactual.Preheight = MakeHexWordNumber(HexString.substr(54, 4));
        IAactual.Amplitude = MakeHexWordNumber(HexString.substr(58, 4));
        IAactual.Height = MakeHexWordNumber(HexString.substr(62, 4)); //+ Splice.HeightCorr
        IAactual.Amplitude2 = MakeHexWordNumber(HexString.substr(66, 4));
        IAactual.PPHeight = MakeHexWordNumber(HexString.substr(70, 4));
        IAactual.Force = MakeHexWordNumber(HexString.substr(74, 4));
        //IAactual.Alarmflags = MakeHexWordNumber(HexString.substr(78, 4));
        IAactual.Alarmflags = MakeHexWordNumberLong(HexString.substr(78, 8));
        //--Set Correct Flag
        ptr_M2010->ReceiveFlags.WELDdata = true;
        if (ptr_M2010->Child_Mode == Graph_SCREEN)
        {
           //Actual Procedure to plot the weld data
//           frmGraph.GraphOutline
//           frmGraph.DisplayWeldData
        }
        if (ptr_MDefine->WriteHistoryFlag == true)
        {
           ptr_Statistics->HistoryEvent();
           ptr_MDefine->WriteHistoryFlag = false;
        }
//        get_weld
        break;
    case IASigPower:           //Data Signature = "04"
        //Data is in an unknown number of strings, all but last is 16 Bytes of data
        //  (length = 43 Characters)
        int StringLen, StringCount, LastString, StartData;
        int num, Total, tmpIndex, Datalen;
        StringLen = HexString.length();
        StringCount = int(StringLen / 51);
        LastString = StringLen % 51;
        PowerString = "";
        StartData = 18;      //First data character
        tmpIndex = 0;
        Total = MakeHexWordNumber(HexString.substr((tmpIndex + 10), 4));
        RawDataGraph = new string[Total];
        for (i = 0; i < StringCount; i++)
        {
 //            PowerString = PowerString & Mid(HexString, StartData, 32)
 //            StartData = StartData + 51
            Total = MakeHexWordNumber(HexString.substr((tmpIndex + 10), 4));
            num = MakeHexWordNumber(HexString.substr(tmpIndex + 14, 4));
            RawDataGraph[num] = HexString.substr(tmpIndex + 1, 51);
            tmpIndex = tmpIndex + 51;
        }

        if (LastString > 0)
        {
            //Take off the overhead and tack the string onto the Power String
            //PowerString = PowerString & Mid(HexString, StartData, LastString - 19)
            Total = MakeHexWordNumber(HexString.substr((tmpIndex + 10), 4));
            num = MakeHexWordNumber(HexString.substr(tmpIndex + 14, 4));
            Datalen = MakeHexByteNumber(HexString.substr(tmpIndex + 2, 4));
            RawDataGraph[num] = HexString.substr(tmpIndex + 1, LastString);
            if ((Datalen - 4) != ((LastString - 19) / 2)) num = num - 1;
        }
        if ((num = (Total - 1)) || (ptr_M10INI->StatusData.KeepDailyHistory == false))
        {
            for (i = 0; i < StringCount;i++)
                PowerString = PowerString + RawDataGraph[i].substr(StartData, 32);
            PowerString = PowerString + RawDataGraph[i].substr(StartData, (RawDataGraph[i].length() - 19));
        }
        else
        {
//             If dlgMsgScreen.DataGraphComplete = True Then
//                 dlgMsgScreen.DataGraphComplete = False
//                 dlgMsgScreen.DataGraphIndex = num
//                 dlgMsgScreen.lblMsg = GetResString(892) & "......"
//                 dlgMsgScreen.Show vbModeless, Screen.ActiveForm
//             End If
            return 0;
        }
//        If dlgMsgScreen.DataGraphComplete = False Then dlgMsgScreen.DataGraphComplete = True
        ptr_M2010->ConvertGraphData(PowerString);
        ptr_M2010->ReceiveFlags.PowerData = true;
        ptr_M10INI->PowerDataReady = true;
        break;
    case IASigSerialNumber:
        SerialNoData = ptr_M2010->ParseSerialNumber(HexString.substr(10, 32));
        ptr_M2010->ReceiveFlags.SNdata = true;
        break;
    case IASigHeightCal:
        HeightCalResult = MakeHexWordNumber(HexString.substr(10, 4));
        if (HeightCalResult == 1)
        {
            DownSpeed = MakeHexWordNumber(HexString.substr(14, 4));
//            dlgCalibHeight.UniLabel6.Caption = GetResString(1106) & " = " & Format(DownSpeed / 100, "0.00 mm/sec")
        }
        if (HeightCalResult != 1)  ptr_M2010->ReceiveFlags.CalibrationDone = true;
        break;
    case IASigIO:
        //--IO Data - Data Signature = "06"
        //--I/O Data includes Line Voltage, Ac Tap Min/Max Setting & Adjusted & Absolute Height
        //--A sample IOData structure as sent by IA.
        //                     Data Signal
        //   :02 0000 03 0600 F5 Header
        //                         I/O         AdjHt AbsHt ACV  AcTp AcMx AcMn
        //                         25           29    33    37   41   45   49
        //   :0E 99BB 00 C7 40 0B 00 00 00 03   00 7C 00 78 00 8A 00 66 00 A5
        //   :01 0000 01 00 FE
        IOstatus.IO = MakeHexWordNumberLong(HexString.substr(10, 8));
        IOstatus.AdjHeight = MakeHexWordNumber(HexString.substr(18, 4));
        IOstatus.AbsHeight = MakeHexWordNumber(HexString.substr(22, 4));
        IOstatus.ACV = MakeHexWordNumber(HexString.substr(26, 4));
        IOstatus.ACTap = MakeHexWordNumber(HexString.substr(30, 4));
        IOstatus.ACmax = MakeHexWordNumber(HexString.substr(34, 4));
        IOstatus.ACmin = MakeHexWordNumber(HexString.substr(38, 4));

        //--Adjust data fields that are part of another command
        HEIGHTbuffer[0] = IOstatus.AdjHeight;
        HEIGHTbuffer[1] = IOstatus.AbsHeight;
        //--Set Correct Flag
        ptr_M2010->ReceiveFlags.IOdata = true;
        break;
    case IASigSonicHits:
        SonicHitsStrData[3] = HexString.substr(10, 2);
        SonicHitsStrData[2] = HexString.substr(12, 2);
        SonicHitsStrData[1] = HexString.substr(14, 2);
        SonicHitsStrData[0] = HexString.substr(16, 2);
        SonicHitsData = "";
        for (i = 0; i< 4; i++)
            SonicHitsData = SonicHitsData + SonicHitsStrData[i];
        ptr_M2010->ReceiveFlags.SonicHitsData = true;
        break;
    case IASigPressure:
        PressureRead = MakeHexWordNumber(HexString.substr(10, 4));
        ptr_M2010->ReceiveFlags.PressureData = true;
        break;
    case IASigIOswitch:
        //--FootSwitch IO data - Data Signature = "09"
        LastIOSwitchData.IO = MakeHexWordNumberLong(HexString.substr(10, 8));
        //LastIOSwitchData.WordData = MakeHexWordNumber(Mid(HexString, 25, 4))
        IOstatus.IO = LastIOSwitchData.IO;
//        LastIOstatus.IO = CLng(LastIOSwitchData.WordData)
        ptr_M2010->ReceiveFlags.IOSWITCHdata = true;
//        CheckIAControl
        break;
    case IASigAbortEnable:
        temp = MakeHexWordNumber(HexString.substr(10, 4));
        if (temp == 1)
            EnableAbortButton1 = true;
        else
            EnableAbortButton1 = false;
        ptr_M2010->ReceiveFlags.HeightData = true;
        break;
//    case IASigWeldHistory      //"0A"
    case IASigHistoryPar:        //"0B"
    case IASigMemory:            //"0C"
    case IASigHeight:            //"0D"
        CalibHeight = MakeHexWordNumber(HexString.substr(10, 4));
        RawHeight = MakeHexWordNumber(HexString.substr(14, 4));
        OpenChkHeight = MakeHexWordNumber(HexString.substr(18, 4));
        ptr_M2010->ReceiveFlags.HeightData = true;
        break;
    case IASigWidth:             //"0E"
        //--Remmember the WIDTHbuffer(0) = the Actual Width & WIDTHbuffer(1) = the Absolute Width
        //--You need to be careful when you check the Actual Width Number because,
        //--if the IA sends a value greater than 128 then the IA set the Width just a hair under Zero 7 goes to 1mm
        //--Width Motor Error
        //         If Val("&H" + Mid(HexString, 10, 2)) >= 128 Then
        //            WIDTHbuffer(0) = -1
        //        Else
        //            WIDTHbuffer(0) = MakeHexWordNumber(Mid(HexString, 10, 4))
        //        End If
        WIDTHbuffer[0] = MakeHexWordNumber(HexString.substr(10, 4));
        WIDTHbuffer[1] = MakeHexWordNumber(HexString.substr(14, 4));
        ptr_M2010->ReceiveFlags.WIDTHdata = true;
        break;
    case IASigPWRrating:         //"0F"
        ptr_M10INI->StatusData.Soft_Settings.SonicGenWatts =
                MakeHexWordNumber(HexString.substr(10, 4));
        _Utility->Maxpower = int(1.2 * ptr_M10INI->StatusData.Soft_Settings.SonicGenWatts);
        for (Index = 0; Index <= 6; Index++)
        {
             ptr_M10INI->Pwr_Prefix_Data[Index] = Index *
                     int(0.2 * ptr_M10INI->StatusData.Soft_Settings.SonicGenWatts);
        }
//        With Splice
//        SetTextData DINPowerPl, .power.Plus, .RecData.power.Plus, MINPOWER, _
//        CLng(Maxpower), 100, 1, "0W"
//        SetTextData DINPowerMs, .power.Minus, .RecData.power.Minus, MINPOWER, _
//        CLng(StatusData.Soft_Settings.SonicGenWatts), 100, 1, "0W"
//        End With
        ptr_M2010->ReceiveFlags.POWERrating = true;
        break;
    case IASigSequenceTable:     // Data Signature = "10"
    case IASigHornAmplitude:
//        --Calibrated Horn Amp. Value - Data Signature = "11"
        ptr_M10INI->StatusData.Soft_Settings.Horn_Calibrate = MakeHexWordNumber(HexString.substr(10, 4));
        ptr_M2010->ReceiveFlags.HORNamplitude = true;
        break;
    case IASigSystemID:          //"12"
        //tempStatusData.MachineType = MakeHexWordNumber(Mid(HexString, 10, 4))
        //tempStatusData.MachineDate = ParseSerialNumber(Mid(HexString, 14, 12))
        ptr_M2010->ReceiveFlags.SYSTEMid = true;
        break;
    case IASigMaintCount:        //"13"
    case IASigActuator:
        ptr_M10INI->StatusData.MachineType = MakeHexWordNumber(HexString.substr(10, 4));
        ptr_M10INI->StatusData.ActuatorMode = MakeHexWordNumber(HexString.substr(14, 4));
        ptr_M10INI->StatusData.AntisideSpliceTime = MakeHexWordNumber(HexString.substr(18, 4));
        switch (ptr_M10INI->StatusData.MachineType)
        {
            case ACTULTRA20:
            case ACTULTRA40:
            case ACTMTS20:
            case ACTGUN40:
                ptr_M2010->Machine = Welder;
            break;
            default:
            ptr_M2010->Machine = WireSplicer;
            break;
        }
        break;
    case IASigWidthZero:
        ptr_ModRunSetup->tempWidthOffsetVal = MakeHexWordNumber(HexString.substr(10, 4));
        ptr_M2010->ReceiveFlags.CalibrationDone = true;
        break;
    case IAsigCooling:
        ptr_M10INI->StatusData.CurrentCoolingDur = MakeHexWordNumber(HexString.substr(10, 4));
        ptr_M10INI->StatusData.CurrentCoolingDel = MakeHexWordNumber(HexString.substr(14, 4));
        break;
    case IASigHeightZero:
        ptr_ModRunSetup->tempHeightOffsetval = MakeHexWordNumber(HexString.substr(10, 4));
        break;
    case IASigDataLockOnAlarm:
         ptr_M10INI->StatusData.LockonAlarm = MakeHexWordNumber(HexString.substr(10, 4));
        break;
    case IASigRunMode:
        ptr_M10INI->StatusData.RunMode = MakeHexWordNumber(HexString.substr(10, 4));
        ptr_M2010->ReceiveFlags.FootPadelDATA = true;
        break;
    case IASigMachineFlags:
        ptr_M10INI->StatusData.Machineflags[0] = MakeHexWordNumber(HexString.substr(10, 4));
        ptr_M10INI->StatusData.Machineflags[1] = MakeHexWordNumber(HexString.substr(14, 4));
        ptr_M10INI->StatusData.Machineflags[2] = MakeHexWordNumber(HexString.substr(18, 4));
        ptr_M10INI->StatusData.Machineflags[3] = MakeHexWordNumber(HexString.substr(22, 4));
        break;
    case IASigDataMaintCntr:
        ptr_M10INI->StatusData.currentMaintenanceLimits[0] = GetLongValue(HexString, 10);
        ptr_M10INI->StatusData.currentMaintenanceLimits[1] = GetLongValue(HexString, 18);
        ptr_M10INI->StatusData.currentMaintenanceLimits[2] = GetLongValue(HexString, 26);
        ptr_M10INI->StatusData.currentMaintenanceLimits[3] = GetLongValue(HexString, 34);

        ptr_M10INI->StatusData.currentMaintenanceLimits[4] = GetLongValue(HexString, 42);
        ptr_M10INI->StatusData.currentMaintenanceLimits[5] = GetLongValue(HexString, 50);
        ptr_M10INI->StatusData.currentMaintenanceLimits[6] = GetLongValue(HexString, 58);
        ptr_M10INI->StatusData.currentMaintenanceLimits[7] = GetLongValue(HexString, 66);
        ptr_M2010->ReceiveFlags.MAINTENANCEcounters = true;
//        Save_StatusData False
        break;
    case IASigDataCycleCntr:
        ptr_M10INI->StatusData.CycleCount = GetLongValue(HexString, 10);
//        Save_StatusData False
        break;
    case IASigReadPower:
        ADPower = MakeHexWordNumber(HexString.substr(10, 4));
        break;
    case IASigControllerVer:
        ContollerVersion = ptr_M2010->ParseSerialNumber(HexString.substr(10, 32));
        ptr_M2010->ReceiveFlags.ControllerVersionData = true;
        break;
    case IASigDATADOUBLECLICK:
//        DoubleClickHandler
        break;
    case IASigDownSpeed:
        DownSpeed = MakeHexWordNumber(HexString.substr(10, 4));
//         If (DownSpeed < 10) Then
//            dlgCalibHeight.UniLabel6.Caption = GetResString(1998)
//         Else
//           dlgCalibHeight.UniLabel6.Caption = GetResString(1106) & " = " & Format(DownSpeed / 100, "0.00 mm/sec")
//         End If
        break;
    case IASigMaximumGauge:
        CalibHeightMaxGauge = MakeHexWordNumber(HexString.substr(10, 4));
        ptr_M10INI->StatusData.CalHightMaximumGauge = CalibHeightMaxGauge;
        ptr_M2010->ReceiveFlags.CalHeightMaxGaugeData = true;
        break;
    case IASigHostReadyStatus:
        ptr_M2010->ReceiveFlags.HostReadyData = true;
        break;
    case IASigTunePoint:
        ptr_M10INI->StatusData.Soft_Settings.TunePoint = MakeHexWordNumber(HexString.substr(10, 4));
        break;
    case IASigCutoff:
        ptr_M10INI->StatusData.CutoffMode = MakeHexWordNumber(HexString.substr(10, 4));
        break;
    case IASigFrequencyOffset:
         ptr_M10INI->StatusData.Soft_Settings.FrequencyOffset = MakeHexWordNumber(HexString.substr(10, 4));
        break;
    case IASigActuatorVer:
        ActuatorVersion = ptr_M2010->ParseSerialNumber(HexString.substr(10, 32));
        ptr_M2010->ReceiveFlags.ActuatorVersionData = true;
        break;
    case IASigActuatorPartNum:
        ActuatorPartNum = ptr_M2010->ParseSerialNumber(HexString.substr(10, 32));
        ptr_M2010->ReceiveFlags.ActuatorPartNumData = true;
        break;
    case IASigActuatorSerialNum:
        ActuatorSerialNum = ptr_M2010->ParseSerialNumber(HexString.substr(10, 64));
        break;
    default:
        break;
    }
    return 0;
}

void M102IA::SendCommandData(int CommandData)
{
    int Time, Retries;
    M2010 *ptr_M2010 = M2010::Instance();
    ModRunSetup *ptr_ModRunSetup = ModRunSetup::Instance();
    BransonSerial *ptr_Serial    = BransonSerial::Instance();
    Retries = 0;
    Time = 500;
    //SendCommandSetRunMode CommandData
    ptr_M2010->ReceiveFlags.HostReadyData = false;
    SendIACommand(IAComHostReady, CommandData);
    if (CommandData == 1) return;
    ptr_Serial->SetCommandTimer(Time);
    while (ptr_M2010->ReceiveFlags.HostReadyData == false)
    {
//        DoEvents ' Wait for response
        QCoreApplication::processEvents();
        if (ptr_ModRunSetup->OfflineModeEnabled == true) break;
        if ((ptr_Serial->IsCommandTimeout() == true) && (Retries < 20))
        {
            SendIACommand(IAComHostReady, CommandData);
            ptr_Serial->SetCommandTimer(Time);
            Retries = Retries + 1;
        }
        else if (Retries >= 19)
            break;
     }
    ptr_Serial->ResetCommandTimer();
    if (Retries >= 19)
    {
//        MsgBox "Can't get Response from controller!"
    }
}
