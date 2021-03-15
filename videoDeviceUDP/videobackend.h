#ifndef VIDEOBACKEND_H
#define VIDEOBACKEND_H

#include <QtCore>
#include <QtNetwork>
#include "videoinput.h"

class VideoBackend : public QObject
{
    Q_OBJECT
public:
    VideoBackend(quint16 port, QString pathDirectory,int deviceID, int clientID);
    ~VideoBackend();
private:
    void parser( QByteArray data);
    void switchToXremote(); // ???????

public slots:
    void writeDataUDP(QByteArray data);
    void writeDataTCP(QByteArray data);
    void readyReadTcpXremote();
    void readyReadTcpClient();
    void readyReadUDP();
    void newConnection();
    void zeropointer();
    void zeropointerXremote();

signals:
    void refreshUDPconnection(QHostAddress* sender, quint16* senderPort, QUdpSocket* udpSocket,int deviceID, int clientID,bool* loop);

private:
    QUdpSocket *udpSocket;
    VideoInput* input;
    QHostAddress sender;
    quint16 senderPort;
    QThread workerThread;
    int deviceID;
    int clientID;
    QTcpServer* server;
    QTcpSocket* tcpSocketClient;
    QTcpSocket* tcpSocketToXremote;
    bool byXremote;

};




#endif // VIDEOBACKEND_H


