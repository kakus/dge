#-------------------------------------------------
#
# Project created by QtCreator 2013-04-09T17:04:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    console.cpp \
    tabview.cpp \
    stage.cpp

HEADERS  += mainwindow.h \
    console.h \
    tabview.h \
    stage.h

FORMS    += mainwindow.ui \
    console.ui \
    tabview.ui \
    stage.ui
