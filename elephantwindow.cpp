#include "elephantwindow.h"

const float LIGHT_MOVE = 0.1f;
const float ZOOM_SPEED = 1.0f;
const float PAN_SPEED  = 0.05f;
const float INIT_SCALE = 0.25f;

const sf::Vector2f ALIGN_LEFT   = sf::Vector2f(0.0f, 0.5f);
const sf::Vector2f ALIGN_RIGHT  = sf::Vector2f(1.0f, 0.5f);
const sf::Vector2f ALIGN_CENTER = sf::Vector2f(0.5f, 0.5f);

ElephantWindow::ElephantWindow(sf::VideoMode mode, const sf::String &title)
    : OpenGLWindow(mode, title)
{
    isWindowSelect = false;
    clock = new sf::Clock();

    arcball = new Arcball();
    setActiveCamera(arcball);
}

ElephantWindow::~ElephantWindow()
{
    delete clock;
}

void ElephantWindow::draw()
{
}

void ElephantWindow::init()
{
    std::string resource_dir = "./resource/";
    elephant = new Mesh(resource_dir + "elephant-triangulated.obj");
    elephant->setTexture(resource_dir + "elephant-texture-1024.jpg");
    elephant->setScale(INIT_SCALE);

    plane = new Plane(10);

    offLights();
    guiSetup();
}

bool ElephantWindow::handleEvents()
{
    sf::Event e;
    while (this->pollEvent(e)) {
        desktop.HandleEvent(e);
        switch (e.type) {
        case sf::Event::Closed:
            this->close();
            return true;
            break;

        // Resize event : adjust viewport
        case sf::Event::Resized:
            resizeGL(e.size.width, e.size.height);
            break;

        // Handle keyboard events
        case sf::Event::KeyPressed:
            if (keyboardEventHandler(e.key.code)) return true;
            break;

        case sf::Event::MouseMoved:
            if (isWindowSelect) break;
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                getActiveCamera()->mouseDrag(vec2(e.mouseMove.x, e.mouseMove.y));
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                getActiveCamera()->pan(vec2(e.mouseMove.x, e.mouseMove.y), PAN_SPEED);
            }
            break;

        case sf::Event::MouseWheelMoved:
            if (isWindowSelect) break;
            if (e.mouseWheel.delta > 0) {
                getActiveCamera()->moveForward(ZOOM_SPEED);
            } else {
                getActiveCamera()->moveForward(-ZOOM_SPEED);
            }
            break;


        default:
            break; // suppress enum not handled warnings
        }
    }
    return false;
}

void ElephantWindow::guiDraw()
{
    // Update the GUI every 1ms
    if( clock->getElapsedTime().asMicroseconds() >= 1000 ) {
        auto delta = static_cast<float>( clock->getElapsedTime().asMicroseconds() ) / 1000000.f;
        // Update() takes the elapsed time in seconds.
        desktop.Update(delta);
        clock->restart();
    }
    sfgui.Display(*this);
}

void ElephantWindow::guiSetup()
{
    setActive();

    transform_panel = sfg::TransformPanel::Create();
    transform_panel->setActiveMesh(elephant);

    camera_panel = sfg::CameraPanel::Create();
    camera_panel->setActiveCamera(arcball);

    addWindow(transform_panel, "Transform tools");
    addWindow(camera_panel, "Camera Controls", 0, 180);
}

void ElephantWindow::addWindow(sfg::Widget::Ptr widget, sf::String title,  float x, float y)
{
    auto window = sfg::Window::Create();
    window->SetStyle(window->GetStyle() ^ sfg::Window::RESIZE);
    window->SetTitle(title);
    window->SetPosition(sf::Vector2f(x,y));
    window->Add(widget);

    window->GetSignal(sfg::Widget::OnMouseEnter).Connect(
                std::bind(&ElephantWindow::onWindowMove, this));
    window->GetSignal(sfg::Widget::OnMouseLeave).Connect(
                std::bind(&ElephantWindow::onWindowMoveRelease, this));

    desktop.Add(window);
}

bool ElephantWindow::keyboardEventHandler(int key)
{
    switch (key) {
    case sf::Keyboard::Escape:
        this->close();
        return true;

    case sf::Keyboard::F11:
        toggleFullscreen();
        break;

    case sf::Keyboard::Num4:
        wireframeDisplay();
        break;

    case sf::Keyboard::Num7:
        shadedDisplay();
        break;

    case sf::Keyboard::Num8:
        flatShadeDisplay();
        break;

    }

    return false;
}

void ElephantWindow::onWindowMove()
{
    isWindowSelect = true;
}

void ElephantWindow::onWindowMoveRelease()
{
    isWindowSelect = false;
}



