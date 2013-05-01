#-------------------------------------------------
#
# Project created by QtCreator 2013-04-27T20:42:56
#
#-------------------------------------------------

QT       += script svg multimedia testlib

TARGET = tst_qbodydeftest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_qbodydeftest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"


HEADERS += ../../src/worldmodel.h \
           ../../src/qbodydef.h \
           ../../src/qfixturedef.h

SOURCES += ../../src/worldmodel.cpp \
           ../../src/qbodydef.cpp \
           ../../src/qfixturedef.cpp

INCLUDEPATH += ../../src

include( ../../box2d.pri )
