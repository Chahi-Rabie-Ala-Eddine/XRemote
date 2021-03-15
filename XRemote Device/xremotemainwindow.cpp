#include "ui_mainwindow.h"

#include "xremotemainwindow.h"
#include "xremoteregex.h"
#include "xremotenetworkmanagement.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QComboBox>
#include <QFileDialog>

/*Constructor of main window*/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    /*Create client context*/
    this->client = new xremoteclient();

    /*Init GUI*/
    _InitGUI();
}

/*
        GRAPHIC
*/

/*Init client graphical interface*/
void MainWindow::_InitGUI(){

    _HideMainWindow();
    _StartSingInWindow();
    _SetSingalsSlots();
}

/*Start sign up window*/
void MainWindow::_StartSingUpWindow(){

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
    check = new QCheckBox("", this);
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

    QObject::connect(SignUp, SIGNAL(clicked()), this, SLOT(signUP()));

}

/*Start sign in window*/
void MainWindow::_StartSingInWindow(){

    setFixedSize(1215, 645);
    setWindowTitle("XRemote Client");
    setStyleSheet(" *{background-color: white;} "
                  " QPushButton { background-color: #1D7BDB; color: white;} "
                  " QPushButton:hover { background-color: blue; } "
                  " QLineEdit {background-color: white; color: grey;} "
                  " QLineEdit:hover {color: black;} "
                  );

    QMovie *movie = new QMovie("/home/aladin/Téléchargements/logo.png");
    ui->logLabel->setMovie(movie);
    movie->start();
    ui->logLabel->move(180,100);

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

    ui->SingInUpLabel->setText("<strong><font color = '#273252'>New on Xremote ? </font><font color='navy'>Sign up</font><font color = '#273252'> now and get started !</font></strong>");

    /*
        Left side
    */

    QMovie *gif = new QMovie("/home/aladin/Documents/XRemote Project/Client/XRemote Client/logo3.gif");
    ui->gifLabel->setMovie(gif);
    gif->start();
    ui->gifLabel->move(530,225);
}

/*Hide main window*/
void MainWindow::_HideMainWindow(){

    ui->setupUi(this);
    ui->listWidget->hide();
    ui->listWidget_2->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->tabWidget->hide();
    ui->menubar->hide();
    ui->textEdit_3->hide();
    ui->textEdit_2->hide();
    ui->textEdit->hide();
}

/*Show main window*/
void MainWindow::_ShowMainWindow(){

    ui->listWidget->show();
    ui->listWidget_2->show();
    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_4->show();
    ui->pushButton_5->show();
    ui->pushButton_6->show();
    ui->tabWidget->show();
    ui->menubar->show();
    ui->textEdit_3->show();
    ui->textEdit_2->show();
    ui->textEdit->show();
    ui->logLabel->hide();
    ui->gifLabel->hide();
    ui->SingInUpLabel->hide();
    this->email->hide();
    this->password->hide();
    this->SignIn->hide();
}

/*Start main window*/
void MainWindow::_StartMainWindow(){

    /*Main Window*/
    _ShowMainWindow();

    setStyleSheet("QMainWindow{background-color: #F8FFDA;}"); //QMenuBar{background-color: #FBFFEA;}

    /*Menu de gauche*/
    ui->listWidget->addItem("📁 folder");
    ui->listWidget->addItem("   📄 todo.txt");
    ui->listWidget->addItem("   📦 prog.zip");
    ui->listWidget->addItem("   🖼️ picture.png");
    ui->listWidget->addItem("   🎵 track.mp3");
    ui->listWidget->addItem("   🎬 film.mp4");
    ui->listWidget->addItem("   💿 kali.iso");
    ui->listWidget->addItem("   ⚙️ unkonwn.ext");
    ui->listWidget->addItem("   📄 todo.txt");
    ui->listWidget->addItem("   📦 prog.zip");
    ui->listWidget->addItem("   🖼️ picture.png");
    ui->listWidget->addItem("   🎵 track.mp3");
    ui->listWidget->addItem("   🎬 film.mp4");
    ui->listWidget->addItem("   💿 kali.iso");
    ui->listWidget->addItem("   ⚙️ unkonwn.ext");
    ui->listWidget->addItem("   📄 todo.txt");
    ui->listWidget->addItem("   📦 prog.zip");
    ui->listWidget->addItem("   🖼️ picture.png");
    ui->listWidget->addItem("   🎵 track.mp3");
    ui->listWidget->addItem("   🎬 film.mp4");
    ui->listWidget->addItem("   💿 kali.iso");
    ui->listWidget->addItem("   ⚙️ unkonwn.ext");
    ui->listWidget->addItem("   📄 todo.txt");
    ui->listWidget->addItem("   📦 prog.zip");
    ui->listWidget->addItem("   🖼️ picture.png");
    ui->listWidget->addItem("   🎵 track.mp3");
    ui->listWidget->addItem("   🎬 film.mp4");
    ui->listWidget->addItem("   💿 kali.iso");

    ui->listWidget->setCurrentRow(1);

    /*Menu de droite*/
    ui->listWidget_2->addItem("💻 Devices");
    ui->listWidget_2->addItem("   🔘 Ubuntu 18.08.1 LTS");
    ui->listWidget_2->addItem("   🔘 Kali Linux");
    ui->listWidget_2->addItem("   🔘 Windows 10");
    ui->listWidget_2->addItem("   🔐 Mac Os Sierra");
    ui->listWidget_2->addItem("   ⛔ Windows 7");
    ui->listWidget_2->addItem("   🔐 Red Hat");
    ui->listWidget_2->addItem("   ⛔ Debian");
    ui->listWidget_2->setCurrentRow(2);
    ui->tabWidget->setCurrentIndex(5);
}


/*
        NETWORK
*/


/*Set up singals and slots*/
void MainWindow::_SetSingalsSlots(){

    connect(this->client, SIGNAL(_Recieve()), this, SLOT(_PrintRPSPPacket()));
    connect(ui->saveDocument, SIGNAL(clicked()), this, SLOT(_sendRequestToServer()));
    connect(ui->actionNewDevice, SIGNAL(triggered(bool)), this, SLOT(NewDevice()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(UploadFileToCommonFolder()));
    connect(SignIn, SIGNAL(clicked()), this, SLOT(signIN()));
}

/*Sign up slot*/
void MainWindow::signUP(){

    QTcpSocket* socket = new QTcpSocket(this);
    socket->abort();

    /*Connect to server*/
    socket->connectToHost("127.0.0.1", 19999);

}

/*Sign in slot*/
void MainWindow::signIN(){

    /*Connect to XRemote server*/
    _ConnectHostToXremote(this->client->_GetSocket(), localhost, PORT);

    /*Send credentials to server*/
    _SendCredentials(this->client->_GetSocket(), email->text(), password->text());

    /*Start Main Window*/
    _StartMainWindow();
}

/*Recieved packets management*/
void MainWindow::_PrintRPSPPacket(){

    ui->textEdit_3->append(this->client->_GetRPSPPacket());
}

/*Send request remotely to device from server*/
void MainWindow::_sendRequestToServer(){

    this->client->_SendRPSPPacketToServer(ui->textEdit->toPlainText());

    ui->textEdit->setPlainText("Sended !");
}

/*Send request directly to device*/
void MainWindow::_sendRequestToHost(){}
























































/*
 * Devices
*/

void MainWindow::NewDevice(){

    QDialog dialog(this);
    dialog.setFixedSize(350,130);
    dialog.setWindowTitle("XRemote New Device");
    dialog.setStyleSheet("QDialog{background-color: #FBFFEA;}");

    QFormLayout form(&dialog);

    /*Device name*/
    QLineEdit *deviceName = new QLineEdit(&dialog);
    deviceName->setPlaceholderText("My Desktop Machine");
    QString deviceNamelabel = QString("👤 <strong>Device Name </font></strong>");
    form.addRow(deviceNamelabel, deviceName);

    /*Device Ip*/
    QLineEdit *deviceIP = new QLineEdit(&dialog);
    deviceIP->setPlaceholderText("127.0.0.1");
    QString deviceIPLabel = QString("🌐 <strong>Device @IP </font></strong>");
    form.addRow(deviceIPLabel, deviceIP);

    /*Device Type*/
    QComboBox *deviceType = new QComboBox(&dialog);
    deviceType->setEditable(true);
    deviceType->addItem("Linux");
    deviceType->addItem("Mac");
    deviceType->addItem("Windows");
    deviceType->addItem("Other");
    QString deviceTypeLabel = QString("🌀 <strong>Device Type </font></strong>");
    form.addRow(deviceTypeLabel, deviceType);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    /*If the user didn't dismiss the dialog, do something with the fields*/
    if (dialog.exec() == QDialog::Accepted && !deviceIP->text().isEmpty()) {
        qDebug() << deviceName->text() << deviceIP->text() << deviceType->currentText();
        ui->listWidget_2->addItem(QString("   🔐 " + deviceName->text()).toLocal8Bit().data());

        /*AJOUTER DU TEMPS DE TRAITEMENT ET UN CHANGEMENT DU CODE CHAQUE 5 MINUTES*/
        QMessageBox::information(this, "XRemote New Device", "<strong><font color='navy'" + QString(deviceName->text()) + "</font></strong> has been <strong><font color='green'>successfully</font></strong> added to your device list." + "\n" + "<strong><font color='red'>However</font></strong> you need to enter the code below into the XRemote utility on your machine to be able to use it remotely !");

    }

    else{
       // QMessageBox::critical(this, "No device", "No device added !");
    }
}

void MainWindow::DeleteDevice(){

}

void MainWindow::UpdateDevice(){

}

void MainWindow::testSlot(){


}


/*
 * Common files
*/

/*Upload file to remote device*/
void MainWindow::UploadFileToCommonFolder(){

    QString file = QFileDialog::getOpenFileName(this, "File selection", QString(), "");

    if (!file.isEmpty()){

        ui->listWidget->addItem(QString(_setFileIconFromExtension(_getFileExtensionFromPath(file)) + _getFileNameFromPath(file)).toLocal8Bit().data());

        // ENVOYER REELEMENT LE FICHIER SUR LE REASEAU VERS LA DEVICE

        QMessageBox::information(this, "XRemote File Transfer", "<strong><font color='navy'" + _getFileNameFromPath(file) + "</font></strong> has been <strong><font color='green'>successfully</font></strong> transferred !");
    }

    else
        QMessageBox::critical(this, "XRemote File Transfert", "No file selected !");
}

void MainWindow::DeleteFile(){

}

void MainWindow::UpdateTextDocument(){

}

void MainWindow::PlayMusicTrack(){

}

void MainWindow::PlayVideoClip(){

}

void MainWindow::StartWebcam(){

}

void MainWindow::StartMicrophone(){

}
