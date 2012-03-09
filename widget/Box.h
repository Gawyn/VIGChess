#ifndef _BOX_H_
#define _BOX_H_

#include "Point.h"

#ifdef min 
#undef min
#endif

#ifdef max 
#undef max
#endif

// Box - permet representar una capsa aliniada amb els eixos
// (ex. capsa englobant)
class Box
{
 private:


 public:


  Box(const Point& minimum=Point(), const Point& maximum=Point());

  // update - expandeix la capsa per que inclogui el punt donat
  void update(const Point& p);
  // init - inicialitza la capsa amb el punt donat
  void init(const Point& p);

  void Render(double r, double g, double b);
	
  // atributs
  Point minb, maxb;	// extrems m�nim i m�xim de la capsa

  void Render();
  Point Center();
};



#endif
