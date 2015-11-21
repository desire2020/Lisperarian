#-------------------------------------------------
#
# Project created by QtCreator 2015-11-18T01:27:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lisperarian
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    iosystem.cpp \
    library.cpp \
    log.cpp \
    users.cpp \
    users_md5.cpp \
    wlogin.cpp \
    interface.cpp

HEADERS  += mainwindow.h \
    classes.hpp \
    constants.hpp \
    globalvar.hpp \
    stdincs.hpp \
    wlogin.h \
    interface.hpp

FORMS    += mainwindow.ui \
    wlogin.ui
