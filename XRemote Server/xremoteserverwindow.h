#ifndef HEADER_FENSERVEUR
#define HEADER_FENSERVEUR

#include <QtWidgets>
#include <QtNetwork>

#include "xremoteclientmanagement.h"
#include "xremoteserver.h"

class XRemoteServer : public QWidget{

    Q_OBJECT

    public:
        XRemoteServer();
        void _RunGUI();
        void _SetSingalsSlots();

    private slots:
        void _OnStateChange();
        void _OnNumberOfHostChange();
        void _OnLogChange();
        void _FreeLogsWindow();

    private:
        QPushButton *turnOFF;
        QPushButton *exportLog;
        QPushButton *clearLog;
        QVBoxLayout *layout;
        QTextEdit *logs;
        QTcpServer *server;
        QList<client *> clients;
        QLineEdit *connectedHosts;

        xremoteserver* BackServer;
};

#endif
