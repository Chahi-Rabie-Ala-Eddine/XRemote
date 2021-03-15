#include "xremotenetwork.h"
#include "xremoteclientmanagement.h"

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

/*Compare sockets*/
bool operator==(QTcpSocket const& socketA, QTcpSocket const& socketB)
{

    if (socketA.peerAddress().toString().mid(7, socketA.peerAddress().toString().size() - 7).compare(socketB.peerAddress().toString().mid(7, socketB.peerAddress().toString().size() - 7)))
        return true;

    else
        return false;
}

/*Find the user related to this socket*/
client* retrieveClient(QList<client *> clients, QTcpSocket *socket){

    Q_FOREACH (client* clt, clients)
        if(clt->getClientSocket() == socket)
            return clt;

    return NULL;
}

