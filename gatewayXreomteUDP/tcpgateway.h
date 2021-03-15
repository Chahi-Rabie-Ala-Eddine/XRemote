#ifndef TCPGATEWAY_H
#define TCPGATEWAY_H

#include <QtCore>
#include <QtNetwork>
#include"tcpconnection.h"


class TcpGateway : public QObject
{
    Q_OBJECT
public:
    TcpGateway(quint16 port);

private slots:
    void newConnection();
    void searchClient(int id,QByteArray data);
    void searchDevice(int id,QByteArray data);
    void removeDuplicateConnection(int userID, int deviceID, bool isDevice);


private:
    QTcpServer *server;
    QVector<TCPConnection*> socketList;

};

#endif // TCPGATEWAY_H









