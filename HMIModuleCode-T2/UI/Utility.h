#ifndef CURRENTCLOCK_H
#define CURRENTCLOCK_H
#include <qobject>

#define HMI_PRINT (qDebug() <<"HMI adapter by zhangjy:" << __FILE__ << __FUNCTION__ << __LINE__ << ": ")
class Utility : public QObject
{
 Q_OBJECT
public:
    Utility(QObject *parent = 0);
signals:
    void currentTime(const QString &strTime);
public slots:

protected:
    void timerEvent(QTimerEvent *event);
private:
    void start();
    void stop();
    int m_nCurrentTimer;
};
#endif // CURRENTCLOCK_H
