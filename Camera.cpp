// --------------------------------------------------------
// Camera.cpp
//    A class that holds the data about the camera
//
// Carick Wienke
// --------------------------------------------------------


#include "Camera.h"
#include <GL/glut.h>
#include <iostream>

using namespace std;

   // -----------------------------------------------------
   // Constructor:
   //    sets up default values
Camera::Camera()
{
   mode = Mode_Ortho;

   eye.x = 100; eye.y = 50; eye.z = 50;
   center.x = 0; center.y = 0; center.z = 0;
   up.x = 0; up.y = 0; up.z = 1;

   oRight  = -10;
   oLeft   = 10;
   oTop    = 10;
   oBottom = -10;
   oNear   = 1;
   oFar    = 10000;

   fRight  = -4;
   fLeft   = 4;
   fTop    = 4;
   fBottom = -4;
   fNear   = 50;
   fFar    = 10000;

   pFar = 10000;
   pNear = 1;
   fov = 10;
   aspect = 1;
}

   // -----------------------------------------------------
   // sets up the matrices so everything appears
   // as i tell it it should
void Camera::SetUpGLMatrices() const
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();

   switch( mode )
   {
      case Mode_Ortho:
         glOrtho( oRight, oLeft, oBottom,
                  oTop, oNear, oFar );
         break;

      case Mode_Perspective:
         gluPerspective( fov, aspect, pNear, pFar );
         break;

      case Mode_Frustum:
         glFrustum( fRight, fLeft, fBottom, fTop, 
                    fNear, fFar );
         break;
   }

   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();
   gluLookAt( eye.x, eye.y, eye.z,
              center.x, center.y, center.z,
              up.x, up.y, up.z );
}

   // Mutators ============================================
void Camera::SetMode( Mode m )
{
   mode = m;
}

void Camera::SetEye( GLPoint p )
{
   eye = p;
}

void Camera::SetCenter( GLPoint p )
{
   center = p;
}

void Camera::SetUp( GLVector v )
{
   up = v;
}

void Camera::SetRight( GLdouble r )
{
   if( mode == Mode_Ortho )
      oRight = r;
   else if( mode == Mode_Frustum )
      fRight = r;
}

void Camera::SetLeft( GLdouble l )
{
   if( mode == Mode_Ortho )
      oLeft = l;
   else if( mode == Mode_Frustum )
      fLeft = l;
}

void Camera::SetTop( GLdouble t )
{
   if( mode == Mode_Ortho )
      oTop = t;
   else if( mode == Mode_Frustum )
      fTop = t;
}

void Camera::SetBottom( GLdouble b )
{
   if( mode == Mode_Ortho )
      oBottom = b;
   else if( mode == Mode_Frustum )
      fBottom = b;
}

void Camera::SetNear( GLdouble n )
{
   if( mode == Mode_Ortho )
      oNear = n;
   else if( mode == Mode_Perspective )
      pNear = n;
   else if( mode == Mode_Frustum )
      fNear = n;
}

void Camera::SetFar( GLdouble f )
{
   if( mode == Mode_Ortho )
      oFar = f;
   else if( mode == Mode_Perspective )
      pFar = f;
   else if( mode == Mode_Frustum )
      fFar = f;
}

void Camera::SetFOV( GLdouble f )
{
   fov = f;
}

void Camera::SetAspectRatio( GLdouble r )
{
   aspect = r;
}

   // Accessors ===========================================
Camera::Mode Camera::GetMode() const
{
   return mode;
}

GLPoint Camera::GetEye() const
{
   return eye;
}

GLPoint Camera::GetCenter() const
{
   return center;
}

GLVector Camera::GetUp() const
{
   return up;
}

GLdouble Camera::GetRight() const
{
   switch( mode )
   {
      case Mode_Frustum:   return fRight;
      case Mode_Ortho:     return oRight;
      default:             return 0;
   }
}

GLdouble Camera::GetLeft() const
{
   switch( mode )
   {
      case Mode_Frustum:   return fLeft;
      case Mode_Ortho:     return oLeft;
      default:             return 0;
   }
}

GLdouble Camera::GetTop() const
{
   switch( mode )
   {
      case Mode_Frustum:   return fTop;
      case Mode_Ortho:     return oTop;
      default:             return 0;
   }
}

GLdouble Camera::GetBottom() const
{
   switch( mode )
   {
      case Mode_Frustum:   return fBottom;
      case Mode_Ortho:     return oBottom;
      default:             return 0;
   }
}

GLdouble Camera::GetNear() const
{
   switch( mode )
   {
      case Mode_Frustum:     return fNear;
      case Mode_Ortho:       return oNear;
      case Mode_Perspective: return pNear;
      default:               return 0;
   }
}

GLdouble Camera::GetFar() const
{
   switch( mode )
   {
      case Mode_Frustum:     return fFar;
      case Mode_Ortho:       return oFar;
      case Mode_Perspective: return pFar;
      default:               return 0;
   }
}

GLdouble Camera::GetFOV() const
{
   return fov;
}

GLdouble Camera::GetAspectRatio() const
{
   return aspect;
}
