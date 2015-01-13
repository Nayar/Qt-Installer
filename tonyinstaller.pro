#-------------------------------------------------
#
# Project created by QtCreator 2015-01-12T16:50:26
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tonydeploy
TEMPLATE = app


SOURCES += main.cpp\
    licensewizard.cpp \
    functions.cpp \
    downloadmanager.cpp \
    textprogressbar.cpp

HEADERS  += \
    licensewizard.h \
    functions.h \
    downloadmanager.h \
    textprogressbar.h

FORMS    += \
    downloadjava.ui

SUBDIRS += \
    downloadmanager.pro

