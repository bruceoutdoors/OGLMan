#ifndef GUIWINDOW_H
#define GUIWINDOW_H

#include "oglman/oglmwindow.h"
#include <SFGUI/SFGUI.hpp>

class GuiWindow : public OGLMWindow
{
public:
    GuiWindow(sf::VideoMode mode, const sf::String &title);
    virtual ~GuiWindow();
    virtual void draw() = 0;
    virtual void init() = 0;
    bool handleEvents(sf::Event e);
    void renderScene();

protected:
    void addWindow(sfg::Widget::Ptr widget,
                   sf::String title = "Default Title",
                   float x = 0, float y = 0);
    bool isWindowSelect;

private:
    sf::Clock *clock;
    sfg::Desktop desktop;
    sfg::SFGUI sfgui;


    // slots
    void onWindowMove();
    void onWindowMoveRelease();
};

#endif // GUIWINDOW_H
