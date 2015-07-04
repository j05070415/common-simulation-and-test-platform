#-------------------------------------------------
#
# Project created by QtCreator 2015-06-30T14:27:04
#
#-------------------------------------------------

QT       += xml

QT       -= gui

TARGET = ResourceManager
TEMPLATE = lib

DEFINES += RESOURCEMANAGER_LIBRARY

SOURCES += ResourceManager.cpp

HEADERS += ResourceManager.h\
        resourcemanager_global.h \
    HCViewConfigManager.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
