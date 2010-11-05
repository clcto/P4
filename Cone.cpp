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

   gluCylinder( quadric, 1, 0, 1, 50, 50 );

   if( highlight )
   {
      Material::BLACK_PLASTIC.GLInit();

      glBegin( GL_LINE_STRIP );
         glVertex3f( -1, -1, 0);
         glVertex3f( -1, -1, +1);
         glVertex3f( -1, +1, +1);
         glVertex3f( -1, +1, 0);
         glVertex3f( -1, -1, 0);
         glVertex3f( +1, -1, 0);
         glVertex3f( +1, -1, +1);
         glVertex3f( -1, -1, +1);
      glEnd();

      glBegin( GL_LINE_STRIP );
         glVertex3f( +1, -1, 0);
         glVertex3f( +1, +1, 0);
         glVertex3f( +1, +1, +1);
         glVertex3f( -1, +1, +1);
         glVertex3f( -1, +1, +1);
      glEnd();

      glBegin( GL_LINE );
         glVertex3f( -1, +1, 0);
         glVertex3f( +1, +1, 0);
         glVertex3f( +1, -1, +1);
         glVertex3f( +1, +1, +1);
      glEnd();
   }

   Shape::endTransform();
}
