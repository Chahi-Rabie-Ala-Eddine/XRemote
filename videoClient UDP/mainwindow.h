#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "streamVideo.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void startLiveVideo();
    void stopLiveVideo();
    void startVideo();
    void stopVideo();
    void pauseVideo();
    void recordVideo();
    void endOfVideo();
    void stopRec();
    void displayImage(QImage image);
    void displayImageSFile(QImage image);
    void setLiveHD();
    void setLiveSD();
    void setFileHD();
    void setFileSD();


private:
    StreamVideo *streamVideo;


    QPushButton* boutonRecordVideo;
    QPushButton* boutonRecordVideoStop;
    QPushButton* boutonLiveVideoStream;
    QPushButton* boutonVideoStream;
    QPushButton* boutonLiveVideoStreamStop;
    QPushButton* boutonVideoStreamStop;
    QPushButton* boutonVideoStreamPause;
    QPushButton* boutonSetSD;
    QPushButton* boutonSetHD;
    QPushButton* boutonSetFileHD;
    QPushButton* boutonSetFileSD;

    QLabel* mylabel;
    QLabel* mylabelStreamFile;


};

#endif // MAINWINDOW_H

