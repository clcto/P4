#include "Light.h"
#include <cmath>

#define PI (3.14159265)
#define TO_RAD (PI/180)

Light::Light( GLenum l, GLfloat p[] )
{
   light = l;
   for( int i = 0; i < 4; ++i )
   {
      position[i]  = p[i];
      ambient[i]   = 1;
      diffuse[i] = 1;
      specular[i]  = 1;
   }
}

Light::Light( GLenum l, GLfloat p[], GLfloat a[],
              GLfloat d[], GLfloat s[] )
{
   light = l;
   for( int i = 0; i < 4; ++i )
   {
      position[i]  = p[i];
      ambient[i]   = a[i];
      diffuse[i] = d[i];
      specular[i]  = s[i];
   }
}

void Light::GLInit()
{
   if( on )
   {
      glPushMatrix();
      glEnable( light );
      glLightfv( light, GL_POSITION, position );
      glLightfv( light, GL_AMBIENT, ambient );
      glLightfv( light, GL_DIFFUSE, diffuse );
      glPopMatrix();
   }
   else
      glDisable( light );
}

void Light::SetLocationSpherical(
               float theta, float phi, float radius )
{
   position[0] = 
      radius * cos( theta * TO_RAD ) * cos( phi * TO_RAD );
   position[1] = 
      radius * cos( theta * TO_RAD ) * sin( phi * TO_RAD );
   position[2] =
      radius * sin( theta * TO_RAD );
}

void Light::SetLocationRectangular(
               GLfloat x, GLfloat y, GLfloat z )
{
   position[0] = x;
   position[1] = y;
   position[2] = z;
}

void Light::Disable()
{
   on = false;
}

void Light::Enable()
{
   on = true;
}
