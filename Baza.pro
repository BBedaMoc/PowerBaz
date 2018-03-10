#-------------------------------------------------
#
# Project created by QtCreator 2014-05-17T10:20:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Baza
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog1.cpp \
    dialog2.cpp \
    dialog3.cpp \
    dialog4.cpp \
    qfilm.cpp \
    filmlistitem.cpp

HEADERS  += mainwindow.h \
    dialog1.h \
    dialog2.h \
    dialog3.h \
    dialog4.h \
    qfilm.h \
    filmlistitem.h

FORMS    += mainwindow.ui \
    dialog1.ui \
    dialog2.ui \
    dialog3.ui \
    dialog4.ui

RC_FILE = power.rc
