// --------------------------------------------------------
// Sphere
//    a wrapper for the gluSphere
//
// Carick Wienke

#include "Sphere.h"

Sphere::Sphere( string n ) : Shape( n )
{
}

void Sphere::Redraw()
{
   Shape::beginTransform();

   material.GLInit();

   gluSphere( quadric, 1, 50, 50 );

   if( highlight )
   {
      Material::BLACK_PLASTIC.GLInit();

      glBegin( GL_LINE_STRIP );
         glVertex3f( -1, -1, -1);
         glVertex3f( -1, -1, +1);
         glVertex3f( -1, +1, +1);
         glVertex3f( -1, +1, -1);
         glVertex3f( -1, -1, -1);
         glVertex3f( +1, -1, -1);
         glVertex3f( +1, -1, +1);
         glVertex3f( -1, -1, +1);
      glEnd();

      glBegin( GL_LINE_STRIP );
         glVertex3f( +1, -1, -1);
         glVertex3f( +1, +1, -1);
         glVertex3f( +1, +1, +1);
         glVertex3f( -1, +1, +1);
         glVertex3f( -1, +1, +1);
      glEnd();

      glBegin( GL_LINE );
         glVertex3f( -1, +1, -1);
         glVertex3f( +1, +1, -1);
         glVertex3f( +1, -1, +1);
         glVertex3f( +1, +1, +1);
      glEnd();
   }

   Shape::endTransform();
}
