#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <GL/glew.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "oglman/shaderman.h"
#include "oglman/bufferman.h"
#include "oglman/arcball.h"
#include "oglman/walkcam.h"
#include "oglman/mesh.h"

class OpenGLWindow : public sf::Window
{
    public:
        OpenGLWindow(sf::VideoMode mode,
                     const sf::String &title,
                     unsigned int style = sf::Style::Default);
        virtual ~OpenGLWindow();
        virtual void draw() = 0;
        virtual void init() = 0;
        virtual bool handleEvents() = 0;
        virtual void guiDraw();
        void wireframeToggle();
        void toggleFullscreen();
        void run();
        void setup();
        void setupGL();
        void renderScene();
        void setupLights();
        void shadermanSetup();

    protected:
        GLvoid resizeGL(GLsizei width, GLsizei height);

        ShaderMan *active_shader;
        ShaderMan *flat_shader;
        ShaderMan *default_shader;
        BufferMan *bufferman;
        Camera *active_camera;
        Arcball *arcball;
        WalkCam *walkcam;

        glm::vec3 light_position;
        glm::vec4 ambientLight;
        glm::vec2 oldMousePosition;

        bool isLightOn;
        bool isFullscreen;
        bool isWireframeMode;

    private:
        sf::VideoMode m_mode;
        sf::String m_title;

        GLint ambientLightUniformLocation;
        GLint lightPositionUniformLocation;
        GLint eyePositionWorldUniformLocation;
};

#endif // OPENGLWINDOW_H
