#ifndef XREMOTEHOMEWINDOW_H
#define XREMOTEHOMEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QLineEdit>
#include <QCheckBox>

#include "xremoteclient.h"

class XRemoteHomeWindow : public QWidget{

    Q_OBJECT

    private:
    QPushButton *SignIn, *SignUp;
    QLineEdit *email, *password;
    QCheckBox *check;
    xremoteclient* client;

    public slots:
    void signIN();
    void signUP();

    public:
    XRemoteHomeWindow();
    void _InitGUI();
    void _SetSingalsSlots();
};

#endif // XREMOTEHOMEWINDOW_H
