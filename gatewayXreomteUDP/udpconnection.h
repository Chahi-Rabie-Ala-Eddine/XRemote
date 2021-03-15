#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include <QtNetwork>


class UDPConnection {
public:
    UDPConnection( int userID,int deviceID,bool isDevice, QHostAddress sender,quint16 senderPort);
    ~UDPConnection(){}
    int getDeviceID();
    int getClientID();
    bool IsDevice();
    QHostAddress getSender();
    quint16 getSenderPort();


private:
    int deviceID;
    int userID;
    bool isDevice;
    QHostAddress sender;
    quint16 senderPort;
};
#endif // UDPCONNECTION_H
