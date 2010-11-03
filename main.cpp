// --------------------------------------------------------
// main.cpp for Program 3
// 
// This program shows a 3D Scene and allows the camera
//    to be modified.
//
//    Additional Features:
//       Lighting
//       Read a scene from a file
//       ability to select and change shapes
//       selected shape "emits" light to show it is
//          selected
//
// Assignment 3: 3D Graphics
// UNH CS 770 - Computer Graphics
// Due: 2010.10.14
// --------------------------------------------------------

#include <vector>
#include <iostream>
#include <GL/glut.h>
   // also includes gl.h and glu.h

#include "Shape.h"
#include "Control.h"
#include "Scene.h"
#include "Sphere.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Snowman.h"

#define min( a, b ) ( a < b ? a : b )
#define max( a, b ) ( a > b ? a : b )

using std::vector;
using std::cout;

const int windowWidth  = 500;
const int windowHeight = 500;

   // initializes the GL portion of the application
void appInit(void)
{
   glEnable( GL_DEPTH_TEST );

   glEnable( GL_LIGHTING );
   glEnable( GL_COLOR_MATERIAL );
   glEnable( GL_LIGHT0 );

   glShadeModel( GL_SMOOTH );

      // background color: white
   glClearColor( 1.0, 1.0, 1.0, 0.0 );
}

   // redraws the scene.
   //    clears, draws all the shapes, and flused
void redraw( void )
{
      // clear the screen 
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   Scene::Instance()->Redraw();
   
   glutSwapBuffers();
}

   // runs the program. Sets up the handlers and menu
   // so the program actually does something. 
int main( int argc, char **argv )
{
      // initialize toolkit
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DEPTH | 
           GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize( windowWidth, windowHeight ); 

      // set the window properties
	glutInitWindowPosition( 100, 150 );
   int window = glutCreateWindow( "P3 solution" );

      // define the function to call when a 
      // redraw is requested
	glutDisplayFunc( redraw );

	appInit();

   if( argc > 1 )
      Scene::Instance()->ReadFile( argv[1] );
   else
      Scene::Instance()->LoadDefault();

   Control::Instance()->Initialize( "Control", window );

      // let glut do its thing
	glutMainLoop();
}
