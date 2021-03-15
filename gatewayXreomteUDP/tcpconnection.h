#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QtNetwork>
#include <QObject>


class TCPConnection: public QObject
{
    Q_OBJECT
public:
    TCPConnection();
    ~TCPConnection(){}
    int getDeviceID();
    int getClientID();
    void setSocket(QTcpSocket* newSocket);
    bool IsDevice();


signals:
    void sigSendToClient(int id,QByteArray data);
    void sigSendToDevice(int id,QByteArray data);
    void sigRemoveDuplicateConnection(int userID, int deviceID, bool isDevice);

public slots:
    void writeData(QByteArray data);
    void readyRead();
    void zeropointer();



private:
    QTcpSocket *socket;
    int deviceID;
    int userID;
    bool isDevice;
    bool isInitialized;
};

#endif // TCPCONNECTION_H
