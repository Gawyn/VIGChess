#ifndef _Scene_H_
#define _Scene_H_
#include <QtOpenGL/qgl.h>

#include "ObjectRef.h"
#include "Object.h"
#include "Tauler.h"

using namespace std;

class Scene
{
 private:
  Tauler tauler;  // Objecte corresponent al tauler d'escacs

  // Tindrem un vector amb els models geom�trics dels objectes
  // i un altre amb inst�ncies seves (inst�ncies o refer�ncies a 
  // ojectes).
  vector<Object> models;
int display;

 public:

  static MaterialLib matlib;	  // col�lecci� de materials 
	vector<ObjectRef> copies;

  Scene();
  
  void Init();
  void Render();
	void Renderselect();
  void AddObject(Object &);
  void AddObject(ObjectRef &);
	void disp(int num);
	vector<ObjectRef> getcopies();
	void RenderSelectTauler();
	void setVert(bool b);
};

#endif

