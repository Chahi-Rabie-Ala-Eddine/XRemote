#ifndef VIDEOINPUT_H
#define VIDEOINPUT_H

#include<QtCore>
#include <QVideoProbe>
#include <QCamera>
#include <QMediaPlayer>
#include<QMediaRecorder>

class VideoInput: public QObject
{
    Q_OBJECT
public:
    VideoInput( QObject *parent, QString pathFolder) ;
    ~VideoInput();
    void streamFile( QString path);
    void pauseStream();
    void stopStream();
    void startLiveStream();
    void stopLiveStream();
    void saveCamera();
    void stopRec();
    void setLiveHD();
    void setLiveSD();
    void setFileHD();
    void setFileSD();

private:
    void startCamera();
    void recordCamera();




public slots:
    void sendDataCLient(const QVideoFrame &frame);
    void sendDataCLientFStream(const QVideoFrame &frame);
    void mediaStatus(QMediaPlayer::MediaStatus state);

signals:
    void dataReady(QByteArray data);
    void dataReadyStream(QByteArray data);
    void startConversion(QString pathFolder, QString filename);

private :
QCamera* camera;
QMediaPlayer* media;
QVideoProbe* probeFile;
QVideoProbe* probeLive;
QMediaRecorder* recorder;
bool isStreamingFile;
bool isStreamingLive;
bool  isRecording;
bool isStreamLiveHD;
bool isStreamFileHD;
QString pathFolder;
QString pathFolderVideo;
QThread workerThread;


};

#endif // VIDEOINPUT_H

