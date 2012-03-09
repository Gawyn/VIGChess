#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include "Vertex.h"
#include "Box.h"
#include "Face.h"
#include "MaterialLib.h"

using namespace std;

// Object - permet representar un objecte 3D
class Object
{
 public:
  Object(std::string);

  // llegeix un model en format OBJ
  void readObj(const char* filename, MaterialLib& matlib);

  // calcula la capsa del model
  void updateBoundingBox();
  // retorna la capsa del model (previament s'ha d'haver calculat)
  Box boundingBox() const;

  void Render();
  void CalculaNormals();
  void CalculaNormalsVert();


 private:
  void make_face ( char **words, int nwords, int material );
  void netejaDades ();


 public:
  vector<Vertex> vertices;  // vector amb els vertexs de l'objecte
  vector<Face> faces;       // vector amb les cares de l'objecte
  int display;
	bool NormVert;


 private: 
  std::string name;
  Box _boundingBox;   // caixa contenidora de l'objecte.
int list;
};


#endif
