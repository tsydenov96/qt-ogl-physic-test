QT       += core gui opengl openglwidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


LIBS += -lopengl32 -lglu32



SOURCES += \
    GridObject.cpp \
    KeyboardMouseHandler.cpp \
    MainWindow.cpp \
    OGLExceptions.cpp \
    SceneView.cpp \
    ShaderProgram.cpp \
    SphereObject.cpp \
    main.cpp \
    OpenGLWindow.cpp \
    SphereMesh.cpp \
    transform3d.cpp

HEADERS += \
    Camera.h \
    DebugApplication.h \
    GridObject.h \
    KeyboardMouseHandler.h \
    MainWindow.h \
    OGLExceptions.h \
    SceneView.h \
    ShaderProgram.h \
    SphereObject.h \
    Vertex.h \
    OpenGLWindow.h \
    SphereMesh.h \
    transform3d.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    shaders.qrc
