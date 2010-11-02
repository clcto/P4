// --------------------------------------------------------
// Light.h
//    virtual class that is used to store common 
//    data and functions of all the possible lights
//
// Carick Wienke
// --------------------------------------------------------

#include "GLPoint.h"

class Light
{
   public:
      Light( GLenum l, GLfloat p[] );
       
      Light( GLenum l, GLfloat p[], GLfloat a[],
             GLfloat d[], GLfloat s[] );

      void GLInit();

      void SetLocationSpherical( 
         float theta, float phi, float radius = 1 );

      void SetLocationRectangular(
         GLfloat x, GLfloat y, GLfloat z );

   protected:
      GLenum light;
      GLfloat position[4];
      GLfloat ambient[4], diffusion[4], specular[4];
};
