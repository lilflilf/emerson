#include "M102IA.h"
#include "M10INI.h"
#include "M2010.h"
#include "MDefine.h"
#include "ModRunSetup.h"
#include "BransonSerial.h"
#include "Statistics.h"
#include "M10runMode.h"
#include "UtilityClass.h"
#include "TimerClass.h"
#include "AlarmMessage.h"
#include "Interface/Interface.h"
#include "Interface/MakeWeld//MakeWeldProcess.h"
#include <QCoreApplication>
#include <QDebug>

M102IA* M102IA::_instance = NULL;
M102IA* M102IA::Instance()
{
    if(_instance == 0){
        _instance = new M102IA();
    }
    return _instance;
}

M102IA::M102IA(QObject *parent)
    :QObject(parent)
{
    CalibHeight = 0;
    OpenChkHeight = 0;
    RawHeight = 0;
    DownSpeed = 0;
    CalibHeightMaxGauge = 0;
    EnableAbortButton1 = false;
    RawPowerDataGraph.GraphDataList.clear();
    RawHeightDataGraph.GraphDataList.clear();
    ActDone = No_Axn;
    ErrorFound = false;
    IACommandError = -1;

    IAsetup.ModeFlags = 0;
    IAsetup.Energy = 100;
    IAsetup.Width = 100;
    IAsetup.WeldPressure = 200;
    IAsetup.TriggerPressure = 200;
    IAsetup.Amplitude = 18;
    IAsetup.SqueezeTime = 0;
    IAsetup.Time.max = 1000;
    IAsetup.Time.min = 0;
    IAsetup.Power.max = 4800;
    IAsetup.Power.min = 0;
    IAsetup.Preheight.max = 1500;
    IAsetup.Preheight.min = 0;
    IAsetup.Height.max = 1500;
    IAsetup.Height.min = 0;
    IAsetup.PartCounter = 0;
    IAsetup.StopCount = 0;
    IAsetup.HoldTime = 0;
    IAsetup.ABDelay = 0;
    IAsetup.ABDuration = 0;
    IAsetup.Amplitude2 = 0;
    IAsetup.PartName.clear();
    IAsetup.EnergyToStep = 0;
    IAsetup.TimeToStep = -0;
    IAsetup.PowerToStep = 0;

    IAactual.Reserved.clear();
    IAactual.Energy = -1;
    IAactual.Width = 100;
    IAactual.Time = -1;
    IAactual.PeakPowerPer.clear();
    IAactual.Power = -1;
    IAactual.Preheight = -1;
    IAactual.Amplitude = -1;
    IAactual.Height = -1;
    IAactual.Amplitude2 = -1;
    IAactual.PPHeight = -1;
    IAactual.Pressure = -1;
    IAactual.TPressure = -1;
    IAactual.Alarmflags = 0;

    PWRpoints = 0;
    SerialNoData.clear();
    HeightCalResult = -1;
    ContollerVersion.clear();
    ActuatorVersion.clear();
    ActuatorPartNum.clear();
    ActuatorSerialNum.clear();

    IOstatus.IO = 0;
    IOstatus.IO2 = 0;
    IOstatus.AdjHeight = -1;
    IOstatus.AbsHeight = -1;
    IOstatus.ACV = -1;
    IOstatus.ACTap = -1;
    IOstatus.ACmax = -1;
    IOstatus.ACmin = -1;

    LastIOstatus.IO = 0;
    LastIOstatus.IO2 = 0;
    LastIOstatus.AdjHeight = -1;
    LastIOstatus.AbsHeight = -1;
    LastIOstatus.ACV = -1;
    LastIOstatus.ACTap = -1;
    LastIOstatus.ACmax = -1;
    LastIOstatus.ACmin = -1;

    LASTIOSWITCHS LastIOSwitchData;
    for(int i = 0; i< 2; i++)
        LastIOSwitchData.ByteData[i].clear();
    LastIOSwitchData.WordData = -1;
    LastIOSwitchData.IO = 0;
    LastIOSwitchData.IO2 = 0;

    for(int i = 0; i< 3; i++)
        HEIGHTbuffer[i] = -1;

    for(int i = 0; i < 2; i++)
        WIDTHbuffer[i] = -1;

    PressureRead = -1;

    for(int i = 0; i< 4; i++)
        SonicHitsStrData[i].clear();
    SonicHitsData.clear();

    MaintenanceCounter = 0;
    MaintenanceDueCounter = 0;
    EnergyAccumulator = 0;
    EnergyMaintenanceDue = 0;
    ADPower = -1;

    IAdataSignature.clear();

    HexLine.clear();
    IAstructure.clear();

    OutStructure.clear();

    hexRecord.Count = 0;                 //     First byte
    hexRecord.Address = 0;              //     2 bytes, big endian address
    hexRecord.RecordType = -1;            //     1 byte
    memset(hexRecord.ByteData,0,sizeof(hexRecord.ByteData));          //     0 to 32 bytes as data
    hexRecord.CheckSum = 0;
}

//Following Private Functions
//Sends data stored in hexRecord to the IA
void M102IA::PackHexRecord()
{
    int i = 0;
    QString SendStr;
    unsigned char Abyte;
    hexRecord.Count = 0;
    for(i = 0; i < 16; i++)
    {
        if(hexRecord.ByteData[i] != -1)
            hexRecord.Count++;
        else
            break;
    }
    SendStr = ":";
    SendStr += MakeHexByte(hexRecord.Count);

    hexRecord.CheckSum = hexRecord.Count;
    //High part of address
    //Caution: Vbasic is doing something that requires these operations
    Abyte = (unsigned char)(hexRecord.Address >> 8);
    hexRecord.CheckSum += Abyte;
    SendStr += MakeHexByte(Abyte);
    //Low part of address
    Abyte = (unsigned char)(hexRecord.Address & 0x00ff);
    hexRecord.CheckSum += Abyte;
    SendStr += MakeHexByte(Abyte);

    hexRecord.CheckSum += hexRecord.RecordType;
    SendStr += MakeHexByte(hexRecord.RecordType);
    for (i = 0; i< hexRecord.Count; i++)
    {
        hexRecord.CheckSum += hexRecord.ByteData[i];
        SendStr += MakeHexByte(hexRecord.ByteData[i]);
    }
    hexRecord.CheckSum = (0 - hexRecord.CheckSum) & 0xFF;
    SendStr += MakeHexByte(hexRecord.CheckSum);
    OutStructure += (SendStr + "\r");
}

void M102IA::SetHighByte(int ByteNo, unsigned short Data)
{
    //Set a byte in the hex record to the high part of Data
    hexRecord.ByteData[ByteNo] = (Data >> 8) & 0xff;
}

void M102IA::SetLowByte(int ByteNo, unsigned short Data)
{
    //Set a byte in the hex record to the low part of Data
    hexRecord.ByteData[ByteNo] = Data & 0xff;
}

void M102IA::LittleEndianWord(int HighByte, unsigned short Data)
{
    //Set a short of data into the hex structure
    SetLowByte(HighByte, Data);
    SetHighByte(HighByte + 1, Data);
}

//Following is the Public Functions
void M102IA::Generate_Beep(int BeepTime)
{
    //Send command to beep on controler side.
    //If BeepTime is zero then it will silence the beep during lock on Alarm.
    SendIACommand(IAComBeep, BeepTime);
}

void M102IA::HexLineCheck(QString HexLineData, bool &HexLineFlag)
{
//    this function will check for the error of receiving data.
//    If any data lost or corrupted then it will be detected by this function.
    unsigned long DataSum, LengthCheck;
    unsigned int datalength;
    int SumCount;
    int i;
    QString strTemp;
    HexLineFlag = true;
    if (HexLineData.left(1) != ":")
    {
        HexLineFlag = false;
        return;
    }
    SumCount = (HexLineData.length() - 3) / 2;      //Count for sum check (from 0)
    LengthCheck = SumCount - 4;                     //Data count in string
    bool bResult;
    datalength = HexLineData.mid(1,2).toInt(&bResult, 16);

    if (LengthCheck != datalength)
    {
        HexLineFlag = false;
        return;
    }
    DataSum = 0;
    for(i = 0; i <= SumCount; i++)
    {
       strTemp = HexLineData.mid(2 * i + 1, 2);
       DataSum = DataSum + strTemp.toInt(&bResult, 16);
    }
    if ((DataSum & 0xFF) != 0){
        HexLineFlag = false;
        return;
    }
}

void M102IA::HexLineBufferCheck(QString InputLine)
{
//    This function is to force a buffer on the incoming data so it can't be overwritten
    static int DataSignature;          //Needs to be almost global in scope
    static bool HexLineCheckOK;        //Same here
    QString tmpRecord = InputLine.mid(7, 2);
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
        IAstructure.clear();
        HexLineCheck(InputLine, HexLineCheckOK);
        if (HexLineCheckOK == true){
            QString tmpStr = InputLine.mid(11, 2) + InputLine.mid(9, 2);
            bool bResult;
            DataSignature = tmpStr.toInt(&bResult,16);
        }
    }
}

char M102IA::MakeHexNibble(int InNumber)
{
    //This function will break the integer to nibbles.
    char Result = -1;
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

QString M102IA::MakeHexByte(unsigned char InNumber)
{
    InNumber = InNumber & 0xFF;
    QByteArray Buffer(2, 0);
    Buffer.insert(0, MakeHexNibble(InNumber/16));
    Buffer.insert(1, MakeHexNibble(InNumber % 16));
    return Buffer.data();
}

QString M102IA::MakeHexWord(int InNumber)
{
    //Returns "little endian" string from number, Caution: Must be less than 0x10000
    //Handles all numbers as unsigned
    QString ResultStr = "";
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
    M2010   *_M2010 = M2010::Instance();
    MDefine *_MDefine = MDefine::Instance();
    if ((CommandNumber == IAComHostReady) && (_M2010->M10Run.Alarm_found == true)) return;
    if ((CommandNumber == IAComHostReady) &&
        (_MDefine->FlagModularProduction == true) &&
            (_MDefine->ModularSequenceDone == true)) return;
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
    int SumCheck = 0;
    int datalength = 0;
    int i = 0;
    int length = 0;
    QString strTemp, OutStr;
    MDefine *_MDefine = MDefine::Instance();
    M2010   *_M2010   = M2010  ::Instance();
    M10INI  *_M10INI  = M10INI ::Instance();
    ModRunSetup *_ModRunSetup = ModRunSetup::Instance();
    IACommandError = 0;
    if ((CommandNumber > IAComEnd) || (CommandNumber < 2))
    {
        IACommandError = -1;
        return;
    }
    if ((CommandNumber == IAComSetRunMode) && (CommandData == 0))
        EnableAbortButton1 = false;
    if ((CommandNumber == IAComSetRunMode) && (CommandData == 1) &&
            (_MDefine->ModularSequenceDone == true) &&
            (_MDefine->FlagModularProduction == true))
    {
         _M2010->ReceiveFlags.FootPadelDATA = true;
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
             Data[0] = _M2010->TempActuatorInfo.CurrentActuatorType;
             Data[1] = _M2010->TempActuatorInfo.CurrentActuatorMode;
             Data[2] = _M2010->TempActuatorInfo.CurrentAntisideSpliceTime;
        break;
        case IAComgetActuator:         /* 0x65 */
             length = 0;
             Data[0] = 0;
        break;
        case IAComSetCooling:
            length = 6;
            switch (_M10INI->TempSysConfig.CoolingMode)
            {
                case ENERGYMODE:
                   Data[0] = -1;
                   Data[1] = _M10INI->TempSysConfig.CoolingDel;
                   Data[2] = _M10INI->TempSysConfig.CoolingTooling;
                break;
                case OFF:
                   Data[0] = 0;
                   Data[1] = _M10INI->TempSysConfig.CoolingDel;
                   Data[2] = _M10INI->TempSysConfig.CoolingTooling;
                break;
                default:
                   Data[0] = _M10INI->TempSysConfig.CoolingDur;
                   Data[1] = _M10INI->TempSysConfig.CoolingDel;
                   Data[2] = _M10INI->TempSysConfig.CoolingTooling;
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
             Data[0] = _M10INI->TempSysConfig.Machineflags[0];
             Data[1] = _M10INI->TempSysConfig.Machineflags[1];
             Data[2] = _M10INI->TempSysConfig.Machineflags[2];
             Data[3] = _M10INI->TempSysConfig.Machineflags[3];
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
             Data[1] = _M2010->Shim1Val;
             Data[2] = _M2010->Shim2Val;
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

    for (datalength = 1; datalength <= (length / 2); datalength++)
        OutStr = OutStr + MakeHexWord(Data[datalength - 1]);

    bool bResult;
    for (i = 0; i < (OutStr.length() / 2); i++)
    {
          strTemp = OutStr.mid(2 * i + 1, 2);
          SumCheck += strTemp.toInt(&bResult, 16);
    }
    SumCheck = (0 - SumCheck) & 0xFF;
    OutStr = OutStr + MakeHexByte(SumCheck) + "\r\n";
//    qDebug()<<"Send Frame: "<<OutStr;

    #ifdef IA98System
        BransonSerial::comIA98->write(OutStr.c_str(), OutStr.length());
        BransonSerial::comIA98->waitForBytesWritten(-1);
    #else
        if (_ModRunSetup->OfflineModeEnabled == false)
        {
            QByteArray Buffer = OutStr.toLatin1();
            BransonSerial::IAportSend(Buffer);
            char Command = 0x11;
            Buffer = QByteArray(&Command, 1);
            BransonSerial::IAportSend(Buffer);
        }
    #endif
}

bool M102IA::WaitForResponseAfterSent(int TimeOut, bool *CheckResponseFlag)
{
    ModRunSetup *_ModRunSetup = ModRunSetup::Instance();
    TimerClass *_Timer = new TimerClass();
    _Timer->SetCommandTimer(TimeOut);
//    *CheckResponseFlag = false;
    while (*CheckResponseFlag == false)
    {
        QCoreApplication::processEvents(); // Wait for response
        if ((_ModRunSetup->OfflineModeEnabled == true) ||
                (_Timer->IsCommandTimeout() == true))
            break;
    };
    if(_ModRunSetup->OfflineModeEnabled == true)
        *CheckResponseFlag = true;
    _Timer->ResetCommandTimer();
    delete _Timer;
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

int M102IA::MakeHexByteNumber(QString HexByte)
{
    int Result = 0;
    if(HexByte.length() == 2)
    {
        QByteArray Array = HexByte.toLatin1();
        Result = 16 * MakeHexNibbleNumber(Array.at(0)) +
                MakeHexNibbleNumber(Array.at(1));
    }else
        Result = 0;
    return Result;
}

int M102IA::MakeHexWordNumber(QString HexWord)
{
    //Makes the first four hex characters into number (input is little endian)
    int temp1, IntReturn;
    temp1 = MakeHexByteNumber(HexWord.mid(0, 2)) +
            256 * MakeHexByteNumber(HexWord.mid(2, 2));
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

long M102IA::MakeHexWordNumberLong(QString HexWord)
{
    //Make the first eight characters into a signed long number.
    //Little Endian "67452301" = 0x01234567
    long LSBs, MSBs, Result;

    //Collect Least Significant Bytes
    LSBs = MakeHexByteNumber(HexWord.mid(0,2)) + 0x100 * MakeHexByteNumber(HexWord.mid(2,2));
    //Collect Most Significant Bytes
    MSBs = MakeHexByteNumber(HexWord.mid(4,2)) + 0x100 * MakeHexByteNumber(HexWord.mid(6,2));
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

long M102IA::GetLongValue(QString InputString, int Ref)
{
   return MakeHexWordNumberLong(InputString.mid(Ref, 8));
}

//Retrieves data from the input strings sent by the controller.
//Depending on the DataSignature respective values are extracted from the received HexString.
//Amplitude2 value required for Amplitude Stepping is also added
int M102IA::ParseHexStructure(QString HexString, int tmpDataSignature)
{
    M10INI *_M10INI   = M10INI::Instance();
    M2010  *_M2010    = M2010 ::Instance();
//    MDefine *_MDefine = MDefine::Instance();
//    Statistics *_Statistics = Statistics::Instance();
    ModRunSetup *_ModRunSetup = ModRunSetup::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    M10runMode *_M10runMode = M10runMode::Instance();
    AlarmMessage *_AlarmMsg = AlarmMessage::Instance();
    const QString Colon = ":";

    int i;
    int Index, temp, Div;
    QString TempString = "";
    QString PowerString;
    unsigned int ResetType;
    struct BransonMessageBox tmpMsgBox;
    _M10INI->GlobalSignature = tmpDataSignature;
    switch(tmpDataSignature)
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
        IAactual.Energy = MakeHexWordNumber(HexString.mid(25, 4));
        IAactual.Width = MakeHexWordNumber(HexString.mid(29, 4)); //+ Splice.WidthCorr
        IAactual.Time = MakeHexWordNumber(HexString.mid(33, 4));
        // This Time value has been divided by 5 in firmware, so we only need to divided it by 2 again.
        // So, this time value is able to reduced 10 times.
        IAactual.Time = IAactual.Time / 2;
        //--Need to piece a together to parts here because of Jim's string
        TempString = HexString.mid(39, 2) + HexString.mid(52, 2);
        IAactual.Power = MakeHexWordNumber(TempString);
        //--Need to use the raw peakpower to do calculation
        Div = (_Interface->StatusData.Soft_Settings.SonicGenWatts / 200);
        IAactual.Power = MakeHexByteNumber(HexString.mid(37, 2));
        if (_Interface->StatusData.Soft_Settings.SonicGenWatts > 200)
           IAactual.Power = IAactual.Power * Div;
        else
           IAactual.Power = IAactual.Power * (_Interface->StatusData.Soft_Settings.SonicGenWatts / 200);
        //--Second data record
        IAactual.Preheight = MakeHexWordNumber(HexString.mid(54, 4));
        IAactual.Amplitude = MakeHexWordNumber(HexString.mid(58, 4));
        IAactual.Height = MakeHexWordNumber(HexString.mid(62, 4)); //+ Splice.HeightCorr
        IAactual.Amplitude2 = MakeHexWordNumber(HexString.mid(66, 4));
        IAactual.PPHeight = MakeHexWordNumber(HexString.mid(70, 4));
        IAactual.Pressure = MakeHexWordNumber(HexString.mid(74, 4));
        IAactual.TPressure = MakeHexWordNumber(HexString.mid(78, 4));
        IAactual.Alarmflags = MakeHexWordNumberLong(HexString.mid(82, 8));
//        if ((IAactual.Alarmflags & 0x4000) == 0x4000)
//            IACommand(IAComHostReady, 1);
        //--Set Correct Flag
        _M2010->ReceiveFlags.WELDdata = true;
        if((IAactual.Alarmflags & 0x4000) == 0x4000)
            emit WeldCycleSignal(_M2010->ReceiveFlags.WELDdata);
        else
            emit AlarmStatusSignal(_M2010->ReceiveFlags.WELDdata);
        break;
    case IASigPower:           //Data Signature = "04"
        // Frame head 3 bytes + ":" 7 characters
        // Total 2 bytes            4 characters
        // Index 2 bytes            4 characters
        // One empty byte           2 characters
        // Data is in an unknown number of strings, all but last is 16 Bytes of data
        // Data                     32 characters
        // Check sum 1 byte         2 characters
        //  (length = 51 Characters)
        int StringLen, StringCount, LastString;
        int num, Total, tmpIndex, Datalen;
        num = 0;
        StringLen = HexString.length();
        StringCount = int(StringLen / 51);
        LastString = StringLen % 51;
        PowerString = "";
        tmpIndex = 0;
        Total = MakeHexWordNumber(HexString.mid((tmpIndex + 9), 4));
        RawPowerDataGraph.TotalFrame = Total;
        for (i = 0; i < StringCount; i++)
        {
            Total = MakeHexWordNumber(HexString.mid((tmpIndex + 9), 4));
            num = MakeHexWordNumber(HexString.mid(tmpIndex + 13, 4));
            RawPowerDataGraph.GraphDataList.insert(num,HexString.mid(tmpIndex, 51));
//            qDebug()<<"Total: "<<Total << " Index: "<<num<<" str: "<<HexString.mid(tmpIndex, 51);
            tmpIndex = tmpIndex + 51;
        }
        if (LastString > 0)
        {
            //Take off the overhead and tack the string onto the Power String
            Total = MakeHexWordNumber(HexString.mid((tmpIndex + 9), 4));
            num = MakeHexWordNumber(HexString.mid(tmpIndex + 13, 4));
            Datalen = MakeHexWordNumber(HexString.mid(tmpIndex + 1, 4));
//            qDebug()<<"Total: "<<Total << " Index: "<<num<<" str: "<<HexString.mid(tmpIndex, LastString);
            if ((Datalen - 4) != ((LastString - 19) / 2))
                num = num - 1;
            else
                RawPowerDataGraph.GraphDataList.insert(num, HexString.mid(tmpIndex, LastString));
        }
        RawPowerDataGraph.CurrentIndex = num;
        _M2010->ReceiveFlags.PowerGraphData = true;
        emit PowerGraphSignal(_M2010->ReceiveFlags.PowerGraphData);
        break;
    case IASigSerialNumber:
        SerialNoData = _M2010->ParseSerialNumber(HexString.mid(9, 32));
        _M2010->ReceiveFlags.SNdata = true;
        break;
    case IASigHeightCal:
        HeightCalResult = MakeHexWordNumber(HexString.mid(9, 4));
        qDebug()<<"123"<<HexString.length()<<HeightCalResult;
        if (HeightCalResult == 1)
        {
            DownSpeed = MakeHexWordNumber(HexString.mid(13, 4));
            qDebug()<<"234"<<HexString.length();
//            dlgCalibHeight.UniLabel6.Caption = GetResString(1106) & " = " & Format(DownSpeed / 100, "0.00 mm/sec")
        }
        if (HeightCalResult != 1)  _M2010->ReceiveFlags.CalibrationDone = true;
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
        IOstatus.IO = MakeHexWordNumberLong(HexString.mid(9, 8));
        IOstatus.AdjHeight = MakeHexWordNumber(HexString.mid(17, 4));
        IOstatus.AbsHeight = MakeHexWordNumber(HexString.mid(21, 4));
        IOstatus.ACV = MakeHexWordNumber(HexString.mid(25, 4));
        IOstatus.ACTap = MakeHexWordNumber(HexString.mid(29, 4));
        IOstatus.ACmax = MakeHexWordNumber(HexString.mid(33, 4));
        IOstatus.ACmin = MakeHexWordNumber(HexString.mid(37, 4));

        //--Adjust data fields that are part of another command
        HEIGHTbuffer[0] = IOstatus.AdjHeight;
        HEIGHTbuffer[1] = IOstatus.AbsHeight;
        //--Set Correct Flag
        _M2010->ReceiveFlags.IOdata = true;
        break;
    case IASigSonicHits:
        SonicHitsStrData[3] = HexString.mid(9, 2);
        SonicHitsStrData[2] = HexString.mid(11, 2);
        SonicHitsStrData[1] = HexString.mid(13, 2);
        SonicHitsStrData[0] = HexString.mid(15, 2);
        SonicHitsData.clear();
        for (i = 0; i< 4; i++)
            SonicHitsData = SonicHitsData + SonicHitsStrData[i];
        _M2010->ReceiveFlags.SonicHitsData = true;
        break;
    case IASigPressure:
        PressureRead = MakeHexWordNumber(HexString.mid(9, 4));
        _M2010->ReceiveFlags.PressureData = true;
        break;
    case IASigIOswitch:
        //--FootSwitch IO data - Data Signature = "09"
        LastIOSwitchData.IO = MakeHexWordNumberLong(HexString.mid(9, 8));
        //LastIOSwitchData.WordData = MakeHexWordNumber(Mid(HexString, 25, 4))
        IOstatus.IO = LastIOSwitchData.IO;
//        LastIOstatus.IO = CLng(LastIOSwitchData.WordData)
        _M2010->ReceiveFlags.IOSWITCHdata = true;
        CheckIAControl();
        break;
    case IASigAbortEnable:
        temp = MakeHexWordNumber(HexString.mid(9, 4));
        if (temp == 1)
            EnableAbortButton1 = true;
        else
            EnableAbortButton1 = false;
        _M2010->ReceiveFlags.HeightData = true;
        break;
//    case IASigWeldHistory      //"0A"
    case IASigHistoryPar:        //"0B"
    case IASigMemory:            //"0C"
    case IASigHeight:            //"0D"
        CalibHeight = MakeHexWordNumber(HexString.mid(9, 4));
        RawHeight = MakeHexWordNumber(HexString.mid(13, 4));
        OpenChkHeight = MakeHexWordNumber(HexString.mid(17, 4));
        _M2010->ReceiveFlags.HeightData = true;
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
        WIDTHbuffer[0] = MakeHexWordNumber(HexString.mid(9, 4));
        WIDTHbuffer[1] = MakeHexWordNumber(HexString.mid(13, 4));
        _M2010->ReceiveFlags.WIDTHdata = true;
        break;
    case IASigPWRrating:         //"0F"
        _Interface->StatusData.Soft_Settings.SonicGenWatts =
                MakeHexWordNumber(HexString.mid(9, 4));
        _Utility->Maxpower = (float)(1.2 * _Interface->StatusData.Soft_Settings.SonicGenWatts);
        for (Index = 0; Index <= 6; Index++)
        {
             _M10INI->Pwr_Prefix_Data[Index] = Index *
                     float(0.2 * _Interface->StatusData.Soft_Settings.SonicGenWatts);
        }

        _Utility->InitializeTextData();
        _M2010->ReceiveFlags.POWERrating = true;
        break;
    case IASigSequenceTable:     // Data Signature = "10"
    case IASigHornAmplitude:
//        --Calibrated Horn Amp. Value - Data Signature = "11"
        _Interface->StatusData.Soft_Settings.Horn_Calibrate = MakeHexWordNumber(HexString.mid(9, 4));
        _M2010->ReceiveFlags.HORNamplitude = true;
        break;
    case IASigSystemID:          //"12"
        //tempStatusData.MachineType = MakeHexWordNumber(Mid(HexString, 10, 4))
        //tempStatusData.MachineDate = ParseSerialNumber(Mid(HexString, 14, 12))
        _M2010->ReceiveFlags.SYSTEMid = true;
        break;
    case IASigMaintCount:        //"13"
    case IASigActuator:
        _Interface->StatusData.MachineType = (enum ActuatorType)MakeHexWordNumber(HexString.mid(9, 4));
        _Interface->StatusData.ActuatorMode = (enum ACTUATORMODE)MakeHexWordNumber(HexString.mid(13, 4));
        _Interface->StatusData.AntisideSpliceTime = MakeHexWordNumber(HexString.mid(17, 4));
        switch (_Interface->StatusData.MachineType)
        {
            case ACTULTRA20:
            case ACTULTRA40:
            case ACTMTS20:
            case ACTGUN40:
                _M2010->Machine = Welder;
            break;
            default:
            _M2010->Machine = WireSplicer;
            break;
        }
        _M2010->ReceiveFlags.ActuatorType = true;
        break;
    case IASigWidthZero:
        _ModRunSetup->tempWidthOffsetVal = MakeHexWordNumber(HexString.mid(9, 4));
        _M2010->ReceiveFlags.CalibrationDone = true;
        break;
    case IAsigCooling:
        _Interface->StatusData.CurrentCoolingDur = MakeHexWordNumber(HexString.mid(9, 4));
        _Interface->StatusData.CurrentCoolingDel = MakeHexWordNumber(HexString.mid(13, 4));
        _Interface->StatusData.CurrentCoolingTooling = MakeHexWordNumber(HexString.mid(17,4));
        break;
    case IASigHeightZero:
        _ModRunSetup->tempHeightOffsetval = MakeHexWordNumber(HexString.mid(9, 4));
        break;
    case IASigDataLockOnAlarm:
         _Interface->StatusData.LockonAlarm = MakeHexWordNumber(HexString.mid(9, 4));
        break;
    case IASigRunMode:
        _Interface->StatusData.RunMode.Word = MakeHexWordNumber(HexString.mid(9, 4));
        _M2010->ReceiveFlags.FootPadelDATA = true;
        break;
    case IASigMachineFlags:
        _Interface->StatusData.Machineflags.Word[0] = MakeHexWordNumber(HexString.mid(9, 4));
        _Interface->StatusData.Machineflags.Word[1] = MakeHexWordNumber(HexString.mid(13, 4));
        _Interface->StatusData.Machineflags.Word[2] = MakeHexWordNumber(HexString.mid(17, 4));
        _Interface->StatusData.Machineflags.Word[3] = MakeHexWordNumber(HexString.mid(21, 4));
        break;
    case IASigDataMaintCntr:
        _Interface->StatusData.CurrentMaintenanceLimits[0] = GetLongValue(HexString, 10);
        _Interface->StatusData.CurrentMaintenanceLimits[1] = GetLongValue(HexString, 18);
        _Interface->StatusData.CurrentMaintenanceLimits[2] = GetLongValue(HexString, 26);
        _Interface->StatusData.CurrentMaintenanceLimits[3] = GetLongValue(HexString, 34);

        _Interface->StatusData.CurrentMaintenanceLimits[4] = GetLongValue(HexString, 42);
        _Interface->StatusData.CurrentMaintenanceLimits[5] = GetLongValue(HexString, 50);
        _Interface->StatusData.CurrentMaintenanceLimits[6] = GetLongValue(HexString, 58);
        _Interface->StatusData.CurrentMaintenanceLimits[7] = GetLongValue(HexString, 66);
        _M2010->ReceiveFlags.MAINTENANCEcounters = true;
//        Save_StatusData False
        break;
    case IASigDataCycleCntr:
        _Interface->StatusData.CycleCount = GetLongValue(HexString, 10);
        _M10INI->Save_StatusData(false);
        break;
    case IASigReadPower:
        ADPower = MakeHexWordNumber(HexString.mid(9, 4));
        break;
    case IASigCommError:
//        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
//        tmpMsgBox.MsgPrompt = QObject::tr("Communication Error!");
//        tmpMsgBox.TipsMode = Critical;
//        tmpMsgBox.func_ptr = NULL;
//        _Interface->cMsgBox(&tmpMsgBox);
        break;
    case IASigControllerVer:
        ContollerVersion = _M2010->ParseSerialNumber(HexString.mid(9, 32));
        _M2010->ReceiveFlags.ControllerVersionData = true;
        break;
    case IASigDATADOUBLECLICK:
//        DoubleClickHandler
        break;
    case IASigDownSpeed:
        DownSpeed = MakeHexWordNumber(HexString.mid(9, 4));
//         If (DownSpeed < 10) Then
//            dlgCalibHeight.UniLabel6.Caption = GetResString(1998)
//         Else
//           dlgCalibHeight.UniLabel6.Caption = GetResString(1106) & " = " & Format(DownSpeed / 100, "0.00 mm/sec")
//         End If
        break;
//    case IASigMaximumGauge:
//        CalibHeightMaxGauge = MakeHexWordNumber(HexString.substr(10, 4));
//        _Interface->StatusData.CalHightMaximumGauge = CalibHeightMaxGauge;
//        ptr_M2010->ReceiveFlags.CalHeightMaxGaugeData = true;
//        break;
    case IASigHostReadyStatus:
        _M2010->ReceiveFlags.HostReadyData = true;
        break;
    case IASigTunePoint:
        _Interface->StatusData.Soft_Settings.TunePoint = MakeHexWordNumber(HexString.mid(9, 4));
        break;
    case IASigCutoff:
        _Interface->StatusData.CutoffMode = MakeHexWordNumber(HexString.mid(9, 4));
        break;
    case IASigFrequencyOffset:
         _Interface->StatusData.Soft_Settings.FrequencyOffset = MakeHexWordNumber(HexString.mid(9, 4));
        break;
    case IASigActuatorVer:
        ActuatorVersion = _M2010->ParseSerialNumber(HexString.mid(9, 32));
        _M2010->ReceiveFlags.ActuatorVersionData = true;
        break;
    case IASigActuatorPartNum:
        ActuatorPartNum = _M2010->ParseSerialNumber(HexString.mid(9, 32));
        _M2010->ReceiveFlags.ActuatorPartNumData = true;
        break;
    case IASigActuatorSerialNum:
        ActuatorSerialNum = _M2010->ParseSerialNumber(HexString.mid(9, 64));
        _M2010->ReceiveFlags.ActuatorSerialNumData = true;
        break;
    case IASigResetReady:
        ResetType = MakeHexWordNumber(HexString.mid(9, 4));
        if (_AlarmMsg->IsAlarmShown() == true)
        {
            _M10runMode->RemoteReset();
        }
        break;
    case IASigHeightGraph:
        // Frame head 3 bytes + ":" 7 characters
        // Total 2 bytes            4 characters
        // Index 2 bytes            4 characters
        // One empty byte           2 characters
        // Data is in an unknown number of strings, all but last is 32 Bytes of data
        // Data                     64 characters
        // Check sum 1 byte         2 characters
        //  (length = 83 Characters)
//        int StringLen, StringCount, LastString;
//        int num, Total, tmpIndex, Datalen;
        StringLen = HexString.length();
        StringCount = int(StringLen / 83);
        LastString = StringLen % 83;
        PowerString = "";
        tmpIndex = 0;
        num = 0;
        Total = MakeHexWordNumber(HexString.mid((tmpIndex + 9), 4)); // include the one empty byte
        RawHeightDataGraph.TotalFrame = Total;
        for (i = 0; i < StringCount; i++)
        {
            Total = MakeHexWordNumber(HexString.mid((tmpIndex + 9), 4));
            num = MakeHexWordNumber(HexString.mid(tmpIndex + 13, 4));
            RawHeightDataGraph.GraphDataList.insert(num,HexString.mid(tmpIndex, 83));
//            qDebug()<<"Total: "<<Total << " Index: "<<num<<" str: "<<HexString.mid(tmpIndex, 83);
            tmpIndex = tmpIndex + 83;
        }
        if (LastString > 0)
        {
            //Take off the overhead and tack the string onto the Power String
            Total = MakeHexWordNumber(HexString.mid((tmpIndex + 9), 4));
            num = MakeHexWordNumber(HexString.mid(tmpIndex + 13, 4));
            Datalen = MakeHexWordNumber(HexString.mid(tmpIndex + 1, 4));
//            qDebug()<<"Total: "<<Total << " Index: "<<num<<" str: "<<HexString.mid(tmpIndex, LastString);
            if ((Datalen - 4) != ((LastString - 19) / 2))
                num = num - 1;
            else
                RawHeightDataGraph.GraphDataList.insert(num, HexString.mid(tmpIndex, LastString));
        }
        RawHeightDataGraph.CurrentIndex = num;
        _M2010->ReceiveFlags.HeightGraphData = true;
        emit HeightGraphSignal(_M2010->ReceiveFlags.HeightGraphData);
        break;
    default:
        break;
    }
    return 0;
}

void M102IA::SendCommandData(int CommandData)
{
    int Time, Retries;
    M2010 *_M2010 = M2010::Instance();
    ModRunSetup *_ModRunSetup = ModRunSetup::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    TimerClass *_Timer = new TimerClass();
    Retries = 0;
    Time = 500;
    //SendCommandSetRunMode CommandData
    _M2010->ReceiveFlags.HostReadyData = false;
    SendIACommand(IAComHostReady, CommandData);
    if (CommandData == 1) return;
    _Timer->SetCommandTimer(Time);
    while (_M2010->ReceiveFlags.HostReadyData == false)
    {
        QCoreApplication::processEvents(); //Wait for response
        if (_ModRunSetup->OfflineModeEnabled == true) break;
        if ((_Timer->IsCommandTimeout() == true) && (Retries < 20))
        {
            _Timer->ResetCommandTimer();
            SendIACommand(IAComHostReady, CommandData);
            _Timer->SetCommandTimer(Time);
            Retries = Retries + 1;
        }
        else if (Retries >= 19)
            break;
     }
    _Timer->ResetCommandTimer();
    delete _Timer;
    if (Retries >= 19)
    {
//        MsgBox "Can't get Response from controller!"
        struct BransonMessageBox tmpMsgBox;
        tmpMsgBox.MsgTitle = QObject::tr("Warning");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get Response from controller!");
        tmpMsgBox.TipsMode = Exclamation;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
    }
}

bool M102IA::SetIAWidth(int WidthSet, bool SettingCheck)
{
    //This function sends the width for calibration.
    //Called during loading a preset or when Width alibration is done.
    //Returns error status
    bool Done = false;
    bool bResult = false;            //Assume failure
    M2010* _M2010 = M2010::Instance();
    M10runMode* _M10runMode = M10runMode::Instance();
    ModRunSetup* _ModRunSetup = ModRunSetup::Instance();
//    InterfaceClass* _Interface = InterfaceClass::Instance();
    MakeWeldProcess* _WeldCycle   = MakeWeldProcess::Instance();
    TimerClass* _Timer = new TimerClass();
    //This command is ignored if the safety cover does not exist
    //Aux Motion Control, Close Safety Cover

    if (_M2010->Machine == Welder)
    {
          bResult = true;
          return bResult;
    }
    //If Not StatusData.Soft_Settings.NoToolCover4SU Then _
    //        SendIACommand IAComAuxMotion, DO_CLOSE_SAFETY

    if (WidthSet == -1) WidthSet =
            _WeldCycle->CurrentSplice.WeldSettings.BasicSetting.Width;
    _M2010->ReceiveFlags.WIDTHdata = false;
    _M10runMode->WidthError = true;
    SendIACommand(IAComSetWidth, WidthSet);
    if (WidthSet == 0) SettingCheck = false;

    //Wait for width data
    Done = false;
    _Timer->SetCommandTimer(15000);
    while (Done == false)
    {
        QCoreApplication::processEvents(); // Wait for response
        if (_M2010->ReceiveFlags.WIDTHdata == true) Done = true;
        if(_Timer->IsCommandTimeout() == true) Done = true;
        if(_ModRunSetup->OfflineModeEnabled == true)
        {
            _M2010->ReceiveFlags.WIDTHdata = true;
            Done = true;
        }
    }
    _Timer->ResetCommandTimer();
    delete _Timer;
    //Aux Motion Control, Open Safety Cover
    //SendIACommand IAComAuxMotion, DO_OPEN_SAFETY
    if (_M2010->ReceiveFlags.WIDTHdata == false)
    {
        return bResult;    //Did not make it
    }else{
        _M2010->ReceiveFlags.WIDTHdata = false;
    }

    if (SettingCheck == true)
    {
          if ((WidthSet - WIDTHbuffer[0]) > M10_WIDTH_TOL) return bResult;
          if ((WIDTHbuffer[0] - WidthSet) > M10_WIDTH_TOL) return bResult;
    }
    _M10runMode->WidthError = false;
    bResult = true;
    return bResult;
}

bool M102IA::SendCommandSetRunMode(int CommandData)
{
    M2010   *_M2010   = M2010::Instance();
    _M2010->ReceiveFlags.FootPadelDATA = false;
    SendIACommand(IAComSetRunMode, CommandData);
    WaitForResponseAfterSent(3000, &_M2010->ReceiveFlags.FootPadelDATA);
    return _M2010->ReceiveFlags.FootPadelDATA;
}

void M102IA::SendPresetToIA(int PresetNo)
{
    int NameLen = -1;
    ModRunSetup *_ModRunSetup = ModRunSetup::Instance();
    unsigned short PresetAddress;
    if(PresetNo != 0)
        return;
    if(PresetNo == 0)
        PresetAddress = IAPRESET0;
    SendIACommand(IAAmpStepParameters, 0);

    memset(hexRecord.ByteData, 0, sizeof(hexRecord.ByteData));
    //1st record
    hexRecord.Address = PresetAddress;
    hexRecord.RecordType = 0;
    LittleEndianWord(0, IAsetup.ModeFlags);
    LittleEndianWord(2, IAsetup.Energy);
    LittleEndianWord(4, IAsetup.Width);
    LittleEndianWord(6, IAsetup.WeldPressure);
    LittleEndianWord(8, IAsetup.TriggerPressure);
    LittleEndianWord(10, IAsetup.Amplitude);
    LittleEndianWord(12, IAsetup.SqueezeTime);
    LittleEndianWord(14, IAsetup.Time.min);
    PackHexRecord();
    //2nd record
    hexRecord.Address = PresetAddress + 0x10;
    LittleEndianWord(0, IAsetup.Time.max);
    LittleEndianWord(2, IAsetup.Power.min);
    LittleEndianWord(4, IAsetup.Power.max);
    LittleEndianWord(6, IAsetup.Preheight.min);
    LittleEndianWord(8, IAsetup.Preheight.max);
    LittleEndianWord(10, IAsetup.Height.min);
    LittleEndianWord(12, IAsetup.Height.max);
    LittleEndianWord(14, IAsetup.PartCounter);
    PackHexRecord();
    //3rd record
    //Note: Sending this record triggers the controller function SaveData()
    //to execute SetUpNextWeld() and multiply Time.min and Time.max by 10.
    //See the controller code V0901
    hexRecord.Address = PresetAddress + 0x20;
    LittleEndianWord(0, IAsetup.StopCount);
    LittleEndianWord(2, IAsetup.HoldTime);
    LittleEndianWord(4, IAsetup.ABDelay);
    LittleEndianWord(6, IAsetup.ABDuration);

    //Constuct hex string(s) data from part name
    NameLen = IAsetup.PartName.size();
    if (NameLen > PartNameLength) NameLen = PartNameLength;
    for (int i = 0; i < NameLen; i++)
    {
        QString str = IAsetup.PartName.mid(i, 1);
        QByteArray Buffer = OutStructure.toLatin1();
        hexRecord.ByteData[i + 8] = Buffer.at(0);
        if (i == 7) break; //String is full
    }
    if (NameLen < 8) hexRecord.ByteData[NameLen + 8] = 0;
    if (NameLen < 7) hexRecord.ByteData[NameLen + 9] = -1;
    PackHexRecord();
    //Continue the name into next record if needed
    if (NameLen >= 8){
        hexRecord.Address = PresetAddress + 0x30;

        for(int i = 8; i < NameLen; i++)
        {
            QString str = IAsetup.PartName.mid(i, 1);
            QByteArray Buffer = OutStructure.toLatin1();
            hexRecord.ByteData[i - 8] = Buffer.at(0);
        }

        //Terminate the smaller strings
        if(NameLen < 19) hexRecord.ByteData[NameLen - 7] = 0;
        //Clear the balance of the hex record
        if (NameLen == PartNameLength)
            hexRecord.ByteData[12] = -1;
        else
            hexRecord.ByteData[NameLen - 6] = -1;
        PackHexRecord();
    }

    if (_ModRunSetup->OfflineModeEnabled == false)
    {
        QByteArray Buffer = OutStructure.toLatin1();
        BransonSerial::IAportSend(Buffer);
    }
}

void M102IA::CheckIOEventSlot(bool &_status)
{
    //This function is used to Analyse the IO status data coming from controller
    // and to show/do neccessary action.
    M2010* _M2010 = M2010::Instance();
    if ((_M2010->ReceiveFlags.IOdata == true) ||
            (_M2010->ReceiveFlags.IOSWITCHdata == true))
    {
        _M2010->ReceiveFlags.IOdata = false;
        _M2010->ReceiveFlags.IOSWITCHdata = false;
        //Tool Cover Problem
        if ((IOstatus.IO & 0x04) != (LastIOstatus.IO & 0x04))
        {
            //Look at PalmButton #1 & PalmButton #2
            if (((IOstatus.IO & 0x40) == 0x40) && ((IOstatus.IO & 0x80) == 0x80))
            {
                LastIOstatus.IO = LastIOstatus.IO Eqv (LastIOstatus.IO And &H4 Eqv _
                                IOstatus.IO And &H4)
                SafetyAlertMsg
            }
        }
        //E-Stop check and AirSwitch monitor
        if (((IOstatus.IO & 0x20) == 0x20) || ((IOstatus.IO & 0x08) == 0x08))
             _M2010->IAready = false;
        else
             _M2010->IAready = true;
          '//E-Stop Warning
          If (IOstatus.IO And &H20) <> (LastIOstatus.IO And &H20) Then
             '//Run E-Stop Warning
             LastIOstatus.IO = LastIOstatus.IO Eqv (LastIOstatus.IO And &H20 Eqv _
                              IOstatus.IO And &H20)
             Run_E_Stop_Screen
          Else
             If (LastIOstatus.IO And &H20) Then Run_E_Stop_Screen
          End If
          '//check low-air pressure switch
          If (IOstatus.IO And &H8) <> (LastIOstatus.IO And &H8) Then
             LastIOstatus.IO = LastIOstatus.IO Eqv (LastIOstatus.IO And &H8 Eqv _
                            IOstatus.IO And &H8)
             '//See if you have to run the low-pressure warning!

          End If
          '//check lock key
          If (IOstatus.IO And &H80000) <> (LastIOstatus.IO And &H80000) Then
            LastIOstatus.IO = LastIOstatus.IO Eqv (LastIOstatus.IO And &H80000 Eqv _
                            IOstatus.IO And &H80000)
            LockAlertMsg
          End If
          '//check IN0 for the footPedal
          If (IOstatus.IO And &H2) <> (LastIOstatus.IO And &H2) Then
            LastIOstatus.IO = LastIOstatus.IO Eqv (LastIOstatus.IO And &H2 Eqv _
                            IOstatus.IO And &H2)
            FootPedalMsg
          End If
          '//check Ac Voltage
          If (IOstatus.ACV < IOstatus.ACmin) Or (IOstatus.ACV > IOstatus.ACmax) Then
             '//Shut Down the System
          End If
          If (IOstatus.IO And &H40000) <> (LastIOstatus.IO And &H40000) Then
             LastIOstatus.IO = LastIOstatus.IO Eqv (LastIOstatus.IO And &H40000 Eqv _
                              IOstatus.IO And &H40000)
            'RemoteReset
             ' Remote reset will work only if lock on alarm is not set.
             'If ((IAready) And (StatusData.LockonAlarm = 0) And (dlgCutMsg.AlarmPresent = True)) Then
             'If ((IAready) And (dlgCutMsg.AlarmPresent = True)) Then
                'dlgCutMsg.RunModeMouseButton
              '  RemoteReset
             'End If
          End If
       '//End of Checking IO Data
    }
}
