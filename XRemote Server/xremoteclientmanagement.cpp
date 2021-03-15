#include "xremoteclientmanagement.h"
#include "xremotegenerator.h"

/*Client constructor*/
client::client(QTcpSocket* socket) : socket(socket){this->idClient = XRemoteHazard(32); printf("%s\n", this->idClient.toUtf8().constData()); this->sizeOfPacket = 0;}

/*Get client ID*/
QString client::getClientId(){

    return this->idClient;
}

/*Get client Socket*/
QTcpSocket* client::getClientSocket(){

    return this->socket;
}

/*Set client Packet*/
void client::_setClientSizeOfPacket(_16Bits length){

    this->sizeOfPacket = length;
}

/*Get client size of sended paquet*/
quint16 client::_getClientSizeOfPacket(){

    return this->sizeOfPacket;
}
