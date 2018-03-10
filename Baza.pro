#-------------------------------------------------
#
# Project created by QtCreator 2014-05-17T10:20:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Baza
TEMPLATE = app
#CONFIG+= static


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

static { # everything below takes effect with CONFIG ''= static
 CONFIG+= static
 DEFINES+= STATIC
 message("~~~ static build ~~~") # this is for information, that the static build is done

 win32: TARGET = $$join(TARGET,,,s) #this adds an s in the end, so you can seperate static build fromnon static build

}
