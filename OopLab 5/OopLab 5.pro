#-------------------------------------------------
#
# Project created by QtCreator 2017-04-17T13:31:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 'OopLab 5'
TEMPLATE = app

HEADERS += \
    GraphFromFile/MatrixFromFile/matrix.h \
    GUI/mainwindow.h \
    GraphFromFile/nodeslist.h \
    GUI/graphwidget.h \
    GUI/edge.h \
    GUI/node.h

SOURCES += \
    GraphFromFile/MatrixFromFile/matrix.cpp \
    GUI/mainwindow.cpp \
    main.cpp \
    GraphFromFile/nodeslist.cpp \
    GUI/graphwidget.cpp \
    GUI/edge.cpp \
    GUI/node.cpp

#-------------------------------------------------
#
#  sudo apt-get install libboost-all-dev
#
#INCLUDEPATH += /usr/include/boost
#
#LIBS += -L/usr/include/boost -lboost_system
#LIBS += -L/usr/include/boost  -lboost_chrono
#LIBS += -L/usr/include/boost  -lboost_thread
#LIBS += -L/usr/include/boost  -lboost_timer
#
#-------------------------------------------------
FORMS    += GUI/mainwindow.ui

CONFIG += c++14
