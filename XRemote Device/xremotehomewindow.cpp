#include "xremotehomewindow.h"
#include "xremotemainwindow.h"
#include "xremotedbmanagement.h"
#include "xremoteconstants.h"
#include "xremotenetworkmanagement.h"
#include "xremoteclient.h"

#include <QLabel>
#include <QIcon>
#include <QMovie>

#include <QtNetwork>

XRemoteHomeWindow::XRemoteHomeWindow() : QWidget(){

    _InitGUI();
    _SetSingalsSlots();
}

void XRemoteHomeWindow::_InitGUI(){
    //WINDOW
    setFixedSize(1215, 645);
    this->setWindowTitle("XRemote CLI");
    setStyleSheet(" *{background-color: white;} "
                  " QPushButton { background-color: #1D7BDB; color: white;} "
                  " QPushButton:hover { background-color: blue; } "
                  " QLineEdit {background-color: white; color: grey;} "
                  " QLineEdit:hover {color: black;} "
                  );

    QMovie *movie = new QMovie("/home/aladin/Téléchargements/logo.png");
    QLabel *processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    movie->start();
    processLabel->move(180,100);

    /*
        Right side
    */

    /*SIGN UP PART*/
  /*  check = new QCheckBox("", this);
    check->setGeometry(760, 390 , 290, 30);
    check->setChecked(true);
    QLabel *checkLINK = new QLabel("I agree XRemote's <a href=\"http://ala-eddine-chahi.fr/\">privacy policies</a>.", this);
    checkLINK->move(780,395);
    checkLINK->setTextFormat(Qt::RichText);
    checkLINK->setTextInteractionFlags(Qt::TextBrowserInteraction);
    checkLINK->setOpenExternalLinks(true);

    SignUp = new QPushButton("Sign up",this);
    SignUp->setToolTip("Sign in and control remotely your devices !");
    SignUp->setFont(QFont("Comic Sans MS", 13));
    SignUp->setCursor(Qt::PointingHandCursor);
    SignUp->setGeometry(810, 440,150, 35);

    QLabel *signUPLink = new QLabel("Already have an XRemote account ? <font color='navy'>Sign in</font> now !", this);
    signUPLink->move(730,530);

    QObject::connect(SignUp, SIGNAL(clicked()), this, SLOT(signUP()));*/

    /*SIGN IN PART*/
    email = new QLineEdit("Your e-mail...",this);
    email->setAlignment(Qt::AlignCenter);
    email->setGeometry(200, 300 , 250, 30);
    email->setMaxLength(40);
    email->setClearButtonEnabled(true);

    password = new QLineEdit("Password...",this);
    password->setAlignment(Qt::AlignCenter);
    password->setGeometry(200, 340 , 250, 30);
    password->setEchoMode(QLineEdit::Password);
    password->setClearButtonEnabled(true);
    password->setMaxLength(18);

    SignIn = new QPushButton("Sign in",this);
    SignIn->setToolTip("Sign in to your XRemote account !");
    SignIn->setFont(QFont("Comic Sans MS", 13));
    SignIn->setCursor(Qt::PointingHandCursor);
    SignIn->setGeometry(250, 420,150, 35);

    QLabel *signInLink = new QLabel("<strong>New on Xremote ? <font color='navy'>Sign up</font> now and get started !</strong>", this);
    signInLink->move(150,530);

    /*
        Left side
    */

    QMovie *gif = new QMovie("/home/aladin/Documents/XRemote Project/Client/XRemote Client/logo3.gif");
    QLabel *gifLabel = new QLabel(this);
    gifLabel->setMovie(gif);
    gif->start();
    gifLabel->move(530,155);
}

void XRemoteHomeWindow::_SetSingalsSlots(){

    QObject::connect(SignIn, SIGNAL(clicked()), this, SLOT(signIN()));
}

void XRemoteHomeWindow::signUP(){

    QTcpSocket* socket = new QTcpSocket(this);
    socket->abort();

    /*Connect to server*/
    socket->connectToHost("127.0.0.1", 19999);
    //MainWindow* my_window = new MainWindow(socket);
    //my_window->show();
   // QWidget::hide();
}

void XRemoteHomeWindow::signIN(){

    /*Connect to XRemote server*/
    QTcpSocket* socket = new QTcpSocket(this);
    _ConnectHostToXremote(socket, localhost, PORT);

    /*Send credentials to server*/
    _SendCredentials(socket, email->text(), password->text());

    /*start the client session if the authentication was successful*/

    /*Accès et remplissage de la fenêtre !*/
   // MainWindow* clientWindow = new MainWindow(socket);
   // clientWindow->show();
   // QWidget::hide();

}
