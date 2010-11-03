
#include "Material.h"

const Material Material::BRASS(
         0.3294, 0.2235, 0.02745,
         0.7804, 0.5686, 0.1137,
         0.9922, 0.9412, 0.8078, 27.897 );

Material::Material( float aR, float aG, float aB, 
                    float dR, float dG, float dB,
                    float sR, float sG, float sB,
                    float exp )
{
   ambient.red = aR;
   ambient.green = aG;
   ambient.blue = aB;

   diffuse.red = dR;
   diffuse.green = dG;
   diffuse.blue = dB;

   specular.red = sR;
   specular.green = sG;
   specular.blue = sB;

   shine = exp;
}

void Material::GLInit() const
{
   float param[4];
   param[3] = 1;
   
   param[0] = ambient.red; 
   param[1] = ambient.green; 
   param[2] = ambient.blue; 
   glMaterialfv( GL_FRONT, GL_AMBIENT, param );

   param[0] = diffuse.red; 
   param[1] = diffuse.green; 
   param[2] = diffuse.blue; 
   glMaterialfv( GL_FRONT, GL_DIFFUSE, param );

   param[0] = specular.red; 
   param[1] = specular.green; 
   param[2] = specular.blue; 
   glMaterialfv( GL_FRONT, GL_SPECULAR, param );

   glMaterialf( GL_FRONT, GL_SHININESS, shine );
}
