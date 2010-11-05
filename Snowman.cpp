// --------------------------------------------------------
// Snowman
//    A class that represents a 3d snowman. It uses 
//    other classes that wrap the glu solids
//
// Carick Wienke

#include "Snowman.h"
#include "Disk.h"

#include <iostream>

// Constructor
//    creates the snowman. moves the shapes and
//    resizes them so they actually make the snowman
Snowman::Snowman( string n ) : Shape( n )
{
   bottom.SetTranslation( 0, 0, -1.6 );
   bottom.SetScale( 1.2, 1.2, 1.2 );

   head.SetTranslation( 0, 0, 1.2 );
   head.SetScale( 0.65, 0.65, 0.65 );

   hatBottom.SetScale( 0.6, 0.6, 0.1 );
   hatBottom.SetTranslation( 0, 0, 1.65 );
   hatBottom.SetMaterial( Material::BLACK_PLASTIC );

   hatTop.SetScale( 0.47, 0.47, 0.4 );
   hatTop.SetTranslation( 0, 0, 1.75 );
   hatTop.SetMaterial( Material::BLACK_PLASTIC );

   hatLow.SetScale( 0.6, 0.6, 1 );
   hatLow.SetTranslation( 0, 0, 1.65 );
   hatLow.SetMaterial( Material::BLACK_PLASTIC );

   hatMid.SetScale( 0.6, 0.6, 1 );
   hatMid.SetTranslation( 0, 0, 1.75 );
   hatMid.SetMaterial( Material::BLACK_PLASTIC );

   hatHigh.SetScale( 0.47, 0.47, 1 );
   hatHigh.SetTranslation( 0, 0, 2.15 );
   hatHigh.SetMaterial( Material::BLACK_PLASTIC );
}

   // draw the snowman to the screen
void Snowman::Redraw()
{
   Shape::beginTransform();

   hatBottom.Redraw();
   hatTop.Redraw();
   hatLow.Redraw();
   hatMid.Redraw();
   hatHigh.Redraw();
   bottom.Redraw();
   body.Redraw();
   head.Redraw();

   if( highlight )
   {
      Material::BLACK_PLASTIC.GLInit();

      glBegin( GL_LINE_STRIP );
         glVertex3f( -1.2, -1.2, -2.8 );
         glVertex3f( -1.2, -1.2, +2.15 );
         glVertex3f( -1.2, +1.2, +2.15 );
         glVertex3f( -1.2, +1.2, -2.8 );
         glVertex3f( -1.2, -1.2, -2.8 );
         glVertex3f( +1.2, -1.2, -2.8 );
         glVertex3f( +1.2, -1.2, +2.15 );
         glVertex3f( -1.2, -1.2, +2.15 );
      glEnd();

      glBegin( GL_LINE_STRIP );
         glVertex3f( +1.2, -1.2, -2.8 );
         glVertex3f( +1.2, +1.2, -2.8 );
         glVertex3f( +1.2, +1.2, +2.15 );
         glVertex3f( -1.2, +1.2, +2.15 );
         glVertex3f( -1.2, +1.2, +2.15 );
      glEnd();

      glBegin( GL_LINE );
         glVertex3f( -1.2, +1.2, -2.8 );
         glVertex3f( +1.2, +1.2, -2.8 );
         glVertex3f( +1.2, -1.2, +2.15 );
         glVertex3f( +1.2, +1.2, +2.15 );
      glEnd();
   }

   Shape::endTransform();
}

   // sets the color of the "snow". the hat color is
   // always black
void Snowman::SetMaterial( Material m )
{
   Shape::SetMaterial( m );

   bottom.SetMaterial( m );
   body.SetMaterial( m );
   head.SetMaterial( m );
}
