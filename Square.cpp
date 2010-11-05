// --------------------------------------------------------
// Square
//    wrapper for the gluSquare
//
// Carick Wienke

#include "Square.h"

Square::Square( string n ) : Shape( n )
{
}

void Square::Redraw()
{
   Shape::beginTransform();

   material.GLInit();

   glBegin( GL_POLYGON );
      glEnable( GL_NORMALIZE );
      glNormal3f( 0, 0, 1 );
      glVertex3f( -1, -1, 0 );
      glVertex3f( -1, 1, 0 );
      glVertex3f( 1, 1, 0 );
      glVertex3f( 1, -1, 0 );
      glDisable( GL_NORMALIZE );
   glEnd();

   if( highlight )
   {
      Material::BLACK_PLASTIC.GLInit();

      glBegin( GL_LINE_STRIP );
         glVertex3f( -1, -1, -.1);
         glVertex3f( -1, -1, +.1);
         glVertex3f( -1, +1, +.1);
         glVertex3f( -1, +1, -.1);
         glVertex3f( -1, -1, -.1);
         glVertex3f( +1, -1, -.1);
         glVertex3f( +1, -1, +.1);
         glVertex3f( -1, -1, +.1);
      glEnd();

      glBegin( GL_LINE_STRIP );
         glVertex3f( +1, -1, -.1);
         glVertex3f( +1, +1, -.1);
         glVertex3f( +1, +1, +.1);
         glVertex3f( -1, +1, +.1);
         glVertex3f( -1, +1, +.1);
      glEnd();

      glBegin( GL_LINE );
         glVertex3f( -1, +1, -.1);
         glVertex3f( +1, +1, -.1);
         glVertex3f( +1, -1, +.1);
         glVertex3f( +1, +1, +.1);
      glEnd();
   }

   Shape::endTransform();
}
