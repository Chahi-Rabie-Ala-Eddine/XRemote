#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtNetwork>
#include <QPushButton>
#include <QObject>
#include <QLineEdit>
#include <QCheckBox>

#include "xremoteclient.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    explicit MainWindow(QWidget *parent = 0);
    void _InitGUI();
    void _StartSingUpWindow();
    void _StartSingInWindow();
    void _StartMainWindow();
    void _ShowMainWindow();
    void _HideMainWindow();
    void _SetSingalsSlots();

    private:
    QPushButton *SignIn, *SignUp;
    QLineEdit *email, *password;
    QCheckBox *check;
    xremoteclient* client;
    Ui::MainWindow *ui;

    public slots:
    void signIN();
    void signUP();
    void NewDevice();
    void DeleteDevice();
    void UpdateDevice();
    void testSlot();
    void UploadFileToCommonFolder();
    void DeleteFile();
    void UpdateTextDocument();
    void PlayMusicTrack();
    void PlayVideoClip();
    void StartWebcam();
    void StartMicrophone();
    void _sendRequestToServer();
    void _sendRequestToHost();
    void _PrintRPSPPacket();
};

#endif // MAINWINDOW_H
