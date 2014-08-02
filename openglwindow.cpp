#include "openglwindow.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;

OpenGLWindow::OpenGLWindow(sf::VideoMode mode,
                           const sf::String &title,
                           unsigned int style) :
    sf::Window(mode, title, style),
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



