#-------------------------------------------------
#
# Project created by QtCreator 2013-04-27T20:09:15
#
#-------------------------------------------------

QT       += script svg multimedia testlib dbus

TARGET = tst_worldtesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_worldtesttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += ../../src/worldmodel.h \
           ../../src/qbodydef.h \
           ../../src/qfixturedef.h

SOURCES += ../../src/worldmodel.cpp \
           ../../src/qbodydef.cpp \
           ../../src/qfixturedef.cpp

INCLUDEPATH += ../../src

QMAKE_CXXFLAGS += -std=c++0x

include(../../box2d.pri)
