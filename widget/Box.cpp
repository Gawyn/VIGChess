#include "Box.h"
#include <QtOpenGL/qgl.h>

Box::Box(const Point& minimum, const Point& maximum)
: minb(minimum), maxb(maximum)
{}


void Box::update(const Point& p)
{
  if (p.x < minb.x) minb.x=p.x;
  if (p.y < minb.y) minb.y=p.y;
  if (p.z < minb.z) minb.z=p.z;
  if (p.x > maxb.x) maxb.x=p.x;
  if (p.y > maxb.y) maxb.y=p.y;
  if (p.z > maxb.z) maxb.z=p.z;
}

void Box::init(const Point& p)
{
  minb = p;
  maxb = p;
}

void Box::Render()
{
  glLineWidth(1.0);
  Render(1.0, 1.0, 1.0);
}

void Box::Render(double r, double g, double b)
{
  glColor3f(r, g, b);
  glBegin(GL_LINES);
  glVertex3f(minb.x, minb.y, minb.z);
  glVertex3f(maxb.x, minb.y, minb.z);
  
  glVertex3f(maxb.x, minb.y, minb.z);
  glVertex3f(maxb.x, maxb.y, minb.z);
  
  glVertex3f(maxb.x, maxb.y, minb.z);
  glVertex3f(minb.x, maxb.y, minb.z);
  
  glVertex3f(minb.x, maxb.y, minb.z);
  glVertex3f(minb.x, minb.y, minb.z);
  
  glVertex3f(minb.x, minb.y, maxb.z);
  glVertex3f(maxb.x, minb.y, maxb.z);
  
  glVertex3f(maxb.x, minb.y, maxb.z);
  glVertex3f(maxb.x, maxb.y, maxb.z);
  
  glVertex3f(maxb.x, maxb.y, maxb.z);
  glVertex3f(minb.x, maxb.y, maxb.z);
  
  glVertex3f(minb.x, maxb.y, maxb.z);
  glVertex3f(minb.x, minb.y, maxb.z);
  
  glVertex3f(minb.x, maxb.y, minb.z);
  glVertex3f(minb.x, maxb.y, maxb.z);
  
  glVertex3f(maxb.x, maxb.y, minb.z);
  glVertex3f(maxb.x, maxb.y, maxb.z);
  
  glVertex3f(minb.x, minb.y, minb.z);
  glVertex3f(minb.x, minb.y, maxb.z);
  
  glVertex3f(maxb.x, minb.y, minb.z);
  glVertex3f(maxb.x, minb.y, maxb.z);
  
  glEnd();
}

Point Box::Center()
{
  return (Point((maxb.x+minb.x)/2.,(maxb.y+minb.y)/2.,(maxb.z+minb.z)/2.));
}

