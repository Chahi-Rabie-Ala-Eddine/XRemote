#ifndef XREMOTELOG_H
#define XREMOTELOG_H

#include <QtWidgets>
#include <QtNetwork>

using namespace std;

/*Server state log*/
QString _ServerStateLog(QTcpServer *server);

/*Connection log*/
QString connectionLog(QTcpSocket *host);

/*Disconnection log*/
QString disconnectionLog(QTcpSocket *host);

/*Write logs into log file*/
void writeLog(const QString singleLog);

/*Get source ip Address*/
void exportXRemoteLogs(QTextEdit* text);

#endif // XREMOTELOG_H
