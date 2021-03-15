#include "xremotedevice.h"

xremotedevice::xremotedevice() : QWidget(){

    this->socket = new QTcpSocket(this);

}

QTcpSocket* _GetSocket(){

   // return this->socket;
}

void _SetSocket(){

}
