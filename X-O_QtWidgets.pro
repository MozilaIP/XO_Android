#-------------------------------------------------
#
# Project created by QtCreator 2014-11-09T17:48:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = X-O_QtWidgets
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    res.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES +=

DISTFILES += \
    ImagesIndexes.txt \
    android/AndroidManifest.xml

