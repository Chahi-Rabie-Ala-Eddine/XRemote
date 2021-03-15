#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "FrontendAudio.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void startLiveAudio();
    void stopLiveAudio();
    void startAudio();
    void stopAudio();
    void pauseAudio();
    void recordAudio();
    void endOfAudio();
    void stopRec();


private:
    FrontendAudio *streamAudio;


    QPushButton* boutonRecordAudio;
    QPushButton* boutonRecordAudioStop;
    QPushButton* boutonLiveAudioStream;
    QPushButton* boutonAudioStream;
    QPushButton* boutonLiveAudioStreamStop;
    QPushButton* boutonAudioStreamStop;
    QPushButton* boutonAudioStreamPause;

};

#endif // MAINWINDOW_H

