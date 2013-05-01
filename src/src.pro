#-------------------------------------------------
#
# Project created by QtCreator 2013-04-09T17:04:05
#
#-------------------------------------------------

QT       += core gui script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    console.cpp \
    stage.cpp \
    qbodydef.cpp \
    qfixturedef.cpp \
    worldmodel.cpp \
    controller.cpp

HEADERS  += mainwindow.h \
    console.h \
    stage.h \
    qbodydef.h \
    qfixturedef.h \
    worldmodel.h \
    controller.h \
    worldview.h

FORMS    += mainwindow.ui \
    console.ui \
    tabview.ui \
    stage.ui

include(../box2d.pri)
