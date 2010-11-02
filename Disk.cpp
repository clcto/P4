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

   GLfloat am_diff[4] = {0.9, 0.9, 0.9, 1};
   glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,
                 am_diff );

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

   glColor3f( color.red, color.green, color.blue );

   gluDisk( quadric, 0, 1, 50, 5 );

   Shape::endTransform();
}
