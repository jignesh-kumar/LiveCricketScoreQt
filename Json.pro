#-------------------------------------------------
#
# Project created by QtCreator 2019-05-29T17:40:01
#
#-------------------------------------------------


QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Json
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qtjson.cpp \
    espendata.cpp \
    mythread.cpp

HEADERS  += mainwindow.h \
    qtjson.h \
    espendata.h \
    defines.h \
    mythread.h

FORMS    += mainwindow.ui
