#include "camera.h"
#include <glm/gtx/transform.hpp>
#include <cmath>

using glm::vec2;
using glm::vec3;
using glm::mat3;
using glm::mat4;

const float FILM_DIAGONAL = 43.266615300557f;
const float PI = 3.14159265358979f;

Camera::Camera() :
    Camera(46.0f, 0.1f, 50.0f, 1.34f) {}

Camera::~Camera()
{

}

Camera::Camera(float fov, float near_plane, float far_plane, float aspect_ratio) :
    fov(fov),
    near_plane(near_plane),
    far_plane(far_plane),
    aspect_ratio(aspect_ratio)
{
    updateProjection();
}

void Camera::pan(const glm::vec2 &new_mouse_position, float speed)
{
    vec2 mouse_delta = new_mouse_position - old_mouse_position;
    if (glm::length(mouse_delta) < 50.0f) { // fix jump
        if (mouse_delta.y > 0.0f) {
            moveUp(speed);
        } else if (mouse_delta.y < 0.0f) {
            moveUp(-speed);
        }
        if (mouse_delta.x > 0.0f) {
            moveRight(-speed);
        } else if (mouse_delta.x < 0.0f) {
            moveRight(speed);
        }
    }
    old_mouse_position = new_mouse_position;
}

void Camera::setAspectRatio(float ratio)
{
    aspect_ratio = ratio;
    updateProjection();
}

void Camera::setFov(float view)
{
    fov = view;
    updateProjection();
}

void Camera::setNearPlane(float plane)
{
    near_plane = plane;
    updateProjection();
}

void Camera::setFarPlane(float plane)
{
    far_plane = plane;
    updateProjection();
}

void Camera::setFocalLength(float focal_length)
{
    fov = 2 * std::atan(FILM_DIAGONAL / (2 * focal_length)) * 180 / PI;
    updateProjection();
}

float Camera::getAspectRatio() const
{
    return aspect_ratio;
}

float Camera::getFov() const
{
    return fov;
}

float Camera::getNearPlane() const
{
    return near_plane;
}

float Camera::getFarPlane() const
{
    return far_plane;
}

float Camera::getFocalLength() const
{
    return FILM_DIAGONAL / (2 * std::tan(PI * fov / 360));
}

void Camera::updateProjection()
{
    projection = glm::perspective(fov, aspect_ratio, near_plane, far_plane);
}

void Camera::setPosition(const vec3 &p)
{
    position = p;
}

vec3 Camera::getPosition() const
{
    return position;
}


