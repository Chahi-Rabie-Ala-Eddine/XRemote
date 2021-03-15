#ifndef XREMOTERPSPPROTOCOL_H
#define XREMOTERPSPPROTOCOL_H

#include <QtWidgets>
#include <QtNetwork>

#include "xremotedevice.h"

typedef quint16 _16Bits;

/*Unicast packet to a specific device*/
void _RPSPUnicast(const QString &RecievedPacket, xremotedevice* device);

/*Multicast packet to multiple devices*/
void _RPSPMulticast(const QString &RecievedPacket, QList<xremotedevice*> devices);

/*Broadcast packet to all devices*/
void _RPSPBroadcast(const QString &RecievedPacket, QList<xremotedevice*> devices);

#endif // XREMOTERPSPPROTOCOL_H
