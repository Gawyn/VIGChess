#ifndef _Tauler_H_
#define _Tauler_H_
#include <QtOpenGL/qgl.h>
#include "Material.h"
#include "Object.h"

using namespace std;

class Tauler
{
 private:
  // Aqui cal declarar els atributs adients per al tauler
	int display;
	int llista;
	Material Black;
	Material White;
	void paintBlack();
	void paintWhite();

 public:
  	Tauler();
  	void Init();
  	void Render();
	void displ(int num);
};

#endif
