#-------------------------------------------------
#
# Project created by QtCreator 2016-02-15T13:33:16
#
#-------------------------------------------------

QT       += core gui
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Zork_Controls
TEMPLATE = app


SOURCES += \
    Character.cpp \
    Command.cpp \
    CommandWords.cpp \
    door.cpp \
    entry_interface.cpp \
    item.cpp \
    mainwindow.cpp \
    Parser.cpp \
    Room.cpp


HEADERS  += \
    Character.h \
    Command.h \
    CommandWords.h \
    door.h \
    entry_interface.h \
    item.h \
    mainwindow.h \
    Parser.h \
    Room.h

FORMS    += \
    mainwindow.ui

DISTFILES += \
    mainLevel2.png \
    SecondLevel.png \
    StoryLine.txt \
    red_cross.png

RESOURCES += \
    icons.qrc

