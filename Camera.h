#ifndef CAMERA_H_
#define CAMERA_H_

#include "GLPoint.h"
#include <GL/glut.h>

class Camera
{
   public:
      
      Camera();

      void SetEye( GLPoint );
      void SetCenter( GLPoint );
      void SetUp( GLVector );

      void SetRight( GLdouble );
      void SetLeft( GLdouble );
      void SetTop( GLdouble );
      void SetBottom( GLdouble );
      void SetNear( GLdouble );
      void SetFar( GLdouble );
      
      void SetFOV( GLdouble );
      void SetAspectRatio( GLdouble );

      GLPoint GetEye() const;
      GLPoint GetCenter() const;
      GLVector GetUp() const;

      GLdouble GetRight() const;
      GLdouble GetLeft() const;
      GLdouble GetTop() const;
      GLdouble GetBottom() const;
      GLdouble GetNear() const;
      GLdouble GetFar() const;

      GLdouble GetFOV() const;
      GLdouble GetAspectRatio() const;

      void SetUpGLMatrices() const;

      enum Mode {
         Mode_Ortho = 0,
         Mode_Frustum,
         Mode_Perspective
      };

      void SetMode( Mode );

      Mode GetMode() const;

   private:
      Mode mode;

      GLPoint eye;
      GLPoint center;
      GLVector up;

      GLdouble oRight, oLeft, oTop, oBottom;
      GLdouble oNear, oFar;

      GLdouble fRight, fLeft, fTop, fBottom;
      GLdouble fNear, fFar;

      GLdouble pNear, pFar;

      GLdouble fov, aspect;
};

#endif
