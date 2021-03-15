#ifndef XREMOTEREGEX_H
#define XREMOTEREGEX_H

#include <QWidget>

QString _fileNameValidator();

/*Get filename from Path*/
QString _getFileNameFromPath(QString path);

/*Get file extension from Path*/
QString _getFileExtensionFromPath(QString path);

/*Get file icon from extension*/
QString _setFileIconFromExtension(QString extension);

#endif // XREMOTEREGEX_H
