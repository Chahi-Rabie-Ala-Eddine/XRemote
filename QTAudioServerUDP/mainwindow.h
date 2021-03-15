
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QComboBox>
#include "audioinput.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void getDevInfo();
    //void on_pushButton();
    void stream_file();
    void startAudio(std::string path);
    void startLiveAudio();
    void stopLiveAudio();
    void stopAudio();
    void pauseAudio();

private:

    AudioInput *input;
    Server *server;
    QComboBox* comboBox;
    QPushButton* pushButton;

};

#endif // MAINWINDOW_H
