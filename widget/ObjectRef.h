#ifndef _ObjectREF_H_
#define _ObjectREF_H_
#include <vector>
#include "Color.h"
#include "Point.h"
#include "Object.h"
#include "Box.h"

using namespace std;

class ObjectRef
{
 private:
  int idpeca;   // identificador de la pe�a del tauler 
                // (pex. id de la torre 1 blanca)
  int object;   // identificador de l'objecte (�ndex al vector de models)
Vector pos;    	// posicio
  double orientation; 	// orientaci�, angle respecte Y
  Vector scale;	   	// factors d'escalat
  bool es_viva;       // indica si la pe�a �s viva

  
 public:
  ObjectRef(int idp, int ob, Point p, double ori, Vector s, Material m, int dis, int col, int fil, int idselect);
  ~ObjectRef(void);
   Material mat;

private:
	int display;

public:
	int columna;
	int fila;
  Material matOrig;
	int idselect;

  void Render(vector<Object> &models);


  int getObjectId();
};

#endif
