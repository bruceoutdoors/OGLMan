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
    mat4 getProjectionMatrix() const;
    void mouseUpdate(const vec2 &new_mouse_position);
    void setAspectRatio(float ratio);
    void updateProjection();
    void setPosition(const vec3 &p);
    vec3 getPosition() const;
    void pan(const glm::vec2 &new_mouse_position);

    bool hasAim() const { return isAim; }
    void enableAim();
    void disableAim();

    // keyboard functions:
    void moveForward(float s = -1.0f);
    void moveBackward(float s = -1.0f);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

private:
    inline void updateSidewayVector();
    vec3 view_direction;
    vec3 aim;
    vec3 up;
    vec3 position;
    vec2 old_mouse_position;
    vec2 orbit_theta;
    vec3 sideways;

    float aspect_ratio;
    float fov;
    float far_plane;
    float near_plane;

    bool isAim;

    mat4 projection;
};

#endif // CAMERA_H
