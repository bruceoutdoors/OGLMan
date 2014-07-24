#include "walkcam.h"
#include <glm/gtx/transform.hpp>

const float ROTATION_SPEED = 0.3f;

using glm::vec2;
using glm::vec3;
using glm::mat3;
using glm::mat4;

WalkCam::WalkCam()
{
    setUpVector(vec3(0, 1, 0));
    setForwardVector(vec3(0, 0, -1));
    setEye(vec3(0, 0, 0));

    updateSideVector();
}

void WalkCam::mouseDrag(const vec2 &new_mouse_position)
{
    vec2 mouse_delta = new_mouse_position - old_mouse_position;

    if (glm::length(mouse_delta) < 50.0f) { // fix camera jump
        forward =
                mat3(
                    glm::rotate(-mouse_delta.x * ROTATION_SPEED, up) *
                    glm::rotate(-mouse_delta.y * ROTATION_SPEED, side)
                    ) * forward;
        updateSideVector();
    }
    old_mouse_position = new_mouse_position;
}

void WalkCam::updateSideVector()
{
    side = glm::normalize(glm::cross(forward, up));
    calculateLookat();
}

void WalkCam::setForwardVector(const vec3 &f)
{
    forward = glm::normalize(f);
    calculateLookat();
}

vec3 WalkCam::getForwardVector() const
{
    return forward;
}

vec3 WalkCam::getSideVector() const
{
    return side;
}

void WalkCam::setUpVector(const vec3 &u)
{
    up = glm::normalize(u);
    calculateLookat();
}

void WalkCam::calculateLookat()
{
    up2 = glm::cross(side, forward);

    view[0][0] = side.x;
    view[1][0] = side.y;
    view[2][0] = side.z;

    view[0][1] = up2.x;
    view[1][1] = up2.y;
    view[2][1] = up2.z;

    view[0][2] = -forward.x;
    view[1][2] = -forward.y;
    view[2][2] = -forward.z;

    view[3][0] = -glm::dot(side, eye);
    view[3][1] = -glm::dot(up2, eye);
    view[3][2] = glm::dot(forward, eye);
}

vec3 WalkCam::getUpVector() const
{
    return up;
}

void WalkCam::moveForward(float speed)
{
    eye += speed * forward;
    calculateLookat();
}

void WalkCam::moveRight(float speed)
{
    eye += speed * side;
    calculateLookat();
}

void WalkCam::moveUp(float speed)
{
    eye += speed * up2;
    calculateLookat();
}

void WalkCam::setEye(const glm::vec3 &p)
{
    Camera::setEye(p);
    calculateLookat();
}
