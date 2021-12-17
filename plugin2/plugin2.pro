#-------------------------------------------------
#
# Project created by QtCreator 2021-12-08T19:39:09
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = plugin2

TEMPLATE = lib

CONFIG += c++11 link_pkgconfig plugin

PKGCONFIG += dtkwidget dtkcore

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DISTFILES += \
    plugin2.json


SOURCES += \
    commonplugin.cpp \
    commoncrumbcontroller.cpp \
    sidebarcommonitemhandler.cpp \
    plugin2view.cpp

HEADERS += \
    commonplugin.h \
    commoncrumbcontroller.h \
    sidebarcommonitemhandler.h \
    plugin2view.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ../filemanager-lib

LIBS += -L$$OUT_PWD/../filemanager-lib -lfilemanager-lib

CONFIG(debug, debug|release) {
    DEPENDPATH += $$PWD/../filemanager-lib
    unix:QMAKE_RPATHDIR += $$OUT_PWD/../filemanager-lib
}

DESTDIR = $$OUT_PWD/../
