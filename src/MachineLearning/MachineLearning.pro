TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += "../MachineLearning/gdal/include"
LIBS += -L../MachineLearning/gdal/lib -lgdal

SOURCES += main.cpp \
    imagetif.cpp \
    polygon.cpp \
    imageout.cpp \
    train.cpp

HEADERS += \
    imagetif.h \
    polygon.h \
    imageout.h \
    train.h

