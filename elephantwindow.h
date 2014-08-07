#ifndef ELEPHANTWINDOW_H
#define ELEPHANTWINDOW_H

#include "openglwindow.h"

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
    void setupSpinButton(sfg::SpinButton::Ptr &b, float min, float max, float step, unsigned int precision = 2);
    void attachLabel(sf::String text, sf::Uint32 r, sf::Uint32 c,
                     sf::Uint32 rs, sf::Uint32 cs,
                     sf::Vector2f align = sf::Vector2f(0.5f, 0.5f));
    bool keyboardEventHandler(int key);
    void onWindowMove();
    void onWindowMoveRelease();
    std::string floatToString(float fl, unsigned int precision = 2);

    sf::Clock *clock;
    Arcball *arcball;
    Mesh *elephant;
    Plane *plane;

    bool isWindowSelect;

    // GUI:
    sfg::SFGUI sfgui;
    sfg::Desktop desktop;
    sfg::Table::Ptr table;
    sfg::Button::Ptr reset_trans_button;
    sfg::Scale::Ptr scale_slider;
    sfg::Label::Ptr scale_label;
    sfg::SpinButton::Ptr focal_length;
    sfg::SpinButton::Ptr near_plane;
    sfg::SpinButton::Ptr far_plane;
    std::vector<sfg::SpinButton::Ptr> spin_group;

    void onTranslateX();
    void onTranslateY();
    void onTranslateZ();
    void onRotateX();
    void onRotateY();
    void onRotateZ();
    void onScale();
    void onFocalLength();
    void onNearPlane();
    void onFarPlane();
    void onResetTransformations();
};

#endif // ELEPHANTWINDOW_H
