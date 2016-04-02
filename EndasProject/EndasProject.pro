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
    Command.cpp \
    CommandWords.cpp \
    door.cpp \
    entry_interface.cpp \
    item.cpp \
    Parser.cpp \
    Room.cpp \
    hero.cpp \
    riddledialog.cpp

HEADERS  += mainwindow.h \
    Character.h \
    Command.h \
    CommandWords.h \
    door.h \
    entry_interface.h \
    item.h \
    Parser.h \
    Room.h \
    hero.h \
    riddledialog.h

FORMS    += mainwindow.ui \
    riddledialog.ui

RESOURCES += \
    icons.qrc

DISTFILES +=
