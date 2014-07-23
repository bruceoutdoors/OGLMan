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
    setUpVector(vec3(0, 1, 0));
    setForwardVector(vec3(0, 0, -1));
    setPosition(vec3(0, 0, 0));

    updateSidewayVector();
    updateProjection();
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

void Camera::setPosition(const glm::vec3 &p)
{
    position = p;
}

glm::vec3 Camera::getPosition() const
{
    return position;
}

void Camera::setForwardVector(const glm::vec3 &f)
{
    forward = glm::normalize(f);
}

glm::vec3 Camera::getForwardVector() const
{
    return forward;
}

void Camera::setSideVector(const glm::vec3 &s)
{
    side = glm::normalize(s);
}

glm::vec3 Camera::getSideVector() const
{
    return side;
}

void Camera::setUpVector(const glm::vec3 &u)
{
    up = glm::normalize(u);
}

glm::vec3 Camera::getUpVector() const
{
    return up;
}

void Camera::moveForward(float speed)
{
    position += speed * forward;
}

void Camera::moveRight(float speed)
{
    position += speed * side;
}

void Camera::moveUp(float speed)
{
    position += speed * up;
}

void Camera::updateSidewayVector()
{
    side = glm::normalize(glm::cross(forward, up));
}
