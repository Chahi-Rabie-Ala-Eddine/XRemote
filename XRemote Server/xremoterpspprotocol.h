#ifndef XREMOTERPSMANAGER_H
#define XREMOTERPSMANAGER_H

#include <QtWidgets>
#include <QtNetwork>

#include "xremoteclientmanagement.h"

typedef quint16 _16Bits;

/*Unicast packet to a specific device*/
void _RPSPUnicast(const QString &RecievedPacket, QList<client *> clients);

/*Multicast packet to multiple devices*/
void _RPSPMulticast(const QString &RecievedPacket, QList<client *> clients);

/*Broadcast packet to all devices*/
void _RPSPBroadcast(const QString &RecievedPacket, QList<client *> clients);

#endif // XREMOTERPSMANAGER_H
