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
   cam_elevation->set_float_limits( -90, 90 );
   cam_elevation->set_speed( .2 );

   panel = glui->add_panel( "Directional Light" );

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
   Light *d;
      
      // used to convert the 3 spinners into
      // one struct for passing to the cam
   GLPoint p; GLVector v;

   Shape* selected = Scene::Instance()->GetSelected();
   switch( control )
   {
      case Modified_Camera:
         cerr << "Modified_Camera\n";
         cam.SetEyeSpherical(
            cam_elevation->get_float_val(),
            cam_heading->get_float_val(),
            cam_radius->get_float_val() );
         break;
            
      case Modified_Directional:
         d = Scene::Instance()->GetDirectionalLight();
         d->SetLocationSpherical(
            dir_elevation->get_float_val(),
            dir_heading->get_float_val() );
         
         if( dir_enable->get_int_val() )
            d->Enable();
         else
            d->Disable();

         break;

      case Modified_Eye:
         p.x = eyeX->get_float_val();
         p.y = eyeY->get_float_val();
         p.z = eyeZ->get_float_val();
         cam.SetEye( p );
         break;
      
      case Modified_Center:
         p.x = centerX->get_float_val();
         p.y = centerY->get_float_val();
         p.z = centerZ->get_float_val();
         cam.SetCenter( p );
         break;

      case Modified_Up:
         v.x = upX->get_float_val();
         v.y = upY->get_float_val();
         v.z = upZ->get_float_val();
         cam.SetUp( v );
         break; 

      case Modified_OrthoFrustum:
         cam.SetRight( right->get_float_val() );
         cam.SetLeft( left->get_float_val() );
         cam.SetTop( top->get_float_val() );
         cam.SetBottom( bottom->get_float_val() );
         cam.SetNear( ofNear->get_float_val() );
         cam.SetFar( ofFar->get_float_val() );
         break;

      case Modified_Perspective:
         cam.SetNear( pNear->get_float_val() );
         cam.SetFar( pFar->get_float_val() );
         cam.SetFOV( fov->get_float_val() );
         cam.SetAspectRatio( aspect->get_float_val() );
         break;

      case Modified_Selection:
         Scene::Instance()->SetSelected(
            (uint) selectionControl->get_int_val() );
         break;

      case Modified_Translation:
         selected->SetTranslation(
            xTransControl->get_float_val(),
            yTransControl->get_float_val(),
            zTransControl->get_float_val() );
         break;

      case Modified_Scale:
         selected->SetScale(
            xScaleControl->get_float_val(),
            yScaleControl->get_float_val(),
            zScaleControl->get_float_val() );
         break;

      case Modified_Rotation:
         GLVector rv;
         rv.x = rotateVectorX->get_float_val();
         rv.y = rotateVectorY->get_float_val();
         rv.z = rotateVectorZ->get_float_val();

         selected->SetRotation( 
            angleControl->get_float_val(), rv );
         break;

      case Modified_Color:
         selected->SetColor(
            redControl->get_float_val(),
            greenControl->get_float_val(),
            blueControl->get_float_val() );           
         break;

      case Modified_Mode:
         cam.SetMode( 
            (Camera::Mode) mode->get_int_val() );
         
         LoadValues( Scene::Instance()->GetCamera() );
         break;


      case Modified_Quit:
         exit(0);
   }

      //
      // refresh please
   glutPostRedisplay();
}

   // -----------------------------------------------------
   // LoadValues
   //    loads the camera values into the gui
void Control::LoadValues( const Camera& c )
{
   GLPoint eye = c.GetEye();
   eyeX->set_float_val( eye.x );
   eyeY->set_float_val( eye.y );
   eyeZ->set_float_val( eye.z );

   GLPoint center = c.GetCenter();
   centerX->set_float_val( center.x );
   centerY->set_float_val( center.y );
   centerZ->set_float_val( center.z );

   GLVector up = c.GetUp();
   upX->set_float_val( up.x );
   upY->set_float_val( up.y );
   upZ->set_float_val( up.z );


   switch( c.GetMode() )
   {
      case Camera::Mode_Ortho:
      case Camera::Mode_Frustum:
         right->set_float_val( c.GetRight() );
         left->set_float_val( c.GetLeft() );
         bottom->set_float_val( c.GetBottom() );
         top->set_float_val( c.GetTop() );
         ofNear->set_float_val( c.GetNear() );
         ofFar->set_float_val( c.GetFar() );

         perspectivePanel->disable();
         orthoFrustumPanel->enable();
         break;
      case Camera::Mode_Perspective:
         fov->set_float_val( c.GetFOV() );
         aspect->set_float_val( c.GetAspectRatio() );
         pNear->set_float_val( c.GetNear() );
         pFar->set_float_val( c.GetFar() );
         
         orthoFrustumPanel->disable();
         perspectivePanel->enable();
         break;
   }

   mode->set_int_val( c.GetMode() );

}

   // -----------------------------------------------------
   // void SelectionChanged( int )
   //    updates the information for a newly selected
   //    shape
   //
   // newSel: the index of the new shape
void Control::SelectionChanged( const uint& newSel )
{
   Shape* selected = Scene::Instance()->GetSelected();

   if( glui && selected )
   {
      selectionControl->set_int_val( newSel );
      
      GLPoint trans = selected->GetTranslation();

      xTransControl->set_float_val( trans.x );
      yTransControl->set_float_val( trans.y );
      zTransControl->set_float_val( trans.z );

      GLScale scale = selected->GetScale();

      xScaleControl->set_float_val( scale.x );
      yScaleControl->set_float_val( scale.y );
      zScaleControl->set_float_val( scale.z );

      angleControl->set_float_val(
            selected->GetRotationAngle() );

      GLVector rv = selected->GetRotationVector();
      rotateVectorX->set_float_val( rv.x );
      rotateVectorY->set_float_val( rv.y );
      rotateVectorZ->set_float_val( rv.z );

      redControl->set_float_val(
            selected->GetColor().red );
      greenControl->set_float_val(
            selected->GetColor().green );
      blueControl->set_float_val(
            selected->GetColor().blue );
   }
      
}

   // createTransforations
   //    creates the transformations part of the gui
void Control::createTransformations()
{
   GLUI_Panel* panel;

   panel = glui->add_panel( "Transformations" );
   xTransControl = new GLUI_Spinner(
      panel, "Translation X",
      GLUI_SPINNER_FLOAT, NULL, Modified_Translation,
      modified_cb );

   yTransControl = new GLUI_Spinner(
      panel, "Translation Y",
      GLUI_SPINNER_FLOAT, NULL, Modified_Translation,
      modified_cb );

   zTransControl = new GLUI_Spinner(
      panel, "Translation Z",
      GLUI_SPINNER_FLOAT, NULL, Modified_Translation,
      modified_cb );

   glui->add_separator_to_panel( panel );

   xScaleControl = new GLUI_Spinner(
      panel, "Scale X",
      GLUI_SPINNER_FLOAT, NULL, Modified_Scale,
      modified_cb );

   yScaleControl = new GLUI_Spinner(
      panel, "Scale Y",
      GLUI_SPINNER_FLOAT, NULL, Modified_Scale,
      modified_cb );

   zScaleControl = new GLUI_Spinner(
      panel, "Scale Z",
      GLUI_SPINNER_FLOAT, NULL, Modified_Scale,
      modified_cb );

   glui->add_separator_to_panel( panel );

   angleControl = new GLUI_Spinner(
      panel, "Angle",
      GLUI_SPINNER_FLOAT, NULL, Modified_Rotation,
      modified_cb );
   angleControl->set_float_limits( -360, 360 );

   rotateVectorX = new GLUI_Spinner(
      panel, "Rotate i", GLUI_SPINNER_FLOAT,
      NULL, Modified_Rotation, modified_cb );
   rotateVectorY = new GLUI_Spinner(
      panel, "Rotate j", GLUI_SPINNER_FLOAT,
      NULL, Modified_Rotation, modified_cb );
   rotateVectorZ = new GLUI_Spinner(
      panel, "Rotate k", GLUI_SPINNER_FLOAT,
      NULL, Modified_Rotation, modified_cb );
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
