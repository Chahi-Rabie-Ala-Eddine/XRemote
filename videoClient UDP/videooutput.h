#ifndef VIDEOOUTPUT_H
#define VIDEOOUTPUT_H
#include <QtCore>

class VideoOutput : public QObject
{
    Q_OBJECT
public:
    explicit VideoOutput(QObject *parent = 0);


public slots:
    void writeData(QByteArray data);

};

#endif // VIDEOOUTPUT_H
