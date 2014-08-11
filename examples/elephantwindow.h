#ifndef ELEPHANTWINDOW_H
#define ELEPHANTWINDOW_H

#include "gui/guiwindow.h"
#include "gui/transformpanel.h"
#include "gui/camerapanel.h"

#include "primitives/plane.h"
#include "oglman/arcball.h"

class ElephantWindow : public GuiWindow
{
public:
    ElephantWindow(sf::VideoMode mode,
                   const sf::String &title = "Gook the elephant");
    virtual ~ElephantWindow();
    void draw();
    void init();
    bool handleEvents(sf::Event e);

private:
    void guiSetup();
    bool keyboardEventHandler(int key);

    Arcball *arcball;
    Mesh *elephant;
    Plane *plane;

    // GUI:
    sfg::TransformPanel::Ptr transform_panel;
    sfg::CameraPanel::Ptr camera_panel;
};

#endif // ELEPHANTWINDOW_H
