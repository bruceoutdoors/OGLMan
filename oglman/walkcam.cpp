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

    updateSideVector();
}

mat4 WalkCam::getViewProjectionMatrix()
{
    return projection * lookat;
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

    lookat[0][0] = side.x;
    lookat[1][0] = side.y;
    lookat[2][0] = side.z;

    lookat[0][1] = up2.x;
    lookat[1][1] = up2.y;
    lookat[2][1] = up2.z;

    lookat[0][2] = -forward.x;
    lookat[1][2] = -forward.y;
    lookat[2][2] = -forward.z;

    lookat[3][0] = -glm::dot(side, position);
    lookat[3][1] = -glm::dot(up2, position);
    lookat[3][2] = glm::dot(forward, position);
}

vec3 WalkCam::getUpVector() const
{
    return up;
}

void WalkCam::moveForward(float speed)
{
    position += speed * forward;
    calculateLookat();
}

void WalkCam::moveRight(float speed)
{
    position += speed * side;
    calculateLookat();
}

void WalkCam::moveUp(float speed)
{
    position += speed * up2;
    calculateLookat();
}

void WalkCam::setPosition(const glm::vec3 &p)
{
    Camera::setPosition(p);
    calculateLookat();
}
