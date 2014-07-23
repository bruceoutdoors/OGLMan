#include "walkcam.h"
#include <glm/gtx/transform.hpp>

const float ROTATION_SPEED = 0.3f;

using glm::vec2;
using glm::vec3;
using glm::mat3;
using glm::mat4;

WalkCam::WalkCam() : Camera()
{
}

mat4 WalkCam::getViewProjectionMatrix()
{
    return projection * glm::lookAt(position, position + forward, up);
}

void WalkCam::mouseDrag(const glm::vec2 &new_mouse_position)
{
    vec2 mouse_delta = new_mouse_position - old_mouse_position;

    if (glm::length(mouse_delta) < 50.0f) { // fix camera jump
            forward =
                mat3(
                    glm::rotate(-mouse_delta.x * ROTATION_SPEED, up) *
                    glm::rotate(-mouse_delta.y * ROTATION_SPEED, side)
                ) * forward;
            updateSidewayVector();
    }
    old_mouse_position = new_mouse_position;
}

void WalkCam::pan(glm::vec2 const &new_mouse_position, float speed)
{
    vec2 mouse_delta = new_mouse_position - old_mouse_position;
    if (glm::length(mouse_delta) < 50.0f) { // fix jump
        if (mouse_delta.y > 0.0f) {
            moveUp(speed);
        } else if (mouse_delta.y < 0.0f) {
            moveUp(-speed);
        }
        if (mouse_delta.x > 0.0f) {
            moveRight(-speed);
        } else if (mouse_delta.x < 0.0f) {
            moveRight(speed);
        }
    }
    old_mouse_position = new_mouse_position;
}
