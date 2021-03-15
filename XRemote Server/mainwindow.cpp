#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xremoteconstants.h"
#include "xremoteserverwindow.h"
#include "xremoteconstants.h"
#include "xremotelog.h"
#include "xremoteclientmanagement.h"
#include "xremotenetwork.h"
#include "xremotedbmanagement.h"
#include "xremoterpspprotocol.h"
#include "xremoteserver.h"

/*Constructor*/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    /*Launch Server*/
    this->BackServer = new xremoteserver();

    /*Run Server Window*/
    _RunGUI();
}

/*Create and run server's GUI*/
void MainWindow::_RunGUI(){

    ui->setupUi(this);

    /*Window propreties*/
    this->setFixedSize(790,585);
    this->setWindowTitle("XRemote Server");

    /*Initial printing*/
    ui->logs->append(this->BackServer->_GetServerState());

    /*Connect signals to slots*/
    _SetSingalsSlots();
}

/*Connect signals to slots*/
void MainWindow::_SetSingalsSlots(){

    /* Connect turn Off button to the quit slot */
    connect(ui->turnOFF, SIGNAL(clicked()), this, SLOT(_ServerOnOff()));
    connect(this->BackServer, SIGNAL(_NewLog()), this, SLOT(_OnLogChange()));
    connect(this->BackServer, SIGNAL(_NewHostsNumber()), this, SLOT(_OnNumberOfHostChange()));
    connect(ui->clearLog, SIGNAL(clicked()), this, SLOT(_FreeLogsWindow()));
}

/*Turn Off/On Server*/
void MainWindow::_ServerOnOff(){

    if(this->BackServer->_GetServer()->isListening()){

        ui->turnOFF->setStyleSheet("background-color: red; color:white;");
        ui->turnOFF->setText("Off");
        this->BackServer->_GetServer()->close();
    }

    else{
        ui->turnOFF->setStyleSheet("background-color: green; color:white;");
        ui->turnOFF->setText("On");
        this->BackServer->_SetServer();
    }
}

/*Print server state*/
void MainWindow::_OnStateChange(){

    ui->logs->append(this->BackServer->_GetServerState());
}

/*Print number of connected hosts*/
void MainWindow::_OnNumberOfHostChange(){

    ui->connectedHosts->display(this->BackServer->_GetNumberOfConnectedHosts());
}

/*Print new log*/
void MainWindow::_OnLogChange(){

     ui->logs->append(this->BackServer->_GetServerLog());
}

/*Clear server logs*/
void MainWindow::_FreeLogsWindow(){

     ui->logs->setText("");
}

/*Destructor*/
MainWindow::~MainWindow(){

    delete ui;
}
