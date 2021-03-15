#include "videobackend.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    quint16 port = 15002;
    QString pathDirectory="/home/kali/xremote/video/";
    int deviceID = 145;
    int clientID = 122;
    VideoBackend* backVideo = new VideoBackend(port,pathDirectory,deviceID,clientID);

    return a.exec();
}
