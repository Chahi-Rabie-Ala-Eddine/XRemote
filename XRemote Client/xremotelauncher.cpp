#include "xremotelauncher.h"
#include "xremotemainwindow.h"

#include <QApplication>

/*Run XRemote Server*/
int _RUN(int argc, char** argv){

    QApplication app(argc, argv);

    MainWindow* clientWindow = new MainWindow();
    clientWindow->setWindowIcon(QIcon("/home/aladin/XRemote-CLI/mm.png"));
    clientWindow->show();

    return app.exec();
}

