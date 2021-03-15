#include "udpgateway.h"
#include<iostream>

int initSizeRequest(100);
// create QUDP sockets ; one to send and receive data from client ; an other one to receive data from device
udpGateway::udpGateway(quint16 port)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::AnyIPv4, port);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

// for each new connection , we create a connection object which hold the connection socket, user id , device id ...
void udpGateway::readPendingDatagrams()
{

    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
     qDebug() << "Message from: " << sender.toString();
     qDebug() << "Message port: " << senderPort;
    // qDebug() << "Message: " << buffer;

    if (buffer.size()<initSizeRequest){
        bool isDevice = false;
        QString request = QString::fromStdString(buffer.data());
        QStringList elements = request.split(':');
        if(elements.at(0) == "init"){
            int userID=elements.at(1).toInt();
            int deviceID=elements.at(2).toInt();
            if(elements.at(3)=="true"){
                isDevice=true;
            }
            UDPConnection* newCon = new UDPConnection(userID,deviceID,isDevice,sender,senderPort);
            connectionList.append(newCon);
            removeDuplicateConnection(userID, deviceID, isDevice);
        }
   }else { // not an initializing request
    UDPConnection* conn= mapConncetion(sender,senderPort);
    if(conn != nullptr){
    qDebug()<<" data sent : "<<socket->writeDatagram(buffer, conn->getSender(), conn->getSenderPort());
    }
    }
 }

UDPConnection* udpGateway::mapConncetion(QHostAddress sender,quint16 senderPort){
    UDPConnection *sourceConn;
    UDPConnection *destinationConn;

    int i(0);
    bool loop=true;
    while(i<connectionList.size() && loop ){
     if(connectionList.at(i)->getSender()==sender && connectionList.at(i)->getSenderPort()==senderPort){
         qDebug()<<" connection sender found ";
         sourceConn = connectionList.at(i);
         loop=false;
     }
     i++;
    }

    if (loop==true){
        qDebug()<<"source not found";
        return nullptr;
    }


    i=0;
    loop=true;
    while(i<connectionList.size() && loop ){
     if(connectionList.at(i)->getClientID()==sourceConn->getClientID() &&
             connectionList.at(i)->getDeviceID()==sourceConn->getDeviceID() &&
             connectionList.at(i)->IsDevice()!= sourceConn->IsDevice()){
         qDebug()<<" connection destination found ";
         destinationConn = connectionList.at(i);
         loop=false;
     }
     i++;
    }
    if (loop==true){
        qDebug()<<"destination not found";
        return nullptr;
    }else{
    return destinationConn;
    }
}

// remove duplicate connections , ( two sockets used frome the same device or client )
// we remove the old connection
void udpGateway::removeDuplicateConnection(int userID, int deviceID, bool isDevice){
   int i(0);
   int index(-1);
   while(i<connectionList.size()){
    if(connectionList.at(i)->getClientID()==userID && (connectionList.at(i)->IsDevice()==isDevice) &&  connectionList.at(i)->getDeviceID()==deviceID ){
        if (index != -1){
            connectionList.removeAt(index);
        }
        index=i;
    }
    i++;
   }

}
