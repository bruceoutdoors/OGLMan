#include "elephantwindow.h"

const float LIGHT_MOVE = 0.1f;
const float ZOOM_SPEED = 1.0f;
const float INIT_SCALE = 0.25f;

ElephantWindow::ElephantWindow(sf::VideoMode mode, const sf::String &title)
    : GuiWindow(mode, title)
{
    arcball = new Arcball();
    setActiveCamera(arcball);

    enableFPSCounter();
}

ElephantWindow::~ElephantWindow()
{
    delete arcball;
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

bool ElephantWindow::handleEvents(sf::Event e)
{
    GuiWindow::handleEvents(e);
    switch (e.type) {
        case sf::Event::KeyPressed:
            if (keyboardEventHandler(e.key.code)) return true;
            break;

        case sf::Event::MouseMoved:
            if (isWindowSelect) break;
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                getActiveCamera()->mouseDrag(vec2(e.mouseMove.x, e.mouseMove.y));
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                getActiveCamera()->pan(vec2(e.mouseMove.x, e.mouseMove.y));
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
    return false;
}

void ElephantWindow::guiSetup()
{
    setActive();

    transform_panel = sfg::TransformPanel::Create();
    transform_panel->setActiveMesh(elephant);

    camera_panel = sfg::CameraPanel::Create();
    camera_panel->setActiveCamera(arcball);

    addWindow(transform_panel->get(), "Transform tools");
    addWindow(camera_panel->get(), "Camera Controls", 0, 180);
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
