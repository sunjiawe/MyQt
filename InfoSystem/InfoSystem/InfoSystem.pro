#-------------------------------------------------
#
# Project created by QtCreator 2016-08-06T17:06:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InfoSystem
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    datasource.cpp \
    dialog.cpp

HEADERS  += widget.h \
    student.h \
    datasource.h \
    dialog.h \
    GBK.h

FORMS    += widget.ui \
    dialog.ui
