#include "xremoteserver.h"
#include "xremoteconstants.h"
#include "xremotelog.h"
#include "xremoteclientmanagement.h"
#include "xremotenetwork.h"
#include "xremotedbmanagement.h"
#include "xremoterpspprotocol.h"

/*Server constructor*/
xremoteserver::xremoteserver(){

    /*Lunch Managment*/
    server = new QTcpServer(this);
    this->_LaunchServer(server);

    /*Connect to Database*/
    _ConnectServerToDatabase("./XRemoteDb");
}

/*Destructor*/
xremoteserver::~xremoteserver(){

    delete this;
}

/*Launch server*/
void xremoteserver::_LaunchServer(QTcpServer *server){

    if (!this->server->listen(QHostAddress::Any, _ServerPORT)){

        /*If the port is already in use */
        if((string)"The bound address is already in use" == this->server->errorString().toStdString().c_str()){
            this->state = tr(portErrorMsg);
        }
        else{
            this->state = QString("Error : " + this->server->errorString());
        }
    }else {
        /*If the server starts up smoothly, we then create a window with the different components*/
        this->state =_ServerStateLog(server);
        connect(this->server, SIGNAL(newConnection()), this, SLOT(_NewConnectionToServer()));
    }
}

/*Connect server to database*/
void xremoteserver::_ConnectServerToDatabase(const char* databaseName){

    _DBConnection(databaseName);
}

/*Manage client connection*/
void xremoteserver::_NewConnectionToServer(){

    /*Create and assign the socket to the new client*/
    QTcpSocket *socket = server->nextPendingConnection();
    client* newClient = new client(socket);

    /*Add the new client to clients list*/
    clients << newClient;

    /*Retrieve the client's port and addres*/
    newClient->getClientSocket()->peerAddress();

    /*Write process to logs*/
    log = connectionLog(newClient->getClientSocket());
    emit _NewLog();
    emit _NewHostsNumber();
    //writeLog(connectionLog(client));

    /*Connect client's socket to RPS manager*/
    connect(newClient->getClientSocket(), SIGNAL(readyRead()), this, SLOT(_PacketManagement()));

    /*Connect client's socket in order to disconnect it throw socket's deletion*/
    connect(newClient->getClientSocket(), SIGNAL(disconnected()), this, SLOT(_DeleteClientSocket()));

    /*Say to clients that a new client is connected*/
    string str = newClient->getClientId().toUtf8().constData();
    str+= " is connected now !";
    _RPSPBroadcast(tr(str.c_str()), clients);
}

/*Sign out client and delete its socket*/
void xremoteserver::_DeleteClientSocket(){

    /*Find the sender socket*/
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());

    /*If we dont find this socket*/
    if (socket == 0)
        return;

    /*Find the user related to this socket*/
    client* cli = retrieveClient(clients, socket);

    /*Say to clients that a user is signing out*/
    string str = cli->getClientId().toUtf8().constData();
    str+= " is signing out now !";
    _RPSPBroadcast(tr(str.c_str()), clients);

    /*Delete both user and socket*/
    if(cli != NULL){

        log = disconnectionLog(socket);
        cli->getClientSocket()->deleteLater();
        clients.removeOne(cli);
        emit _NewLog();
        emit _NewHostsNumber();
    }

    else{
        return;
    }
}

/*Manage TCP packets / sub-packets*/
void xremoteserver::_PacketManagement(){

    /*RECIEVING PACKETS*/

    /*Identify QTcpSocket client : Who's sending ?*/
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());

    /* If the server cannont find who is sending the packets or sub-packets */
    if (socket == 0)
        return;

    /*Find the user related to this socket*/
    client* cli = retrieveClient(clients, socket);
    quint16 packetSize = cli->_getClientSizeOfPacket();

    /*Once we know who's sending, we create a data streamer to capture packet*/
    QDataStream networkBuffer(socket);

    /*If we don't know packet size, we check if we received enough data to catch it*/
    if (packetSize == 0){

        /*We didn't catch packet size*/
        if (socket->bytesAvailable() < (int)sizeof(_16Bits))
             return;

        /*Catch packet size*/
        networkBuffer >> packetSize;
        cli->_setClientSizeOfPacket(packetSize);
    }

    /*If we know the message size, check if we recieved the entier message, if not go out and wait for new call*/
    if (socket->bytesAvailable() < packetSize)
        return;

    /*Catch packet and convert it into a QString object */
    QString request;
    networkBuffer >> request;




    /*PARSE RPSP PACKET*/

        /*REDIRECT PACKET*/

        /*MANAGE PACKET*/


    /*PRINT THE MESSAGE*/
    log = request;
    emit _NewLog();

    /*BROADCAST THE MESSAGE*/
    _RPSPBroadcast(request, clients);

    /*Reinit paquet size*/
    cli->_setClientSizeOfPacket(0);
}

/*Get pointer to Server*/
QTcpServer* xremoteserver::_GetServer(){

    return this->server;
}

/*Get Server's State*/
QString xremoteserver::_GetServerState(){

    return this->state;
}

/*Get Server's log*/
QString xremoteserver::_GetServerLog(){

    return this->log;
}

/*Get Server's log*/
int xremoteserver::_GetNumberOfConnectedHosts(){

    return (int)this->clients.size();
}

/*Set tcp server propreties*/
void xremoteserver::_SetServer(){

    server = new QTcpServer(this);
    _LaunchServer(server);
}
