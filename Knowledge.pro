#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T15:10:12
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Knowledge
TEMPLATE = app


SOURCES += main.cpp\
        src/MainWindow.cpp \
    src/HeaderForm.cpp \
    src/CssUtils.cpp \
    src/MFLabel.cpp \
    src/DialogGeneratePro.cpp \
    src/DialogWidgetLists.cpp \
    src/bean/WidgetBean.cpp \
    src/item/ItemWidgetListForm.cpp \
    src/choose/DialogToolsList.cpp \
    src/utils/FileUtil.cpp \
    src/utils/KernelGenerateProject.cpp \
    src/bean/ConfBean.cpp \
    src/bean/WidgetToolBean.cpp \
    src/bean/FileBean.cpp

HEADERS  += src/MainWindow.h \
    src/HeaderForm.h \
    src/CssUtils.h \
    src/MFLabel.h \
    src/DialogGeneratePro.h \
    src/DialogWidgetLists.h \
    src/bean/WidgetBean.h \
    src/item/ItemWidgetListForm.h \
    src/choose/DialogToolsList.h \
    src/utils/FileUtil.h \
    src/utils/KernelGenerateProject.h \
    src/bean/ConfBean.h \
    src/bean/WidgetToolBean.h \
    src/bean/FileBean.h

FORMS    += src/MainWindow.ui \
    src/HeaderForm.ui \
    src/DialogGeneratePro.ui \
    src/DialogWidgetLists.ui \
    src/ItemWidgetList.ui \
    src/item/ItemWidgetListForm.ui \
    src/choose/DialogToolsList.ui

RESOURCES += \
    Resources.qrc \
    Resources.qrc

DISTFILES +=
