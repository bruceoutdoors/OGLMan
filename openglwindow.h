#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <GL/glew.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "oglman/shaderman.h"
#include "oglman/bufferman.h"
#include "oglman/camera.h"
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
        virtual void guiDraw() {}
        void toggleFullscreen();
        void run();
        void setup();
        void setupGL();
        void renderScene();
        void setupLights();
        void shadermanSetup();
        void setActiveCamera(Camera *cam);
        Camera *getActiveCamera() const;

        void onLights();
        void offLights();
        bool hasLights() const;

        bool hasWireframeMode() const;

        void wireframeDisplay();
        void shadedDisplay();
        void flatShadeDisplay();

    protected:
        GLvoid resizeGL(GLsizei width, GLsizei height);

        ShaderMan *active_shader;
        ShaderMan *flat_shader;
        ShaderMan *default_shader;
        BufferMan *bufferman;

        glm::vec3 light_position;
        glm::vec4 ambientLight;
        glm::vec2 oldMousePosition;

        void wireframeModeOn();
        void wireframeModeOff();


    private:
        sf::VideoMode m_mode;
        sf::String m_title;

        Camera *active_camera;

        GLint ambientLightUniformLocation;
        GLint lightPositionUniformLocation;
        GLint eyePositionWorldUniformLocation;

        bool isFullscreen;
        bool isWireframeMode;
        bool isLightOn;
};

#endif // OPENGLWINDOW_H
