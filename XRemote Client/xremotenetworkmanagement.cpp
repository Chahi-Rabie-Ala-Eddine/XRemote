#include "xremotenetworkmanagement.h"

#include <QTranslator>

using namespace std;

/*Get source ip Address*/
QString getHostIPAddress(QTcpSocket *host){

   return host->peerAddress().toString().mid(7, host->peerAddress().toString().size() - 7);
}

/*Get source Port*/
QString getHostPORTAddress(QTcpSocket *host){

   return QString::number(host->peerPort());
}

/*Get country location from ip Address*/
QString getLocalizationFromIP(QTcpSocket *host) {

    string ipAddr = host->peerAddress().toString().toUtf8().constData(), command = "", result = "";
    char buffer[128];

    if(ipAddr.compare("127.0.0.1") != 0)
        return QString::fromStdString(" local position (France)");

    command+= "python3 locate.py " + ipAddr;

    FILE* pipe = popen(command.c_str(), "r");

    if(!pipe)
       return "Cannot retrieve country [System error] !";

    while(!feof(pipe))
       if(fgets(buffer, 128, pipe) != NULL)
          result += buffer;

    pclose(pipe);

    return QString::fromStdString(result);
}

/*Connect to XRemote server*/
void _ConnectHostToXremote(QTcpSocket* socket, _String hostAddr, unsigned int port){

    /*Make sure that socket is not used*/
    socket->abort();

    /*Connect to server*/
    socket->connectToHost(hostAddr, port);

    /*switch(_error) // On affiche un message différent selon l'erreur qu'on nous indique
    {
        case QAbstractSocket::HostNotFoundError:
            ui->textEdit_3->append(tr("<em>Error : Server not found. Check out Ip and port.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            ui->textEdit_3->append(tr("<em>Error : Connection refused ! Check out Ip and port.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            ui->textEdit_3->append(tr("<em>Error : Server disconnected.</em>"));
            break;
        default:
            ui->textEdit_3->append(tr("<em>Error : ") + this->socket->errorString() + tr("</em>"));
    }*/
}

/*Send credientials to server*/
void _SendCredentials(QTcpSocket* socket, QString email, QString password){

    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    /*Paquet preparation*/
    QString request = QString("Mail : ") + email + QString(" Password : ") + password;

    /*Paquet configuration*/
    out << (quint16) 0;
    out << request;
    out.device()->seek(0);
    out << (quint16) (packet.size() - sizeof(quint16));

    /*Send request*/
    socket->write(packet);
}

