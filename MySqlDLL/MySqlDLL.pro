#-------------------------------------------------
#
# Project created by QtCreator 2018-03-27T18:44:11
#
#-------------------------------------------------

QT       -= gui
QT += sql network core

TARGET = MySqlDLL
TEMPLATE = lib

DEFINES += MYSQLDLL_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        mysqldll.cpp \
    queryengine.cpp \
    session.cpp \
    transaction.cpp \
    cryptocurrency.cpp

HEADERS += \
        mysqldll.h \
        mysqldll_global.h \   
    queryengine.h \
    session.h \
    transaction.h \
    cryptocurrency.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
