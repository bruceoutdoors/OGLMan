TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    oglman/buffer.cpp \
    oglman/bufferman.cpp \
    oglman/camera.cpp \
    oglman/mesh.cpp \
    oglman/shader.cpp \
    oglman/shaderman.cpp \
    oglman/walkcam.cpp \
    oglman/arcball.cpp \
    oglman/objreader.cpp \
    oglman/texture.cpp \
    oglman/oglmwindow.cpp \
    primitives/arrow.cpp \
    primitives/cube.cpp \
    primitives/plane.cpp \
    gui/panelwidget.cpp \
    gui/transformpanel.cpp \
    gui/camerapanel.cpp \
    gui/outliner.cpp \
    gui/guiwindow.cpp \
    examples/myglwindow.cpp \
    examples/elephantwindow.cpp \
    primitives/sphere.cpp

HEADERS += \
    oglman/buffer.h \
    oglman/bufferman.h \
    oglman/camera.h \
    oglman/mesh.h \
    oglman/shader.h \
    oglman/shaderman.h \
    oglman/walkcam.h \
    oglman/arcball.h \
    oglman/objreader.h \
    oglman/texture.h \
    oglman/oglmwindow.h \
    primitives/arrow.h \
    primitives/cube.h \
    primitives/plane.h \
    gui/panelwidget.h \
    gui/transformpanel.h \
    gui/camerapanel.h \
    gui/outliner.h \
    gui/guiwindow.h \
    examples/myglwindow.h \
    examples/elephantwindow.h \
    primitives/sphere.h


QMAKE_CXXFLAGS += -std=c++11

win32 {
    LIBS += -lopengl32 -lglu32
    LIBS += -L$$_PRO_FILE_PWD_/dependencies/lib-mingw/ -lglew32 -lsfml-graphics -lsfml-window -lsfml-system -lsfgui
}

unix {
    LIBS += -lGL -lGLU -lGLEW -lsfml-graphics -lsfml-window -lsfml-system -lsfgui
}

INCLUDEPATH += $$_PRO_FILE_PWD_/dependencies/include

OTHER_FILES += \
    shaders/default.frag \
    shaders/default.vert \
    shaders/flat.frag \
    shaders/flat.vert

DESTDIR = $$_PRO_FILE_PWD_/build
