#ifndef UDPGATEWAY_H
#define UDPGATEWAY_H

#include <QtCore>
#include <QtNetwork>
#include"udpconnection.h"


class udpGateway : public QObject
{
    Q_OBJECT
public:
    udpGateway(quint16 port);
    UDPConnection* mapConncetion(QHostAddress sender,quint16 senderPort);
    void removeDuplicateConnection(int userID, int deviceID, bool isDevice);

private slots:
    void readPendingDatagrams();
    //void readPendingDatagramsDevice();

private:
    QUdpSocket* socket;
    //QUdpSocket* socketDevice;

    QVector<UDPConnection*> connectionList;

};


#endif // UDPGATEWAY_H






