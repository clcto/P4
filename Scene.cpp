// --------------------------------------------------------
// Scene.cpp
//    Represents the scene on the screen using the
//    singleton pattern.
//
//    Allows for adding, but not removal, of shapes,
//    and holds the currently selected shape
//
// Carick Wienke
// --------------------------------------------------------

#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <sstream>
#include <typeinfo>

#include "Scene.h"
#include "Control.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Sphere.h"
#include "Square.h"
#include "Snowman.h"
#include "Disk.h"

using std::ifstream;
using std::cerr;
using std::istringstream;
using std::ofstream;

Scene* Scene::instance = NULL;

   // -----------------------------------------------------
   // singleton pattern to get the sole scene
Scene* Scene::Instance()
{
   if( !instance )
      instance = new Scene();
   return instance;
}

   // -----------------------------------------------------
   //  Constructor
Scene::Scene() 
{
   selected = false;

   GLfloat dir_pos[4] = { 1, 0, 0, 0 };
   directionalLight = new Light( GL_LIGHT0, dir_pos );
   directionalLight->Disable();

   GLfloat pnt_pos[4] = { 10, 0, 0, 1 };
   pointLight = new Light( GL_LIGHT1, pnt_pos );
}

Scene::~Scene()
{
   while( !shapes.empty() )
   {
      delete shapes.back();
      shapes.pop_back();
   }

   delete directionalLight;
   delete pointLight;

}

   // -----------------------------------------------------
   // Redraw
   //    draw the scene again, boxing selected
void Scene::Redraw()
{
   GLfloat ambient[] = { 0.4, 0.4, 0.4, 1 };
   glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient );

   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

   camera.SetUpGLMatrices();
   directionalLight->GLInit();
   pointLight->GLInit();

   vector<Shape*>::iterator it;
   
   for( it = shapes.begin(); it < shapes.end(); ++it )
      (*it)->Redraw();
}

   // -----------------------------------------------------
   // adds a shape to the scene
void Scene::AddShape( Shape* newShape )
{
   shapes.push_back( newShape );
}

Camera& Scene::GetCamera()
{
   return camera;
}

void Scene::LoadDefault()
{
   Shape *s = new Snowman( "Snowman_1" );
   s->SetScale( 2, 2, 2 );
   s->SetRotation( 30, 1, 1, 1 );
   s->SetMaterial( Material::CHROME );
   AddShape( s );

   Sphere *sp = new Sphere( "Sphere" );
   sp->SetScale( 3, 3, 3 );
   sp->SetTranslation( 5, -2, -2 );
   sp->SetMaterial( Material::MATTE_RED );
   AddShape( sp );

   Cone *cone = new Cone( "cone" );
   cone->SetScale( 3, 3, 4 );
   cone->SetTranslation( 2, 5, 2 );
   cone->SetRotation( 90, 1, 0, 0 );
   cone->SetMaterial( Material::BRASS );
   AddShape( cone );

   Disk *d = new Disk( "disk" );
   d->SetScale( 1.2, 2.1, 1 );
   d->SetTranslation( -3, -6, 3 );
   d->SetRotation( 60, 1, 1, 1 );
   d->SetMaterial( Material::CHROME );
   AddShape( d );

   
   Cylinder *c = new Cylinder( "Cylinder" );
   c->SetScale( 2, 2, 3 );
   c->SetTranslation( 3, 3, 8 );
   c->SetRotation( 90, 1, 0, 0 );
   c->SetMaterial( Material::BLACK_PLASTIC );
   AddShape( c );

   s = new Snowman( "Snowman_2" );
   s->SetScale( 1.3, 1.8, 2 );
   s->SetTranslation( -9, -3, -5 );
   s->SetMaterial( Material::BLACK_PLASTIC );
   AddShape( s );

   Square* sq = new Square( "Square" );
   sq->SetScale( 3, 2, 1 );
   sq->SetTranslation( 5, 5, -4 );
   sq->SetRotation( 90, 0, 1, 0 );
   sq->SetMaterial( Material::MATTE_RED );
   AddShape( sq );

}

   // -----------------------------------------------------
   // setselected
   //    changes the currently selected shape
void Scene::SetSelected( const uint& index )
{
   std::cerr << "SetSelected( " << index << ")\n";
   std::cerr << "size: " << shapes.size() << "\n";
   if( index < shapes.size() )
   {
      if( selected )
         shapes[ selectedIndex ]->HighlightOff();

      selectedIndex = index;
      selected = true;

      shapes[ selectedIndex ]->HighlightOn();
   }
}

   // -----------------------------------------------------
   // Shape* getselected
   //    returns the currently selected shape
Shape* Scene::GetSelected()
{
   if( selected )
      return shapes[ selectedIndex ];
   else
      return NULL;
}

   // -----------------------------------------------------
   // Shape* GetShape( name )
   //    returns the shape that has the name passed,
   //    or NULL if it does not exist
Shape* Scene::GetShape( string name )
{
   vector<Shape*>::iterator it;

   for( it = shapes.begin(); it < shapes.end(); ++it )
      if( name.compare( (*it)->GetName() ) == 0 )
         return *it;

   return NULL;
}

   // -----------------------------------------------------
   // vector<string> GetNames
   //    retuns the list of names of the shapes
vector<string> Scene::GetNames()
{
   vector<string> names;

   vector<Shape*>::iterator it;
   
   for( it = shapes.begin(); it < shapes.end(); ++it )
      names.push_back( (*it)->GetName() );

   return names;
}

Light* Scene::GetDirectionalLight()
{
   return directionalLight;
}

Light* Scene::GetPointLight()
{
   return pointLight;
}
