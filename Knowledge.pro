#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T15:10:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Knowledge
TEMPLATE = app


SOURCES += main.cpp\
        src/MainWindow.cpp \
    src/HeaderForm.cpp \
    src/CssUtils.cpp \
    src/MFLabel.cpp

HEADERS  += src/MainWindow.h \
    src/HeaderForm.h \
    src/CssUtils.h \
    src/MFLabel.h

FORMS    += src/MainWindow.ui \
    src/HeaderForm.ui

RESOURCES += \
    Resources.qrc \
    Resources.qrc

DISTFILES +=
