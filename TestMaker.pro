#-------------------------------------------------
#
# Project created by QtCreator 2016-09-17T13:27:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestMaker
TEMPLATE = app


SOURCES += main.cpp \
    uitestmaker.cpp \
    testmaker.cpp \
    initwidgets.cpp \
    json_classes.cpp

HEADERS  += \
    uitestmaker.h \
    testmaker.h \
    json_classes.h

CONFIG += mobility
MOBILITY = 

