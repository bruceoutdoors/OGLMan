#include "arcball.h"
#include <glm/gtx/transform.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

Arcball::Arcball(float dist) :
    pitch(0),
    yaw(0),
    aim(vec3(0,0,0))
{
    distance = dist;
    transformation = glm::mat4();

    side = vec3(1,0,0);
    updateTransformation();
}

void Arcball::mouseDrag(const vec2 &new_mouse_position)
{
    vec2 mouse_delta = new_mouse_position - old_mouse_position;

    if (glm::length(mouse_delta) < 50.0f) { // fix camera jump
        pitch += mouse_delta.y;
        yaw   += mouse_delta.x;
//        cout << "pitch: " << pitch << "  |  " << "yaw: " << yaw << endl;
        updateTransformation();
    }
    old_mouse_position = new_mouse_position;
}

void Arcball::pan(const glm::vec2 &new_mouse_position, float speed)
{

}

void Arcball::moveForward(float speed)
{
    distance -= speed;
    updateTransformation();
}

void Arcball::updateTransformation()
{
    transformation =
            glm::translate(vec3(0,0,-distance)) *
            glm::rotate(pitch, side) *
            glm::rotate(yaw, up);

    position = vec3((glm::rotate(pitch, side) *
                     glm::rotate(yaw, up)) *
                     glm::translate(vec3(0,0,-distance)) *
                   vec4(0,0,0,1));

    position = vec3(position.x, position.y, -position.z);
}

mat4 Arcball::getViewProjectionMatrix()
{
    return projection * transformation;
}
