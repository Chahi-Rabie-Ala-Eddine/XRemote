#include "udpconnection.h"

UDPConnection::UDPConnection(int userIDin,int deviceIDin,bool isDevicein, QHostAddress senderin,quint16 senderPortin)
{
    userID=userIDin;
    deviceID=deviceIDin;
    isDevice=isDevicein;
    sender=senderin;
    senderPort=senderPortin;

}

int UDPConnection::getDeviceID(){
    return deviceID;
}
int UDPConnection::getClientID(){
    return userID;
}
bool UDPConnection::IsDevice(){
    return isDevice;
}
QHostAddress UDPConnection::getSender(){
    return sender;
}
quint16 UDPConnection::getSenderPort(){
    return senderPort;
}


