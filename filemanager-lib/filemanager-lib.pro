#-------------------------------------------------
#
# Project created by QtCreator 2021-12-14T17:03:36
#
#-------------------------------------------------

QT       += widgets

TARGET = filemanager-lib
TEMPLATE = lib

CONFIG += c++11 link_pkgconfig

PKGCONFIG += dtkwidget dtkcore

DEFINES += FILEMANAGERLIB_LIBRARY

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
    sidebar.cpp \
    sidebarview.cpp \
    sidebaritem.cpp \
    sidebarmanager.cpp \
    sidebarmodel.cpp \
    sidebaritemdelegate.cpp \
    filemanagerwindow.cpp \
    pluginmanager.cpp \
    toolbar.cpp \
    crumbbar.cpp \
    crumblistviewmodel.cpp \
    crumbinterface.cpp \
    crumbmanager.cpp \
    windowmanager.cpp \
    sidebariteminterface.cpp \
    viewmanager.cpp \
    interfaces/baseview.cpp

HEADERS += \
    sidebarview.h \
    sidebarmanager.h \
    sidebarmodel.h \
    sidebaritemdelegate.h \
    filemanagerwindow.h \
    pluginmanager.h \
    interfaces/sidebar.h \
    interfaces/sidebariteminterface.h \
    interfaces/plugininterface.h \
    interfaces/sidebaritem.h \
    toolbar.h \
    crumbbar.h \
    crumblistviewmodel.h \
    interfaces/crumbinterface.h \
    crumbmanager.h \
    windowmanager.h \
    viewmanager.h \
    interfaces/baseview.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}
