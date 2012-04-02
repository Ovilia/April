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
    Solid/ASolid.h \
    Solid/ACube.h \
    Solid/ASphere.h \
    Solid/ACylinder.h \
    Solid/ACone.h \
    Solid/APyramid.h \
    Solid/APrism.h \
    Vector3d.h \
    ViewWidget.h \
    ToolWidget.h \
    CreateDialog.h \
    Solid/APrimitive.h

SOURCES += \
    ModelManager.cpp \
    AGLWidget.cpp \
    Solid/ASolid.cpp \
    Solid/APrimitive.cpp \
    Solid/ACube.cpp \
    Solid/ASphere.cpp \
    Solid/ACylinder.cpp \
    Solid/ACone.cpp \
    Solid/APyramid.cpp \
    Solid/APrism.cpp \
    Vector3d.cpp \
    ViewManager.cpp \
    ViewWidget.cpp \
    ToolWidget.cpp \
    CreateDialog.cpp

RESOURCES += \
    resource.qrc

FORMS += \
    ToolWidget.ui \
    CreateDialog.ui
