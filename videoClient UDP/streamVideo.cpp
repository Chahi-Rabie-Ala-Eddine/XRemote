#include "streamVideo.h"

StreamVideo::StreamVideo( QObject *parent,int clientID,int deviceID, quint16 Localport, QString host, quint16 port,bool directIP) : QObject(parent)
{
    this->clientID=clientID;
    this->deviceID=deviceID;
    sender=QHostAddress(host);
    senderPort=port;


    // to receive media data and maintain connection
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, Localport);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readyReadUDP()));
   // startTime=  QDateTime::currentDateTime();
   // thread for maintaining udp connections with device or xremoteServer
    ThreadRefresh *worker = new ThreadRefresh();
    worker->moveToThread(&workerThread);
    connect(this, SIGNAL(refreshUDPconnection(QHostAddress* , quint16* , QUdpSocket*,int,int,bool* )), worker, SLOT(refreshConnection(QHostAddress* , quint16* , QUdpSocket*,int,int,bool* )));
    workerThread.start();
    refresh=true;
    emit refreshUDPconnection(&sender, &senderPort, udpSocket, clientID,  deviceID,&refresh); //************* check when i have to put refresh = false or true


    // to send requests to device in direct ip or via Xremote server
    tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost(host, port);
    // tcpSocketToXremote->connectToHost("127.0.0.1", 19000);
    connect(tcpSocket, SIGNAL(readyRead()), this ,SLOT(readyReadTCP()));
    connect(tcpSocket, SIGNAL(disconnected()), tcpSocket, SLOT(deleteLater()));
    connect(tcpSocket, SIGNAL(destroyed()), SLOT(zeropointer()));

    //******************************* for xremote connection i have to send an ini request ??? it depends on ala implementation !!!
    if (!directIP){
        sendReq("init:"+QString::number(clientID)+":"+QString::number(deviceID)+":false");
    }

}


StreamVideo::~StreamVideo(){
    refresh=false; // can remove it
    workerThread.quit();
    workerThread.wait();
}

// read the received video data
// the Video data is sent to the loudspeaker
void StreamVideo::readyReadUDP()
{
    QByteArray data;
    data.resize(udpSocket->pendingDatagramSize());

    udpSocket->readDatagram(data.data(), data.size());


    if ( data.size()>4){ // minimum valid data size

                qDebug()<< " data size "<<data.size();
                // extract image data
                if(data.at(0)=='l' && data.at(1)=='i' && data.at(2)=='v' && data.at(3)=='e'&& data.at(4)=='V'){
                    data.remove(0,5);
                    decodeImage(data,true); // true if it is live stream "liveV"
                } else  if(data.at(0)=='f' && data.at(1)=='i' && data.at(2)=='l' && data.at(3)=='e'&& data.at(4)=='V'){
                    data.remove(0,5);
                    decodeImage(data,false); // false if it is file stream "fileV"
                }


    }
}
void StreamVideo::readyReadTCP(){
    QByteArray data;
    while (tcpSocket->bytesAvailable() > 0)
        data.append(tcpSocket->readLine());
    if(data=="eofVideo"){     //***************** this message i have to receive it from TCPSOCKET !!!
        qDebug()<<"EOF Video !!!";
        //VideoData=false;
        emit eofVideo();
    }
}

void StreamVideo::zeropointer()
{
    tcpSocket = 0;
}

void StreamVideo::decodeImage(QByteArray data, bool isLiveStream){
    QByteArray decryptedByte;
     qDebug()<<"loadImage"<<data.size();
     QByteArray uncompressByte=qUncompress(data);
     QImage image;
     image.loadFromData(uncompressByte);
/*
     // desplay received pictures each 2 milliseconds == 30 FPS
     //QDateTime now ;
     //qint64 millisecondsDiff =  0;
     bool boucle=true;
     while(boucle){
        //now = QDateTime::currentDateTime();
       // millisecondsDiff =  startTime.msecsTo(now);
        if(millisecondsDiff>2)
        {
            if (isLiveStream){
            emit imageReceived(image);
               }else{
            emit imageReceivedSFile(image);
            }
            boucle=false;
            startTime=QDateTime::currentDateTime();
        }
     }*/

     if (isLiveStream){
     emit imageReceived(image);
        }else{
     emit imageReceivedSFile(image);
     }
}


//***************** this function has to be modified and useTCP******************************!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// send a request to the device : request could be startA, startLA, recA, stopA, pauseA, stopLA .....
void StreamVideo::sendReq(QString request)
{
    QByteArray data(request.toUtf8());
    qDebug()<<data;
    if(tcpSocket){
        tcpSocket->write(data); // send data to the host , the host could be device or xRemote server
    }
}


void StreamVideo::startRecordCamera(){
    sendReq("recV");
}

void StreamVideo::startLiveStream(){
    sendReq("startLV");
}

void StreamVideo::startStreamFile(QString path){
    sendReq("startV?"+path);
}

void StreamVideo::pauseStreamFile(){
    sendReq("pauseV");
}

void StreamVideo::stopStreamFile(){
    sendReq("stopV");
}

void StreamVideo::stopLiveStream(){
    sendReq("stopLV");
}

void StreamVideo::stopRec(){
    sendReq("stopRV");
}

void StreamVideo::setLiveHD(){
    sendReq("setLiveHD");
}

void StreamVideo::setLiveSD(){
    sendReq("setLiveSD");
}

void StreamVideo::setFileHD(){
    sendReq("setFileHD");
}

void StreamVideo::setFileSD(){
    sendReq("setFileSD");
}
