#include "FrontendAudio.h"

FrontendAudio::FrontendAudio( QObject *parent,int clientID,int deviceID, quint16 Localport, QString host, quint16 port,bool directIP) : QObject(parent)
{
    this->clientID=clientID;
    this->deviceID=deviceID;
    sender=QHostAddress(host);
    senderPort=port;


    // to receive media data and maintain connection
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, Localport);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readyReadUDP()));

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




FrontendAudio::~FrontendAudio(){
    //refresh=false;
    workerThread.quit();
    workerThread.wait();
}



/*
// open a connection to host with the socket
void FrontendAudio::connectToHost(QString host, quint16 port) {
    socket->connectToHost(host, port);
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
}

// read the received data : the received data could be audio data or "eofAudio" message
// the audio data is sent to the loudspeaker
// the "eofAudio" emit a signal to change the GUI , it is sent from the device when the stream finishes
void FrontendAudio::readyRead()
{
    QByteArray data;
    while (socket->bytesAvailable() > 0)
        data.append(socket->readAll()); 
    //qDebug()<<data;
     bool audioData(true);
     int i(0);
     // check if we have received the "eofAudio" message
     while(audioData && i<data.size()){
         if(data.at(i)=='e' && data.at(i+1)=='o' && data.at(i+2)=='f' && data.at(i+3)=='A'  && data.at(i+4)=='u'
                && data.at(i+5)=='d' && data.at(i+6)=='i' && data.at(i+7)=='o'  ){
             qDebug()<<"EOF Audio !!!";
             audioData=false;
             emit eofAudio();
         }
         i++;
     }
    // audioData equal true means the previous check failed and then we have received audio data
    // send the audio data to the loudspeaker
    if(audioData){
    output.writeData(data);
    }
}*/


void FrontendAudio::readyReadTCP(){
    QByteArray data;
    while (tcpSocket->bytesAvailable() > 0)
        data.append(tcpSocket->readLine());
    if(data=="eofAudio"){
        emit eofAudio();
    }
}

void FrontendAudio::readyReadUDP()
{
    QByteArray data;
    data.resize(udpSocket->pendingDatagramSize());
    udpSocket->readDatagram(data.data(), data.size());
    if ( data.size()>4){ // minimum valid data size
                // check it it is an audio packet streamA
                if(data.at(0)=='s' && data.at(1)=='t' && data.at(2)=='r' && data.at(3)=='e'&& data.at(4)=='a'&& data.at(5)=='m'&& data.at(6)=='A'){
                    data.remove(0,7);
                    output.writeData(data);
                }
    }
}

/*
// send a request to the device : request could be startA, startLA, recA, stopA, pauseA, stopLA .....
void FrontendAudio::sendReq(QString request)
{
   // qDebug()<<request.toUtf8();
    QByteArray data(request.toUtf8());
   // qDebug()<<data;
    if (socket->state()!=QTcpSocket::ConnectedState){ // if the socket is not already connected
        socket->waitForConnected(3000); // we wait the socket to be in connected state
    }
    socket->write(data,data.size()); // send data to the host , the host could be device or xRemote server

}


// disconnect from the host
void FrontendAudio::close()
{
    socket->disconnectFromHost();
}

// check if the socket is connected to the server host
bool FrontendAudio::isConnected(){
        return (socket->state() == QTcpSocket::ConnectedState);
}
*/

void FrontendAudio::zeropointer()
{
    tcpSocket = 0;
}

// send a request to the device : request could be startA, startLA, recA, stopA, pauseA, stopLA .....
void FrontendAudio::sendReq(QString request)
{
    QByteArray data(request.toUtf8());
    qDebug()<<data;
    if(tcpSocket){
        tcpSocket->write(data); // send data to the host , the host could be device or xRemote server
    }
}


void FrontendAudio::startRecordMic(){
    sendReq("recA");
}

void FrontendAudio::startLiveStream(){
    sendReq("startLA");
}

void FrontendAudio::startStreamFile(QString path){
    sendReq("startA?"+path);
}

void FrontendAudio::pauseStreamFile(){
    sendReq("pauseA");
}

void FrontendAudio::stopStreamFile(){
    sendReq("stopA");
}

void FrontendAudio::stopLiveStream(){
    sendReq("stopLA");
}

void FrontendAudio::stopRec(){
    sendReq("stopRA");
}
