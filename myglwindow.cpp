#include "myglwindow.h"
#include <glm/gtx/transform.hpp>
#include <iostream>

const float LIGHT_MOVE = 0.1f;
const float ZOOM_SPEED = 1.0f;
const float PAN_SPEED = 0.05f;

MyGLWindow::MyGLWindow(sf::VideoMode mode, const sf::String &title) : OpenGLWindow(mode, title)
{
    isWindowSelect = false;

    setActive();
    auto window = sfg::Window::Create();
    window->SetTitle("An amazing title");
    test_label = sfg::Label::Create("Hello I am a window\nthat serves to occupy\nspace" );
    window->Add(test_label);
    desktop.Add(window);

    window->GetSignal(sfg::Widget::OnMouseEnter).Connect(std::bind(&MyGLWindow::onWindowMove, this));
    window->GetSignal(sfg::Widget::OnMouseLeave).Connect(std::bind(&MyGLWindow::onWindowMoveRelease, this));

    arcball = new Arcball();
    walkcam = new WalkCam();
    setActiveCamera(arcball);
}

MyGLWindow::~MyGLWindow()
{
    delete cube2;
    delete cube;
    delete monkey;
    delete elephant;
    delete plane;
    delete arrow;

    delete arcball;
    delete walkcam;
}

void MyGLWindow::draw()
{
    cube->setWorldMatrix(
                glm::translate(light_position) *
                glm::scale(mat4(1.0f), vec3(0.3f)));
    cube->draw();

    cube->enableFlatColor();
    cube->setFlatColor(vec3(1.0f,1.0f,0.0f));
    cube->setWorldMatrix(
                glm::translate(vec3(-3.0f, 1.0f, 0.0f)) *
                glm::rotate(-40.0f, vec3(1.0f, 0.0f, 0.0f)) *
                glm::rotate(25.0f, vec3(0.0f, 1.0f, 0.0f)));
    cube->draw();
    cube->disableFlatColor();

    cube2->setWorldMatrix(
                glm::translate(vec3(2.0f, 1.0f, 1.0f)) *
                glm::rotate(-30.0f, vec3(0.0f, 1.0f, 0.0f)) *
                glm::scale(mat4(1.0f), vec3(0.7f)));
    cube2->draw();


    arrow->setWorldMatrix(
                glm::translate(vec3(-1.0f, 2.0f, 2.0f)) *
                glm::rotate(-150.0f, vec3(0.0f, 1.0f, 0.0f)));
    arrow->draw();

    monkey->draw();
    elephant->draw();
    plane->draw();
}

void MyGLWindow::init()
{
    std::string resource_dir = "./resource/";

    cube2 = new Mesh(resource_dir + "cube.obj");
    cube2->setTexture(resource_dir + "cube-texture.jpg");

    monkey = new Mesh(resource_dir + "suzanne-triangulated.obj");
    monkey->setTexture(resource_dir + "monkey-texture.jpg");

    monkey->setTranslateX(-2.0f);
    monkey->setTranslateY(1.0f);
    monkey->setTranslateZ(-2.8f);

    elephant = new Mesh(resource_dir + "elephant-triangulated.obj");
    elephant->setTexture(resource_dir + "elephant-texture-1024.jpg");

    elephant->setTranslateX(1.2f);
    elephant->setTranslateZ(-1.5f);
    elephant->setRotateY(-25);
    elephant->setScale(0.15f);

    cube = new Cube();
    plane = new Plane(10);
    arrow = new Arrow();

    arrow->enableVertexColor();

    plane->enableFlatColor();
    plane->setFlatColor(vec3(0.6f,0.8f,1.0f));

    // set fish eye lens:
//    active_camera->setFocalLength(10);

    walkcam->setForwardVector(vec3(-0.06f, -0.35f, -0.94f));
    walkcam->setEye(vec3(-0.157f, 3.288f, 8.79f));

    arcball->setPitch(20);
    arcball->setYaw(5);
    arcball->setDistance(10);
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
                active_camera->mouseDrag(vec2(e.mouseMove.x, e.mouseMove.y));
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                active_camera->pan(vec2(e.mouseMove.x, e.mouseMove.y), PAN_SPEED);
            }
            break;

        case sf::Event::MouseWheelMoved:
            if (isWindowSelect) break;
            if (e.mouseWheel.delta > 0) {
                active_camera->moveForward(ZOOM_SPEED);
            } else {
                active_camera->moveForward(-ZOOM_SPEED);
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
    desktop.Update(1.0f);
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
        break;

    case sf::Keyboard::Num7:
        isLightOn = !isLightOn;
        shadermanSetup();
        break;

    case sf::Keyboard::Num4:
        wireframeToggle();
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
