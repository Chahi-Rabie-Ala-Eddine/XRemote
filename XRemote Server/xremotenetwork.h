#ifndef XREMOTENETWORK_H
#define XREMOTENETWORK_H

#include <QtWidgets>
#include <QtNetwork>

#include "xremoteclientmanagement.h"

/*Get source ip Address*/
QString getHostIPAddress(QTcpSocket *host);

/*Get source Port*/
QString getHostPORTAddress(QTcpSocket *host);

/*Get country location from ip Address*/
QString getLocalizationFromIP(QTcpSocket *host);

/*Compare sockets*/
bool operator==(QTcpSocket const& socketA, QTcpSocket const& socketB);

/*Find the user related to this socket*/
client* retrieveClient(QList<client *> clients, QTcpSocket *socket);

#endif // XREMOTENETWORK_H

