#ifndef SPHERE_H
#define SPHERE_H

/**
  * the algorithm to generate this sphere originated
  * from Jamie King's YouTube OpenGL tutorials:
  *
  *   http://bit.ly/1t2Rxde
  *
  * Check'em out. They're awesum! :D
  *
  **/

#include "plane.h"

class Sphere : public Plane
{
public:
    Sphere(float r = 1,
           GLuint subdv = 10);

    GLuint getSubdv() const;
    float getRadius() const;

    void setSubdv(const GLuint &value);
    void setRadius(float value);

private:
    GLuint m_subdv;
    float radius;
};

#endif // SPHERE_H
