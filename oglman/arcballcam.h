#ifndef ARCBALLCAM_H
#define ARCBALLCAM_H

#include "camera.h"

using glm::vec2;
using glm::vec3;
using glm::mat3;
using glm::mat4;

class ArcballCam : public Camera
{
public:
    ArcballCam();
    mat4 getViewProjectionMatrix();
    void mouseDrag(const vec2 &new_mouse_position);
    void pan(const glm::vec2 &new_mouse_position, float speed);
};

#endif // ARCBALLCAM_H
