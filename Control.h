//---------------------------------------------------------
// Control.h
//    class definition for the control window
//
// Author: Carick Wienke
// --------------------------------------------------------

#ifndef CONTROL_H_
#define CONTROL_H_

#include <string>
#include <GL/glut.h>
#include <GL/glui.h>

#include "Camera.h"

using std::string;

class Control
{
   public:
         // singleton pattern method to get instance
      static Control* Instance();
      
         // sets up the control box with the name
         // given and the windowID of the main
         // graphics window
      void Initialize( string name, int windowID );

      void LoadValues();

      void SelectionChanged( const uint& );

   protected:
         // singleton instance
      static Control* instance;

         // callback function for content changing
      static void modified_cb( int );
      
         // callback instance method
      void modified( int );
      
      void createCamera();
      void createDirectional();
      void createPoint();
      void createColor();
      
         // enum determining which value changed
      enum ModifiedControl
      {
         Modified_Directional,
         Modified_Point,
         Modified_Camera,


         Modified_Eye,
         Modified_Center,
         Modified_Up,
         Modified_Mode,
         Modified_OrthoFrustum,
         Modified_Perspective,
         Modified_Right,
         Modified_Left,
         Modified_Top,
         Modified_Bottom,
         Modified_FOV,
         Modified_Aspect,
         Modified_Selection,
         Modified_Translation,
         Modified_Scale,
         Modified_Rotation,
         Modified_Color,
         Modified_Quit
      };

         // Controls
      GLUI *glui;

         // Camera properties, spherical
      GLUI_Spinner *cam_radius,
                   *cam_heading,
                   *cam_elevation;

         // Directional Light properties
      GLUI_Spinner *dir_heading,
                   *dir_elevation;
      GLUI_Checkbox *dir_enable;

        // Point light properties 
      GLUI_Checkbox *pnt_enable;
      GLUI_Spinner *pnt_x, *pnt_y, *pnt_z;

      GLUI_Listbox *selectionControl;
      
      GLUI_Spinner *redControl;
      GLUI_Spinner *greenControl;
      GLUI_Spinner *blueControl;
      
      GLUI_EditText *saveFileControl;
      GLUI_Button   *saveButton;
      GLUI_StaticText *saveStatus;


};

#endif // CONTROL_H_
