TEMPLATE = app

QT += qml quick

SOURCES += main.cpp

RESOURCES += qml.qrc
RC_FILE = framework.rc
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

#DISTFILES += \
#    framework.rc
