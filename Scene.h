// --------------------------------------------------------
// Scene.h
//    represents a singleton scene on the screen.
//    allows for selecting object, and their interaction
//    with the control
//
// Carick Wienke
// --------------------------------------------------------
#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <string>

#include "Shape.h"
#include "Camera.h"

using std::vector;
using std::string;

class Scene
{
   public:
      static Scene* Instance();
      void Redraw();
      void AddShape( Shape* newShape );
      void LoadDefault();
      Camera& GetCamera();
      void SetSelected( const uint& );
      Shape* GetSelected();
      vector<string> GetNames();
      Shape* GetShape( string name );
      void ReadFile( string );
      bool Save( string );

   private:
      Scene();

      void processDefine( const vector<string>& );
      void processTranslate( const vector<string>& );
      void processScale( const vector<string>& );
      void processRotate( const vector<string>& );
      void processColor( const vector<string>& );
      void processEye( const vector<string>& );
      void processCenter( const vector<string>& );
      void processUp( const vector<string>& );
      void processOrtho( const vector<string>& );
      void processFrustum( const vector<string>& );
      void processPerspective( const vector<string>& );


         // holds the shapes on the screen
      vector<Shape*> shapes;
      
      Camera camera;
      bool selected;
      uint selectedIndex;

      static Scene* instance;
};

vector<string> tokenize( const string& input,
                         const string& delims );

bool stringToFloat( const string&, float& );

#endif // SCENE_H_
