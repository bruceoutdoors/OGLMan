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

private:
    Mesh *cube;
    Mesh *monkey;
    Plane *plane;
    Arrow *arrow;
};

#endif // MYGLWINDOW_H
