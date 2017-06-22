#include "AlarmIcon.h"
#include <QDebug>
#include "DataBase/DBAlarmLogTable.h"
#include "Interface/AlarmElement.h"
#include "Modules/M102IA.h"
#include "Modules/M2010.h"
#include "Interface/MakeWeld/MakeWeldProcess.h"
#include "Modules/typedef.h"
AlarmIcon* AlarmIcon::_instance = NULL;
AlarmIcon* AlarmIcon::Instance()
{
    if(_instance == NULL){
        _instance = new AlarmIcon();
    }
    return _instance;
}
AlarmIcon::AlarmIcon()
{

}

void AlarmIcon::ResetAlarmItem(int AlarmID)
{
    DBAlarmLogTable* _AlarmLog = DBAlarmLogTable::Instance();
    M2010* _M2010 = M2010::Instance();
    M102IA* _M102IA = M102IA::Instance();
    MakeWeldProcess* _WeldProcess = MakeWeldProcess::Instance();
    AlarmElement CurrentAlarm;
    bool bResult = _AlarmLog->QueryOneRecordFromTable(AlarmID, &CurrentAlarm);
    if(bResult == true)
    {
        CurrentAlarm.IsReseted = true;
        _AlarmLog->UpdateRecordIntoTable(&CurrentAlarm);

        //Send Command to reset
        _M2010->M10Run.Alarm_found = false;
    //    _M102IA->IACommand(IAComSigLightOff);
        _M102IA->IACommand(IAComClrAlarms);
        if(_WeldProcess->GetWeldStatus() == true)
        {
            _M102IA->SendCommandSetRunMode(ON);
            _M2010->ReceiveFlags.HostReadyData = false;
            _M102IA->IACommand(IAComHostReady);
            _M102IA->WaitForResponseAfterSent(DELAY3SEC,&_M2010->ReceiveFlags.HostReadyData);
        }
    }

    qDebug()<<"ResetAlarmItem";
}
