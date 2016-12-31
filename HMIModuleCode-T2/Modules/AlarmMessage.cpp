#include "AlarmMessage.h"
#include "M102IA.h"
#include "M2010.h"
#include "Interface/interface.h"
#include "Interface/AlarmElement.h"
#include "DataBase/DBAlarmLogTable.h"
#include "Interface/VariantToString.h"
AlarmMessage* AlarmMessage::_instance = NULL;

AlarmMessage* AlarmMessage::Instance()
{
    if(_instance == 0){
        _instance = new AlarmMessage();
    }
    return _instance;
}

AlarmMessage::AlarmMessage()
{
//    AlarmPresent = false;
}

void AlarmMessage::Initialization(int SpliceID)
{
    M102IA *_M102IA = M102IA::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
//    AlarmPresent = false;
    struct BransonMessageBox tmpMsgBox;
    if(_M102IA->SendCommandSetRunMode(0) == false)
    {
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
    }else{
        ShowText(SpliceID);
    }

}

void AlarmMessage::ShowText(int SpliceID)
{
    M102IA *_M102IA = M102IA::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    VariantToString* _Var2Str = VariantToString::Instance();
    int Index = 0;
    QString AlarmMsg;
    AlarmMsg.clear();
    //Width Error
    if((_M102IA->IAactual.Alarmflags & 0x800) == 0x800)
    {
        AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("WIDTH ERROR");
        QString AlarmType = _Var2Str->AlarmTypeToString(MOTORERROR);
        UpdateAlarmLog(AlarmMsg, AlarmType, SpliceID);
        Index++;
    }
    //Overload
    if((_M102IA->IAactual.Alarmflags & 0x01) == 0x01)
    {
        if(Index != 0)
            AlarmMsg += "\n";
        AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("Power OVERLOAD");
        QString AlarmType = _Var2Str->AlarmTypeToString(OVERLOADALARM);
        UpdateAlarmLog(AlarmMsg, AlarmType, SpliceID);
        Index++;
    }
    //Safety
    if((_M102IA->IAactual.Alarmflags & 0x400) == 0x400)
    {
        if(Index != 0)
            AlarmMsg += "\n";
        AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("Weld Safety Alarm");
        QString AlarmType = _Var2Str->AlarmTypeToString(SAFETYERROR);
        UpdateAlarmLog(AlarmMsg, AlarmType, SpliceID);
        Index++;
    }
    //Height Error
    if((_M102IA->IAactual.Alarmflags & 0x02) == 0x02)
    {
        if(Index != 0)
            AlarmMsg += "\n";
        AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("Height System failure");
        QString AlarmType = _Var2Str->AlarmTypeToString(HEIGHTENCODERERROR);
        UpdateAlarmLog(AlarmMsg, AlarmType, SpliceID);
        Index++;
    }
    //Time Error
    if((_M102IA->IAactual.Alarmflags & 0x20) == 0x20)
    {
        if(Index != 0)
            AlarmMsg += "\n";
        if(_M102IA->IAactual.Time < _M102IA->IAsetup.Time.min)
        {
            AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("Weld shorter than minimum time");
            Index++;
        }
        else
        {
            AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("Weld longer than maximum time");
            Index++;
        }
        QString AlarmType = _Var2Str->AlarmTypeToString(TIMEALARM);
        UpdateAlarmLog(AlarmMsg, AlarmType, SpliceID);
    }
    //Power Error
    if((_M102IA->IAactual.Alarmflags & 0x40) == 0x40)
    {
        if(Index != 0)
            AlarmMsg += "\n";
        if(_M102IA->IAactual.Power < _M102IA->IAsetup.Power.min)
        {
            AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("Highest power is below power minimum");
            Index++;
        }else
        {
            AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("Highest power is above power maximum");
            Index++;
        }
        QString AlarmType = _Var2Str->AlarmTypeToString(PEAKPOWERALARM);
        UpdateAlarmLog(AlarmMsg, AlarmType, SpliceID);
    }
    //PostHeight Error
    if((_M102IA->IAactual.Alarmflags & 0x80) == 0x80)
    {
        if(Index != 0)
            AlarmMsg += "\n";
        if(_M102IA->IAactual.Height < _M102IA->IAsetup.Height.min)
        {
            AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("Result is smaller than minimum height");
            Index++;
        }else
        {
            AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("Result is taller than maximum height");
            Index++;
        }
        QString AlarmType = _Var2Str->AlarmTypeToString(HEIGHTALARM);
        UpdateAlarmLog(AlarmMsg, AlarmType, SpliceID);
    }
    //PerHeight Error
    if((_M102IA->IAactual.Alarmflags & 0x04) == 0x04)
    {
        if(Index != 0)
            AlarmMsg += "\n";
        if(_M102IA->IAactual.Preheight < _M102IA->IAsetup.Preheight.min)
        {
            Index++;
            AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("Result is smaller than minimum Perheight");
        }else{
            AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("Result is taller than maximum Perheight");
            Index++;
        }
        QString AlarmType = _Var2Str->AlarmTypeToString(PREHEIGHTALARM);
        UpdateAlarmLog(AlarmMsg, AlarmType, SpliceID);
    }
    //Sense 24V
    if((_M102IA->IAactual.Alarmflags & 0x10000) == 0x10000)
    {
        if(Index != 0)
            AlarmMsg += "\n";
        AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("Power supply for solenoid valve is smaller than 24V");
        QString AlarmType = _Var2Str->AlarmTypeToString(VOL24ERROR);
        UpdateAlarmLog(AlarmMsg, AlarmType, SpliceID);
        Index++;
    }
    //Cutter Alarm for the New Wire Splicer
    if((_M102IA->IAactual.Alarmflags & 0x20000) == 0x20000)
    {
        if(Index != 0)
            AlarmMsg += "\n";
        AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("New wire splicer cutter alarm");
        QString AlarmType = _Var2Str->AlarmTypeToString(CUTERROR);
        UpdateAlarmLog(AlarmMsg, AlarmType, SpliceID);
        Index++;
    }
    //Lock Key Alarm for New Wire Splicer
    if((_M102IA->IAactual.Alarmflags & 0x40000) == 0x40000)
    {
        if(Index != 0)
            AlarmMsg += "\n";
        AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("Lock Open Alert");
        Index++;
    }
    //ID chip alarm for the New Wire Splicer
    if((_M102IA->IAactual.Alarmflags & 0x80000) == 0x80000)
    {
        if(Index != 0)
            AlarmMsg += "\n";
        AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("Please check Actuator Board connecting");
        QString AlarmType = _Var2Str->AlarmTypeToString(IDCHIPERROR);
        UpdateAlarmLog(AlarmMsg, AlarmType, SpliceID);
        Index++;
    }
    //FRAM, RAM error
    if((_M102IA->IAactual.Alarmflags & 0x100000) == 0x100000)
    {
        if(Index != 0)
            AlarmMsg += "\n";
        AlarmMsg += QString::number(Index + 1, 10) + ". " + QObject::tr("FRAM, RAM error");
        QString AlarmType = _Var2Str->AlarmTypeToString(RAMERROR);
        UpdateAlarmLog(AlarmMsg, AlarmType, SpliceID);
        Index++;
    }
    struct BransonMessageBox tmpMsgBox;
    tmpMsgBox.MsgPrompt = AlarmMsg;
    tmpMsgBox.MsgTitle = QObject::tr("Alarm");
    tmpMsgBox.TipsMode = (RESETCancel | Alarm);
    tmpMsgBox.func_ptr = AlarmMessage::ResetAnyAlarm;
    tmpMsgBox._Object = this;
    _Interface->cMsgBox(&tmpMsgBox);
    qDebug()<<"Alarm Send";
}

void AlarmMessage::ResetAnyAlarm(void* _obj)
{
    M102IA *_M102IA = M102IA::Instance();
    _M102IA->Generate_Beep();
    ((AlarmMessage*)_obj)->RunModeMouseButton();
}

void AlarmMessage::RunModeMouseButton()
{
    M2010 *_M2010 = M2010::Instance();
    M102IA *_M102IA = M102IA::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    _M2010->M10Run.Alarm_found = false;
    _M2010->M10Run.Pre_Hght_Error = false;
    _M2010->M10Run.SafetyFailed = false;
    _M102IA->IACommand(IAComSigLightOff);
    _M102IA->IACommand(IAComClrAlarms);
    struct BransonMessageBox tmpMsgBox;
    if(_M102IA->SendCommandSetRunMode(1) == false)
    {
        tmpMsgBox.MsgTitle = QObject::tr("ERROR");
        tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
        tmpMsgBox.TipsMode = Critical;
        tmpMsgBox.func_ptr = NULL;
        _Interface->cMsgBox(&tmpMsgBox);
    }else
    {
        _M2010->ReceiveFlags.HostReadyData = false;
        _M102IA->IACommand(IAComHostReady);
        _M102IA->WaitForResponseAfterSent(3000,&_M2010->ReceiveFlags.HostReadyData);
        if(_M2010->ReceiveFlags.HostReadyData == false)
        {
            tmpMsgBox.MsgTitle = QObject::tr("ERROR");
            tmpMsgBox.MsgPrompt = QObject::tr("Can't get any Response from controller!");
            tmpMsgBox.TipsMode = Critical;
            tmpMsgBox.func_ptr = NULL;
            _Interface->cMsgBox(&tmpMsgBox);
        }
    }
}

void AlarmMessage::UpdateAlarmLog(QString AlarmStr, QString AlarmType, int SpliceID)
{
    InterfaceClass *_Interface = InterfaceClass::Instance();
    DBAlarmLogTable *_AlarmLog = DBAlarmLogTable::Instance();
    AlarmElement CurrentAlarm;
    CurrentAlarm.AlarmMsg = AlarmStr;
    CurrentAlarm.AlarmType = AlarmType;
    CurrentAlarm.OperatorID = _Interface->CurrentOperator.OperatorID;
    CurrentAlarm.SpliceID = SpliceID;
    _AlarmLog->InsertRecordIntoTable(&CurrentAlarm);
}
