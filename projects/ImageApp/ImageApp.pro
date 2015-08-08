#-------------------------------------------------
#
# Project created by QtCreator 2015-07-19T09:29:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageApp
TEMPLATE = app


SOURCES += main.cpp\
        imageapp.cpp

HEADERS  += imageapp.h

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.10


INCLUDEPATH +=/usr/local/include
INCLUDEPATH +=/Users/willard/Public/vlfeat-0.9.20

LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc
LIBS += -L/Users/willard/Public/vlfeat-0.9.20/bin/maci64 -lvl

