QT += core
QT -= gui

TARGET = OopLabs_8
CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    matrix.cpp \
    polynom.cpp

HEADERS += \
    matrix.h \
    matriximpl.h \
    parse.h \
    polynom.h \
    include.h

