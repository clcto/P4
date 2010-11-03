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

   gluDisk( quadric, 0, 1, 50, 5 );

   Shape::endTransform();
}
