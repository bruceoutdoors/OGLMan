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

    float getRadius() const;

private:
    GLuint m_subdv;
    float m_r;
};

#endif // SPHERE_H
