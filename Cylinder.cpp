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

   gluCylinder( quadric, 1, 1, 1, 50, 50 );

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
