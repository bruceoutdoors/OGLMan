#include "myglwindow.h"
#include <glm/gtx/transform.hpp>
#include <iostream>

const float LIGHT_MOVE = 0.1f;
const float ZOOM_SPEED = 1.0f;
const float PAN_SPEED = 0.05f;

MyGLWindow::MyGLWindow(sf::VideoMode mode, const sf::String &title) : OpenGLWindow(mode, title)
{
    isWindowSelect = false;
    clock = new sf::Clock();

    arcball = new Arcball();
    walkcam = new WalkCam();
    setActiveCamera(arcball);
}

MyGLWindow::~MyGLWindow()
{
    delete clock;
    delete arcball;
    delete walkcam;
}

void MyGLWindow::draw()
{
    cube->setTranslate(light_position);
}

void MyGLWindow::init()
{
    std::string resource_dir = "./resource/";

    cube2 = new Mesh(resource_dir + "cube.obj");
    cube2->setTexture(resource_dir + "cube-texture.jpg");
    cube2->setName("Textured Cube");

    cube2->setTranslate(vec3(2.0f, 1.0f, 1.0f));
    cube2->setRotateY(-30);
    cube2->setScale(0.7f);

    monkey = new Mesh(resource_dir + "suzanne-triangulated.obj");
    monkey->setTexture(resource_dir + "monkey-texture.jpg");
    monkey->setName("Blender's Suzzane");
    monkey->setTranslateX(-2.0f);
    monkey->setTranslateY(1.0f);
    monkey->setTranslateZ(-2.8f);

    monkey_instance1 = new Mesh(monkey);
    monkey_instance1->setName("Suzzane Instance");
    monkey_instance1->enableFlatColor();
    monkey_instance1->setFlatColor(vec3(.7,.4,.7));
    monkey_instance1->setScale(0.6f);
    monkey_instance1->setTranslateY(1.0f);
    monkey_instance1->setTranslateZ(2.2f);
    monkey_instance1->setRotateX(-180);

    elephant = new Mesh(resource_dir + "elephant-triangulated.obj");
    elephant->setTexture(resource_dir + "elephant-texture-1024.jpg");
    elephant->setName("Gook the elephant");
    elephant->setTranslateX(1.2f);
    elephant->setTranslateZ(-1.5f);
    elephant->setRotateY(-25);
    elephant->setScale(0.15f);

//    elephant->setVisibility(false);

    cube = new Cube();
    cube->setName("Cube mesh");
    cube->setScale(0.3f);

    plane = new Plane(10);
    plane->setName("Plane mesh");
    plane->enableFlatColor();
    plane->setFlatColor(vec3(0.6f,0.8f,1.0f));

    arrow = new Arrow();
    arrow->setName("Arrow (Vertex Colored)");
    arrow->setTranslate(vec3(-1.0f, 2.0f, 2.0f));
    arrow->setRotateY(-150);
    arrow->enableVertexColor();

    cube_instance1 = new Mesh(cube);
    cube_instance1->setName("Cube instance");
    cube_instance1->enableFlatColor();
    cube_instance1->setFlatColor(vec3(1.0f,1.0f,0.0f));
    cube_instance1->setTranslateX(-3.0f);
    cube_instance1->setTranslateY(1.0f);
    cube_instance1->setRotateX(-40);
    cube_instance1->setRotateY(25);

    // set fish eye lens:
//    active_camera->setFocalLength(10);

    walkcam->setForwardVector(vec3(-0.06f, -0.35f, -0.94f));
    walkcam->setEye(vec3(-0.157f, 3.288f, 8.79f));

    arcball->setPitch(20);
    arcball->setYaw(5);
    arcball->setDistance(10);

    guiSetup();
}

void MyGLWindow::guiSetup()
{
    setActive();

    transform_panel = sfg::TransformPanel::Create();

    camera_panel = sfg::CameraPanel::Create();
    camera_panel->setActiveCamera(getActiveCamera());

    outliner = sfg::Outliner::Create(bufferman);

    outliner->GetSignal(sfg::Outliner::OnSelect).Connect(
                std::bind(&MyGLWindow::onOutlinerSelect, this));

    addWindow(transform_panel, "Transform tools");
    addWindow(camera_panel, "Camera Controls", 0, 185);
    addWindow(outliner->getBox(), "Outliner", 0, 350);
}

void MyGLWindow::addWindow(sfg::Widget::Ptr widget, sf::String title,  float x, float y)
{
    auto window = sfg::Window::Create();
    window->SetStyle(window->GetStyle() ^ sfg::Window::RESIZE);
    window->SetTitle(title);
    window->SetPosition(sf::Vector2f(x,y));
    window->Add(widget);

    window->GetSignal(sfg::Widget::OnMouseEnter).Connect(
                std::bind(&MyGLWindow::onWindowMove, this));
    window->GetSignal(sfg::Widget::OnMouseLeave).Connect(
                std::bind(&MyGLWindow::onWindowMoveRelease, this));

    desktop.Add(window);
}

bool MyGLWindow::handleEvents()
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

void MyGLWindow::guiDraw()
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

bool MyGLWindow::keyboardEventHandler(int key)
{
    switch (key) {
    case sf::Keyboard::Escape:
        this->close();
        return true;

    case sf::Keyboard::F11:
        toggleFullscreen();
        break;

    case sf::Keyboard::C:
        getActiveCamera() == arcball ? setActiveCamera(walkcam) : setActiveCamera(arcball);
        camera_panel->setActiveCamera(getActiveCamera());
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

    case sf::Keyboard::U:
        light_position.z += LIGHT_MOVE;
        break;
    case sf::Keyboard::J:
        light_position.z -= LIGHT_MOVE;
        break;
    case sf::Keyboard::H:
        light_position.x -= LIGHT_MOVE;
        break;
    case sf::Keyboard::K:
        light_position.x += LIGHT_MOVE;
        break;
    case sf::Keyboard::O:
        light_position.y += LIGHT_MOVE;
        break;
    case sf::Keyboard::L:
        light_position.y -= LIGHT_MOVE;
        break;
    }

    return false;
}

void MyGLWindow::onWindowMove()
{
//    std::cout << "window is selected!!" << std::endl;
    isWindowSelect = true;
}

void MyGLWindow::onWindowMoveRelease()
{
//    std::cout << "window is released!!" << std::endl;
    isWindowSelect = false;
}

void MyGLWindow::onOutlinerSelect()
{
    if (outliner->getSelectedMesh() != nullptr) {
        std::cout << "You have selected: "
                  << outliner->getSelectedMesh()->getName()
                  << std::endl;
    } else {
        std::cout << "Nothing is selected." << std::endl;
    }

    transform_panel->setActiveMesh(outliner->getSelectedMesh());
}
