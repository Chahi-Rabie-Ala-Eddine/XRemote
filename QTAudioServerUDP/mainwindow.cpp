#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{


    setFixedSize(size());

    input = new AudioInput(this);
    quint16 port = 15002;
    server = new Server(port, this);
    connect(server, SIGNAL(sig_startA(std::string)), this,SLOT(startAudio(std::string)));
    connect(server, SIGNAL(sig_startLA()), this,SLOT(startLiveAudio()));
    connect(server, SIGNAL(sig_stopA()), this,SLOT(stopAudio()));
    connect(server, SIGNAL(sig_stopLA()), this,SLOT(stopLiveAudio()));
    connect(server, SIGNAL(sig_pauseA()), this,SLOT(pauseAudio()));


    connect(input, SIGNAL(dataReady(QByteArray)), server, SLOT(writeData(QByteArray)));


}

MainWindow::~MainWindow()
{

}

void MainWindow::startLiveAudio()
{
    input->streamMics();
}

void MainWindow::startAudio(std::string path)
{

   input->streamFile(path);
}

void MainWindow::stopLiveAudio()
{
   input->stopMics();
}

void MainWindow::stopAudio()
{
   input->stopStream();
}

void MainWindow::pauseAudio()
{
   input->pauseStream();
}

