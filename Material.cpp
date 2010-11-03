
#include "Material.h"

const Material Material::BRASS(
         0.3294, 0.2235, 0.02745,
         0.7804, 0.5686, 0.1137,
         0.9922, 0.9412, 0.8078, 27.897 );

Material::Material( float aR, float aB, float aG, 
                    float dR, float dB, float dG,
                    float sR, float sB, float sG,
                    float exp )
{
   ambient.red = aR;
   ambient.blue = aB;
   ambient.green = aG;

   diffuse.red = dR;
   diffuse.blue = dB;
   diffuse.green = dG;

   specular.red = sR;
   specular.blue = sB;
   specular.green = sG;

   shine = exp;
}

void Material::GLInit() const
{
   float param[4];
   param[3] = 1;
   
   param[0] = ambient.red; 
   param[1] = ambient.blue; 
   param[2] = ambient.green; 
   glMaterialfv( GL_FRONT, GL_AMBIENT, param );

   param[0] = diffuse.red; 
   param[1] = diffuse.blue; 
   param[2] = diffuse.green; 
   glMaterialfv( GL_FRONT, GL_DIFFUSE, param );

   param[0] = specular.red; 
   param[1] = specular.blue; 
   param[2] = specular.green; 
   glMaterialfv( GL_FRONT, GL_SPECULAR, param );

   glMaterialf( GL_FRONT, GL_SHININESS, shine );
}
