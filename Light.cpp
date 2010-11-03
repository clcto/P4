#include "Light.h"
#include "radians.h"

Light::Light( GLenum l, GLfloat p[] )
{
   on = true;
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
      glMatrixMode( GL_MODELVIEW );
      glPushMatrix();
      glEnable( light );
      glLightfv( light, GL_POSITION, position );
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

void Light::SetColor( float r, float g, float b )
{
   diffuse[0] = r;
   diffuse[1] = g;
   diffuse[2] = b;
}

float Light::GetRadius()
{
   return sqrt( pow( position[0], 2 ) +
                pow( position[1], 2 ) +
                pow( position[2], 2 ) );
}

float Light::GetElevation()
{
   return 90 - acos( position[2] / GetRadius() ) * TO_DEG;
}

float Light::GetHeading()
{
   return atan2( position[1], position[0] ) * TO_DEG;
}

GLPoint Light::GetLocation()
{
   GLPoint p = { position[0],
                 position[1],
                 position[2] };
   return p;
}

Color Light::GetColor() const
{
   Color c = { diffuse[0], diffuse[1], diffuse[2] };
   return c;
}

bool Light::IsOn()
{
   return on;
}

void Light::Disable()
{
   on = false;
}

void Light::Enable()
{
   on = true;
}
