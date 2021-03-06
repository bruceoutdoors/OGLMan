#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <string>

using glm::vec2;
using glm::vec3;
using glm::mat4;

class Camera
{
public:
    Camera();
    virtual ~Camera();
    Camera(float fov, float near_plane, float far_plane, float aspect_ratio);
    void pan(const glm::vec2 &new_mouse_position, float speed = .035);
    mat4 getViewProjectionMatrix() const;

    virtual void mouseDrag(const vec2 &new_mouse_position) = 0;

    // move functions:
    virtual void moveForward(float speed) = 0;
    virtual void moveRight(float speed) = 0;
    virtual void moveUp(float speed) = 0;
    virtual void setEye(const vec3 &p);

    vec3 getEye() const;
    float getAspectRatio() const;
    float getFov() const;
    float getNearPlane() const;
    float getFarPlane() const;
    float getFocalLength() const;

    void setAspectRatio(float ratio);
    void setFov(float view);
    void setNearPlane(float plane);
    void setFarPlane(float plane);
    void setFocalLength(float focal_length);

    std::string getName() const;
    void setName(const std::string &value);

protected:
    vec3 eye;
    vec2 old_mouse_position;
    mat4 view;

private:
    void updateProjection();

    std::string name;
    float fov;
    float near_plane;
    float far_plane;
    float aspect_ratio;
    mat4 projection;
};

#endif // CAMERA_H
