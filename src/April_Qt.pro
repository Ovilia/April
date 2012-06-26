#-------------------------------------------------
#
# Project created by QtCreator 2012-03-27T13:49:14
#
#-------------------------------------------------

QT       += core gui xml

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
    AGLWidget.h \
    ModelManager.h \
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
    Solid/APrimitive.h \
    StateEnum.h \
    ACreateDialog.h \
    Vector3i.h \
    ArcBall.h \
    MatrixD.h \
    FileManager.h \
    ColorDialog.h \
    Material.h \
    TextureFile.h \
    TextUvGlWidget.h \
    Texture.h \
    TextureDialog.h \
    Lighting.h

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
    ACreateDialog.cpp \
    Vector3i.cpp \
    ArcBall.cpp \
    MatrixD.cpp \
    FileManager.cpp \
    ColorDialog.cpp \
    Material.cpp \
    TextureFile.cpp \
    TextUvGlWidget.cpp \
    Texture.cpp \
    TextureDialog.cpp \
    Lighting.cpp

RESOURCES += \
    resource.qrc

FORMS += \
    ToolWidget.ui \
    ACreateDialog.ui \
    ColorDialog.ui \
    TextureDialog.ui
