#include "arcball.h"
#include <glm/gtx/transform.hpp>

//#include <iostream>
//using namespace std;

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

const vec3 X_AXIS = vec3(1,0,0);
const vec3 Y_AXIS = vec3(0,1,0);

Arcball::Arcball(float dist) :
    pitch(0),
    yaw(0),
    aim(vec3(0,0,0))
{
    distance = dist;
    transformation = glm::mat4();

    updateTransformation();
}

void Arcball::mouseDrag(const vec2 &new_mouse_position)
{
    vec2 mouse_delta = new_mouse_position - old_mouse_position;

    if (glm::length(mouse_delta) < 50.0f) { // fix camera jump
        pitch += mouse_delta.y;
        yaw   += mouse_delta.x;
//        cout << "pitch: " << pitch << "  |  " << "yaw: " << yaw << endl;
        updateTransformation();
    }
    old_mouse_position = new_mouse_position;
}

void Arcball::moveForward(float speed)
{
    distance -= speed;
    updateTransformation();
}

void Arcball::moveRight(float speed)
{
    // TODO: what is side?
}

void Arcball::moveUp(float speed)
{
    // TODO: what is up?
}

glm::vec3 Arcball::getAim() const
{
    return aim;
}

void Arcball::setAim(const glm::vec3 &a)
{
    aim = a;
    updateTransformation();
}

void Arcball::updateTransformation()
{
    transformation =
            glm::translate(vec3(0,0,-distance)) *
            glm::rotate(pitch, X_AXIS) *
            glm::rotate(yaw, Y_AXIS) *
            glm::translate(-aim);

    position =
            vec3(glm::translate(aim) *
                 glm::rotate(pitch, X_AXIS) *
                 glm::rotate(yaw, Y_AXIS) *
                 glm::translate(vec3(0,0,-distance)) *
                 vec4(0,0,0,1));

    vec3 position2 =
            vec3(glm::translate(aim) *
                 glm::rotate(yaw, Y_AXIS) *
                 glm::rotate(pitch, X_AXIS) *
                 glm::translate(vec3(0,0,-distance)) *
                 vec4(0,0,0,1));

    position = vec3(position.x, position2.y, -position.z);

//    cout << "x: " << position.x << ", y: " << position.y
//         << ", z: " << position.z << endl;

}

mat4 Arcball::getViewProjectionMatrix()
{
    return projection * transformation;
}
