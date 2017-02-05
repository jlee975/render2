TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    camera.cpp \
    physics.cpp \
    render.cpp \
    worker.cpp \
    clock.cpp

DISTFILES += \
    branches.txt

LIBS += -pthread

HEADERS += \
    camera.h \
    physics.h \
    config.h \
    geo/vector.h \
    event_queue.h \
    render.h \
    worker.h \
    inplace.h \
    clock.h
