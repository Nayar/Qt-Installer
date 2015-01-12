#-------------------------------------------------
#
# Project created by QtCreator 2015-01-12T16:50:26
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tonyinstaller
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    licensewizard.cpp \
    functions.cpp

HEADERS  += mainwindow.h \
    licensewizard.h \
    functions.h

FORMS    += mainwindow.ui

DISTFILES += \
    tonyinstaller.pro.autosave \
    tonyinstaller.pro.user
