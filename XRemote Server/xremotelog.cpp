#include "xremotelog.h"
#include "xremotenetwork.h"
#include "xremoteconstants.h"

/*Server state log*/
QString _ServerStateLog(QTcpServer *server){

    return "<strong>" + QDate::currentDate().toString() + " - " + QTime::currentTime().toString() + " : " + "</strong>"
            +  QString(serverConnectionMsg) + QString::number(server->serverPort())
            + ".";
}

/*Connection log*/
QString connectionLog(QTcpSocket *host){

    return "<strong>"
            + QDate::currentDate().toString() + " - " + QTime::currentTime().toString() + "</strong>" + " : <em>"
            + "<strong><font color='red'>" + getHostIPAddress(host) + "</font></strong>"
            + " is connected from port "
            + "<strong><font color='navy'>" +  getHostPORTAddress(host)  + "</font></strong>"
            + " in " + "<strong><font color='green'>" + getLocalizationFromIP(host) + "</font></strong>"
            + ".";
}

/*Disconnection log*/
QString disconnectionLog(QTcpSocket *host){

    return "<strong>"
            + QDate::currentDate().toString() + " - " + QTime::currentTime().toString() + "</strong>" + " : <em>"
            + "<strong><font color='red'>" + getHostIPAddress(host) + "</font></strong>"
            + " logged out from "
            + "<strong><font color='green'>" + getLocalizationFromIP(host);
}

/*Write logs into log file*/
void writeLog(const QString singleLog){

    const QString qPath("./.xremoteLogs.txt");
    QFile qFile(qPath);

    if (qFile.open(QIODevice::WriteOnly)) {
        QTextStream buffer(&qFile);
        buffer << singleLog;
        qFile.close();
    }
}

/*Get source ip Address*/
void exportXRemoteLogs(QTextEdit* text){

    QFile log;
    log.setFileName("./log.txt");
    log.open(QIODevice::Append);
    QTextStream out(&log);
    out << text->toPlainText() << endl;
}
