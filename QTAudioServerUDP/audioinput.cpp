#include "audioinput.h"
#include <iostream>

// the constructor
// create the file where we will save audio files ( record from microphone ) if it doesn't exist , beware we need the right permission
// isRecording variable is true when we are saving the audio inputs to a file
// isStreamingFile to check if we are already streaming from a file or not
// create the QAudioRecorder used for live stream and saving
AudioInput::AudioInput( QObject *parent, QString pathDirectory) : QObject(parent)
{

    sharedDirectory=pathDirectory;
    pathFolder="/tmp/";
    if(!QDir(pathFolder).exists()){
        QDir().mkpath(pathFolder);
    }


    isRecording=false;
    isStreamingFile=false;
    isStreamingLive=false;
}

// stop the live stream
// if we are not saving data, we remove the audio file of the live stream
void AudioInput::stopLiveStream(){
    probe->~QAudioProbe();
    if(!isRecording){
        audioRec->stop();
        QFile file (pathFileRemove);
        file.remove();
    }
    isStreamingLive=false;
}

// stop the audio record with saving
void AudioInput::stopRec(){
     QString filePath=audioRec->outputLocation().toString();
     audioRec->stop();
     QString filename = filePath;
     filename = filename.remove(pathFolder);
     QString newPath(sharedDirectory+"xRemote-"+filename);
     qDebug()<<newPath;
     qDebug()<<filename;
     QFile file (filePath);
     file.rename(filePath,newPath);


    if (isStreamingLive){
        pathFileRemove=startMicrophone();
        probe = new QAudioProbe;
        probe->setSource(audioRec);
        connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
    }
     isRecording=false;
}

// pause the audio stream from a file
void AudioInput::pauseStream(){
    media->pause();
}

// stop the audio stream from a file
void AudioInput::stopStream(){
    media->stop();
    probeFile->~QAudioProbe();
    isStreamingFile=false;
}

// start getting audio data from the microphone
// put the audio format settings
// the output file ( saving )
// it could be better and safer if we try to use default parameters of the mic and send them to the device
QString AudioInput::startMicrophone(){
    audioRec = new QAudioRecorder;
    audioRec->defaultAudioInput();
    QAudioEncoderSettings audioSettings;
    audioSettings.setChannelCount(1);
    audioSettings.setCodec("audio/AMR");
    audioSettings.setBitRate(16);
    audioSettings.setQuality(QMultimedia::HighQuality);
    audioSettings.setSampleRate(8000);

    audioRec->setAudioSettings(audioSettings);
    QString day = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString hour = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString filePath= pathFolder+"audio-"+day+"-"+hour;
    audioRec->setOutputLocation(QUrl(filePath));
    audioRec->record();
    return filePath;
}

// start recording from the microphone
void AudioInput::recordMic(){
    if(!isStreamingLive){
        startMicrophone();
    }else{ // we run the saving mode after restarting the live stream
        audioRec->stop();
        QFile file (pathFileRemove);
        file.remove();
        startMicrophone();
        probe = new QAudioProbe;
        probe->setSource(audioRec);
        connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
    }
     isRecording=true;
}

// run the live stream in saving mode and no-saving mode ( depends on isRecording boolean )
void AudioInput::streamMics(){
    if(!isRecording){ // not saving mode
        // run the microphone and save the output file to remove it later
        pathFileRemove= startMicrophone();
    }
     probe = new QAudioProbe;
     qDebug()<<probe->setSource(audioRec);
     connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
     isStreamingLive = true;
}


// lunch the sreaming from a file
// restart the streaming file after break ( isStreamingFile equals true )
void AudioInput::streamFile(std::string path){

    if(isStreamingFile){
        media->play();
    }else{
        media = new QMediaPlayer;
        media->setMuted(true);
        QString Qpath = QString::fromUtf8(path.data(),path.size());
        media->setMedia(QUrl::fromLocalFile(Qpath));
        media->play();
        probeFile = new QAudioProbe;
        probeFile->setSource(media);
        connect(probeFile, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
        isStreamingFile=true;
        connect(media,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(mediaStatus(QMediaPlayer::MediaStatus)));
    }

}

// check the streaming file status
// if the streaming finished it notifies the client "eofAudio" message
void AudioInput::mediaStatus(QMediaPlayer::MediaStatus state)
{
    if(state == QMediaPlayer::EndOfMedia)
    {
        QByteArray data;
        data.append("eofAudio");
        stopStream();
        emit dataReady(data);;
    }
}

// it sends the audio data to the client
void AudioInput::processBuffer(const QAudioBuffer &buffer)
{
    QByteArray data;
    qDebug()<<buffer.format();
    data.append(buffer.constData<char>(), buffer.byteCount());
    data.prepend("streamA");

    emit dataReadyStream(data);
}
