#ifndef CAMERA_H_
#define CAMERA_H_

#include "GLPoint.h"
#include <GL/glut.h>

class Camera
{
   public:
      
      Camera();

      void SetEyeSpherical( float t, float p,
                            float r = 1 );

      void SetUpGLMatrices() const;

   private:
      float theta, phi, radius;

      GLPoint center;
      GLVector up;

      GLdouble pNear, pFar;

      GLdouble fov, aspect;
};

#endif
