#ifndef ALARMICON_H
#define ALARMICON_H


class AlarmIcon
{
public:
    void ResetAlarmItem(int AlarmID);
public:
    static AlarmIcon* Instance();
private:
    static AlarmIcon* _instance;
private:
    AlarmIcon();
};

#endif // ALARMICON_H
