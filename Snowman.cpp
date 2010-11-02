// --------------------------------------------------------
// Snowman
//    A class that represents a 3d snowman. It uses 
//    other classes that wrap the glu solids
//
// Carick Wienke

#include "Snowman.h"
#include "Disk.h"

// Constructor
//    creates the snowman. moves the shapes and
//    resizes them so they actually make the snowman
Snowman::Snowman( string n ) : Shape( n )
{
   bottom.SetTranslation( 0, 0, -1.6 );
   bottom.SetScale( 1.2, 1.2, 1.2 );

   head.SetTranslation( 0, 0, 1.2 );
   head.SetScale( 0.65, 0.65, 0.65 );

   hatBottom.SetColor( 0.07, 0.07, 0.07 );
   hatBottom.SetScale( 0.6, 0.6, 0.1 );
   hatBottom.SetTranslation( 0, 0, 1.65 );

   hatTop.SetColor( 0.07, 0.07, 0.07 );
   hatTop.SetScale( 0.47, 0.47, 0.4 );
   hatTop.SetTranslation( 0, 0, 1.75 );

   hatLow.SetColor( 0.07, 0.07, 0.07 );
   hatLow.SetScale( 0.6, 0.6, 1 );
   hatLow.SetTranslation( 0, 0, 1.65 );

   hatLow.SetColor( 0.07, 0.07, 0.07 );
   hatLow.SetScale( 0.6, 0.6, 1 );
   hatLow.SetTranslation( 0, 0, 1.75 );

   hatHigh.SetColor( 0.07, 0.07, 0.07 );
   hatHigh.SetScale( 0.47, 0.47, 1 );
   hatHigh.SetTranslation( 0, 0, 2.15 );
}

   // draw the snowman to the screen
void Snowman::Redraw()
{
   Shape::beginTransform();

   bottom.Redraw();
   body.Redraw();
   head.Redraw();
   hatBottom.Redraw();
   hatTop.Redraw();
   hatLow.Redraw();
   hatMid.Redraw();
   hatHigh.Redraw();

   Shape::endTransform();
}

   // sets the color of the "snow". the hat color is
   // always black
void Snowman::SetColor( GLfloat r, GLfloat g, GLfloat b )
{
   Shape::SetColor( r, g, b );

   bottom.SetColor( r, g, b );
   body.SetColor( r, g, b );
   head.SetColor( r, g, b );
}

void Snowman::SetColor( Color c )
{
   Shape::SetColor( c );

   bottom.SetColor( c );
   body.SetColor( c );
   head.SetColor( c );
}

   // highlight each of it's components
void Snowman::HighlightOn()
{
   bottom.HighlightOn();
   body.HighlightOn();
   head.HighlightOn();
   hatBottom.HighlightOn();
   hatTop.HighlightOn();
   hatLow.HighlightOn();
   hatMid.HighlightOn();
   hatHigh.HighlightOn();
}

   // stop highlighting each of its components
void Snowman::HighlightOff()
{
   bottom.HighlightOff();
   body.HighlightOff();
   head.HighlightOff();
   hatBottom.HighlightOff();
   hatTop.HighlightOff();
   hatLow.HighlightOff();
   hatMid.HighlightOff();
   hatHigh.HighlightOff();
}
