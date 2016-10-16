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
    testchartranslate.cpp \
    global.cpp \
    testfunctions.cpp \
    uitestmaker.cpp \
    testmaker.cpp

HEADERS  += \
    global.h \
    testchartranslate.h \
    testfunctions.h \
    uitestmaker.h \
    testmaker.h

CONFIG += mobility
MOBILITY = 

