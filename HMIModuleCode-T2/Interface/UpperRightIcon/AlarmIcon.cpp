#include "AlarmIcon.h"
#include <QDebug>
#include "DataBase/DBAlarmLogTable.h"
#include "Interface/AlarmElement.h"
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
    AlarmElement CurrentAlarm;
    bool bResult = _AlarmLog->QueryOneRecordFromTable(AlarmID, &CurrentAlarm);
    if(bResult == true)
    {
        CurrentAlarm.IsReseted = true;
        _AlarmLog->UpdateRecordIntoTable(&CurrentAlarm);
    }

    qDebug()<<"ResetAlarmItem";
}
