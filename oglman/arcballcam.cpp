#include "arcballcam.h"
#include <glm/gtx/transform.hpp>

using glm::vec2;
using glm::vec3;
using glm::mat3;
using glm::mat4;

ArcballCam::ArcballCam() : Camera()
{
}

void ArcballCam::mouseDrag(const vec2 &new_mouse_position)
{
    // TODO: implement mouseDrag
}

void ArcballCam::pan(const glm::vec2 &new_mouse_position, float speed)
{
    // TODO: implement pan
}

mat4 ArcballCam::getViewProjectionMatrix()
{
    // TODO: implement getViewProjectionMatrix
}
