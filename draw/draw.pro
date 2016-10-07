#-------------------------------------------------
#
# Project created by QtCreator 2016-10-07T11:50:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = draw
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    touchpaint.cpp \
    utilities.cpp

HEADERS  += widget.h \
    touchpaint.h \
    utilities.h

FORMS    += widget.ui

CONFIG += mobility
MOBILITY = 

