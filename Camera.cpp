// --------------------------------------------------------
// Camera.cpp
//    A class that holds the data about the camera
//
// Carick Wienke
// --------------------------------------------------------


#include "Camera.h"
#include "radians.h"

#include <GL/glut.h>
#include <iostream>

using namespace std;

   // -----------------------------------------------------
   // Constructor:
   //    sets up default values
Camera::Camera()
{
   radius = 50;
   theta = 0;
   phi = 0;

   center.x = 0; center.y = 0; center.z = 0;
   up.x = 0; up.y = 0; up.z = 1;

   pFar = 10000;
   pNear = 1;
   fov = 30;
   aspect = 1;
}

   // -----------------------------------------------------
   // sets up the matrices so everything appears
   // as i tell it it should
void Camera::SetUpGLMatrices() const
{
   glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      gluPerspective( fov, aspect, pNear, pFar );

   glMatrixMode( GL_MODELVIEW );
      int x = 
         radius * cos( theta*TO_RAD ) * cos( phi*TO_RAD );
      int y = 
         radius * cos( theta*TO_RAD ) * sin( phi*TO_RAD );
      int z =  
         radius * sin( theta*TO_RAD );

      gluLookAt( x, y, z,
                 center.x, center.y, center.z,
                 up.x, up.y, up.z );
}

void Camera::SetEyeSpherical( float t, float p, 
                              float r )
{
   theta = t;
   phi = p;
   radius = r;
}

float Camera::GetElevation()
{
   return theta;
}

float Camera::GetHeading()
{
   return phi;
}

float Camera::GetRadius()
{
   return radius;
}
