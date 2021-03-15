#include "mainwindow.h"
#include "unistd.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //****************************************************************************
    //*****************************************************************************
    //*****************************************************************************

    // au moment de choisir une device on cree l'objet
    // si la device change d'@ ip il faut detruire l'objet et recreer un nouveau avec la bonne valeur host/port
    // this part you have to call it as a slot and don't forget an other slot to destruct streamVideo object !!
    // slot function(int clientID, int deviceID, QString host,quint16 port,quint16 localport=14525)

    int clientID=122;
    int deviceID=145;

     QString host;
     quint16 port;
     quint16 localport=14525; // choose a random port to bind on it an udp socket

    bool directIP = false;
    if (directIP){ // direct ip
         host = "127.0.0.1"; // ip address of device
         port = 15002; // UDP video port in the device
    }else{
        //QString host = "35.181.45.215"; // ip address of xremote server
         host = "127.0.0.1";
         port = 12300; // Xreomte UDP video port
    }

    streamVideo = new StreamVideo(this,clientID,deviceID,localport,host,port,directIP);
    connect(streamVideo,SIGNAL(eofVideo()),this,SLOT(endOfVideo())); // when the stream is finished the signal is emited end the gui will be updated
    connect(streamVideo,SIGNAL(imageReceived(QImage)),this,SLOT( displayImage(QImage)));
    connect(streamVideo,SIGNAL(imageReceivedSFile(QImage)),this,SLOT( displayImageSFile(QImage)));

    //****************************************************************************
    //*****************************************************************************
    //*****************************************************************************




    setFixedSize(1280,1900);


    boutonRecordVideo = new QPushButton("Record Video", this);
    boutonRecordVideo->move(50, 50);
    connect(boutonRecordVideo,SIGNAL(clicked()),this,SLOT(recordVideo()));

    boutonRecordVideoStop = new QPushButton("Stop record", this);
    boutonRecordVideoStop->move(250, 50);
    connect(boutonRecordVideoStop,SIGNAL(clicked()),this,SLOT(stopRec()));
    boutonRecordVideoStop->setEnabled(false);

    boutonLiveVideoStream = new QPushButton("Play Live Video", this);
    boutonLiveVideoStream->move(50, 200);
    connect(boutonLiveVideoStream,SIGNAL(clicked()),this,SLOT(startLiveVideo()));


    boutonVideoStream = new QPushButton("Play Video", this);
    boutonVideoStream->move(50, 400);
    connect(boutonVideoStream,SIGNAL(clicked()),this,SLOT(startVideo()));


    boutonVideoStreamPause = new QPushButton("Pause Video", this);
    boutonVideoStreamPause->move(250, 400);
    connect(boutonVideoStreamPause,SIGNAL(clicked()),this,SLOT(pauseVideo()));
    boutonVideoStreamPause->setEnabled(false);

    boutonLiveVideoStreamStop = new QPushButton("Stop Live Video", this);
    boutonLiveVideoStreamStop->move(350, 200);
    connect(boutonLiveVideoStreamStop,SIGNAL(clicked()),this,SLOT(stopLiveVideo()));
    boutonLiveVideoStreamStop->setEnabled(false);

    boutonVideoStreamStop = new QPushButton("Stop Video", this);
    boutonVideoStreamStop->move(450, 400);
    connect(boutonVideoStreamStop,SIGNAL(clicked()),this,SLOT(stopVideo()));
    boutonVideoStreamStop->setEnabled(false);

    boutonSetHD = new QPushButton("Set HD", this);
    boutonSetHD->move(0, 500);
    connect(boutonSetHD,SIGNAL(clicked()),this,SLOT(setLiveHD()));
    boutonSetHD->setEnabled(true);

    boutonSetSD = new QPushButton("Set SD", this);
    boutonSetSD->move(100, 500);
    connect(boutonSetSD,SIGNAL(clicked()),this,SLOT(setLiveSD()));
    boutonSetSD->setEnabled(false);

    boutonSetFileHD = new QPushButton("Set HD", this);
    boutonSetFileHD->move(300, 500);
    connect(boutonSetFileHD,SIGNAL(clicked()),this,SLOT(setFileHD()));
    boutonSetFileHD->setEnabled(true);

    boutonSetFileSD = new QPushButton("Set SD", this);
    boutonSetFileSD->move(400, 500);
    connect(boutonSetFileSD,SIGNAL(clicked()),this,SLOT(setFileSD()));
    boutonSetFileSD->setEnabled(false);

    mylabel = new QLabel(this);
    mylabel->move(500,0);

    mylabelStreamFile= new QLabel(this);
    mylabelStreamFile->move(500,300);

}

MainWindow::~MainWindow()
{

}

// update the gui whe the stream is finished
void MainWindow::endOfVideo(){
    boutonVideoStream->setEnabled(true);
    boutonVideoStreamStop->setEnabled(false);
    boutonVideoStreamPause->setEnabled(false);
}

void MainWindow::setLiveHD(){
    streamVideo->setLiveHD();
    boutonSetHD->setEnabled(false);
    boutonSetSD->setEnabled(true);

}

void MainWindow::setLiveSD(){
    streamVideo->setLiveSD();
    boutonSetSD->setEnabled(false);
    boutonSetHD->setEnabled(true);

}
void MainWindow::setFileHD(){
    streamVideo->setFileHD();
    boutonSetFileHD->setEnabled(false);
    boutonSetFileSD->setEnabled(true);

}

void MainWindow::setFileSD(){
    streamVideo->setFileSD();
    boutonSetFileSD->setEnabled(false);
    boutonSetFileHD->setEnabled(true);

}

// stop recording Video in the device ( by recording i mean saving the microphone inputs in the device )
void MainWindow::stopRec(){

    streamVideo->stopRec();

    boutonRecordVideoStop->setEnabled(false);
    boutonRecordVideo->setEnabled(true);

}

// start recording Video in the device ( by recording i mean saving the microphone inputs in the device )
void MainWindow::recordVideo(){

    streamVideo->startRecordCamera();

    boutonRecordVideoStop->setEnabled(true);
    boutonRecordVideo->setEnabled(false);
}

// start the live Video stream from the microphone in the device
void MainWindow::startLiveVideo(){

    streamVideo->startLiveStream();

    boutonLiveVideoStream->setEnabled(false);
    boutonLiveVideoStreamStop->setEnabled(true);
}

// stop the live Video stream from the microphone in the device
void MainWindow:: stopLiveVideo(){

    streamVideo->stopLiveStream();

    boutonLiveVideoStream->setEnabled(true);
    boutonLiveVideoStreamStop->setEnabled(false);
}

// stop the  Video stream from a file in the device ............... the file path must be changed here !!!!!!
void MainWindow::startVideo(){
    QString path="/home/kali/Desktop/video.mp4";

    streamVideo->startStreamFile(path);

    boutonVideoStream->setEnabled(false);
    boutonVideoStreamPause->setEnabled(true);
    boutonVideoStreamStop->setEnabled(true);
}

// stop the  Video stream from a file in the device
void MainWindow::stopVideo(){

    streamVideo->stopStreamFile();

    boutonVideoStream->setEnabled(true);
    boutonVideoStreamPause->setEnabled(false);
    boutonVideoStreamStop->setEnabled(false);
}

// pause the  Video stream from a file in the device
void MainWindow::pauseVideo(){

    streamVideo->pauseStreamFile();

    boutonVideoStream->setEnabled(true);
    boutonVideoStreamPause->setEnabled(false);
    boutonVideoStreamStop->setEnabled(true);
}



void MainWindow::displayImage(QImage image){
    mylabel->setPixmap(QPixmap::fromImage(image));
    mylabel->resize(640,480);
}


void MainWindow::displayImageSFile(QImage image){
    mylabelStreamFile->setPixmap(QPixmap::fromImage(image));
    mylabelStreamFile->resize(640,480);
}
