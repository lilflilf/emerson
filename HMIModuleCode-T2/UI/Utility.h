#ifndef CURRENTCLOCK_H
#define CURRENTCLOCK_H
#include <qobject>
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
