#-------------------------------------------------
#
# Project created by QtCreator 2015-12-10T22:47:01
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WinampRemoteCommander
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    WinampAPI/WinampCommunicator.cpp

HEADERS  += mainwindow.h \
    WinampAPI/Exceptions.h \
    WinampAPI/Util.h \
    WinampAPI/WinampCommunicator.h \
    WinampAPI/WinampWindowMessages.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
