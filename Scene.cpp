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
#include "Snowman.h"

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
}

   // -----------------------------------------------------
   // Redraw
   //    draw the scene again, boxing selected
void Scene::Redraw()
{
   camera.SetUpGLMatrices();
   GLfloat pos[4] = {1, 1, 1, 0};
   glLightfv( GL_LIGHT0, GL_POSITION, pos );

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
   s->SetTranslation( 10, 10, 0 );
   AddShape( s );

   Cone *cone = new Cone( "cone" );
   cone->SetScale( 0.5, 0.5, 0.5 );
   cone->SetTranslation( -2, -2, 4 );
   cone->SetColor( 0, 0, 1 );
   AddShape( cone );

   Disk *d = new Disk( "disk" );
   d->SetScale( 1.2, 2.1, 1 );
   d->SetTranslation( 1, 0, -1 );
   d->SetRotation( 60, 1, 1, 1 );
   d->SetColor( 1, 0, 1 );
   AddShape( d );

   Sphere *sp = new Sphere( "Sphere" );
   sp->SetScale( -2, 1.1, 0.3 );
   sp->SetTranslation( 5, 0, -2 );
   sp->SetColor( 0.5, 1, 0 );
   AddShape( sp );
   
   Cylinder *c = new Cylinder( "Cylinder" );
   c->SetScale( 2, 2, 3 );
   c->SetTranslation( 3, 3, 8 );
   c->SetRotation( 90, 1, 0, 0 );
   c->SetColor( 0, 1, 0.5 );
   AddShape( c );

   s = new Snowman( "Snowman_2" );
   s->SetScale( 1.3, 1.8, 2 );
   s->SetTranslation( -5, -5, -5 );
   s->SetColor( 0.5, 0, 1 );
   AddShape( s );

   GLVector v = { 1, 0, 0 };

   cone->SetRotation( 90, v );


   
}

   // -----------------------------------------------------
   // setselected
   //    changes the currently selected shape
void Scene::SetSelected( const uint& index )
{
   if( index < shapes.size() )
   {
      if( selected )
         shapes[ selectedIndex ]->HighlightOff();

      selectedIndex = index;
      selected = true;
      Control::Instance()->SelectionChanged( index );

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

   // reads command from a file to create a scene
void Scene::ReadFile( string filename )
{
   ifstream file( filename.c_str() );

   if( !file.is_open() )
   {
      cerr << "Error opening file '" << filename << "'\n"
           << "  Creating default Scene\n";
      LoadDefault();
      return;
   }

   char line[256];
   file.getline( line, 256 );
   while( !file.eof() )
   {
      vector<string> tok = tokenize( line, "\t " );

      if( tok.size() >= 1 )
      {
         if( tok[0].compare( "define" ) == 0 )
            processDefine( tok );
         
         else if( tok[0].compare( "translate" ) == 0 )
            processTranslate( tok );
         
         else if( tok[0].compare( "scale" ) == 0 )
            processScale( tok );
         
         else if( tok[0].compare( "rotate" ) == 0 )
            processRotate( tok );

         else if( tok[0].compare( "color" ) == 0 )
            processColor( tok );

         else if( tok[0].compare( "eye" ) == 0 )
            processEye( tok );

         else if( tok[0].compare( "center" ) == 0 )
            processCenter( tok );

         else if( tok[0].compare( "up" ) == 0 )
            processUp( tok );

         else if( tok[0].compare( "ortho" ) == 0 )
            processOrtho( tok );

         else if( tok[0].compare( "frustum" ) == 0 )
            processFrustum( tok );

         else if( tok[0].compare( "perspective" ) == 0 )
            processPerspective( tok );
         
         else if( tok[0].c_str()[0] != '#' )
         {
            cerr << "Invalid Command <" << tok[0]
                 << ">\n";
         }
      }

      file.getline( line, 256 );
   }

   file.close();
}

   // -----------------------------------------------------
   // void processDefine
   //    processes a d command from the file
void Scene::processDefine( const vector<string> &tok )
{
      // makes sure there are enough arguments
   if( tok.size() < 3 )
   {
      cerr << "'define' expects <type> <name>\n"
           << "   To few arguments.\n";
      return;
   }

   if( 0 ){}
   else if( tok[1].compare( "cylinder" ) == 0 )
   {
      Cylinder *c = new Cylinder( tok[2] );
      Scene::Instance()->AddShape( c );
   }
   else if( tok[1].compare( "cone" ) == 0 )
   {
      Cone *t = new Cone( tok[2] );
      Scene::Instance()->AddShape( t );
   }
   else if( tok[1].compare( "sphere" ) == 0 )
   {
      Sphere *p = new Sphere( tok[2] );
      Scene::Instance()->AddShape( p );
   }
   else if( tok[1].compare( "disk" ) == 0 )
   {
      Disk *p = new Disk( tok[2] );
      Scene::Instance()->AddShape( p );
   }
   else if( tok[1].compare( "snowman" ) == 0 )
   {
      Snowman *p = new Snowman( tok[2] );
      Scene::Instance()->AddShape( p );
   }
   else
      cerr << "define: Invalid Shape Type '" << tok[1]
           << "'\n";
}

   // -----------------------------------------------------
   // void processTranslate
   //    processes a t command from the file
void Scene::processTranslate( const vector<string> &tok )
{
      // makes sure there are enough arguments
   if( tok.size() < 5 )
   {
      cerr << "'translate' expects <name> "
           << "<float tx> <float ty> <float tz>\n"
           << "   To few arguments.\n";
      return;
   }

      // are the float parameters floats?
   float tx, ty, tz;
   if( ! stringToFloat( tok[2], tx ) )
   {
      cerr << "'translate' expects <name> "
           << "<float tx> <float ty> <float tz>\n"
           << "   '" << tok[2] << "' is not a float.\n";
      return;
   }

   if( ! stringToFloat( tok[3], ty ) )
   {
      cerr << "'translate' expects <name> "
           << "<float tx> <float ty> <float tz>\n"
           << "   '" << tok[3] << "' is not a float.\n";
      return;
   }

   if( ! stringToFloat( tok[4], tz ) )
   {
      cerr << "'translate' expects <name> "
           << "<float tx> <float ty> <float tz>\n"
           << "   '" << tok[4] << "' is not a float.\n";
      return;
   }

   Shape* sel = Scene::Instance()->GetShape( tok[1] );
   if( sel )
      sel->SetTranslation( tx, ty, tz );
   else
      cerr << "translate: Shape '" << tok[1] 
           << "' is not defined\n";
}

   // -----------------------------------------------------
   // void processScale
   //    processes a s command from the file
void Scene::processScale( const vector<string> &tok )
{
      // makes sure there are enough arguments
   if( tok.size() < 5 )
   {
      cerr << "'scale' expects <name> "
           << "<float xs> <float ys> <float zs>\n"
           << "   To few arguments.\n";
      return;
   }

      // are the float parameters floats?
   float sx, sy, sz;
   if( ! stringToFloat( tok[2], sx ) )
   {
      cerr << "'scale' expects <name> "
           << "<float xs> <float ys> <float zs>\n"
           << "   '" << tok[2] << "' is not a float.\n";
      return;
   }

   if( ! stringToFloat( tok[3], sy ) )
   {
      cerr << "'scale' expects <name> "
           << "<float xs> <float ys> <float zs>\n"
           << "   '" << tok[3] << "' is not a float.\n";
      return;
   }

   if( ! stringToFloat( tok[4], sz ) )
   {
      cerr << "'scale' expects <name> "
           << "<float xs> <float ys> <float zs>\n"
           << "   '" << tok[4] << "' is not a float.\n";
      return;
   }

   Shape* sel = Scene::Instance()->GetShape( tok[1] );
   if( sel )
      sel->SetScale( sx, sy, sz );
   else
      cerr << "scale: Shape '" << tok[1] 
           << "' is not defined\n";
}

   // -----------------------------------------------------
   // void processRotate
   //    processes a rotate command from the file
void Scene::processRotate( const vector<string> &tok )
{
      // makes sure there are enough arguments
   if( tok.size() < 6 )
   {
      cerr << "'rotate' expects <name> <float angle> "
           << "floats <i> <j> <k>\n"
           << "   To few arguments.\n";
      return;
   }

   float a, i, j, k;
      // are the float parameters floats?
   if( ! stringToFloat( tok[2], a ) )
   {
      cerr << "'rotate' expects <name> <float angle> "
           << "floats <i> <j> <k>\n"
           << tok[2] << "' is not a float.\n";
      return;
   }

   if( ! stringToFloat( tok[3], i ) )
   {
      cerr << "'rotate' expects <name> <float angle> "
           << "floats <i> <j> <k>\n"
           << tok[3] << "' is not a float.\n";
      return;
   }

   if( ! stringToFloat( tok[4], j ) )
   {
      cerr << "'rotate' expects <name> <float angle> "
           << "floats <i> <j> <k>\n"
           << tok[4] << "' is not a float.\n";
      return;
   }

   if( ! stringToFloat( tok[5], k ) )
   {
      cerr << "'rotate' expects <name> <float angle> "
           << "floats <i> <j> <k>\n"
           << tok[5] << "' is not a float.\n";
      return;
   }

   Shape* sel = Scene::Instance()->GetShape( tok[1] );
   if( sel )
   {
      GLVector v = { i, j, k };
      sel->SetRotation( a, v );
   }
   else
      cerr << "rotate: Shape '" << tok[1] 
           << "' is not defined\n";
}

   // -----------------------------------------------------
   // processColor
   //    process a color command line
void Scene::processColor( const vector<string> &tok )
{
      // makes sure there are enough arguments
   if( tok.size() < 5 )
   {
      cerr << "'color' expects <name>"
           << " floats <r> <g> <b>>\n"
           << "   To few arguments.\n";
      return;
   }

   float r, g, b;
      // are the float parameters floats?
   if( ! stringToFloat( tok[2], r ) )
   {
      cerr << "'color' expects <name>"
           << " floats <r> <g> <b>>\n"
           << tok[2] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[3], g ) )
   {
      cerr << "'color' expects <name>"
           << " floats <r> <g> <b>>\n"
           << tok[3] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[4], b ) )
   {
      cerr << "'color' expects <name>"
           << " floats <r> <g> <b>>\n"
           << tok[4] << "' is not a float.\n";
      return;
   }

      // get the shape and make sure it is valid
   Shape* sel = Scene::Instance()->GetShape( tok[1] );
   if( sel )
      sel->SetColor( r, g, b );
   else
      cerr << "color: Shape '" << tok[1] 
           << "' is not defined\n";
}

   // -----------------------------------------------------
   // processEye
   //    process a eye command line
void Scene::processEye( const vector<string> &tok )
{
      // makes sure there are enough arguments
   if( tok.size() < 4 )
   {
      cerr << "'eye' expects floats <x> <y> <z>\n"
           << "   To few arguments.\n";
      return;
   }

   float x, y, z;
      // are the float parameters floats?
   if( ! stringToFloat( tok[1], x ) )
   {
      cerr << "'eye' expects floats <x> <y> <z>\n"
           << tok[1] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[2], y ) )
   {
      cerr << "'eye' expects floats <x> <y> <z>\n"
           << tok[2] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[3], z ) )
   {
      cerr << "'eye' expects floats <x> <y> <z>\n"
           << tok[3] << "' is not a float.\n";
      return;
   }

   GLPoint p = { x, y, z };
   camera.SetEye( p );
}

   // -----------------------------------------------------
   // processCenter
   //    process a center command line
void Scene::processCenter( const vector<string> &tok )
{
      // makes sure there are enough arguments
   if( tok.size() < 4 )
   {
      cerr << "'center' expects floats <x> <y> <z>\n"
           << "   To few arguments.\n";
      return;
   }

   float x, y, z;
      // are the float parameters floats?
   if( ! stringToFloat( tok[1], x ) )
   {
      cerr << "'center' expects floats <x> <y> <z>\n"
           << tok[1] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[2], y ) )
   {
      cerr << "'center' expects floats <x> <y> <z>\n"
           << tok[2] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[3], z ) )
   {
      cerr << "'center' expects floats <x> <y> <z>\n"
           << tok[3] << "' is not a float.\n";
      return;
   }

   GLPoint p = { x, y, z };
   camera.SetCenter( p );
}

   // -----------------------------------------------------
   // processUp
   //    process a up command line
void Scene::processUp( const vector<string> &tok )
{
      // makes sure there are enough arguments
   if( tok.size() < 4 )
   {
      cerr << "'up' expects floats <i> <j> <k>\n"
           << "   To few arguments.\n";
      return;
   }

   float x, y, z;
      // are the float parameters floats?
   if( ! stringToFloat( tok[1], x ) )
   {
      cerr << "'up' expects floats <i> <j> <k>\n"
           << tok[1] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[2], y ) )
   {
      cerr << "'up' expects floats <i> <j> <k>\n"
           << tok[2] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[3], z ) )
   {
      cerr << "'up' expects floats <i> <j> <k>\n"
           << tok[3] << "' is not a float.\n";
      return;
   }

   GLVector v = { x, y, z };
   camera.SetUp( v );
}

   // -----------------------------------------------------
   // processOrtho
   //    process a ortho command line
void Scene::processOrtho( const vector<string> &tok )
{
      // makes sure there are enough arguments
   if( tok.size() < 7 )
   {
      cerr << "'ortho' expects floats "
           << "<l> <r> <b> <t> <n> <f>\n"
           << "   To few arguments.\n";
      return;
   }

   float l, r, b, t, n, f;
      // are the float parameters floats?
   if( ! stringToFloat( tok[1], l ) )
   {
      cerr << "'ortho' expects floats "
           << "<l> <r> <b> <t> <n> <f>\n"
           << tok[1] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[2], r ) )
   {
      cerr << "'ortho' expects floats "
           << "<l> <r> <b> <t> <n> <f>\n"
           << tok[2] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[3], b ) )
   {
      cerr << "'ortho' expects floats "
           << "<l> <r> <b> <t> <n> <f>\n"
           << tok[3] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[4], t ) )
   {
      cerr << "'ortho' expects floats "
           << "<l> <r> <b> <t> <n> <f>\n"
           << tok[4] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[5], n ) )
   {
      cerr << "'ortho' expects floats "
           << "<l> <r> <b> <t> <n> <f>\n"
           << tok[5] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[6], f ) )
   {
      cerr << "'ortho' expects floats "
           << "<l> <r> <b> <t> <n> <f>\n"
           << tok[6] << "' is not a float.\n";
      return;
   }

   camera.SetMode( Camera::Mode_Ortho );
   camera.SetLeft( l );
   camera.SetRight( r );
   camera.SetBottom( b );
   camera.SetTop( t );
   camera.SetNear( n );
   camera.SetFar( f );
}

   // -----------------------------------------------------
   // processFrustum
   //    process a frustum command line
void Scene::processFrustum( const vector<string> &tok )
{
      // makes sure there are enough arguments
   if( tok.size() < 7 )
   {
      cerr << "'frustum' expects floats "
           << "<l> <r> <b> <t> <n> <f>\n"
           << "   To few arguments.\n";
      return;
   }

   float l, r, b, t, n, f;
      // are the float parameters floats?
   if( ! stringToFloat( tok[1], l ) )
   {
      cerr << "'frustum' expects floats "
           << "<l> <r> <b> <t> <n> <f>\n"
           << tok[1] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[2], r ) )
   {
      cerr << "'frustum' expects floats "
           << "<l> <r> <b> <t> <n> <f>\n"
           << tok[2] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[3], b ) )
   {
      cerr << "'frustum' expects floats "
           << "<l> <r> <b> <t> <n> <f>\n"
           << tok[3] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[4], t ) )
   {
      cerr << "'frustum' expects floats "
           << "<l> <r> <b> <t> <n> <f>\n"
           << tok[4] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[5], n ) )
   {
      cerr << "'frustum' expects floats "
           << "<l> <r> <b> <t> <n> <f>\n"
           << tok[5] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[6], f ) )
   {
      cerr << "'frustum' expects floats "
           << "<l> <r> <b> <t> <n> <f>\n"
           << tok[6] << "' is not a float.\n";
      return;
   }

   camera.SetMode( Camera::Mode_Frustum );
   camera.SetLeft( l );
   camera.SetRight( r );
   camera.SetBottom( b );
   camera.SetTop( t );
   camera.SetNear( n );
   camera.SetFar( f );
}

   // -----------------------------------------------------
   // processPerspective
   //    process a perspective command line
void Scene::processPerspective( const vector<string> &tok )
{
      // makes sure there are enough arguments
   if( tok.size() < 5 )
   {
      cerr << "'perspective' expects floats "
           << "<fov> <aspect> <n> <f>\n"
           << "   To few arguments.\n";
      return;
   }

   float fov, asp, n, f;
      // are the float parameters floats?
   if( ! stringToFloat( tok[1], fov ) )
   {
      cerr << "'perspective' expects floats "
           << "<fov> <aspect> <n> <f>\n"
           << tok[1] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[2], asp ) )
   {
      cerr << "'perspective' expects floats "
           << "<fov> <aspect> <n> <f>\n"
           << tok[2] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[3], n ) )
   {
      cerr << "'perspective' expects floats "
           << "<fov> <aspect> <n> <f>\n"
           << tok[3] << "' is not a float.\n";
      return;
   }
   if( ! stringToFloat( tok[4], f ) )
   {
      cerr << "'perspective' expects floats "
           << "<fov> <aspect> <n> <f>\n"
           << tok[4] << "' is not a float.\n";
      return;
   }

   camera.SetMode( Camera::Mode_Perspective );
   camera.SetFOV( fov );
   camera.SetAspectRatio( asp );
   camera.SetNear( n );
   camera.SetFar( f );
}

   // -----------------------------------------------------
   // vector<string> tokenize
   //    splits the input string into tokens
   //
   // input: the string to split
   // delims: the delims to split on
   //
   // returns a vector containing all the tokens
vector<string> tokenize( const string& input,
                         const string& delims )
{
   vector<string> tokens;

   string::size_type tokenStart, tokenEnd;

      // get the start and end of the first token
   tokenStart = input.find_first_not_of( delims, 0 );
   tokenEnd   = input.find_first_of( delims, tokenStart );

   while( !( tokenStart == string::npos && 
             tokenEnd   == string::npos ) )
   {
         // add the token to the vector.
      tokens.push_back( input.substr( tokenStart, 
                                      tokenEnd - tokenStart ) );

      tokenStart = input.find_first_not_of( delims, tokenEnd );
      tokenEnd   = input.find_first_of(     delims, tokenStart );
   }

   return tokens;
}

   // -----------------------------------------------------
   // bool stringToFloat( const string&, float& )
   //    converts the string to a float, saves it in the 
   //    out variable, and returns if it was successful
bool stringToFloat( const string& str, float& out )
{
   istringstream iss( str );
   return !( iss >> std::dec >> out ).fail();
}
