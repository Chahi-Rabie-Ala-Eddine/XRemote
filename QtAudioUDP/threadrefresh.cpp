#include "threadrefresh.h"

ThreadRefresh::ThreadRefresh(){
}

void ThreadRefresh::refreshConnection( QHostAddress* sender, quint16* senderPort, QUdpSocket* udpSocket, int clientID, int deviceID,bool* loop) {
    // for direct ip connection i have to do something else !!
    qDebug()<< *sender;
    qDebug()<< *senderPort;
    QString request = "init:"+QString::number(clientID)+":"+QString::number(deviceID)+":false";
    while (true) {
        if(*loop){
            QByteArray data(request.toUtf8());
            qDebug()<< "data sent" <<udpSocket->writeDatagram(data.data(), *sender, *senderPort);
            sleep(2);
        }
    }
}


