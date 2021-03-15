#include "videoinput.h"
//#include<QMediaPlayer>
#include<QCameraInfo>
#include<QBuffer>
#include<unistd.h>
#include"threadconverter.h"





VideoInput::VideoInput( QObject *parent, QString pathDirectory) : QObject(parent)
{

    startCamera();

    isStreamLiveHD=false;
    isStreamFileHD=false;


    pathFolderVideo=pathDirectory;
    pathFolder="/tmp/";
    if(!QDir(pathFolder).exists()){
        QDir().mkpath(pathFolder);
    }
    isRecording=false;
    isStreamingFile=false;
    isStreamingLive=false;


    //thread for video convertion from Yuv422p to Yuv420p
    ThreadConverter *worker = new ThreadConverter();
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, SIGNAL(startConversion(QString,QString)), worker, SLOT(convert(QString,QString )));
    workerThread.start();
}

VideoInput::~VideoInput(){
    workerThread.quit();
    workerThread.wait();
}

void VideoInput::setLiveHD(){
    isStreamLiveHD=true;
}

void VideoInput::setLiveSD(){
    isStreamLiveHD=false;
}

void VideoInput::setFileHD(){
    isStreamFileHD=true;
}

void VideoInput::setFileSD(){
    isStreamFileHD=false;
}

void VideoInput::startCamera(){
    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    if(cameras.isEmpty())
        qDebug() << "No camera available ";
    bool initialized(false);
    for (const QCameraInfo &cameraInfo : cameras) {
        qDebug() << cameraInfo.deviceName();
        if (cameraInfo == QCameraInfo::defaultCamera()){
            camera = new QCamera(cameraInfo);
            initialized= true;
             qDebug() <<" cam is initialized";
            camera->setCaptureMode(QCamera::CaptureVideo);
            camera->start();
        }
    }

    // if the default camera is not available , we choose an other one camera available ( i didn't test this part )
    if (!initialized and !cameras.isEmpty()){
         camera = new QCamera(cameras.first());
         camera->setCaptureMode(QCamera::CaptureVideo);
         camera->start();
    }
}

void VideoInput::recordCamera(){
    recorder = new QMediaRecorder(camera,this);
    QString day = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString hour = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString filePath= pathFolder+"video-"+day+"-"+hour;
    recorder->setOutputLocation(QUrl(filePath));
    recorder->setMuted(true);
    //QVideoEncoderSettings videoSettings;
    //videoSettings.setResolution(320, 240);
    //videoSettings.setQuality(QMultimedia::LowQuality);
    //recorder->setVideoSettings(videoSettings);
    // recorder->videoSettings().setResolution(320,240);
    // recorder->videoSettings().setQuality(QMultimedia::LowQuality);
    recorder->record();
}


void VideoInput::saveCamera(){
    if(!isRecording){
        if(!isStreamingLive){
            //startCamera();
            recordCamera();
            qDebug()<<recorder->error();
            qDebug()<<"reccord on";
        }else{ // we run the saving mode after restarting the live stream
            QString pathFileRemove =recorder->outputLocation().fileName();
            recorder->stop();
            QFile file (pathFolder + pathFileRemove);
            file.remove();
            recordCamera();
            probeLive->~QVideoProbe();
            probeLive = new QVideoProbe;
            probeLive->setSource(recorder);
            connect(probeLive, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(sendDataCLient(QVideoFrame)));
        }
         isRecording=true;
    }else{
        qDebug()<<"error : xRemote is already recording camera";
    }
}

// stop the video record with saving
void VideoInput::stopRec(){
    if(isRecording){
        QString filename =recorder->outputLocation().fileName();
        recorder->stop();
        if (isStreamingLive){
            //startCamera();
            recordCamera();
            probeLive->~QVideoProbe();
            probeLive = new QVideoProbe;
            probeLive->setSource(recorder);
            connect(probeLive, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(sendDataCLient(QVideoFrame)));
        }
         isRecording=false;
         emit startConversion(pathFolderVideo,filename);
    }else{
        qDebug()<<"error : xRemote is not recording camera";
    }

}



// run the live stream
void VideoInput::startLiveStream(){
    if (!isStreamingLive){
        if(!isRecording){
           // startCamera();
            recordCamera();
        }
        qDebug()<<recorder->error();
         probeLive = new QVideoProbe;
         probeLive->setSource(recorder);
         connect(probeLive, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(sendDataCLient(QVideoFrame)));
         isStreamingLive = true;
    }else{
        qDebug()<<"error : live stream is already running";
    }
}

// stop the live stream
// if we are not saving data, we remove the video file of the live stream
void VideoInput::stopLiveStream(){
    if(isStreamingLive){
        if(!isRecording){
            QString pathFileRemove =recorder->outputLocation().fileName();
            recorder->stop();
            QFile file (pathFolder + pathFileRemove);
            file.remove();
            //recorder->stop();
            //camera->stop();
        }
        probeLive->~QVideoProbe();
        isStreamingLive=false;
    }else{
        qDebug()<<"error : live stream is not running";
    }
}



void VideoInput::streamFile( QString path){
    if(isStreamingFile){
        media->play();
    }else{
        media = new QMediaPlayer;
        qDebug()<< " streaming file "<< path;
        media->setMedia(QUrl::fromLocalFile(path));
        media->setMuted(true);
        media->play();
        probeFile = new QVideoProbe;
        probeFile->setSource(media);
        connect(probeFile, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(sendDataCLientFStream(QVideoFrame)));
        isStreamingFile=true;
        connect(media,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(mediaStatus(QMediaPlayer::MediaStatus)));
    }
}

// pause the audio stream from a file
void VideoInput::pauseStream(){
    if(isStreamingFile){
        media->pause();
    }else{
        qDebug()<<"error : video streaming is not running";
    }
}

// stop the audio stream from a file
void VideoInput::stopStream(){
    if(isStreamingFile){
        media->stop();
        probeFile->~QVideoProbe();
        isStreamingFile=false;
    }else{
        qDebug()<<"error : video streaming is not running";
    }
}


// check the streaming file status
// if the streaming finished it notifies the client "eofVideo" message
void VideoInput::mediaStatus(QMediaPlayer::MediaStatus state)
{
    if(state == QMediaPlayer::EndOfMedia)
    {
        QByteArray data;
        data.append("eofVideo");
        stopStream();
        emit dataReady(data);
    }
}

void VideoInput::sendDataCLient(const QVideoFrame &frame){
    if (frame.isValid()) {
        qDebug()<<frame;
        QVideoFrame cloneFrame(frame);
        cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
        QImage image = cloneFrame.image();


        //image=image.convertToFormat(QImage::Format_RGB444);
        //qDebug()<<image;
        QByteArray byte;
        QBuffer buff(&byte);

        if(!isStreamLiveHD){
        image=image.scaled(420,320,Qt::KeepAspectRatio);
        image.save(&buff,"JPEG",18);         // image first down to the type of byte, then save it into buff
        }else{
            image.save(&buff,"JPEG");
        }
       // Create a buffer for I/O read and write
        qDebug()<<" size before compression" << byte.size();
        QByteArray compressByte = qCompress(byte,9);         // Data compression algorithm
        qDebug()<<" size after compression" << compressByte.size();

        compressByte.prepend("liveV");


        emit dataReadyStream(compressByte);
        cloneFrame.unmap();
    }
}


    void VideoInput::sendDataCLientFStream(const QVideoFrame &frame){
        if (frame.isValid()) {
            qDebug()<<frame;
            QVideoFrame cloneFrame(frame);
            cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
            QImage image = cloneFrame.image();
            //qDebug()<<image;
            QByteArray byte;
            QBuffer buff(&byte);       // Create a buffer for I/O read and write

            if(!isStreamFileHD){
            image=image.scaled(420,320,Qt::KeepAspectRatio);
            image.save(&buff,"JPEG",18);         // image first down to the type of byte, then save it into buff
            }else{
                image=image.scaled(640,480,Qt::KeepAspectRatio);
                image.save(&buff,"JPEG");
            }

            qDebug()<<" size before compression" << byte.size();
            QByteArray compressByte = qCompress(byte,9);         // Data compression algorithm
            qDebug()<<" size after compression" << compressByte.size();

            compressByte.prepend("fileV");
            emit dataReadyStream(compressByte);
            cloneFrame.unmap();
        }
}


