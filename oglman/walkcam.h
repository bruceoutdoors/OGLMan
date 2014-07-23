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
    void pan(const glm::vec2 &new_mouse_position, float speed);
};

#endif // WALKCAM_H
