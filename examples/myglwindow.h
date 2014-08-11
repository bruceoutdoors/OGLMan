#ifndef MYGLWINDOW_H
#define MYGLWINDOW_H

#include "gui/guiwindow.h"

#include "oglman/arcball.h"
#include "oglman/walkcam.h"
#include "gui/transformpanel.h"
#include "gui/camerapanel.h"
#include "gui/outliner.h"
#include "primitives/cube.h"
#include "primitives/arrow.h"
#include "primitives/plane.h"

class MyGLWindow : public GuiWindow
{
public:
    MyGLWindow(sf::VideoMode mode,
               const sf::String &title = "Test OGLMan Example");
    virtual ~MyGLWindow();
    void draw();
    void init();
    bool handleEvents(sf::Event e);

private:
    bool keyboardEventHandler(int key);
    void guiSetup();

    sfg::Label::Ptr test_label;
    sfg::TransformPanel::Ptr transform_panel;
    sfg::CameraPanel::Ptr camera_panel;
    sfg::Outliner::Ptr outliner;

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

    // slots:
    void onOutlinerSelect();
};

#endif // MYGLWINDOW_H
