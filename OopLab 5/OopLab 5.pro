#-------------------------------------------------
#
# Project created by QtCreator 2018-02-18T15:59:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "OopLab 5"
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graph.cpp \
    matrix.cpp \
    graphwindow.cpp

HEADERS  += mainwindow.h \
    graph.h \
    matrix.h \
    graphwindow.h

FORMS    += mainwindow.ui \
    graphwindow.ui
