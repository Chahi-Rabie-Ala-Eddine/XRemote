#include "xremoteclient.h"

xremoteclient::xremoteclient() : QWidget(){

    /*Start socket*/
    this->socket = new QTcpSocket(this);

    _SetSingalsSlots();

    /*Initialise paquets size*/
    this->messageLength = 0;
}

void xremoteclient::_SetSingalsSlots(){

    connect(this->socket, SIGNAL(readyRead()), this, SLOT(_RecieveRPSPPacket()));
    connect(this->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(_SocketErrors(QAbstractSocket::SocketError)));
}

void xremoteclient::_SendRPSPPacketToServer(QString RPSPRequest){

    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    /*Paquet preparation*/
    QString request = tr("<strong><font color = 'navy'>") + "Client" + tr("</font></strong> : ") + RPSPRequest;

    /*Paquet configuration*/
    out << (quint16) 0;
    out << request;
    out.device()->seek(0);
    out << (quint16) (packet.size() - sizeof(quint16));

    /*Send request*/
    this->socket->write(packet);
    emit _Send();
}

void xremoteclient::_SendRPSPPacketToHost(){}

void xremoteclient::_RecieveRPSPPacket(){

    QDataStream in(socket);

    if (messageLength == 0){

        if (socket->bytesAvailable() < (int)sizeof(quint16))
             return;

        in >> messageLength;
    }

    if (socket->bytesAvailable() < messageLength)
        return;

    in >> RPSPPacket;
    emit _Recieve();

    messageLength = 0;
}

void xremoteclient::_SocketErrors(QAbstractSocket::SocketError _error){

    switch(_error){

        case QAbstractSocket::HostNotFoundError:
            error = "<em>Error : Server not found. Check out Ip and port.</em>";
            break;

        case QAbstractSocket::ConnectionRefusedError:
            error = "<em>Error : Connection refused ! Check out Ip and port.</em>";
            break;

        case QAbstractSocket::RemoteHostClosedError:
            error = "<em>Error : Server disconnected.</em>";
            break;

        default:
            error = "<em>Error : " + this->socket->errorString() + "</em>";
    }
}

QTcpSocket* xremoteclient::_GetSocket(){

    return this->socket;
}

QString xremoteclient::_GetRPSPPacket() {

    return RPSPPacket;
}
