#include "xremoteserverwindow.h"
#include "xremoteconstants.h"
#include "xremotelog.h"
#include "xremoteclientmanagement.h"
#include "xremotenetwork.h"
#include "xremotedbmanagement.h"
#include "xremoterpspprotocol.h"
#include "xremoteserver.h"

#include <QtDebug>

using namespace std;

/*Construcor : Init server, its GUI and make connection to database*/
XRemoteServer::XRemoteServer(){

    /*Launch Server*/
    this->BackServer = new xremoteserver();

    /*Run Server Window*/
    _RunGUI();
}

/*Create and run server's GUI*/
void XRemoteServer::_RunGUI(){

    /*Window propreties*/
    setWindowTitle(tr(titleMsg));
    setFixedSize(700, 500);
    setStyleSheet("   *{background-color: white;} "
                      " QPushButton { background-color: navy; color: white;} "
                      " QPushButton:hover { background-color: red; } "
                      " QLineEdit { color: navy; font-size: x-large;}"
                  );

    /*Widgets*/
    turnOFF = new QPushButton(tr(turnOffMsg), this);
    exportLog = new QPushButton("Export", this);
    clearLog = new QPushButton("Clear", this);
    logs = new QTextEdit(this);
    connectedHosts = new QLineEdit(this);
    layout = new QVBoxLayout;

    turnOFF->setToolTip("Turn server Off !");
    turnOFF->setFont(QFont("Comic Sans MS", 12));
    turnOFF->setCursor(Qt::PointingHandCursor);
    exportLog->setCursor(Qt::PointingHandCursor);
    clearLog->setCursor(Qt::PointingHandCursor);
    connectedHosts->setReadOnly(true);
    logs->setReadOnly(true);

    /*Initial printing*/
    connectedHosts->setText(QString(numberOfHosts) +  "0");
    logs->append(this->BackServer->_GetServerState());

    /*Layout building*/
    /*layout->addWidget(connectedHosts);
    layout->addWidget(logs);
    layout->addWidget(exportLog);
    layout->addWidget(turnOFF);
    layout->addWidget(clearLog);
    setLayout(layout);*/

    /*Connect signals to slots*/
    _SetSingalsSlots();
}

/*Connect signals to slots*/
void XRemoteServer::_SetSingalsSlots(){

    /* Connect turn Off button to the quit slot */
    connect(turnOFF, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(this->BackServer, SIGNAL(_NewLog()), this, SLOT(_OnLogChange()));
    connect(this->BackServer, SIGNAL(_NewHostsNumber()), this, SLOT(_OnNumberOfHostChange()));
    connect(clearLog, SIGNAL(clicked()), this, SLOT(_FreeLogsWindow()));
}

/*Print server state*/
void XRemoteServer::_OnStateChange(){

    logs->append(this->BackServer->_GetServerState());
}

/*Print number of connected hosts*/
void XRemoteServer::_OnNumberOfHostChange(){

    char result[100];
    strcpy(result,numberOfHosts);
    strcat(result,to_string(this->BackServer->_GetNumberOfConnectedHosts()).c_str());
    this->connectedHosts->setText(result);
}

/*Print new log*/
void XRemoteServer::_OnLogChange(){

    logs->append(this->BackServer->_GetServerLog());
}

/*Clear server logs*/
void XRemoteServer::_FreeLogsWindow(){

    this->logs->setText("");
}
