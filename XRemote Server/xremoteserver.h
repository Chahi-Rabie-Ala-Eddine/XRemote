#ifndef XREMOTESERVER_H
#define XREMOTESERVER_H

#include <QtWidgets>
#include <QtNetwork>

#include "xremoteclientmanagement.h"

typedef quint16 _16Bits;

class xremoteserver : public QWidget{

    Q_OBJECT

    public:
    xremoteserver();
    ~xremoteserver();
    void _LaunchServer(QTcpServer *server);
    void _ConnectServerToDatabase(const char *databaseName);
    QTcpServer* _GetServer();
    QString _GetServerState();
    QString _GetServerLog();
    int _GetNumberOfConnectedHosts();
    /*Set tcp server propreties*/
    void _SetServer();

    private:
    QTcpServer* server;
    QList<client *> clients;
    QString state;
    QString log;

    private slots:
    void _NewConnectionToServer();
    void _PacketManagement();
    void _DeleteClientSocket();

    signals:
    void _NewLog();
    void _NewHostsNumber();
};

#endif // XREMOTESERVER_H
