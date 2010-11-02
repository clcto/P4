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
      diffusion[i] = 1;
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
      diffusion[i] = d[i];
      specular[i]  = s[i];
   }
}

void Light::GLInit()
{
   if( 1 )
   {
      glPushMatrix();
      glEnable( light );
      glLightfv( light, GL_POSITION, position );
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
