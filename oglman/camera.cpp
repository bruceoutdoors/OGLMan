#include "camera.h"
#include <glm/gtx/transform.hpp>

using glm::vec2;
using glm::vec3;
using glm::mat3;
using glm::mat4;

const float ROTATION_SPEED = 0.3f;
const float MOVE_SPEED = 0.2f;


Camera::Camera() :
    view_direction(-0.06f, -0.35f, -0.94f),
    aim(0.0f, 0.0f, 0.0f),
    up(0.0f, 1.0f, 0.0f),
    position(-0.157f, 3.288f, 7.79f)

{
    // default camera values emulate the human eye
    isAim = false;
    fov = 46.0f;
    near_plane = 0.1f;
    far_plane = 50.0f;
    aspect_ratio = 1.34f;

    updateSidewayVector();
}

mat4 Camera::getProjectionMatrix()
{
    if (isAim) {
        return projection * glm::lookAt(position, aim, up);
    }
    return projection * glm::lookAt(position, position + view_direction, up);
}

void Camera::mouseUpdate(const glm::vec2 &new_mouse_position)
{
    vec2 mouseDelta = new_mouse_position - old_mouse_position;

    if (glm::length(mouseDelta) < 50.0f) { // fix camera jump
        if (isAim) {
//            up = glm::normalize(glm::cross(sideways, (aim - position)));
//            updateSidewayVector();
//            float a = glm::angle(vec3(1, 0, 0), glm::normalize(position));
//            float ratio;
//            if (a <= 90.0f) {
//                ratio = a/90.0f;
//                qDebug() << "ratio to left: " << ratio;
//            }
//            float b = glm::angle(vec3(-1, 0, 0), glm::normalize(position));
//            if (b <= 90.0f) {
//                ratio = b/90.0f;
//                qDebug() << "right area: " << ratio;
//            }

            position =
                mat3(
                    glm::rotate(-mouseDelta.y, vec3(1, 0, 0)) *
                    glm::rotate(-mouseDelta.x, vec3(0, 1, 0))
                ) * position;

//            up =
//                mat3(
//                    glm::rotate(-mouseDelta.y, vec3(1, 0, 0)) *
//                    glm::rotate(-mouseDelta.x, vec3(0, 1, 0))
//                ) * up;

        } else {
            view_direction =
                mat3(
                    glm::rotate(-mouseDelta.x * ROTATION_SPEED, up) *
                    glm::rotate(-mouseDelta.y * ROTATION_SPEED, sideways)
                ) * view_direction;
            updateSidewayVector();
        }

    }
    old_mouse_position = new_mouse_position;
}

void Camera::setAspectRatio(float ratio)
{
    aspect_ratio = ratio;
    updateProjection();
}

void Camera::updateProjection()
{
    projection = glm::perspective(fov, aspect_ratio, near_plane, far_plane);
}

void Camera::setPosition(const glm::vec3 &p)
{
    position = p;
}

glm::vec3 Camera::getPosition() const
{
    return position;
}

void Camera::moveForward(float s)
{
    float speed;
    s == -1.0f ? speed = MOVE_SPEED : speed = s;
    if (isAim) {
        position += speed * glm::normalize(aim - position);
    } else {
        position += speed * view_direction;
    }
}

void Camera::moveBackward(float s)
{
    float speed;
    s == -1.0f ? speed = MOVE_SPEED : speed = s;
    if (isAim) {
        position -= speed * glm::normalize(aim - position);
    } else {
        position -= speed * view_direction;
    }
}

void Camera::moveLeft()
{
    position -= MOVE_SPEED * sideways;
}

void Camera::moveRight()
{
    position += MOVE_SPEED * sideways;
}

void Camera::moveUp()
{
    position += MOVE_SPEED * up;
}

void Camera::moveDown()
{
    position -= MOVE_SPEED * up;
}

void Camera::updateSidewayVector()
{
    sideways = glm::normalize(glm::cross(view_direction, up));
}
