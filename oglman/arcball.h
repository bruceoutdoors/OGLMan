#ifndef ARCBALLCAM_H
#define ARCBALLCAM_H

#include "camera.h"

using glm::vec2;
using glm::vec3;
using glm::mat3;
using glm::mat4;

class Arcball : public Camera
{
public:
    Arcball(float dist = 7);
    mat4 getViewProjectionMatrix();
    void mouseDrag(const vec2 &new_mouse_position);
    void pan(const glm::vec2 &new_mouse_position, float speed);
    void moveForward(float speed);

private:
    void updateTransformation();

    vec3 aim;
    mat4 transformation;
    float pitch;
    float yaw;
    float distance;
};

#endif // ARCBALLCAM_H
