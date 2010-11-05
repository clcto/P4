
#include "Material.h"

const Material Material::BRASS(
         0.3294, 0.2235, 0.02745,
         0.7804, 0.5686, 0.1137,
         0.9, .9, .9, 128 );

const Material Material::MATTE_RED(
         0.25, 0.0, 0.0,
         0.6, 0.1, 0.1,
         0.2, 0.2, 0.2, 3 );

const Material Material::CHROME(
         0.23125, 0.23125, 0.23125,
         0.5775, 0.5775, 0.5775,
         0.9339, 0.9339, 0.9339, 110 );

const Material Material::BLACK_PLASTIC(
         0, 0, 0,
         0.2, 0.2, 0.2,
         0.2, 0.2, 0.2, 32 );

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
