#include "xremoterpspprotocol.h"

/*Unicast packet to a specific device*/
void _RPSPUnicast(const QString &RecievedPacket, QList<client *> clients){

    /*Prepare packet*/
    QByteArray packet;
    QDataStream packetBuffer(&packet, QIODevice::WriteOnly);

    /*Write packet*/
    packetBuffer << (_16Bits) 0;
    packetBuffer << RecievedPacket;
    packetBuffer.device()->seek(0);
    packetBuffer << (_16Bits) (packet.size() - sizeof(_16Bits));

    /*Send packet*/
    for (int i = 0; i < clients.size(); i++)
        clients[i]->getClientSocket()->write(packet);
}

/*Multicast packet to multiple devices*/
void _RPSPMulticast(const QString &RecievedPacket, QList<client *> clients){

    /* Prepare packet */
    QByteArray packet;
    QDataStream packetBuffer(&packet, QIODevice::WriteOnly);

    /* Write packet */
    packetBuffer << (_16Bits) 0;
    packetBuffer << RecievedPacket;
    packetBuffer.device()->seek(0);
    packetBuffer << (_16Bits) (packet.size() - sizeof(_16Bits));

    /* Send packet */
    for (int i = 0; i < clients.size(); i++)
        clients[i]->getClientSocket()->write(packet);
}

/*Broadcast packet to all devices*/
void _RPSPBroadcast(const QString &RecievedPacket, QList<client *> clients){

    /* Prepare packet */
    QByteArray packet;
    QDataStream packetBuffer(&packet, QIODevice::WriteOnly);

    /* Write packet */
    packetBuffer << (_16Bits) 0;
    packetBuffer << RecievedPacket;
    packetBuffer.device()->seek(0);
    packetBuffer << (_16Bits) (packet.size() - sizeof(_16Bits));

    /* Send packet */
    for (int i = 0; i < clients.size(); i++)
        clients[i]->getClientSocket()->write(packet);
}
