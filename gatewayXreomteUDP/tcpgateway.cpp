#include "tcpgateway.h"
#include<iostream>

// create a QTcpServer to accept incomming TCP connetions
TcpGateway::TcpGateway(quint16 port)
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), SLOT(newConnection()));
    server->listen(QHostAddress::Any, port);

}

// for each new connection , we create a connection object which hold the connection socket, user id , device id ...
void TcpGateway::newConnection()
{
    qDebug()<<" new connextion";
    TCPConnection* newCon= new TCPConnection();
    socketList.append(newCon);
    newCon->setSocket (server->nextPendingConnection()) ;
    connect(newCon, SIGNAL(sigSendToClient(int,QByteArray)),this, SLOT(searchClient(int,QByteArray)));
    connect(newCon, SIGNAL(sigSendToDevice(int,QByteArray)),this, SLOT(searchDevice(int,QByteArray)));
    connect(newCon, SIGNAL(sigRemoveDuplicateConnection(int , int , bool )
),this, SLOT(removeDuplicateConnection(int , int , bool )
));
}

// search the connection object related to the device id , and send the data ( from client connection object ) to this device
void TcpGateway::searchDevice(int id,QByteArray data){
   qDebug()<<" searching device id " + QString(id);
   int i(0);
   bool loop=true;
   while(i<socketList.size() && loop ){
    if(socketList.at(i)->getDeviceID()==id and socketList.at(i)->IsDevice()){
        qDebug()<<" device found ";
        socketList.at(i)->writeData(data);
        loop=false;
    }
    i++;
   }

}


// search the connection object related to the client id , and send the data ( from device connection object ) to this client
void TcpGateway::searchClient(int id,QByteArray data){
   int i(0);
   bool loop=true;
   while(i<socketList.size() && loop ){
    if(socketList.at(i)->getClientID()==id && (!socketList.at(i)->IsDevice()) ){
        //qDebug()<<"client found ";
        try {
            socketList.at(i)->writeData(data);
            loop=false;
        }  catch (std::exception &e) {
            qDebug()<<"Connexion interrompue";
        }

    }
    i++;
   }

}

// remove duplicate connections , ( two sockets used frome the same device or client )
// we remove the old connections
void TcpGateway::removeDuplicateConnection(int userID, int deviceID, bool isDevice){
   int i(0);
   int index(-1);
   while(i<socketList.size()){
    if(socketList.at(i)->getClientID()==userID && (socketList.at(i)->IsDevice()==isDevice) &&  socketList.at(i)->getDeviceID()==deviceID ){
        if (index != -1){
            socketList.removeAt(index);
            //qDebug()<<"Remove duplicate";
        }
        index=i;
    }
    i++;
   }

}
