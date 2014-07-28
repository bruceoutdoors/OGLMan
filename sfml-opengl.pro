TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    myglwindow.cpp \
    openglwindow.cpp \
    oglman/buffer.cpp \
    oglman/bufferman.cpp \
    oglman/camera.cpp \
    oglman/mesh.cpp \
    oglman/shader.cpp \
    oglman/shaderman.cpp \
    primitives/arrow.cpp \
    primitives/cube.cpp \
    primitives/plane.cpp \
    oglman/walkcam.cpp \
    oglman/arcball.cpp \
    oglman/objreader.cpp \
    oglman/texture.cpp

HEADERS += \
    myglwindow.h \
    openglwindow.h \
    oglman/buffer.h \
    oglman/bufferman.h \
    oglman/camera.h \
    oglman/mesh.h \
    oglman/shader.h \
    oglman/shaderman.h \
    primitives/arrow.h \
    primitives/cube.h \
    primitives/plane.h \
    oglman/walkcam.h \
    oglman/arcball.h \
    oglman/objreader.h \
    oglman/texture.h


QMAKE_CXXFLAGS += -std=c++11

LIBS += -lopengl32 -lglu32 -lglew32
LIBS += -LC:/SFML-2.1/lib/ -lsfml-graphics -lsfml-window -lsfml-system

INCLUDEPATH += C:/SFML-2.1/include

OTHER_FILES += \
    shaders/default.frag \
    shaders/default.vert \
    shaders/flat.frag \
    shaders/flat.vert

DESTDIR = $$_PRO_FILE_PWD_/build
