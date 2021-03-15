#include "xremotelauncher.h"
#include "mainwindow.h"

/*Run XRemote Server*/
int _RUN(int argc, char** argv){

    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
