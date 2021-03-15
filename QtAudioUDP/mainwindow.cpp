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
     quint16 localport=14625; // choose a random port to bind on it an udp socket

    bool directIP = true;
    if (directIP){ // direct ip
         host = "127.0.0.1"; // ip address of device
         port = 15001; // UDP Audio port in the device
    }else{
        //QString host = "35.181.45.215"; // ip address of xremote server
         host = "127.0.0.1";
         port = 12301; // Xreomte UDP audio port
    }

    streamAudio = new FrontendAudio(this,clientID,deviceID,localport,host,port,directIP);
    connect(streamAudio,SIGNAL(eofAudio()),this,SLOT(endOfAudio())); // when the stream is finished the signal is emited end the gui will be updated

    //****************************************************************************
    //*****************************************************************************
    //*****************************************************************************













    setFixedSize(size());

    boutonRecordAudio = new QPushButton("Record Audio", this);
    boutonRecordAudio->move(50, 50);
    connect(boutonRecordAudio,SIGNAL(clicked()),this,SLOT(recordAudio()));

    boutonRecordAudioStop = new QPushButton("Stop record", this);
    boutonRecordAudioStop->move(250, 50);
    connect(boutonRecordAudioStop,SIGNAL(clicked()),this,SLOT(stopRec()));
    boutonRecordAudioStop->setEnabled(false);

    boutonLiveAudioStream = new QPushButton("Play Live Audio", this);
    boutonLiveAudioStream->move(50, 200);
    connect(boutonLiveAudioStream,SIGNAL(clicked()),this,SLOT(startLiveAudio()));


    boutonAudioStream = new QPushButton("Play Audio", this);
    boutonAudioStream->move(50, 400);
    connect(boutonAudioStream,SIGNAL(clicked()),this,SLOT(startAudio()));


    boutonAudioStreamPause = new QPushButton("Pause Audio", this);
    boutonAudioStreamPause->move(250, 400);
    connect(boutonAudioStreamPause,SIGNAL(clicked()),this,SLOT(pauseAudio()));
    boutonAudioStreamPause->setEnabled(false);

    boutonLiveAudioStreamStop = new QPushButton("Stop Live Audio", this);
    boutonLiveAudioStreamStop->move(350, 200);
    connect(boutonLiveAudioStreamStop,SIGNAL(clicked()),this,SLOT(stopLiveAudio()));
    boutonLiveAudioStreamStop->setEnabled(false);

    boutonAudioStreamStop = new QPushButton("Stop Audio", this);
    boutonAudioStreamStop->move(450, 400);
    connect(boutonAudioStreamStop,SIGNAL(clicked()),this,SLOT(stopAudio()));
    boutonAudioStreamStop->setEnabled(false);

}

MainWindow::~MainWindow()
{

}

// update the gui whe the stream is finished
void MainWindow::endOfAudio(){
    boutonAudioStream->setEnabled(true);
    boutonAudioStreamStop->setEnabled(false);
    boutonAudioStreamPause->setEnabled(false);
    boutonLiveAudioStream->setEnabled(true);
}

// stop recording audio in the device ( by recording i mean saving the microphone inputs in the device )
void MainWindow::stopRec(){
    streamAudio->stopRec();
    boutonRecordAudioStop->setEnabled(false);
    boutonRecordAudio->setEnabled(true);

}

// start recording audio in the device ( by recording i mean saving the microphone inputs in the device )
void MainWindow::recordAudio(){
    streamAudio->startRecordMic();
    boutonRecordAudioStop->setEnabled(true);
    boutonRecordAudio->setEnabled(false);
}

// start the live audio stream from the microphone in the device
void MainWindow::startLiveAudio(){
    streamAudio->startLiveStream();
    boutonLiveAudioStream->setEnabled(false);
    boutonLiveAudioStreamStop->setEnabled(true);
    boutonAudioStream->setEnabled(false);
}

// stop the live audio stream from the microphone in the device
void MainWindow:: stopLiveAudio(){
    streamAudio->stopLiveStream();
    boutonLiveAudioStream->setEnabled(true);
    boutonLiveAudioStreamStop->setEnabled(false);
    boutonAudioStream->setEnabled(true);
}

// stop the  audio stream from a file in the device ............... the file path must be changed here !!!!!!
void MainWindow::startAudio(){
    QString path="/home/kali/Desktop/record5.amr";
    streamAudio->startStreamFile(path);
    boutonLiveAudioStream->setEnabled(false);
    boutonAudioStream->setEnabled(false);
    boutonAudioStreamPause->setEnabled(true);
    boutonAudioStreamStop->setEnabled(true);
}

// stop the  audio stream from a file in the device
void MainWindow::stopAudio(){
    streamAudio->stopStreamFile();
    boutonLiveAudioStream->setEnabled(true);
    boutonAudioStream->setEnabled(true);
    boutonAudioStreamPause->setEnabled(false);
    boutonAudioStreamStop->setEnabled(false);

}

// pause the  audio stream from a file in the device
void MainWindow::pauseAudio(){
    streamAudio->pauseStreamFile();
    boutonAudioStream->setEnabled(true);
    boutonAudioStreamPause->setEnabled(false);
    boutonAudioStreamStop->setEnabled(true);
}

