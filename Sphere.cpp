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

   if( highlight )
   {
      GLfloat emit[4] = {0.3, 0.3, 0.3, 1};
      glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, emit );
   }
   else
   {
      GLfloat emit[4] = {0, 0, 0, 1};
      glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, emit );
   }

   gluSphere( quadric, 1, 50, 50 );

   Shape::endTransform();
}
