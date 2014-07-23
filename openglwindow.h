#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <GL/glew.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "oglman/shaderman.h"
#include "oglman/bufferman.h"
#include "oglman/arcball.h"
#include "oglman/mesh.h"

class OpenGLWindow : public sf::Window
{
    public:
        OpenGLWindow(sf::VideoMode mode, const sf::String &title);
        virtual ~OpenGLWindow();
        void toggleFullscreen();
        void run();
        void setup();
        void setupGL();
        void renderScene();
        virtual void draw() = 0;
        virtual void init() = 0;

    protected:
        GLvoid resizeGL(GLsizei width, GLsizei height);
        ShaderMan *shaderman;
        BufferMan *bufferman;
        Camera *camera;

        glm::vec3 light_position;
        glm::vec4 ambientLight;
        glm::vec2 oldMousePosition;


    private:
        bool handleEvents();
        bool keyboardEventHandler(int key);

        bool m_fullscreen;
        sf::VideoMode m_mode;
        sf::String m_title;

        GLint ambientLightUniformLocation;
        GLint lightPositionUniformLocation;
        GLint eyePositionWorldUniformLocation;

};

#endif // OPENGLWINDOW_H
