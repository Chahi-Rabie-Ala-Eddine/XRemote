#ifndef STREAMVIDEO_H
#define STREAMVIDEO_H


#include <QtCore>
#include <QtNetwork>
//#include <QDateTime>
#include <QImage>
#include "threadrefresh.h"

class StreamVideo : public QObject
{
    Q_OBJECT
public:
    StreamVideo( QObject *parent,int clientID,int deviceID, quint16 Localport,QString host,quint16 port,bool directIP);
    ~StreamVideo();
    void startRecordCamera();
    void startLiveStream();
    void startStreamFile(QString path);
    void pauseStreamFile();
    void stopStreamFile();
    void stopLiveStream();
    void stopRec();
    void setLiveHD();
    void setLiveSD();
    void setFileHD();
    void setFileSD();

private :
    void sendReq(QString request);
    void decodeImage(QByteArray data, bool isLiveStream);


private slots:
    void readyReadUDP();
    void readyReadTCP();
    void zeropointer();
     signals:
     void eofVideo();
     void imageReceived(QImage image);
     void imageReceivedSFile(QImage image);
     void refreshUDPconnection(QHostAddress* sender, quint16* senderPort, QUdpSocket* udpSocket, int clientID, int deviceID, bool* loop);

private:
    QUdpSocket *udpSocket;
    QThread workerThread;
    QTcpSocket* tcpSocket;

    //QDateTime startTime;
    //QByteArray dataReceived;

    QHostAddress sender;
    quint16 senderPort;

    int clientID;
    int deviceID;


    bool refresh;

};

#endif // STREAMVIDEO_H


