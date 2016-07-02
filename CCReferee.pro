QT += qml quick svg sql

CONFIG += c++11

SOURCES += main.cpp \
    torneodata.cpp \
    refereedatabase.cpp \
    torneomodel.cpp \
    participantesmodel.cpp \
    participantedata.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = .

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    torneodata.h \
    refereedatabase.h \
    torneomodel.h \
    participantesmodel.h \
    participantedata.h
