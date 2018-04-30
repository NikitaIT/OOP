#-------------------------------------------------
#
# Project created by QtCreator 2018-04-29T13:00:44
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++14
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CurseWorkVar7
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    productstore.cpp \
    employee.cpp \
    customer.cpp \
    live.cpp \
    statistic.cpp

HEADERS  += mainwindow.h \
    productstore.h \
    employee.h \
    customer.h \
    live.h \
    random.h \
    statistic.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
