TEMPLATE = app
QT += widgets network sql
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += \
    xremotelog.h \
    xremotenetwork.h \
    xremotegenerator.h \
    xremotedbmanagement.h \
    xremoteauthentication.h \
    xremotesecurity.h \
    xremoteclientmanagement.h \
    xremoteconstants.h \
    xremotelauncher.h \
    xremoteparser.h \
    xremoterpspprotocol.h \
    xremoteserver.h \
    xremotecryptography.h \
    mainwindow.h
SOURCES +=  main.cpp \
    xremotelog.cpp \
    xremotenetwork.cpp \
    xremotegenerator.cpp \
    xremotedbmanagement.cpp \
    xremoteauthentication.cpp \
    xremotesecurity.cpp \
    xremoteclientmanagement.cpp \
    xremotelauncher.cpp \
    xremoteparser.cpp \
    xremoterpspprotocol.cpp \
    xremoteserver.cpp \
    xremoteconstants.cpp \
    xremotecryptography.cpp \
    mainwindow.cpp

FORMS += \
    mainwindow.ui

