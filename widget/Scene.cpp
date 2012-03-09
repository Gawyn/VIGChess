#include "Scene.h"

MaterialLib Scene::matlib;

Scene::Scene()
{}

void Scene::Init()
{
  tauler.Init();
	display=0;
}

void Scene::setVert(bool b){
  std::vector<Object>::iterator ito;
	for (ito=models.begin(); ito!=models.end(); ito++){
    		(*ito).NormVert=b;
	}

}

// M�tode que pinta l'escena
void Scene::Render()
{
  // Cal pintar tots els objectes de l'escena que es troben al 
  // vector d'inst�ncies i el tauler
	tauler.displ(display);
  tauler.Render();
  std::vector<ObjectRef>::iterator ito;
  for (ito=copies.begin(); ito!=copies.end(); ito++){
    (*ito).Render(this->models);
	}
}

void Scene::Renderselect(){
  // Cal pintar tots els objectes de l'escena que es troben al 
  // vector d'inst�ncies i el tauler
	//tauler.displ(display);
  //tauler.Render();
	tauler.displ(display);
  std::vector<ObjectRef>::iterator ito;
  for (ito=copies.begin(); ito!=copies.end(); ito++){
    (*ito).Render(this->models);
	}
}
void Scene::RenderSelectTauler(){
	tauler.displ(display);
  	tauler.Render();
}

void Scene::AddObject(Object &o)
{
  models.push_back(o);
}

void Scene::AddObject(ObjectRef &oref)
{
  copies.push_back(oref);
}

void Scene::disp(int num){
	display=num;
}

vector<ObjectRef> Scene::getcopies(){
	return copies;
}


