`#-------------------------------------------------
#
# Project created by QtCreator 2017-04-14T14:28:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = S_project_graph_maker
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    creatingfunc.cpp \
    form.cpp \
    qcustomplot.cpp \
    settings.cpp

HEADERS  += \
    mainwindow.h \
    creatingfunc.h \
    form.h \
    qcustomplot.h \
    settings.h

FORMS    += \
    mainwindow.ui \
    form.ui \
    settings.ui
