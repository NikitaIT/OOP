#-------------------------------------------------
#
# Project created by QtCreator 2018-03-12T01:26:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 'OopLab 6'
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    target.cpp \
    point.cpp \
    figures.cpp \
    random.cpp

HEADERS  += mainwindow.h \
    target.h \
    point.h \
    figures.h \
    random.h

FORMS    += mainwindow.ui

CONFIG += console c++11
