#-------------------------------------------------
#
# Project created by QtCreator 2020-02-20T20:39:55
#
#-------------------------------------------------

QT       += core gui printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GreenHouse_V3
TEMPLATE = app
target.path     = /home/pi
INSTALLS       += target

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    gpio.cpp \
    temphum.cpp \
    camera.cpp \
    controlwindow.cpp \
    infowindow.cpp \
    plantwindow.cpp \
    automatictemperature.cpp \
    automaticwatering.cpp \
    automaticlightning.cpp \
    qcustomplot.cpp \
    tsl2591.cpp

HEADERS += \
    mainwindow.h \
    gpio.h \
    temphum.h \
    camera.h \
    controlwindow.h \
    infowindow.h \
    plantwindow.h \
    automatictemperature.h \
    automaticwatering.h \
    automaticlightning.h \
    qcustomplot.h \
    tsl2591.h

FORMS += \
    mainwindow.ui \
    controlwindow.ui \
    infowindow.ui \
    plantwindow.ui

DISTFILES +=
