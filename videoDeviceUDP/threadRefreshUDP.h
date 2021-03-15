#ifndef THREADREFRESHUDP_H
#define THREADREFRESHUDP_H
#include <QtCore>
#include <QtNetwork>
#include <unistd.h>


class ThreadRefresh : public QObject
{
    Q_OBJECT
public:    ThreadRefresh();

public slots:
    void refreshConnection( QHostAddress* sender, quint16* senderPort, QUdpSocket* udpSocket, int deviceID, int clientID,bool* loop );
/*
signals:
    void resultReady(const QString &result);*/
};

#endif // THREADREFRESHUDP_H
