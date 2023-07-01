#-------------------------------------------------
#
# Project created by QtCreator 2023-06-04T02:48:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = weimin
TEMPLATE = app


SOURCES += main.cpp\
    mylabel.cpp \
        mymainwindow.cpp \
    location_direction.cpp \
    widget_visitorpage.cpp \
    screenutil.cpp

HEADERS  += mymainwindow.h \
    location_direction.h \
    mylabel.h \
    widget_visitorpage.h \
    navigation.h \
    screenutil.h

FORMS    += mymainwindow.ui
