#ifndef FRONTENDAUDIO_H
#define FRONTENDAUDIO_H

#include <QtCore>
#include <QtNetwork>
#include "audiooutput.h"
#include "threadrefresh.h"


class FrontendAudio : public QObject
{
    Q_OBJECT
public:
    FrontendAudio( QObject *parent,int clientID,int deviceID, quint16 Localport,QString host,quint16 port,bool directIP);

    ~FrontendAudio();
    void sendReq(QString request);
    //void close();
    //void connectToHost(QString host, quint16 port);
    //bool isConnected();

    void startRecordMic();
    void startLiveStream();
    void startStreamFile(QString path);
    void pauseStreamFile();
    void stopStreamFile();
    void stopLiveStream();
    void stopRec();


private slots:
   // void readyRead();
    void readyReadTCP();
    void readyReadUDP();
    void zeropointer();
     signals:
     void eofAudio();
     void refreshUDPconnection(QHostAddress* sender, quint16* senderPort, QUdpSocket* udpSocket, int clientID, int deviceID, bool* loop);

private:
    QTcpSocket *tcpSocket;
    QUdpSocket* udpSocket;
    AudioOutput output;
    QThread workerThread;
    QHostAddress sender;
    quint16 senderPort;
    int clientID;
    int deviceID;
    bool refresh;
};

#endif // FRONTENDAUDIO_H

