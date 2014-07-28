#include "myglwindow.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

MyGLWindow::MyGLWindow(sf::VideoMode mode, const sf::String &title) : OpenGLWindow(mode, title)
{
}

MyGLWindow::~MyGLWindow()
{
    delete cube;
    delete monkey;
    delete plane;
    delete arrow;
}

void MyGLWindow::draw()
{
    cube->setWorldMatrix(
                glm::translate(light_position) *
                glm::scale(mat4(1.0f), vec3(0.3f)));
    cube->draw();
    cube->setWorldMatrix(
                glm::translate(vec3(-3.0f, 1.0f, 0.0f)) *
                glm::rotate(-40.0f, vec3(1.0f, 0.0f, 0.0f)) *
                glm::rotate(25.0f, vec3(0.0f, 1.0f, 0.0f)));
    cube->draw();

    cube->enableFlatColor();
    cube->setFlatColor(vec3(1.0f,1.0f,0.0f));
    cube->setWorldMatrix(
                glm::translate(vec3(2.0f, 1.0f, 1.0f)) *
                glm::rotate(-30.0f, vec3(0.0f, 1.0f, 0.0f)) *
                glm::scale(mat4(1.0f), vec3(0.7f)));
    cube->draw();
    cube->disableFlatColor();

    arrow->setWorldMatrix(
                glm::translate(vec3(-1.0f, 2.0f, 2.0f)) *
                glm::rotate(-150.0f, vec3(0.0f, 1.0f, 0.0f)));
    arrow->draw();

    monkey->setWorldMatrix(
                glm::translate(vec3(0.0f, 1.0f, -2.0f)));
    monkey->draw();

    plane->draw();
}

void MyGLWindow::init()
{
    std::string resource_dir = "./resource/";
    cube = new Mesh(resource_dir + "cube.obj");
    monkey = new Mesh(resource_dir + "suzanne-triangulated.obj");
    plane = new Plane(10);
    arrow = new Arrow();

    arrow->enableVertexColor();

    plane->enableFlatColor();
    plane->setFlatColor(vec3(0.6f,0.8f,1.0f));

    // set fish eye lens:
//    active_camera->setFocalLength(10);

    walkcam->setForwardVector(vec3(-0.06f, -0.35f, -0.94f));
    walkcam->setEye(vec3(-0.157f, 3.288f, 8.79f));

    arcball->setPitch(20);
    arcball->setYaw(5);
    arcball->setDistance(10);
}
