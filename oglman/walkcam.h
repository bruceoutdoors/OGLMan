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

    void setPosition(const vec3 &p);

    vec3 getForwardVector() const;
    vec3 getUpVector() const;
    vec3 getSideVector() const;

    void setForwardVector(const vec3 &f);
    void setUpVector(const vec3 &u);

    void calculateLookat();

private:
    void updateSideVector();

    vec3 forward;
    vec3 up;
    vec3 up2;
    vec3 side;
    mat4 lookat;
};

#endif // WALKCAM_H
