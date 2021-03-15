#ifndef THREADCONVERTER_H
#define THREADCONVERTER_H


#include <QtCore>
#include <QtNetwork>
#include <unistd.h>


class ThreadConverter : public QObject
{
    Q_OBJECT
public:    ThreadConverter();

public slots:
    void convert( QString path, QString filename );
};

#endif // THREADCONVERTER_H
