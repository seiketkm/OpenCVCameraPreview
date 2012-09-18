#-------------------------------------------------
#
# Project created by QtCreator 2012-07-01T21:48:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CameraPreview
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imgprocqt.cpp

HEADERS  += mainwindow.h \
    imgprocqt.h \
    Labeling.h

FORMS    += mainwindow.ui

DEPENDPATH += E:\opencv241\build\include
INCLUDEPATH += E:\opencv241\build\include
LIBS += -LE:\opencv241\build\x86\mingw\lib \
    -lopencv_core241 \
    -lopencv_imgproc241 \
    -lopencv_highgui241
