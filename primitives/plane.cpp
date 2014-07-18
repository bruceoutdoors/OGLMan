#include "plane.h"

using glm::vec3;

Plane::Plane(unsigned int dimensions)
{
    this->dimensions = dimensions;
    makeVerts(dimensions);
    makeIndices(dimensions);
}

void Plane::makeVerts(unsigned int dimensions)
{
    unsigned int size = dimensions * dimensions;
    vertices.reserve(size);
    normals.reserve(size);

    int half = dimensions / 2;
    for(int i = 0; i < dimensions; i++) {
        for(int j = 0; j < dimensions; j++) {
            vertices.push_back(vec3(j - half, 0, i - half));
            normals.push_back(vec3(0, 1, 0));
        }
    }
}

void Plane::makeIndices(unsigned int dimensions)
{
    unsigned int size = (dimensions - 1) * (dimensions - 1) * 2 * 3;
    indices.reserve(size);

    for(int row = 0; row < dimensions - 1; row++) {
        for(int col = 0; col < dimensions - 1; col++) {
            indices.push_back(dimensions * row + col);
            indices.push_back(dimensions * row + col + dimensions);
            indices.push_back(dimensions * row + col + dimensions + 1);

            indices.push_back(dimensions * row + col);
            indices.push_back(dimensions * row + col + dimensions + 1);
            indices.push_back(dimensions * row + col + 1);
        }
    }
}
