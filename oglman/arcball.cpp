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

float Arcball::getPitch() const
{
    return pitch;
}

float Arcball::getYaw() const
{
    return yaw;
}

float Arcball::getDistance() const
{
    return distance;
}

void Arcball::setAim(const glm::vec3 &a)
{
    aim = a;
    updateTransformation();
}

void Arcball::setPitch(float val)
{
    pitch = val;
    updateTransformation();
}

void Arcball::setYaw(float val)
{
    yaw = val;
    updateTransformation();
}

void Arcball::setDistance(float val)
{
    distance = val;
    updateTransformation();
}

void Arcball::updateTransformation()
{
    view =
            glm::translate(vec3(0,0,-distance)) *
            glm::rotate(pitch, X_AXIS) *
            glm::rotate(yaw, Y_AXIS) *
            glm::translate(-aim);

    vec4 getXZ =
            glm::translate(aim) *
            glm::rotate(pitch, X_AXIS) *
            glm::rotate(yaw, Y_AXIS) *
            glm::translate(vec3(0,0,-distance)) *
            vec4(0,0,0,1);

    // to solve gimbal lock, a separate transformation is created
    // with only pitch movement
    vec4 getY =
            glm::translate(aim) *
            glm::rotate(pitch, X_AXIS) *
            glm::translate(vec3(0,0,-distance)) *
            vec4(0,0,0,1);

    eye = vec3(getXZ.x, getY.y, -getXZ.z);

//    cout << "x: " << eye.x << ", y: " << eye.y
//         << ", z: " << eye.z << endl;

}
