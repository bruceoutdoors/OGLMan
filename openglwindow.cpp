#include "openglwindow.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;

const float LIGHT_MOVE = 0.1f;
const float ZOOM_SPEED = 1.0f;
const float PAN_SPEED = 0.05f;

OpenGLWindow::OpenGLWindow(sf::VideoMode mode, const sf::String &title) :
    sf::Window(mode, title),
    m_mode(mode),
    m_title(title),
    isFullscreen(false),
    isWireframeMode(false)
{
    isLightOn = true;

    light_position = vec3(0.0f, 3.0f, 1.0f);
    ambientLight = vec4(0.05f, 0.05f, 0.05f ,1.0f);

    std::string shader_dir = "./shaders/";
    default_shader = new ShaderMan(shader_dir + "default");
    flat_shader = new ShaderMan(shader_dir + "flat");

    bufferman = new BufferMan();

    arcball = new Arcball();
    walkcam = new WalkCam();

    active_camera = arcball;

    Mesh::setCamera(active_camera);
    Mesh::setBufferMan(bufferman);

    shadermanSetup();
}

OpenGLWindow::~OpenGLWindow()
{
    delete default_shader;
    delete flat_shader;
    delete bufferman;
    delete arcball;
    delete walkcam;
}

void OpenGLWindow::toggleFullscreen()
{
    isFullscreen = !isFullscreen;

    if (isFullscreen) {
        create(sf::VideoMode::getDesktopMode(), m_title, sf::Style::Fullscreen);
        resizeGL(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    } else {
        create(m_mode, m_title, sf::Style::Resize | sf::Style::Close);
        resizeGL(m_mode.width, m_mode.height);
    }

    // have to setup OpenGL again
    setupGL();

    // use the program
    active_shader->use();

    // recreating the window causes the buffers to get cleared so we need to
    // add the data back again.
    bufferman->setupBuffers();
}

void OpenGLWindow::run()
{
    setup();

    while (true) {
        if (handleEvents()) break;
        renderScene();
    }
}

void OpenGLWindow::setup()
{
    setupGL();

    init();

    bufferman->setupBuffers();
    resizeGL(getSize().x, getSize().y);
}

void OpenGLWindow::setupGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void OpenGLWindow::renderScene()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    if (isLightOn) {
        vec3 eyePositionWorld = active_camera->getEye();
        glUniform4fv(ambientLightUniformLocation, 1, &ambientLight[0]);
        glUniform3fv(lightPositionUniformLocation, 1, &light_position[0]);
        glUniform3fv(eyePositionWorldUniformLocation, 1, &eyePositionWorld[0]);
    }

    draw();

    display();
}

void OpenGLWindow::setupLights()
{
    eyePositionWorldUniformLocation = active_shader->getUniformLoc("eyePositionWorld");
    ambientLightUniformLocation = active_shader->getUniformLoc("ambientLight");
    lightPositionUniformLocation = active_shader->getUniformLoc("lightPosition");
}

void OpenGLWindow::shadermanSetup()
{
    if (isLightOn) {
        active_shader = default_shader;
        setupLights();
    } else {
        active_shader = flat_shader;
    }
    Mesh::setShaderMan(active_shader);
}

GLvoid OpenGLWindow::resizeGL(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);         // Reset the current viewport
    float aspect_ratio = ((float)width)/height;
    active_camera->setAspectRatio(aspect_ratio);
}

void OpenGLWindow::wireframeToggle()
{
    isWireframeMode = !isWireframeMode;
    if (isWireframeMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_CULL_FACE);
    } else {
        glPolygonMode(GL_FRONT, GL_FILL);
        glEnable(GL_CULL_FACE);
    }
}

bool OpenGLWindow::handleEvents()
{
    sf::Event e;
    while (this->pollEvent(e)) {
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
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                active_camera->mouseDrag(vec2(e.mouseMove.x, e.mouseMove.y));
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                active_camera->pan(vec2(e.mouseMove.x, e.mouseMove.y), PAN_SPEED);
            }
            break;

        case sf::Event::MouseWheelMoved:
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

bool OpenGLWindow::keyboardEventHandler(int key)
{
    switch (key) {
    case sf::Keyboard::Escape:
        this->close();
        return true;

    case sf::Keyboard::F11:
        toggleFullscreen();
        break;

    case sf::Keyboard::C:
        active_camera == arcball ? active_camera = walkcam : active_camera = arcball;
        // update the mesh's Camera pointer
        Mesh::setCamera(active_camera);
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

