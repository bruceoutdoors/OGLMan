#include "openglwindow.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec3;

OpenGLWindow::OpenGLWindow(sf::VideoMode mode, const sf::String &title) : sf::Window(mode, title)
{
    m_title = title;
    m_mode = mode;
    m_fullscreen = false;
}

OpenGLWindow::~OpenGLWindow()
{
    delete shaderman;
    delete bufferman;
    delete camera;
}

void OpenGLWindow::toggleFullscreen()
{
    m_fullscreen = !m_fullscreen;

    if (m_fullscreen) {
        create(sf::VideoMode::getDesktopMode(), m_title, sf::Style::Fullscreen);
        setup();
        resizeGL(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    } else {
        create(m_mode, m_title, sf::Style::Resize | sf::Style::Close);
        setup();
        resizeGL(m_mode.width, m_mode.height);
    }
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
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    std::string path = "D:/Libraries/Documents/Qt/sfml-opengl/shaders/default";
    shaderman = new ShaderMan(path);
    bufferman = new BufferMan();
    camera = new Camera();

    eyePositionWorldUniformLocation = shaderman->getUniformLoc("eyePositionWorld");
    ambientLightUniformLocation = shaderman->getUniformLoc("ambientLight");
    lightPositionUniformLocation = shaderman->getUniformLoc("lightPosition");

    lightPosition = vec3(0.0f, 1.0f, 1.0f);
    ambientLight = vec4(0.05f, 0.05f, 0.05f ,1.0f);

    Mesh::setShaderMan(shaderman);
    Mesh::setBufferMan(bufferman);
    Mesh::setCamera(camera);

    init();

    bufferman->setupBuffers();
    resizeGL(getSize().x, getSize().y);
}

void OpenGLWindow::renderScene()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    vec3 eyePositionWorld = camera->getPosition();
    glUniform4fv(ambientLightUniformLocation, 1, &ambientLight[0]);
    glUniform3fv(lightPositionUniformLocation, 1, &lightPosition[0]);
    glUniform3fv(eyePositionWorldUniformLocation, 1, &eyePositionWorld[0]);

    draw();

    display();
}

GLvoid OpenGLWindow::resizeGL(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);         // Reset the current viewport
    float aspect_ratio = ((float)width)/height;
    camera->setAspectRatio(aspect_ratio);
}

bool OpenGLWindow::handleEvents()
{
    sf::Event event;
    while (this->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            this->close();
            return true;
            break;

        // Resize event : adjust viewport
        case sf::Event::Resized:
            resizeGL(event.size.width, event.size.height);
            break;

        // Handle keyboard events
        case sf::Event::KeyPressed:
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                this->close();
                return true;
                break;

            case sf::Keyboard::F1:
                toggleFullscreen();
                break;

            default:
                break; // suppress enum not handled warnings

            }
            break;

        default:
            break; // suppress enum not handled warnings
        }
    }
    return false;
}

