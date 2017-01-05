#ifndef BRASONSOCKET_H
#define BRASONSOCKET_H

#include <QObject>
#include <QTcpSocket>

class BransonSocket : public QObject
{
    Q_OBJECT
private:
    bool IsActivated;
public:
    QTcpSocket *m_pConnectSocket; //client connect socket
    bool IsAvailableSocket();
    void SocketSendData(QString);
    explicit BransonSocket(QObject *parent = 0);
    ~BransonSocket();
signals:

public slots:
    void ReadTcpDataSlot();
};

#endif // BRASONSOCKET_H
