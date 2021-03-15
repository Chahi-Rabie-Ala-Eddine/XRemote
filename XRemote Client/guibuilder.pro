TEMPLATE = app
QT += widgets sql qml network
DEPENDPATH += .
INCLUDEPATH += .

HEADERS += \
    xremoteregex.h \
    xremotesecurity.h \
    xremotetoken.h \
    xremotesessionmanagement.h \
    xremotemainwindow.h \
    xremotenetworkmanagement.h \
    xremoteconstants.h \
    xremotecryptographie.h \
    xremoteclient.h \
    xremotelauncher.h \
    xremoterpspprotocol.h \
    xremotedevice.h

SOURCES += main.cpp \
    xremoteregex.cpp \
    xremotesecurity.cpp \
    xremotesessionmanagement.cpp \
    xremotemainwindow.cpp \
    xremotenetworkmanagement.cpp \
    xremoteconstants.cpp \
    xremotecryptographie.cpp \
    xremoteclient.cpp \
    xremotelauncher.cpp \
    xremoterpspprotocol.cpp \
    xremotedevice.cpp

FORMS += mainwindow.ui
