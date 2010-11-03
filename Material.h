
#include "Color.h"
#include "GL/gl.h"

class Material
{
   public:
      Material( float = 0, float = 0, float = 0,
                float = 0, float = 0, float = 0,
                float = 0, float = 0, float = 0,
                float = 0 );

      void GLInit() const;

      static const Material BRASS,
                            MATTE_RED,
                            CHROME,
                            BLACK_PLASTIC;
      
   private:
      Color ambient, diffuse, specular, exponent;
      float shine;
};
