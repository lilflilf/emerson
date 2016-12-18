#ifndef ALARMMESSAGE_H
#define ALARMMESSAGE_H
#include <QString>

class AlarmMessage
{
private:
    bool AlarmPresent;
    int WeldResultID;
private:
    void RunModeMouseButton();
    void ShowText(int weldresult);
    void UpdateAlarmLog(QString AlarmStr, QString AlarmType, int WeldResultID);
    static void ResetAnyAlarm(void* _obj);
public:
    void Initialization(int weldresult);
public:
    static AlarmMessage* Instance();
protected:
    AlarmMessage();
private:
    static AlarmMessage* _instance;
public:
    ~AlarmMessage();
};

#endif // ALARMMESSAGE_H
