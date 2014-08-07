#include "openglwindow.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;

const vec3 select_color = vec3(1);

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
    Mesh::setBufferMan(bufferman);

    shadermanSetup();
}

OpenGLWindow::~OpenGLWindow()
{
    delete default_shader;
    delete flat_shader;
    delete bufferman;
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
    init();
    setupGL();

    bufferman->setupBuffers();
    resizeGL(getSize().x, getSize().y);
}

void OpenGLWindow::setupGL()
{
    glEnable(GL_CULL_FACE);
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

    if (hasWireframeMode()) wireframeModeOn();
    draw();
    bufferman->draw();
    // return back to drawing triangles, or GUI will get
    // drawn as lines
    if (hasWireframeMode()) wireframeModeOff();

    drawSelectHighlight();

    // disable depth test so SFGUI can render
    glDisable(GL_DEPTH_TEST);

    // unbound any shader programs, or GUI will not render
    glUseProgram(0);

    guiDraw();
    display();
}

void OpenGLWindow::setupLights()
{
    eyePositionWorld_loc = active_shader->getUniformLoc("eyePositionWorld");
    ambientLight_loc = active_shader->getUniformLoc("ambientLight");
    lightPosition_loc = active_shader->getUniformLoc("lightPosition");
}

void OpenGLWindow::shadermanSetup()
{
    if (isLightOn) {
        active_shader = default_shader;
        setupLights();
    } else {
        active_shader = flat_shader;
    }

    isSelectRender_loc = active_shader->getUniformLoc("isSelectRender");
    selectColor_loc = active_shader->getUniformLoc("selectColor");

    Mesh::setShaderMan(active_shader);
    Mesh::setWireframeColor(vec3(.5f,.5f,1));

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
    Mesh::setWireframeMode(true);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_CULL_FACE);
}

void OpenGLWindow::wireframeModeOff()
{
    Mesh::setWireframeMode(false);
    glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_CULL_FACE);
}

void OpenGLWindow::drawSelectHighlight()
{
    wasLightOn = isLightOn;
    if (isLightOn) offLights();

    glUniform1f(isSelectRender_loc, true);
    glLineWidth(1.5f);
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    bufferman->drawSelected();
    glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_CULL_FACE);
    glLineWidth(1);
    glUniform1f(isSelectRender_loc, false);

    if (wasLightOn) onLights();
}

GLvoid OpenGLWindow::resizeGL(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);         // Reset the current viewport
    float aspect_ratio = ((float)width)/height;
    active_camera->setAspectRatio(aspect_ratio);
}
