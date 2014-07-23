#ifndef WALKCAM_H
#define WALKCAM_H

#include "camera.h"

using glm::vec2;
using glm::vec3;
using glm::mat4;

class WalkCam : public Camera
{
public:
    WalkCam();
    mat4 getViewProjectionMatrix();
    void mouseDrag(const vec2 &new_mouse_position);

    void moveForward(float speed);
    void moveRight(float speed);
    void moveUp(float speed);

    vec3 getForwardVector() const;
    vec3 getUpVector() const;
    vec3 getSideVector() const;

    void setForwardVector(const vec3 &f);
    void setSideVector(const vec3 &s);
    void setUpVector(const vec3 &u);

private:
    void updateSidewayVector();

    vec3 forward;
    vec3 up;
    vec3 side;
};

#endif // WALKCAM_H
