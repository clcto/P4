#ifndef SNOWMAN_H_
#define SNOWMAN_H_

#include "Shape.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Color.h"
#include "Disk.h"

class Snowman : public Shape
{
   public:
      Snowman( string n = "" );

      void SetMaterial( Material );
      void Redraw();
    //  void HighlightOn();
    //  void HighlightOff();
      
   protected:
      Sphere bottom, body, head;
      Cylinder hatBottom, hatTop;
      Disk hatLow, hatMid, hatHigh;
       
};

#endif
