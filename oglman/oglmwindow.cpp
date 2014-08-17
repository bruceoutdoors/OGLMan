#include "oglmwindow.h"
#include <sstream>
#include <iostream>

using glm::vec2;
using glm::vec3;
using glm::vec4;

const vec3 select_color = vec3(1);
const vec3 wireframe_color = vec3(.5, .5, 1);

OGLMWindow::OGLMWindow(sf::VideoMode mode,
                           const sf::String &title,
                           unsigned int style) :
    sf::Window(mode, title, style),
    m_mode(mode),
    m_title(title),
    isFullscreen(false),
    isWireframeMode(false),
    isFPSCountEnabled(false)
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

OGLMWindow::~OGLMWindow()
{
    delete default_shader;
    delete flat_shader;
    delete bufferman;
}

void OGLMWindow::toggleFullscreen()
{
    isFullscreen = !isFullscreen;

    if (isFullscreen) {
        create(sf::VideoMode::getDesktopMode(), m_title, sf::Style::Fullscreen);
    } else {
        create(m_mode, m_title, sf::Style::Resize | sf::Style::Close);
    }

    resizeGL();

    // recreating the window causes the buffers to get cleared so we need to
    // add the data back again.
    bufferman->setupBuffers();
}

void OGLMWindow::run()
{
    setup();

    while (true) {
        sf::Event e;

        while (this->pollEvent(e)) {
            switch (e.type) {
            case sf::Event::Closed:
                this->close();
                return;
                break;

            // Resize event : adjust viewport
            case sf::Event::Resized:
                resizeGL();
                break;

            default:
                if (handleEvents(e)) return;
                break; // suppress compiler complains
            }
        }

        renderScene();
        display();
    }
}

void OGLMWindow::setup()
{
    init();

    bufferman->setupBuffers();
    std::cout << "Total vertices in Scene: " << bufferman->getTotalVectices() << std::endl;
    resizeGL();
}

void OGLMWindow::renderScene()
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

    if (isFPSCountEnabled) {
        if (fps_clock.getElapsedTime().asMilliseconds() >= 1000) {
            fps_clock.restart();
            std::stringstream sstr;
            sstr << fps_counter;
            setTitle(m_title + " -- FPS: " + sstr.str());
            fps_counter = 0;
        }
        ++fps_counter;
    }
}

void OGLMWindow::shadermanSetup()
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

void OGLMWindow::setActiveCamera(Camera *cam)
{
    active_camera = cam;
    // update the mesh's Camera pointer
    Mesh::setCamera(active_camera);

    updateCameraAspectRatio();
}

Camera *OGLMWindow::getActiveCamera() const
{
    return active_camera;
}

float OGLMWindow::getFPS() const
{
    if (!isFPSCountEnabled) return -1;

    return fps_counter;
}

void OGLMWindow::enableFPSCounter()
{
    fps_counter = 0;
    fps_clock.restart();
    isFPSCountEnabled = true;
}

void OGLMWindow::disableFPSCounter()
{
    fps_counter = 0;
    isFPSCountEnabled = false;
}

void OGLMWindow::onLights()
{
    isLightOn = true;
    shadermanSetup();
}

void OGLMWindow::offLights()
{
    isLightOn = false;
    shadermanSetup();
}

bool OGLMWindow::hasLights() const
{
    return isLightOn;
}

bool OGLMWindow::hasWireframeMode() const
{
    return isWireframeMode;
}

void OGLMWindow::wireframeDisplay()
{
    isWireframeMode = true;
    offLights();
}

void OGLMWindow::shadedDisplay()
{
    isWireframeMode = false;
    onLights();
}

void OGLMWindow::flatShadeDisplay()
{
    isWireframeMode = false;
    offLights();
}

void OGLMWindow::wireframeModeOn()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_CULL_FACE);
}

void OGLMWindow::wireframeModeOff()
{
    glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_CULL_FACE);
}

void OGLMWindow::drawSelectHighlight()
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

GLvoid OGLMWindow::resizeGL()
{
    // Resize the current viewport
    glViewport(0, 0, getSize().x, getSize().y);
    updateCameraAspectRatio();
}

void OGLMWindow::updateCameraAspectRatio()
{
    float aspect_ratio = ((float)getSize().x) / getSize().y;
    active_camera->setAspectRatio(aspect_ratio);
}

bool OGLMWindow::handleEvents(sf::Event e)
{
    return false;
}
