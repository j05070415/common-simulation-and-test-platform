#-------------------------------------------------
#
# Project created by QtCreator 2015-06-30T14:43:15
#
#-------------------------------------------------

QT       -= gui

TARGET = FrameAnalyser
TEMPLATE = lib

DEFINES += FRAMEANALYSER_LIBRARY

SOURCES += FrameAnalyser.cpp

HEADERS += FrameAnalyser.h\
        frameanalyser_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
