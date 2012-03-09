#include "ObjectRef.h"
#include "Box.h"
#include <QtOpenGL/qgl.h>
#include <vector>

using namespace std;

ObjectRef::ObjectRef(int idp, int ob, Point p, double ori, Vector s, Material m, int dis, int col, int fil, int sel):
  idpeca(idp), object(ob), pos(p), orientation(ori), scale(s), mat(m), display(dis), columna(col), fila(fil), matOrig(m), idselect(sel)
{
  es_viva = true;
}

ObjectRef::~ObjectRef(void)
{}

void ObjectRef::Render(vector<Object> &models)
{

	Object o = models[object];
	o.display=display;
	Point centrat=o.boundingBox().Center();
	glMatrixMode(GL_MODELVIEW);
	GLfloat aux[4];
	glPushMatrix();
	aux[0]=mat.ka.r;
	aux[1]=mat.ka.g;
	aux[2]=mat.ka.b;
	aux[3]=mat.ka.a;
	glMaterialfv(GL_FRONT,GL_AMBIENT,aux);
	aux[0]=mat.kd.r;
	aux[1]=mat.kd.g;
	aux[2]=mat.kd.b;
	aux[3]=mat.kd.a;
	glMaterialfv(GL_FRONT,GL_DIFFUSE,aux);
	aux[0]=mat.ks.r;
	aux[1]=mat.ks.g;
	aux[2]=mat.ks.b;
	aux[3]=mat.ks.a;
	glMaterialfv(GL_FRONT,GL_SPECULAR,aux);
	glMaterialf(GL_FRONT,GL_SHININESS,mat.shininess);
	pos.x=(-0.225/2)+0.225*((columna-1)-3);
	pos.z=0.225*3+(0.225/2)-((fila-1))*0.225;
	glTranslatef(pos.x,pos.y,pos.z);
	glScalef(scale.x,scale.y,scale.z);
	glTranslatef(-centrat.x,-centrat.y,-centrat.z);
	if (fila<9 && fila>0 && columna<9 && columna>0){
		glLoadName(idselect);
		o.Render();
	}
	Object p = models[object];
	glPopMatrix();
  // Cal aplicar les transformacions de model necess�ries i
  // pintar l'objecte del color que toca
}

int ObjectRef::getObjectId()
{
  return object;
}
