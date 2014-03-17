#-------------------------------------------------
#
# Project created by QtCreator 2014-01-28T15:15:29
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = viewer
TEMPLATE = app


SOURCES += main.cpp\
        viewerwindow.cpp \
    acercade.cpp \
    preferencias.cpp \
    capturebuffer.cpp

HEADERS  += viewerwindow.h \
    acercade.h \
    preferencias.h \
    capturebuffer.h

FORMS    += viewerwindow.ui \
    acercade.ui \
    preferencias.ui
