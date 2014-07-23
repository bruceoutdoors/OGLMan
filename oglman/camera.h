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
    Camera(float fov, float near_plane, float far_plane, float aspect_ratio);

    virtual void mouseDrag(const vec2 &new_mouse_position) = 0;
    virtual void pan(const glm::vec2 &new_mouse_position, float speed) = 0;
    virtual mat4 getViewProjectionMatrix() = 0;

    void setPosition(const vec3 &p);
    vec3 getPosition() const;
    void setForwardVector(const vec3 &f);
    vec3 getForwardVector() const;
    void setSideVector(const vec3 &s);
    vec3 getSideVector() const;
    void setUpVector(const vec3 &u);
    vec3 getUpVector() const;

    // move functions:
    void moveForward(float speed);
    void moveRight(float speed);
    void moveUp(float speed);

    // camera setters:
    void setAspectRatio(float ratio);
    void setFov(float view);
    void setNearPlane(float plane);
    void setFarPlane(float plane);
    void setFocalLength(float focal_length);

    float getAspectRatio() const;
    float getFov() const;
    float getNearPlane() const;
    float getFarPlane() const;
    float getFocalLength() const;

protected:
    vec3 position;
    vec2 old_mouse_position;
    mat4 projection;
    vec3 forward;
    vec3 up;
    vec3 side;
    inline void updateSidewayVector();

private:
    void updateProjection();

    float fov;
    float near_plane;
    float far_plane;
    float aspect_ratio;

};

#endif // CAMERA_H
