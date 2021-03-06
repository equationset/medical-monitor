#-------------------------------------------------
#
# Project created by QtCreator 2020-03-20T21:23:58
#
#-------------------------------------------------
DESTDIR = $$PWD/../bin
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTcpServer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        creatinfowidget.cpp \
        detectionwidget.cpp \
        formwidget.cpp \
        main.cpp \
        qpainterwidget.cpp \
        qsplitterwidget.cpp \
        server.cpp \
        smoothcurvecreator.cpp \
        tcpserverwidget.cpp \
        tcpsocket.cpp


HEADERS += \
        creatinfowidget.h \
        detectionwidget.h \
        formwidget.h \
        qpainterwidget.h \
        qsplitterwidget.h \
        server.h \
        smoothcurvecreator.h \
        tcpserverwidget.h \
        tcpsocket.h


FORMS += \
        creatinfowidget.ui \
        detectionwidget.ui \
        formwidget.ui \
        tcpserverwidget.ui



RESOURCES += \
    image/qsrc.qrc

RESOURCES += \
    other/qss.qrc \
    other/main.qrc
win32:RC_FILE   = other/main.rc
