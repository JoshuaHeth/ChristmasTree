#-------------------------------------------------
#
# Project created by QtCreator 2016-03-16T13:22:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EndasProject
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    Character.cpp \
    door.cpp \
    item.cpp \
    Room.cpp \
    hero.cpp \
    riddledialog.cpp

HEADERS  += mainwindow.h \
    Character.h \
    door.h \
    item.h \
    Room.h \
    hero.h \
    riddledialog.h \
    IEntry.h

FORMS    += mainwindow.ui \
    riddledialog.ui

RESOURCES += \
    icons.qrc

DISTFILES +=
