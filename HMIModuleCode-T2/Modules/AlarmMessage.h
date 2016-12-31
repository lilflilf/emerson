#ifndef ALARMMESSAGE_H
#define ALARMMESSAGE_H
#include <QString>
#include <QObject>

class AlarmMessage
{
private:
    bool AlarmPresent;
    int WeldResultID;
private:
    void RunModeMouseButton();
    void ShowText(int SpliceID);
    void UpdateAlarmLog(QString AlarmStr, QString AlarmType, int SpliceID);
    static void ResetAnyAlarm(void* _obj);

public:
    void Initialization(int SpliceID);
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
