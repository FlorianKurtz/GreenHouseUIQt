#-------------------------------------------------
#
# Project created by QtCreator 2020-02-16T20:19:22
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
target.path     = /home/pi
INSTALLS       += target

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testRasp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

FORMS += \
    mainwindow.ui \
    choose.ui \
    new_plant.ui \
    welcomewindow.ui \
    getdatewindow.ui

HEADERS += \
    mainwindow.h \
    choose.h \
    new_plant.h \
    plant.h \
    welcomewindow.h \
    culture_task.h \
    getdatewindow.h

SOURCES += \
    mainwindow.cpp \
    choose.cpp \
    new_plant.cpp \
    plant.cpp \
    main.cpp \
    welcomewindow.cpp \
    culture_task.cpp \
    getdatewindow.cpp
