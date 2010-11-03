// Cylinder
//    wraps the gluCylinder so it is easier to use
//
// Carick Wienke

#include "Cylinder.h"

Cylinder::Cylinder( string n ) : Shape( n )
{
}

   // draws the cylinder to the sceen
void Cylinder::Redraw()
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

   gluCylinder( quadric, 1, 1, 1, 50, 50 );

   Shape::endTransform();
}
