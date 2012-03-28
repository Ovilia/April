#-------------------------------------------------
#
# Project created by QtCreator 2012-03-27T13:49:14
#
#-------------------------------------------------

QT       += core gui

TARGET = April_Qt
TEMPLATE = app

contains(QT_CONFIG, opengl) {
    message(Building with OpenGL support.)
    QT += opengl

    SOURCES += main.cpp\
            MainWindow.cpp

    HEADERS  += MainWindow.h

    FORMS    += MainWindow.ui
} else {
    message(OpenGL support is not available.)
}

HEADERS += \
    ModelManager.h \
    AGLWidget.h \
    ViewManager.h \
    ViewWidget.h \
    Solid/APrimitive.h \
    Solid/ASolid.h

SOURCES += \
    ModelManager.cpp \
    AGLWidget.cpp \
    ViewManager.cpp \
    ViewWidget.cpp \
    Solid/ASolid.cpp \
    Solid/APrimitive.cpp
