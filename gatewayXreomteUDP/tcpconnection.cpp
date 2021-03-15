#include "tcpconnection.h"


TCPConnection::TCPConnection()
{
    socket=new QTcpSocket();
    userID=0;
    deviceID=0;
    isDevice=false;
    isInitialized=false;

}

// create the socket and connect to signals
void TCPConnection::setSocket(QTcpSocket* newSocket){
    socket=newSocket;
    qDebug()<<" set socket";
    connect(socket, SIGNAL(readyRead()),this ,SLOT(readyRead()));
    //if there is a core dumped error , it could be caused by these two next signals
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
    connect(socket, SIGNAL(destroyed()), SLOT(zeropointer()));
}

/*
QTcpSocket* TCPConnection::getSocket(){
    return(socket);
}*/
bool TCPConnection::IsDevice(){
    return(isDevice);
}

int TCPConnection::getDeviceID(){
    return deviceID;
}
int TCPConnection::getClientID(){
    return userID;
}

// read the incoming data
// first incoming data must be an init request
// the next incoming data are sent to the client/device mentioned in the init request
void TCPConnection::readyRead()
{
    QByteArray data;
    while (socket->bytesAvailable() > 0)
        data.append(socket->readAll());

    if(!isInitialized){ // first request must be a init request ; init:userID:deviceID:true/false(is it a device):[request] the [request] is optional
        QString request = QString::fromStdString(data.data());
        QStringList elements = request.split(':');
        if(elements.at(0) == "init"){
             userID=elements.at(1).toInt();
            deviceID=elements.at(2).toInt();
            if(elements.at(3)=="true"){
                isDevice=true;
                qDebug()<<deviceID;
            }
           /* else{
                //qDebug()<< "send to device "<< deviceID <<" data : "<<elements.at(4).toUtf8();
                emit sigSendToDevice(deviceID,elements.at(4).toUtf8());
            }*/
            isInitialized=true;
            emit sigRemoveDuplicateConnection(userID, deviceID, isDevice);
        }else qDebug()<<"error parsing must be an init request but we have "<< data;
    } else { // not an initializing request
        if(isDevice){
            qDebug()<< "send to client "<< data;
            emit sigSendToClient(userID,data);
        }else{
            qDebug()<< "send to device "<< deviceID <<" data : "<<data;
            emit sigSendToDevice(deviceID,data);
        }
    }
}

// send data to the device/client which sent the init request
void TCPConnection::writeData(QByteArray data)
{
    if (socket)
        socket->write(data,data.size());
}

// for writeData function to test if the socket exists ( avoid core dumped error )
void TCPConnection::zeropointer()
{
    socket = 0;
}

