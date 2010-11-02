// Cone.h
//    Header file for the Cone shape.
//    a wrapper for a specific type of cylinder
//    with a radius of 0 at the top

#ifndef CONE_H_
#define CONE_H_

#include "Shape.h"

class Cone : public Shape
{
   public:
      Cone( string n = "" );
      void Redraw();
      
   protected:
       
};

#endif
