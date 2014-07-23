#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

using glm::vec2;
using glm::vec3;
using glm::mat4;

class Camera
{
public:
    Camera();
    virtual ~Camera();
    Camera(float fov, float near_plane, float far_plane, float aspect_ratio);
    void pan(const glm::vec2 &new_mouse_position, float speed);

    virtual void mouseDrag(const vec2 &new_mouse_position) = 0;
    virtual mat4 getViewProjectionMatrix() = 0;

    // move functions:
    virtual void moveForward(float speed) = 0;
    virtual void moveRight(float speed) = 0;
    virtual void moveUp(float speed) = 0;

    void setAspectRatio(float ratio);
    void setFov(float view);
    void setNearPlane(float plane);
    void setFarPlane(float plane);
    void setFocalLength(float focal_length);
    void setPosition(const vec3 &p);

    float getAspectRatio() const;
    float getFov() const;
    float getNearPlane() const;
    float getFarPlane() const;
    float getFocalLength() const;
    vec3 getPosition() const;

protected:
    vec3 position;
    vec2 old_mouse_position;
    mat4 projection;

private:
    void updateProjection();

    float fov;
    float near_plane;
    float far_plane;
    float aspect_ratio;
};

#endif // CAMERA_H
