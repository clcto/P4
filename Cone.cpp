// --------------------------------------------------------
// Cone.cpp
//    A wrapper for a GLU Cone 
//    (well really a specific cylinder...)
//
// Carick Wienke
// --------------------------------------------------------
#include "Cone.h"

Cone::Cone( string n ) : Shape( n )
{
}

   // -----------------------------------------------------
   // Redraw
   //    redraws the cone to the screen
void Cone::Redraw()
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

   gluCylinder( quadric, 1, 0, 1, 50, 50 );

   Shape::endTransform();
}
