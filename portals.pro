#-------------------------------------------------
#
# Project created by QtCreator 2012-03-14T00:02:54
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = portals
TEMPLATE = app


win32:INCLUDEPATH += glew
win32:DEFINES += GLEW_STATIC

SOURCES += main.cpp\
        widget.cpp \
    math/tmat4.cpp \
    math/tquat.cpp \
    math/tmat3.cpp \
    math/tvec3.cpp \
    math/tvec4.cpp \
    math/tplane.cpp \
    procutil.cpp \
    bsptree.cpp \
    kamera.cpp \
    portal.cpp \
    texturemanager.cpp \
    modelarea.cpp \
    glew/GL/glew.c \
    scene.cpp

HEADERS  += widget.h \
    math/tvec2.h \
    math/tmat4.h \
    math/tquat.h \
    math/tmat3.h \
    math/tvec3.h \
    math/tvec4.h \
    math/tplane.h \
    procutil.h \
    bsptree.h \
    kamera.h \
    portal.h \
    texturemanager.h \
    modelarea.h \
    glew/GL/wglew.h \
    glew/GL/glew.h \
    scene.h

FORMS    +=

OTHER_FILES += \
    simple.vsh \
    simple.fsh
