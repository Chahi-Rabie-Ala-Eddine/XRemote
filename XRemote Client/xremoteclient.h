#ifndef XREMOTECLIENT_H
#define XREMOTECLIENT_H

#include <QtNetwork>
#include <QWidget>

#include "xremotedevice.h"

class xremoteclient : public QWidget{

    Q_OBJECT

    public:
    xremoteclient();
    QTcpSocket* _GetSocket();
    QString _GetError();
    QString _GetRPSPPacket();
    void _SendRPSPPacketToServer(QString RPSPRequest);
    void _SendRPSPPacketToHost();
    void _SetSingalsSlots();

    private:
    QTcpSocket* socket;
    QList<xremotedevice *> devices;
    QString RPSPPacket;
    QString error;
    quint16 messageLength;

    public slots:
    void _RecieveRPSPPacket();
    void _SocketErrors(QAbstractSocket::SocketError _error);

    signals:
    void _Recieve();
    void _Send();


};

#endif // XREMOTECLIENT_H
