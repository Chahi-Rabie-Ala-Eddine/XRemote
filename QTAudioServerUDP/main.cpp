#include "BackendAudio.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString pathDirectory="/home/kali/xremote/audio/";
    quint16 port = 15001;
    int deviceID = 145;
    int clientID = 122;
    BackendAudio* backAudio = new BackendAudio(port,pathDirectory,deviceID,clientID);

    return a.exec();
}
