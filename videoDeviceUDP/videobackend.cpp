#include "videobackend.h"
#include<iostream>
#include "threadRefreshUDP.h"

//QString serverIP ="35.181.45.215";
QString serverIP ="127.0.0.1";
int serverPort=12300;

// create an VideoInput object to stream Video from Mics/Video File
// create a QTcpServer to accept incomming TCP connexions
// connect to xremote server
// after connecting to xremote, it it accepts a incoming connection ( direct ip ), it will broke the connection with xremote
// to run a new connextion with xremote server, you have to call to switchToXremote() function, it is a slot function

VideoBackend::VideoBackend(quint16 port, QString pathDirectory,int deviceID, int clientID)
{
    this->deviceID = deviceID;
    this->clientID= clientID;
    byXremote=false; // this variable tell us if we are gonna stream over xremote server or over a direct ip



    // create a VideoInput object to stream Video from Mics/Video File
    input = new VideoInput(this, pathDirectory);
    // send data from input to client over TCP socket
    connect(input, SIGNAL(dataReady(QByteArray)), this, SLOT(writeDataTCP(QByteArray)));
    connect(input, SIGNAL(dataReadyStream(QByteArray)), this, SLOT(writeDataUDP(QByteArray)));



    // create a socket to send  UDP data for streaming and receive init packets from client
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, port);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readyReadUDP()));

    //create qtcpSOCKET for direct ip ....... here i can got many incoming tcp connexions but i need only one :/ !!!!!!!!!!!!!!!!!!
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), SLOT(newConnection()));
    server->listen(QHostAddress::AnyIPv4, port);
    tcpSocketClient = new QTcpSocket(this);

    // create a qtcpSocket for comunication with xremote server ***************** si la co tombe je dois prendre en compte cette aspect ???
    // this sockets receive requests from xremote and send eofVideo packet to Xremote
    tcpSocketToXremote = new QTcpSocket(this);
    tcpSocketToXremote->connectToHost(serverIP, serverPort);
    connect(tcpSocketToXremote, SIGNAL(readyRead()), this ,SLOT(readyReadTcpXremote()));
    connect(tcpSocketToXremote, SIGNAL(disconnected()), tcpSocketToXremote, SLOT(deleteLater()));
    connect(tcpSocketToXremote, SIGNAL(destroyed()), SLOT(zeropointerXremote()));

    // init connexion for xremote server to allow the xremote server to contact the device ........ change it with ala implementation **************************

    QString request= "init:"+QString::number(clientID)+":"+QString::number(deviceID)+":true";
    QByteArray data(request.toUtf8());
    tcpSocketToXremote->write(data,data.size());


    //  if we send requests with tcp we don't need to maintain udp connexion with xremote server  ************* TO BE REMOVED
    // BUT CONNEXION MUST BE MAINTAINED WITH TCP
    // connect to xremote server
    switchToXremote();

}

VideoBackend::~VideoBackend() {
       workerThread.quit();
       workerThread.wait();
   }

void VideoBackend::switchToXremote(){
    ThreadRefresh *worker = new ThreadRefresh();
    worker->moveToThread(&workerThread);
    //connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, SIGNAL(refreshUDPconnection(QHostAddress* , quint16* , QUdpSocket*,int,int,bool* )), worker, SLOT(refreshConnection(QHostAddress* , quint16* , QUdpSocket*,int,int,bool* )));
    workerThread.start();

    sender=QHostAddress(serverIP);
    senderPort=serverPort;
    emit refreshUDPconnection(&sender, &senderPort, udpSocket,deviceID,clientID,&byXremote);
}

// it is called when a new incoming connection is opened ( direct ip communication )
void VideoBackend::newConnection()
{
    tcpSocketClient = server->nextPendingConnection();
    connect(tcpSocketClient, SIGNAL(readyRead()), SLOT(readyReadTcpClient()));
    connect(tcpSocketClient, SIGNAL(disconnected()), tcpSocketClient, SLOT(deleteLater()));
    connect(tcpSocketClient, SIGNAL(destroyed()), SLOT(zeropointer()));
}

// for writeData function to test if the socket exists ( avoid core dumped error )
void VideoBackend::zeropointer()
{
    tcpSocketClient = 0;
}
void VideoBackend::zeropointerXremote()
{
    tcpSocketToXremote = 0;
}


void VideoBackend::readyReadTcpClient()
{
    byXremote=false;
    QByteArray data;
    while (tcpSocketClient->bytesAvailable() > 0)
        data.append(tcpSocketClient->readLine());
    parser(data);
}
void VideoBackend::readyReadTcpXremote()
{
    /*if (byXremote==false){ // initialisation de byXremote ,,
        // send init requests by UDP!
    }*/
    byXremote=true;
    qDebug()<<"readyRead TCP Xremote !!";
    QByteArray data;
    while (tcpSocketToXremote->bytesAvailable() > 0)
        data.append(tcpSocketToXremote->readLine());
    parser(data);
}
// read the incoming data and parse the requests
// this function will be ONLY used when client maintain a UDP connexion ****************************** SOMETHING TO CHECK INSIDE !!!!
void VideoBackend::readyReadUDP()
{
    QByteArray data;
   data.resize(udpSocket->pendingDatagramSize());
   QHostAddress senderCopy;
   quint16 senderPortCopy;
   udpSocket->readDatagram(data.data(), data.size(), &senderCopy, &senderPortCopy);
   // check if it is an init request from client !! befor to change sender and senderPort values !!
   sender=senderCopy;
   senderPort=senderPortCopy;

// parser(data);
}


void VideoBackend::parser( QByteArray data){
    std::string request= data.toStdString();
      qDebug()<<QString(request.data());
    std::string delimiter = "?";
    std::string action = request.substr(0, request.find(delimiter));
    std::cout<<action<<std::endl;
    if (action=="startV") {
        QString path = request.substr(request.find(delimiter)+1, request.size()).data();
        input->streamFile(path);
    }else if (action=="startLV"){
        input->startLiveStream();
    }else if (action=="stopLV"){
        input->stopLiveStream();
    }else if (action=="stopV"){
        input->stopStream();
    }else if (action=="pauseV"){
        input->pauseStream();
    }else if (action=="recV"){
        input->saveCamera();
    }
    else if (action=="stopRV"){
            input->stopRec();
    } else if (action=="setLiveHD"){
        input->setLiveHD();
    } else if (action=="setLiveSD"){
        input->setLiveSD();
    } else if (action=="setFileHD"){
    input->setFileHD();
    } else if (action=="setFileSD"){
        input->setFileSD();
    }


}


// send data to client/xRemote .... the last who sends data ........ UNCORRECT !!!!
void VideoBackend::writeDataUDP(QByteArray data)
{
   if (byXremote){
       sender=QHostAddress(serverIP);
       senderPort=serverPort;
   } // else the sender values are setted in readyReadUDP()
   qDebug() << "sending to "<< sender;
   qDebug()<< "data sent" <<udpSocket->writeDatagram(data, sender, senderPort);
}
// send data to client
void VideoBackend::writeDataTCP(QByteArray data)
{
    qDebug()<<data.size();
    qDebug()<<byXremote;
    if (byXremote){
        if (tcpSocketToXremote){
            qDebug()<< "Via Xremote : data sent" <<tcpSocketToXremote->write(data,data.size());
        }
    }
    else {
        if (tcpSocketClient){
            qDebug()<< "Direct ip : data sent" <<tcpSocketClient->write(data,data.size());
        }
    }
}
