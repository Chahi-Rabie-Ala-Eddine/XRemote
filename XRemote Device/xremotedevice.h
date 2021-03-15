#ifndef XREMOTEDEVICE_H
#define XREMOTEDEVICE_H

#include <QtNetwork>
#include <QWidget>

class xremotedevice : public QWidget{

    public:
    xremotedevice();
    QTcpSocket* _GetSocket();
    void _SetSocket();

    private:
    QTcpSocket* socket;
};

#endif // XREMOTEDEVICE_H
