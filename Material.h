
#include "Color.h"
#include "GL/gl.h"

class Material
{
   public:
      Material( float = 0, float = 0, float = 0,
                float = 0, float = 0, float = 0,
                float = 0, float = 0, float = 0,
                float = 0 );
      Material( Color, Color, Color, float );

      void GLInit() const;

      static const Material BRASS;
      
   private:
      Color ambient, diffuse, specular, exponent;
      float shine;
};
