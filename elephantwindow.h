#ifndef ELEPHANTWINDOW_H
#define ELEPHANTWINDOW_H

#include "openglwindow.h"
#include "transformpanel.h"
#include "camerapanel.h"

#include "primitives/plane.h"
#include "oglman/arcball.h"

#include <SFGUI/SFGUI.hpp>
#include <vector>
#include <sstream>

class ElephantWindow : public OpenGLWindow
{
public:
    ElephantWindow(sf::VideoMode mode, const sf::String &title);
    virtual ~ElephantWindow();
    void draw();
    void init();
    bool handleEvents();
    void guiDraw();

private:
    void guiSetup();
    void addWindow(sfg::Widget::Ptr widget,
                   sf::String title = "Default Title",
                   float x = 0, float y = 0);
    bool keyboardEventHandler(int key);
    void onWindowMove();
    void onWindowMoveRelease();

    sf::Clock *clock;
    Arcball *arcball;
    Mesh *elephant;
    Plane *plane;

    bool isWindowSelect;

    // GUI:
    sfg::SFGUI sfgui;
    sfg::Desktop desktop;
    sfg::Table::Ptr table;
    sfg::TransformPanel::Ptr transform_panel;
    sfg::CameraPanel::Ptr camera_panel;


};

#endif // ELEPHANTWINDOW_H
