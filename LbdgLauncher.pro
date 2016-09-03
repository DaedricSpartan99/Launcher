#-------------------------------------------------
#
# Project created by QtCreator 2016-05-30T18:47:03
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LbdgLauncher
TEMPLATE = app

CONFIG += mobility
MOBILITY += multimedia

SOURCES += main.cpp\
        mainwindow.cpp \
    temp.cpp \
    account.cpp \
    windows.cpp \
    txttemp.cpp \
    bintemp.cpp \
    opwindow.cpp \
    playlist.cpp \
    directories.cpp \
    launching.cpp

HEADERS  += mainwindow.h \
    temp.h \
    account.h \
    playlist.h \
    opwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
