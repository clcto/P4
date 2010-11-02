// -----------------------------------------------------
// Shape.h:
//    abstract class that represents a shape, holding
//    code that is common to all 'shapes'
//
//  Carick Wienke <cdj26@unh.edu>
//
//  Derived from Demo0 by RDB
// -----------------------------------------------------

#ifndef SHAPE_H_
#define SHAPE_H_

#include <GL/glut.h>
#include <cmath>
#include <string>

#include "Color.h"
#include "GLPoint.h"

using std::string;

class Shape
{

   public: //------------------------------------------

         // creates the shape in its own coordinate 
         // system
      Shape( string n = "" );

      virtual ~Shape();
      
         // SetTranslation
         // sets the translation of the shape
      void SetTranslation( GLPoint p );
      void SetTranslation( GLfloat, GLfloat, GLfloat );

      GLPoint GetTranslation() const;

         // set the scale of the shape
      void SetScale( GLScale s );
      void SetScale( GLfloat, GLfloat, GLfloat ); 

      GLScale GetScale() const;

         // set the color of the shape
      virtual void SetColor( float r, float g, float b );
      virtual void SetColor( Color ct );

      Color GetColor() const;
         
         // sets the rotation of the object
      void SetRotation( GLfloat, GLVector );
      void SetRotation( GLfloat, GLfloat, GLfloat,
                        GLfloat );

      GLfloat GetRotationAngle() const;
      GLVector GetRotationVector() const;

      virtual void HighlightOn();
      virtual void HighlightOff();

      string GetName() const;

      virtual void Redraw() = 0;

   protected: // --------------------------------------
      static const float pi = 3.141593;

         // modify the CT for transformations in 2D
      static void initCT();
      static void scale2D( GLdouble sx, GLdouble sy );
      static void translate2D( GLdouble dx,
                               GLdouble dy );
      static void rotate2D( GLdouble angle );

         // sets up the transform matrix so the draw
         // will occur with the proper transforms 
      void beginTransform();
      void endTransform();

         // translation locations
      GLPoint location;
         
         // scale coefficients
      GLScale scale;

         // rotation
      GLfloat angle;
      GLVector rotate;

         // color of the shape, RGB
      Color color;

      GLUquadric* quadric;

      bool highlight;

      string name;

};

#endif /*SHAPE_H_*/
