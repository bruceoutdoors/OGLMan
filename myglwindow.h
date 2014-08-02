#ifndef MYGLWINDOW_H
#define MYGLWINDOW_H

#include "openglwindow.h"

#include "primitives/cube.h"
#include "primitives/arrow.h"
#include "primitives/plane.h"

class MyGLWindow : public OpenGLWindow
{
public:
    MyGLWindow(sf::VideoMode mode, const sf::String &title);
    virtual ~MyGLWindow();
    void draw();
    void init();
    bool handleEvents();

private:
    bool keyboardEventHandler(int key);

    Mesh *cube2;
    Cube *cube;
    Mesh *monkey;
    Mesh *elephant;
    Plane *plane;
    Arrow *arrow;
};

#endif // MYGLWINDOW_H
