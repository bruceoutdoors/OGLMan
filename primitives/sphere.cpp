#include "sphere.h"
#include <cassert>
#include <cmath>
#include <cstdlib>

using glm::vec3;

const float PI = 3.14159265358979f;

Sphere::Sphere(float r, GLuint subdv) :
    Plane(subdv+1),
    m_subdv(subdv+1),
    radius(r)
{
    const double CIRCLE = PI * 2;
    const double SLICE_ANGLE = CIRCLE / (m_subdv - 1);
    for (int col = 0; col < m_subdv; col++) {
        double phi = -SLICE_ANGLE * col;
        for (int row = 0; row < m_subdv; row++) {
            double theta = -(SLICE_ANGLE / 2.0) * row;
            int vertIndex = col * m_subdv + row;
            vertices[vertIndex].x = radius * cos(phi) * sin(theta);
            vertices[vertIndex].y = radius * sin(phi) * sin(theta);
            vertices[vertIndex].z = radius * cos(theta);
            normals[vertIndex] = glm::normalize(vertices[vertIndex]);
        }
    }
}
GLuint Sphere::getSubdv() const
{
    return m_subdv;
}

void Sphere::setSubdv(const GLuint &value)
{
    m_subdv = value;
}
float Sphere::getRadius() const
{
    return radius;
}

void Sphere::setRadius(float value)
{
    radius = value;
}

