#include "guiwindow.h"

GuiWindow::GuiWindow(sf::VideoMode mode, const sf::String &title) :
    OpenGLWindow(mode, title),
    isWindowSelect(false)
{
    clock = new sf::Clock();
}

GuiWindow::~GuiWindow()
{
    delete clock;
}

bool GuiWindow::handleEvents(sf::Event e)
{
    desktop.HandleEvent(e);
}

void GuiWindow::guiDraw()
{
    // Update the GUI every 100ms
    if (clock->getElapsedTime().asMilliseconds() >= 100) {
        auto delta = static_cast<float>(clock->getElapsedTime().asMicroseconds()) / 1000000.f;
        // Update() takes the elapsed time in seconds.
        desktop.Update(delta);
        clock->restart();
    }

    sfgui.Display(*this);
}

void GuiWindow::addWindow(sfg::Widget::Ptr widget, sf::String title, float x, float y)
{
    auto window = sfg::Window::Create();
    window->SetStyle(window->GetStyle() ^ sfg::Window::RESIZE);
    window->SetTitle(title);
    window->SetPosition(sf::Vector2f(x, y));
    window->Add(widget);

    window->GetSignal(sfg::Widget::OnMouseEnter).Connect(
        std::bind(&GuiWindow::onWindowMove, this));
    window->GetSignal(sfg::Widget::OnMouseLeave).Connect(
        std::bind(&GuiWindow::onWindowMoveRelease, this));

    desktop.Add(window);
}

void GuiWindow::onWindowMove()
{
    isWindowSelect = true;
}

void GuiWindow::onWindowMoveRelease()
{
    isWindowSelect = false;
}
