TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    parallelogram.cpp \
    rhombus.cpp \
    rectangle.cpp \
    square.cpp \
    vector2d.cpp

HEADERS += \
    figure.h \
    parallelogram.h \
    rhombus.h \
    rectangle.h \
    square.h \
    point.h \
    vector2d.h

