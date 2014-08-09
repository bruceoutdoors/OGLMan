#ifndef MYGLWINDOW_H
#define MYGLWINDOW_H

#include "openglwindow.h"
#include "gui/transformpanel.h"
#include "gui/camerapanel.h"
#include "gui/outliner.h"

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
    void guiSetup();
    void addWindow(sfg::Widget::Ptr widget,
                   sf::String title = "Default Title",
                   float x = 0, float y = 0);
    void onWindowMove();
    void onWindowMoveRelease();

    sfg::SFGUI sfgui;
    sfg::Desktop desktop;
    sfg::Label::Ptr test_label;
    sfg::TransformPanel::Ptr transform_panel;
    sfg::CameraPanel::Ptr camera_panel;
    sfg::Outliner::Ptr outliner;
    sfg::PanelWidget::Ptr panel;

    sf::Clock *clock;
    Arcball *arcball;
    WalkCam *walkcam;

    Mesh *cube2;
    Cube *cube;
    Mesh *cube_instance1;
    Mesh *monkey;
    Mesh *monkey_instance1;
    Mesh *elephant;
    Plane *plane;
    Arrow *arrow;

    bool isWindowSelect;

    // slots:
    void onOutlinerSelect();
};

#endif // MYGLWINDOW_H
