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
    setPosition(vec3(0, 0, 0));

    updateSidewayVector();
}

mat4 WalkCam::getViewProjectionMatrix()
{
    return projection * glm::lookAt(position, position + forward, up);
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
            updateSidewayVector();
    }
    old_mouse_position = new_mouse_position;
}

void WalkCam::updateSidewayVector()
{
    side = glm::normalize(glm::cross(forward, up));
}

void WalkCam::setForwardVector(const vec3 &f)
{
    forward = glm::normalize(f);
}

vec3 WalkCam::getForwardVector() const
{
    return forward;
}

void WalkCam::setSideVector(const vec3 &s)
{
    side = glm::normalize(s);
}

vec3 WalkCam::getSideVector() const
{
    return side;
}

void WalkCam::setUpVector(const vec3 &u)
{
    up = glm::normalize(u);
}

vec3 WalkCam::getUpVector() const
{
    return up;
}

void WalkCam::moveForward(float speed)
{
    position += speed * forward;
}

void WalkCam::moveRight(float speed)
{
    position += speed * side;
}

void WalkCam::moveUp(float speed)
{
    position += speed * up;
}
