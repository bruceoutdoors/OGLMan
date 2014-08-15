#include "sphere.h"
#include <cassert>
#include <cmath>

using glm::vec3;

const float PI = 3.14159265358979f;

Sphere::Sphere(float r, GLuint subdv) :
    Plane(subdv+1),
    m_subdv(subdv+1),
    m_r(r)
{
    assert(r > 0 && subdv >= 3);

    const double CIRCLE = PI * 2;
    const double SLICE_ANGLE = CIRCLE / (m_subdv - 1);
    for (int col = 0; col < m_subdv; col++) {
        double phi = -SLICE_ANGLE * col;
        for (int row = 0; row < m_subdv; row++) {
            double theta = -(SLICE_ANGLE / 2.0) * row;
            int vertIndex = col * m_subdv + row;
            vertices[vertIndex].x = m_r * cos(phi) * sin(theta);
            vertices[vertIndex].y = m_r * sin(phi) * sin(theta);
            vertices[vertIndex].z = m_r * cos(theta);
            normals[vertIndex] = glm::normalize(vertices[vertIndex]);
        }
    }
}

float Sphere::getRadius() const
{
    return m_r;
}
