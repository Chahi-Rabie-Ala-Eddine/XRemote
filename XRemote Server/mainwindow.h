#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtNetwork>

#include "xremoteclientmanagement.h"
#include "xremoteserver.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void _RunGUI();
    void _SetSingalsSlots();

    private:
    Ui::MainWindow *ui;

    private slots:
    void _ServerOnOff();
    void _OnStateChange();
    void _OnNumberOfHostChange();
    void _OnLogChange();
    void _FreeLogsWindow();

    private:
    QList<client *> clients;
    xremoteserver* BackServer;

};

#endif // MAINWINDOW_H
