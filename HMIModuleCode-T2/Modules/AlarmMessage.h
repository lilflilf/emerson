#ifndef ALARMMESSAGE_H
#define ALARMMESSAGE_H
#include <QString>
#include <QObject>

class AlarmMessage
{
private:
    bool AlarmPresent;
    int WeldResultID;
    QList<int> mAlarmIDList;
private:
    void RunModeMouseButton();
    void ShowText(int SpliceID);
    void UpdateAlarmLog(QString AlarmStr, QString AlarmType, int SpliceID);
    static void ResetAnyAlarm(void* _obj);
    static void GiveupAlarmReset(void* _obj);

public:
    bool IsAlarmShown();
    void Initialization(int SpliceID);
    void ShowMaintenanceText(int SpliceID, QString AlarmMsg, enum ALARMTYPE alarmtype);
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
