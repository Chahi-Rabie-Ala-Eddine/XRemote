#include "threadconverter.h"

ThreadConverter::ThreadConverter()
{

}

void ThreadConverter::convert( QString path, QString filename ){
    sleep(1);
    QProcess::execute("ffmpeg -i /tmp/" +filename+ " -c:v libx264 -pix_fmt yuv420p "+path +"xRemote-"+filename);
    QFile file ("/tmp/" + filename);
    file.remove();
}
