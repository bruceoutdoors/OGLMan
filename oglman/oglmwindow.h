#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <GL/glew.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "shaderman.h"
#include "bufferman.h"
#include "camera.h"
#include "mesh.h"

class OGLMWindow : public sf::Window
{
    public:
        OGLMWindow(sf::VideoMode mode,
                     const sf::String &title,
                     unsigned int style = sf::Style::Default);
        virtual ~OGLMWindow();
        virtual void draw() = 0;
        virtual void init() = 0;
        virtual bool handleEvents(sf::Event e);
        virtual void renderScene();
        void toggleFullscreen();
        void run();
        void setup();
        void shadermanSetup();
        void setActiveCamera(Camera *cam);
        Camera *getActiveCamera() const;
        float getFPS() const;
        void enableFPSCounter();
        void disableFPSCounter();

        void onLights();
        void offLights();
        bool hasLights() const;

        bool hasWireframeMode() const;

        void wireframeDisplay();
        void shadedDisplay();
        void flatShadeDisplay();

    protected:
        ShaderMan *active_shader;
        ShaderMan *flat_shader;
        ShaderMan *default_shader;
        BufferMan *bufferman;

        glm::vec3 light_position;
        glm::vec4 ambientLight;

        void wireframeModeOn();
        void wireframeModeOff();

        void drawSelectHighlight();

    private:
        GLvoid resizeGL();
        void updateCameraAspectRatio();

        sf::VideoMode m_mode;
        sf::String m_title;
        sf::Clock fps_clock;

        Camera *active_camera;

        GLint ambientLight_loc;
        GLint lightPosition_loc;
        GLint eyePositionWorld_loc;
        GLint hasWireframeMode_loc;
        GLint wireframeColor_loc;
        GLint isSelectRender_loc;
        GLint selectColor_loc;

        bool isFullscreen;
        bool isWireframeMode;
        bool isLightOn;
        bool isFPSCountEnabled;

        float fps_counter;
};

#endif // OPENGLWINDOW_H
