// --------------------------------------------------------
// Disk
//    wrapper for the gluDisk
//
// Carick Wienke

#include "Disk.h"

Disk::Disk( string n ) : Shape( n )
{
}

void Disk::Redraw()
{
   Shape::beginTransform();

   material.GLInit();

   gluDisk( quadric, 0, 1, 50, 5 );

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
