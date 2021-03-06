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
    void mouseDrag(const vec2 &new_mouse_position);

    void moveForward(float speed);
    void moveRight(float speed);
    void moveUp(float speed);

    vec3 getAim() const;
    float getPitch() const;
    float getYaw() const;
    float getDistance() const;

    void setAim(const vec3 &a);
    void setPitch(float val);
    void setYaw(float val);
    void setDistance(float val);

private:
    void updateTransformation();

    float pitch;
    float yaw;
    float distance;
    float pan_horizontal;
    float pan_vertical;
    vec3 aim;
};

#endif // ARCBALLCAM_H
