// --------------------------------------------------------
// Control.cpp
//    class code for the control window
//
//    allows for the user to select and modify the 
//    graphics that are drawn in the "scene"
// 
// Author: Carick Wienke
// --------------------------------------------------------
//
#include "Control.h"
#include "Scene.h"
#include <iostream>

using namespace std;

Control* Control::instance = NULL;

   // -----------------------------------------------------
   // Control* Instance()
   //    returns the sole instance of the class
Control* Control::Instance()
{
   if( !instance )
      instance = new Control();

   return instance;
}

   // -----------------------------------------------------
   // void Initialize( string, int )
   //    initializes the glui windows, creating all the
   //    controls and the setting their values
void Control::Initialize( string name, int windowID )
{
      // create the main window
   glui = GLUI_Master.create_glui( name.c_str() );

      // link it to the graphics window
   if( windowID >= 0 )
      glui->set_main_gfx_window( windowID );
   
   createCamera();
   createDirectional();
   createPoint();

   Control::LoadValues();

#if 0
   lookAtPanel = glui->add_panel( "glLookAt" );

      eyeX = new GLUI_Spinner(
         lookAtPanel, "eye x",
         GLUI_SPINNER_FLOAT, NULL, Modified_Eye,
         modified_cb );

      eyeY = new GLUI_Spinner(
         lookAtPanel, "eye y",
         GLUI_SPINNER_FLOAT, NULL, Modified_Eye,
         modified_cb );

      eyeZ = new GLUI_Spinner(
         lookAtPanel, "eye z",
         GLUI_SPINNER_FLOAT, NULL, Modified_Eye,
         modified_cb );

   glui->add_separator_to_panel( lookAtPanel );

      centerX = new GLUI_Spinner(
         lookAtPanel, "center x",
         GLUI_SPINNER_FLOAT, NULL, Modified_Center,
         modified_cb );

      centerY = new GLUI_Spinner(
         lookAtPanel, "center y",
         GLUI_SPINNER_FLOAT, NULL, Modified_Center,
         modified_cb );

      centerZ = new GLUI_Spinner(
         lookAtPanel, "center z",
         GLUI_SPINNER_FLOAT, NULL, Modified_Center,
         modified_cb );

   glui->add_separator_to_panel( lookAtPanel );

      upX = new GLUI_Spinner(
         lookAtPanel, "up i",
         GLUI_SPINNER_FLOAT, NULL, Modified_Up,
         modified_cb );

      upY = new GLUI_Spinner(
         lookAtPanel, "up j",
         GLUI_SPINNER_FLOAT, NULL, Modified_Up,
         modified_cb );

      upZ = new GLUI_Spinner(
         lookAtPanel, "up k",
         GLUI_SPINNER_FLOAT, NULL, Modified_Up,
         modified_cb );

   mode = glui->add_radiogroup( NULL, Modified_Mode,
            modified_cb );
      glui->add_radiobutton_to_group(
         mode, "glOrtho" );
      glui->add_radiobutton_to_group(
         mode, "glFrustum" );
      glui->add_radiobutton_to_group(
         mode, "gluPerspective" );

   orthoFrustumPanel = glui->add_panel(
      "Ortho/Frustum Parameters" );
      
      right = glui->add_spinner_to_panel(
         orthoFrustumPanel, "Right",
         GLUI_SPINNER_FLOAT, NULL,
         Modified_OrthoFrustum, modified_cb );

      left = glui->add_spinner_to_panel(
         orthoFrustumPanel, "Left", 
         GLUI_SPINNER_FLOAT, NULL,
         Modified_OrthoFrustum, modified_cb );

      bottom = glui->add_spinner_to_panel(
         orthoFrustumPanel, "Bottom", 
         GLUI_SPINNER_FLOAT, NULL,
         Modified_OrthoFrustum, modified_cb );

      top = glui->add_spinner_to_panel(
         orthoFrustumPanel, "Top", 
         GLUI_SPINNER_FLOAT, NULL,
         Modified_OrthoFrustum, modified_cb );

      ofNear = glui->add_spinner_to_panel(
         orthoFrustumPanel, "Near", 
         GLUI_SPINNER_FLOAT, NULL,
         Modified_OrthoFrustum, modified_cb );

      ofFar = glui->add_spinner_to_panel(
         orthoFrustumPanel, "Far",
         GLUI_SPINNER_FLOAT, NULL,
         Modified_OrthoFrustum, modified_cb );

   perspectivePanel = glui->add_panel(
      "Perspective Parameters" );

      fov = glui->add_spinner_to_panel(
         perspectivePanel, "FOV Y", 
         GLUI_SPINNER_FLOAT, NULL,
         Modified_Perspective, modified_cb );

      aspect = glui->add_spinner_to_panel(
         perspectivePanel, "Aspect Ratio", 
         GLUI_SPINNER_FLOAT, NULL,
         Modified_Perspective, modified_cb );

      pNear = glui->add_spinner_to_panel(
         perspectivePanel, "Near", 
         GLUI_SPINNER_FLOAT, NULL,
         Modified_Perspective, modified_cb );

      pFar = glui->add_spinner_to_panel(
         perspectivePanel, "Far",
         GLUI_SPINNER_FLOAT, NULL,
         Modified_Perspective, modified_cb );

   glui->add_column( 0 );
   glui->add_column( 0 );

   GLUI_Panel *panel;

   panel = glui->add_panel( "Selection" );

   selectionControl = glui->add_listbox_to_panel(
      panel, "Name", NULL, Modified_Selection,
      modified_cb );

   vector<string> names = Scene::Instance()->GetNames();

   for( uint i = 0; i < names.size(); ++i )
      selectionControl->add_item( i, names[i].c_str() );

   createTransformations();
   createColor();

   glui->add_button( 
      "Quit", Modified_Quit, modified_cb );

   LoadValues( Scene::Instance()->GetCamera() );


   Scene::Instance()->SetSelected( 0 );
#endif
}

void Control::LoadValues()
{
   Scene* s = Scene::Instance();

   cam_radius->set_float_val(
      s->GetCamera().GetRadius() ); 
   cam_heading->set_float_val(
      s->GetCamera().GetHeading() ); 
   cam_elevation->set_float_val(
      s->GetCamera().GetElevation() ); 

   dir_enable->set_int_val(
      s->GetDirectionalLight()->IsOn() );
   dir_heading->set_float_val(
      s->GetDirectionalLight()->GetHeading() );
   dir_elevation->set_float_val(
      s->GetDirectionalLight()->GetElevation() );

   GLPoint p = s->GetPointLight()->GetLocation();
   pnt_enable->set_int_val(
      s->GetPointLight()->IsOn() );
   pnt_x->set_float_val( p.x );
   pnt_y->set_float_val( p.y );
   pnt_z->set_float_val( p.z );

   Color c = s->GetPointLight()->GetColor();
   redControl->set_float_val( c.red );
   greenControl->set_float_val( c.green );
   blueControl->set_float_val( c.blue );
}

   // -----------------------------------------------------
   // void modified_cb( int control )
   //    callback for the controls changing
   //
   // control: which control caused it?
void Control::modified_cb( int control )
{
   Instance()->modified( control );
}

   // -----------------------------------------------------
   // void modified( int control )
   //    callback for the controls changing
   //
   // control: which control caused it?
void Control::modified( int control )
{
   Camera &cam = Scene::Instance()->GetCamera();
   Light *l;
      
      // used to convert the 3 spinners into
      // one struct for passing to the cam

//   Shape* selected = Scene::Instance()->GetSelected();
   switch( control )
   {
      case Modified_Camera:
         cam.SetEyeSpherical(
            cam_elevation->get_float_val(),
            cam_heading->get_float_val(),
            cam_radius->get_float_val() );
         break;
            
      case Modified_Directional:
         l = Scene::Instance()->GetDirectionalLight();
         l->SetLocationSpherical(
            dir_elevation->get_float_val(),
            dir_heading->get_float_val() );
         
         if( dir_enable->get_int_val() )
            l->Enable();
         else
            l->Disable();
         break;

      case Modified_Point:
         l = Scene::Instance()->GetPointLight();
         l->SetLocationRectangular(
            pnt_x->get_float_val(),
            pnt_y->get_float_val(),
            pnt_z->get_float_val() );

         l->SetColor(
            redControl->get_float_val(),
            greenControl->get_float_val(),
            blueControl->get_float_val() );
         
         if( pnt_enable->get_int_val() )
            l->Enable();
         else
            l->Disable();
         break;
   }

      //
      // refresh please
   glutPostRedisplay();
}

void Control::createCamera()
{
   GLUI_Panel* panel = glui->add_panel( "Camera Location" );

   cam_radius = glui->add_spinner_to_panel( panel, "Radius",
      GLUI_SPINNER_FLOAT, NULL, 
      Modified_Camera, modified_cb );
   cam_radius->set_float_limits( 10, 200 );
   cam_radius->set_speed( .1 );

   cam_heading = glui->add_spinner_to_panel( panel, "Heading", 
      GLUI_SPINNER_FLOAT, NULL, 
      Modified_Camera, modified_cb );
   cam_heading->set_float_limits( 0, 360 );
   cam_heading->set_speed( .2 );

   cam_elevation = glui->add_spinner_to_panel( panel, "Elevation",
      GLUI_SPINNER_FLOAT, NULL,
      Modified_Camera, modified_cb );
   cam_elevation->set_float_limits( -80, 80 );
   cam_elevation->set_speed( .2 );
}

   // createColor
   //    creates the Color part of the gui
void Control::createColor()
{
   GLUI_Panel *panel;

   panel = glui->add_panel( "Color" );

   redControl = new GLUI_Spinner( 
      panel, "Red", GLUI_SPINNER_FLOAT, NULL, 
      Modified_Color, modified_cb );
   redControl->set_float_limits( 0, 1 );
   redControl->set_speed( 0.02 );

   greenControl = new GLUI_Spinner( 
      panel, "Green", GLUI_SPINNER_FLOAT, NULL, 
      Modified_Color, modified_cb );
   greenControl->set_float_limits( 0, 1 );
   greenControl->set_speed( 0.02 );

   blueControl = new GLUI_Spinner( 
      panel, "Blue", GLUI_SPINNER_FLOAT, NULL, 
      Modified_Color, modified_cb );
   blueControl->set_float_limits( 0, 1 );
   blueControl->set_speed( 0.02 );
}

void Control::createDirectional()
{
   GLUI_Panel* panel = glui->add_panel( "Directional Light" );

   dir_enable = glui->add_checkbox_to_panel(
      panel, "Enable", NULL, Modified_Directional,
      modified_cb );

   dir_heading = glui->add_spinner_to_panel( panel, "Heading", 
      GLUI_SPINNER_FLOAT, NULL, 
      Modified_Directional, modified_cb );
   dir_heading->set_float_limits( 0, 360 );
   dir_heading->set_speed( .2 );

   dir_elevation = glui->add_spinner_to_panel( panel, "Elevation",
      GLUI_SPINNER_FLOAT, NULL,
      Modified_Directional, modified_cb );
   dir_elevation->set_float_limits( -90, 90 );
   dir_elevation->set_speed( .2 );
}

void Control::createPoint()
{
   GLUI_Panel* panel = glui->add_panel( "Point Light" );

   pnt_enable = glui->add_checkbox_to_panel(
      panel, "Enable", NULL, Modified_Point,
      modified_cb );

   pnt_x = glui->add_spinner_to_panel( panel, "x", 
      GLUI_SPINNER_FLOAT, NULL, 
      Modified_Point, modified_cb );
   pnt_x->set_float_limits( -300, 300 );
   pnt_x->set_speed( .2 );

   pnt_y = glui->add_spinner_to_panel( panel, "y",
      GLUI_SPINNER_FLOAT, NULL,
      Modified_Point, modified_cb );
   pnt_y->set_float_limits( -300, 300 );
   pnt_y->set_speed( .2 );

   pnt_z = glui->add_spinner_to_panel( panel, "y",
      GLUI_SPINNER_FLOAT, NULL,
      Modified_Point, modified_cb );
   pnt_z->set_float_limits( -300, 300 );
   pnt_z->set_speed( .2 );

   redControl = new GLUI_Spinner( 
      panel, "Red", GLUI_SPINNER_FLOAT, NULL, 
      Modified_Point, modified_cb );
   redControl->set_float_limits( 0, 1 );
   redControl->set_speed( 1 );

   greenControl = new GLUI_Spinner( 
      panel, "Green", GLUI_SPINNER_FLOAT, NULL, 
      Modified_Point, modified_cb );
   greenControl->set_float_limits( 0, 1 );
   greenControl->set_speed( 1 );

   blueControl = new GLUI_Spinner( 
      panel, "Blue", GLUI_SPINNER_FLOAT, NULL, 
      Modified_Point, modified_cb );
   blueControl->set_float_limits( 0, 1 );
   blueControl->set_speed( 1 );
}
