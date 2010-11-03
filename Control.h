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

      void LoadValues( const Camera& c );

      void SelectionChanged( const uint& );

   protected:
         // singleton instance
      static Control* instance;

         // callback function for content changing
      static void modified_cb( int );
      
         // callback instance method
      void modified( int );

      void createTransformations();
      void createColor();
      
         // enum determining which value changed
      enum ModifiedControl
      {
         Modified_Directional,


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

      GLUI_Spinner *dir_heading,
                   *dir_elevation;

      GLUI_Checkbox *dir_enable,
                    *pnt_enable;




      GLUI_Panel * lookAtPanel;
      GLUI_Panel * orthoFrustumPanel;
      GLUI_Panel * perspectivePanel;

      GLUI_Spinner * eyeX;
      GLUI_Spinner * eyeY;
      GLUI_Spinner * eyeZ;

      GLUI_Spinner * centerX;
      GLUI_Spinner * centerY;
      GLUI_Spinner * centerZ;

      GLUI_Spinner * upX;
      GLUI_Spinner * upY;
      GLUI_Spinner * upZ;

      GLUI_RadioGroup * mode;
      GLUI_RadioButton * ortho;
      GLUI_RadioButton * perspective;
      GLUI_RadioButton * frustum;
      
      GLUI_Spinner *right,
                   *left,
                   *top,
                   *bottom,
                   *ofNear,
                   *ofFar;

      GLUI_Spinner *fov,
                   *aspect,
                   *pNear,
                   *pFar;

      GLUI_Spinner *angleControl;
      GLUI_Spinner *rotateVectorX;
      GLUI_Spinner *rotateVectorY;
      GLUI_Spinner *rotateVectorZ;

      GLUI_Spinner *xTransControl;
      GLUI_Spinner *yTransControl;
      GLUI_Spinner *zTransControl;

      GLUI_Spinner *xScaleControl;
      GLUI_Spinner *yScaleControl;
      GLUI_Spinner *zScaleControl;

      GLUI_Listbox *selectionControl;
      
      GLUI_Spinner *redControl;
      GLUI_Spinner *greenControl;
      GLUI_Spinner *blueControl;
      
      GLUI_EditText *saveFileControl;
      GLUI_Button   *saveButton;
      GLUI_StaticText *saveStatus;


};

#endif // CONTROL_H_
