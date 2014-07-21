#include "myglwindow.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

MyGLWindow::MyGLWindow(sf::VideoMode mode, const sf::String &title) : OpenGLWindow(mode, title)
{
}

MyGLWindow::~MyGLWindow()
{
    delete cube;
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
    cube->setWorldMatrix(
                glm::translate(vec3(2.0f, 1.0f, 1.0f)) *
                glm::rotate(-30.0f, vec3(0.0f, 1.0f, 0.0f)) *
                glm::scale(mat4(1.0f), vec3(0.7f)));
    cube->draw();

    arrow->setWorldMatrix(
                glm::translate(vec3(-1.0f, 0.5f, 2.0f)) *
                glm::rotate(-150.0f, vec3(0.0f, 1.0f, 0.0f)));
    arrow->draw();

    plane->draw();
}

void MyGLWindow::init()
{
    cube = new Cube();
    plane = new Plane(10);
    arrow = new Arrow();

    camera->enableAim();
}
