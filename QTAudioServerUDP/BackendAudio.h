#ifndef BACKENDAUDIO_H
#define BACKENDAUDIO_H

#include <QtCore>
#include <QtNetwork>
#include "audioinput.h"
#include "threadrefresh.h"

class BackendAudio : public QObject
{
    Q_OBJECT
public:
    BackendAudio(quint16 port, QString pathDirectory,int deviceID, int clientID);
    ~BackendAudio();
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
    QHostAddress sender;
    quint16 senderPort;
    QThread workerThread;
    int deviceID;
    int clientID;
    QTcpServer* server;
    QTcpSocket* tcpSocketClient;
    QTcpSocket* tcpSocketToXremote;
    bool byXremote;

    AudioInput* input;
};

#endif // BACKENDAUDIO_H
