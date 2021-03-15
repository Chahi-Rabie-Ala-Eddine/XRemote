#include "audiooutput.h"
#include <unistd.h>

// in the constructor i put the audio format used in the device (microphone)
AudioOutput::AudioOutput(QObject *parent) : QObject(parent)
{
    QAudioFormat format;
    format.setChannelCount(1);
    format.setSampleRate(8000);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    audio = new QAudioOutput(format, this);
    audio->setBufferSize(8192);
    device = audio->start();
}

// run the loudspeaker
void AudioOutput::writeData(QByteArray data)
{
    device->write(data.data(), data.size());
}


