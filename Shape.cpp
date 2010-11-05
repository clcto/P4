// --------------------------------------------------------
// Shape.cpp:
//    abstract class that represents a shape, holding
//    code that is common to all 'shapes'
//
//  Carick Wienke <cdj26@unh.edu>
//
//  Derived from Demo0 by RDB
// --------------------------------------------------------

#include "Shape.h"

#include <iostream>

// ======== Public Methods/Constructors ===================

   // -----------------------------------------------------
   // Shape::Shape
   // create a shape at its default size/scale/roation
Shape::Shape( string n ) : name( n )
{
   location.x = location.y = location.z = 0;

   scale.x = scale.y = scale.z = 1;

   rotate.x = 0;
   rotate.y = 0;
   rotate.z = 1;

   angle = 0;

   material = Material::BRASS;

   quadric = gluNewQuadric();

   highlight = false;
}

   // -----------------------------------------------------
   // Shape::~Shape
Shape::~Shape()
{
   gluDeleteQuadric( quadric );
}

   // -----------------------------------------------------
   // sets the translation 
void Shape::SetTranslation( GLfloat tx, GLfloat ty,
                            GLfloat tz )
{
   location.x = tx;
   location.y = ty;
   location.z = tz;
}

   // -----------------------------------------------------
   // sets the scale
void Shape::SetScale( GLfloat xs, GLfloat ys,
                      GLfloat zs )
{
   scale.x = xs;
   scale.y = ys;
   scale.z = zs;
}


void Shape::SetMaterial( Material m )
{
   material = m;
}
   
   // -----------------------------------------------------
   // set the matrix for the transform
void Shape::beginTransform()
{
   glMatrixMode( GL_MODELVIEW );
   glPushMatrix();
   glTranslated( location.x, location.y, location.z );
   glRotatef( angle, rotate.x, rotate.y, rotate.z );
   glScaled( scale.x, scale.y, scale.z );
}

   // gets the matrix off the stack so it goes back
   // to how it was before drawing the shape
void Shape::endTransform()
{
   glMatrixMode( GL_MODELVIEW );
   glPopMatrix();
}

void Shape::SetRotation( GLfloat a, GLVector r )
{
   angle = a;
   rotate = r;
}

void Shape::SetRotation( GLfloat a, GLfloat i, GLfloat j,
                         GLfloat k )
{
   GLVector v = {i,j,k};
   SetRotation( a, v );
}

   // -----------------------------------------------------
   // turn on and off highlighting
void Shape::HighlightOn()
{
   highlight = true;
}

void Shape::HighlightOff()
{
   highlight = false;
}

   // Accessors ===============================================
GLPoint Shape::GetTranslation() const
{
   return location;
}

GLScale Shape::GetScale() const
{
   return scale;
}

string Shape::GetName() const
{
   return name;
}

GLfloat Shape::GetRotationAngle() const
{
   return angle;
}

GLVector Shape::GetRotationVector() const
{
   return rotate;
}

Material Shape::GetMaterial() const
{
   return material;
}
