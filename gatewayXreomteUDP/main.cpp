#include <QCoreApplication>
#include "udpgateway.h"
#include "tcpgateway.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    udpGateway* passerelleUDPVideo= new udpGateway(12300);
    TcpGateway* passerelleTCPVideo= new TcpGateway(12300);
    udpGateway* passerelleUDPAudio= new udpGateway(12301);
    TcpGateway* passerelleTCPAudio= new TcpGateway(12301);


    return a.exec();
}
