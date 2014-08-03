#ifndef MYGLWINDOW_H
#define MYGLWINDOW_H

#include "openglwindow.h"

#include "primitives/cube.h"
#include "primitives/arrow.h"
#include "primitives/plane.h"
#include "oglman/arcball.h"
#include "oglman/walkcam.h"

#include <SFGUI/SFGUI.hpp>

class MyGLWindow : public OpenGLWindow
{
public:
    MyGLWindow(sf::VideoMode mode, const sf::String &title);
    virtual ~MyGLWindow();
    void draw();
    void init();
    bool handleEvents();
    void guiDraw();

private:
    bool keyboardEventHandler(int key);
    void onWindowMove();
    void onWindowMoveRelease();

    sfg::SFGUI sfgui;
    sfg::Desktop desktop;
    sfg::Label::Ptr test_label;

    Arcball *arcball;
    WalkCam *walkcam;

    Mesh *cube2;
    Cube *cube;
    Mesh *monkey;
    Mesh *elephant;
    Plane *plane;
    Arrow *arrow;

    bool isWindowSelect;
};

#endif // MYGLWINDOW_H
