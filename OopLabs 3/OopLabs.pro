#-------------------------------------------------
#
# Project created by QtCreator 2018-02-16T22:29:37
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OopLabs
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    polynom.cpp \
    matrix.cpp

HEADERS  += mainwindow.h \
    polynom.h \
    matrix.h \
    parse.h \
    include.h \
    matriximpl.h

FORMS    += mainwindow.ui
