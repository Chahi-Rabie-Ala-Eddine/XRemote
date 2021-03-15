#include "xremoteregex.h"

#include <QFileInfo>
#include <QDebug>

QString _fileNameValidator(){

    return "";
}

/*Get file name from Path*/
QString _getFileNameFromPath(QString path){

    QFileInfo fi(path);

    return fi.fileName();
}

/*Get file extension from Path*/
QString _getFileExtensionFromPath(QString path){

    QFileInfo fi(path);

    return fi.completeSuffix();
}

/*Get file icon from extension*/
QString _setFileIconFromExtension(QString extension){

    QStringList fileSuffix = {"txt", "c", "cpp", "py", "java", "class", "sh", "h", "out", "o", "md", "pdf", "word"};
    QStringList musicSuffix = {"mp3", "wav", "aac", "flac", "ogg"};
    QStringList imageSuffix = {"jpeg", "jpg", "png", "gif", "svg"};
    QStringList videoSuffix = {"mp4", "avi", "mov", "flv", "wmv"};
    QStringList archiveSuffix = {"zip", "tar", "gz", "mar", "shar", "xz", "Z", "z", "7z", "tar.xz", "tar.gz", "tgz", "tar.Z", "tar.bz2", "tbz2", "tar.lz", "tlz", "tar.xz", "txz", "tar.zst"};
    QStringList isoimgSuffix = {"iso"};

    if(fileSuffix.contains(extension))
        return "   📄 ";

    if(musicSuffix.contains(extension))
        return "   🎵 ";

    if(imageSuffix.contains(extension))
        return "   🖼️ ";

    if(videoSuffix.contains(extension))
        return "   🎬 ";

    if(archiveSuffix.contains(extension))
        return "   📦 ";

    if(isoimgSuffix.contains(extension))
        return "   💿 ";

    return "   ⚙️ ";
}
