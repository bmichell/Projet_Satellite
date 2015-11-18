TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -L/usr/include/gdal -lgdal
QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

SOURCES += main.cpp \
    imagetif.cpp \
    imagetraining.cpp \
    imageout.cpp \
    train.cpp

HEADERS += \
    imagetif.h \
    image.h \
    imagetraining.h \
    imageout.h \
    train.h

