#include "openglwindow.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;

const vec3 select_color = vec3(1);
const vec3 wireframe_color = vec3(.5, .5, 1);

OpenGLWindow::OpenGLWindow(sf::VideoMode mode,
                           const sf::String &title,
                           unsigned int style) :
    sf::Window(mode, title, style),
    m_mode(mode),
    m_title(title),
    isFullscreen(false),
    isWireframeMode(false)
{
    light_position = vec3(0.0f, 3.0f, 1.0f);
    ambientLight = vec4(0.05f, 0.05f, 0.05f , 1.0f);

    std::string shader_dir = "./shaders/";
    default_shader = new ShaderMan(shader_dir + "default");
    flat_shader = new ShaderMan(shader_dir + "flat");

    bufferman = new BufferMan();
    Mesh::setBufferMan(bufferman);

    onLights();
}

OpenGLWindow::~OpenGLWindow()
{
    delete default_shader;
    delete flat_shader;
    delete bufferman;
}

bool OpenGLWindow::handleEvents(sf::Event e)
{
    switch (e.type) {
    case sf::Event::Closed:
        this->close();
        return true;
        break;

    // Resize event : adjust viewport
    case sf::Event::Resized:
        resizeGL(e.size.width, e.size.height);
        break;
    }

    return false;
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

    // recreating the window causes the buffers to get cleared so we need to
    // add the data back again.
    bufferman->setupBuffers();
}

void OpenGLWindow::run()
{
    setup();

    while (true) {
        sf::Event e;

        while (this->pollEvent(e)) {
            // handle events for this base class
            if (OpenGLWindow::handleEvents(e)) return;

            // handle events for subclasses
            if (handleEvents(e)) return;
        }

        renderScene();
    }
}

void OpenGLWindow::setup()
{
    init();

    bufferman->setupBuffers();
    resizeGL(getSize().x, getSize().y);
}

void OpenGLWindow::renderScene()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // use shader program as it will nullified later to draw the GUI
    active_shader->use();

    if (isLightOn) {
        vec3 eyePositionWorld = active_camera->getEye();
        glUniform4fv(ambientLight_loc, 1, &ambientLight[0]);
        glUniform3fv(lightPosition_loc, 1, &light_position[0]);
        glUniform3fv(eyePositionWorld_loc, 1, &eyePositionWorld[0]);
    }

    if (hasWireframeMode()) {
        wireframeModeOn();
        glUniform1f(hasWireframeMode_loc, true);
        draw();
        bufferman->draw(true);
        glUniform1f(hasWireframeMode_loc, false);
    } else {
        draw();
        bufferman->draw();
    }

    // if not wireframe mode, turn it on to draw selection wireframe
    if (!hasWireframeMode()) wireframeModeOn();

    drawSelectHighlight();

    // off wireframe for GUI to render properly
    wireframeModeOff();

    // disable depth test so SFGUI can render
    glDisable(GL_DEPTH_TEST);

    // unbound any shader programs, or GUI will not render
    glUseProgram(0);

    guiDraw();
    display();
}

void OpenGLWindow::shadermanSetup()
{
    if (isLightOn) {
        // eliminate redundant calls:
        if (active_shader == default_shader) return;

        active_shader = default_shader;

        // setup lights:
        eyePositionWorld_loc = active_shader->getUniformLoc("eyePositionWorld");
        ambientLight_loc = active_shader->getUniformLoc("ambientLight");
        lightPosition_loc = active_shader->getUniformLoc("lightPosition");
    } else {
        if (active_shader == flat_shader) return;

        active_shader = flat_shader;

        // wireframe render setup:
        isSelectRender_loc = active_shader->getUniformLoc("isSelectRender");
        selectColor_loc = active_shader->getUniformLoc("selectColor");
        hasWireframeMode_loc = active_shader->getUniformLoc("hasWireframeMode");
        wireframeColor_loc = active_shader->getUniformLoc("wireframeColor");
    }

    Mesh::setShaderMan(active_shader);

    glUniform3fv(wireframeColor_loc, 1, &wireframe_color[0]);
    glUniform3fv(selectColor_loc, 1, &select_color[0]);
}

void OpenGLWindow::setActiveCamera(Camera *cam)
{
    active_camera = cam;
    // update the mesh's Camera pointer
    Mesh::setCamera(active_camera);
}

Camera *OpenGLWindow::getActiveCamera() const
{
    return active_camera;
}

void OpenGLWindow::onLights()
{
    isLightOn = true;
    shadermanSetup();
}

void OpenGLWindow::offLights()
{
    isLightOn = false;
    shadermanSetup();
}

bool OpenGLWindow::hasLights() const
{
    return isLightOn;
}

bool OpenGLWindow::hasWireframeMode() const
{
    return isWireframeMode;
}

void OpenGLWindow::wireframeDisplay()
{
    isWireframeMode = true;
    offLights();
}

void OpenGLWindow::shadedDisplay()
{
    isWireframeMode = false;
    onLights();
}

void OpenGLWindow::flatShadeDisplay()
{
    isWireframeMode = false;
    offLights();
}

void OpenGLWindow::wireframeModeOn()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_CULL_FACE);
}

void OpenGLWindow::wireframeModeOff()
{
    glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_CULL_FACE);
}

void OpenGLWindow::drawSelectHighlight()
{
    bool wasLightOn = isLightOn;

    if (isLightOn) offLights();

    glUniform1f(isSelectRender_loc, true);
    glLineWidth(1.5f);
    bufferman->drawSelected();
    glLineWidth(1);
    glUniform1f(isSelectRender_loc, false);

    if (wasLightOn) onLights();
}

GLvoid OpenGLWindow::resizeGL(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);         // Reset the current viewport
    float aspect_ratio = ((float)width) / height;
    active_camera->setAspectRatio(aspect_ratio);
}
