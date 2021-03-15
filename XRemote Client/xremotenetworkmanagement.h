#ifndef XREMOTENETWORKMANAGEMENT_H
#define XREMOTENETWORKMANAGEMENT_H

#include <QtWidgets>
#include <QWidget>
#include <QtNetwork>

#include "xremoteconstants.h"

/*Get source ip Address*/
QString getHostIPAddress(QTcpSocket *host);

/*Get source Port*/
QString getHostPORTAddress(QTcpSocket *host);

/*Get country location from ip Address*/
QString getLocalizationFromIP(QTcpSocket *host);

/*Connect to server using ip Address*/
void _ConnectHostToXremote(QTcpSocket* socket, _String hostAddr, unsigned int port);

/*Send credientials to server*/
void _SendCredentials(QTcpSocket* socket, QString email, QString password);

#endif // XREMOTENETWORKMANAGEMENT_H
