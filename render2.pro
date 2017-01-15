TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    camera.cpp \
    physics.cpp

DISTFILES += \
    branches.txt

LIBS += -pthread

HEADERS += \
    rwvalue.h \
    camera.h \
    physics.h
