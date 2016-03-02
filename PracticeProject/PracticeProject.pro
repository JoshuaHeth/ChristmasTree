#-------------------------------------------------
#
# Project created by QtCreator 2016-02-13T20:57:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PracticeProject
TEMPLATE = app


SOURCES +=\
    mainwindow.cpp \
    Character.cpp \
    Command.cpp \
    CommandWords.cpp \
    item.cpp \
    Parser.cpp \
    Room.cpp \
    door.cpp \
    entry_interface.cpp

HEADERS  += mainwindow.h \
    Character.h \
    Command.h \
    CommandWords.h \
    item.h \
    Parser.h \
    Room.h \
    door.h \
    entry_interface.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc
