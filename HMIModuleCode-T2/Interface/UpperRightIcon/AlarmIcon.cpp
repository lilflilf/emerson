#include "AlarmIcon.h"
#include <QDebug>
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
    qDebug()<<"ResetAlarmItem";
}
