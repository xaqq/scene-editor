#-------------------------------------------------
#
# Project created by QtCreator 2014-02-23T18:41:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Infographie-TP1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qirrlichtwidget.cpp \
    entityTable.cpp \
    entity.cpp \
    cameraentity.cpp

HEADERS  += mainwindow.hpp \
    qirrlichtwidget.hpp \
    entityTable.hpp \
    entity.hpp \
    cameraentity.hpp

FORMS    += mainwindow.ui

LIBS += -lIrrlicht

RESOURCES += \
    app_resources.qrc

QMAKE_CXXFLAGS += -std=c++11
