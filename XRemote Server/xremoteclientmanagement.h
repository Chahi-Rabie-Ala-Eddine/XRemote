#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets>
#include <QtNetwork>

typedef quint16 _16Bits;

class client{

    public:

    /*Client constructor*/
    client(QTcpSocket *socket);

    /*Get client ID*/
    QString getClientId();

    /*Get client Socket*/
    QTcpSocket* getClientSocket();

    /*Set client Packet*/
    void _setClientSizeOfPacket(_16Bits length);

    /*Get client size of sended paquet*/
    quint16 _getClientSizeOfPacket();

    private:

    /*Client id*/
    QString idClient;

    /*Client socket*/
    QTcpSocket* socket;

    /*Client packet size*/
    _16Bits sizeOfPacket;


};





#endif // CLIENT_H
