// --------------------------------------------------------
// GLPoint.h
//    struct representing a point in GL numbers
// --------------------------------------------------------
#ifndef GLPOINT_H_
#define GLPOINT_H_

#include <GL/glut.h>

struct GLPoint
{
   GLfloat x, y, z;
};

typedef GLPoint GLVector;
typedef GLPoint GLScale; 

#endif
