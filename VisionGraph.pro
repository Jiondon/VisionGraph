#-------------------------------------------------
#
# Project created by QtCreator 2018-10-23T11:17:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisionGraph
TEMPLATE = lib

DEFINES += VISIONGRAPH_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0




MOC_DIR = ./tmp
RCC_DIR = ./tmp
UI_DIR = ./tmp
OBJECTS_DIR = ./tmp

Debug:DESTDIR= ./bin/debug
Release:DESTDIR = ./bin/release

#LIBS += ./lib
Debug:LIBS += ./lib/debug/AVL.lib
Debug:LIBS += ./lib/debug/XVCreateRegion.lib
Debug:LIBS += ./lib/debug/XVCombineRegions.lib

Release:LIBS += ./lib/release/AVL.lib
Release:LIBS += ./lib/release/XVCreateRegion.lib
Release:LIBS += ./lib/release/XVCombineRegions.lib

INCLUDEPATH += ./include
INCLUDEPATH += ./include/XVBase.h
INCLUDEPATH += ./include/AVL.h
INCLUDEPATH += ./include/XVCreateRegion.h
INCLUDEPATH += ./include/XVCombineRegions.h



SOURCES += src/visiongraph.cpp \
    src/visiongraph_item.cpp \
    src/visiongraph_region.cpp \
    src/visiongraphtool.cpp \
    src/item/lineitem.cpp \
    src/item/visioncrosspointitem.cpp \
    src/item/visionellipseitem.cpp \
    src/item/visiongraphscene.cpp \
    src/item/visiongraphview.cpp \
    src/item/visionlineitem.cpp \
    src/item/visionpathitem.cpp \
    src/item/visionpoint.cpp \
    src/item/visionpolygon.cpp \
    src/item/visionrectitem.cpp \
    src/item/visionring.cpp \
    src/control/minirect.cpp \
    src/control/visionarrows_rotate.cpp \
    src/control/visionitem.cpp

HEADERS += visiongraph_global.h \
    src/visiongraph.h \
    src/visiongraph_global.h \
    src/visiongraph_item.h \
    src/visiongraph_region.h \
    src/visiongraphtool.h \
    src/item/lineitem.h \
    src/item/visioncrosspointitem.h \
    src/item/visionellipseitem.h \
    src/item/visiongraphscene.h \
    src/item/visiongraphview.h \
    src/item/visionlineitem.h \
    src/item/visionpathitem.h \
    src/item/visionpoint.h \
    src/item/visionpolygon.h \
    src/item/visionrectitem.h \
    src/item/visionring.h \
    src/control/minirect.h \
    src/control/visionarrows_rotate.h \
    src/control/visionitem.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    image.qrc
