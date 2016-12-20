#ifndef THREADCLASS_H
#define THREADCLASS_H
#include <QObject>
#include <QThread>

typedef void (*ptrCallbackFun)(void*); //define a the recall

class ThreadClass : public QThread
{
    Q_OBJECT
private:
    bool m_stop;
    bool m_suspend;
    ptrCallbackFun m_callbackHandle;
    void* m_arg;
public:
    explicit ThreadClass(QObject *parent = 0, void* _funcn = NULL,
                         void* arg = NULL);
    ~ThreadClass();
    void run();
    void setStopEnabled(bool enabled = true);
    void setSuspendEnabled(bool enabled = true);
signals:

public slots:
};

#endif // THREADCLASS_H
