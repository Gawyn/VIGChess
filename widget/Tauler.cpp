#include "Tauler.h"
#include "Box.h"
#include "Point.h"

Object casella("casella");

Tauler::Tauler()
{}
void Tauler::displ(int num){
	display=num;
}


void Tauler::Init()
{
    // Mètode que inicialitza els atributs del tauler de manera que
    // es pugui fer el render ja des de l'inici.
    //capsa = Object("capsa");
    //capsa patro
   
	White = Material("blanc",Color(0.7,0.7,0.7),Color(0.7,0.7,0.7),Color(0.7,0.7,0.7),13.f);
    	Black = Material("negre",Color(0.1,0.1,0.1),Color(0.1,0.1,0.1),Color(0.1,0.1,0.1),13.f);
   	llista=0;
	display=0;
   
    	casella.vertices.push_back(Vertex(Point(-0.9,0,-0.9)));
    	casella.vertices.push_back(Vertex(Point(-0.9,0,-0.675)));
    	casella.vertices.push_back(Vertex(Point(-0.675,0,-0.675)));
    	casella.vertices.push_back(Vertex(Point(-0.675,0,-0.9)));
	casella.vertices.push_back(Vertex(Point(-0.9,-0.1125,-0.9)));
    	casella.vertices.push_back(Vertex(Point(-0.675,-0.1125,-0.9)));
    	casella.vertices.push_back(Vertex(Point(-0.675,-0.1125,-0.675)));
    	casella.vertices.push_back(Vertex(Point(-0.9,-0.1125,-0.675)));
   
	glNormal3f(0,0,1);
    	casella.faces.push_back(Face(6,7,1,2));
	glNormal3f(0,-1,0);
    	casella.faces.push_back(Face(3,2,1,0));
    	glNormal3f(0,1,0);
    	casella.faces.push_back(Face(7,6,5,4));
    	glNormal3f(1,0,0);
    	casella.faces.push_back(Face(6,2,3,5));
    	glNormal3f(-1,0,0);
    	casella.faces.push_back(Face(1,7,4,0));
    	glNormal3f(0,0,-1);
    	casella.faces.push_back(Face(3,0,4,5));
    	casella.CalculaNormals();
    	llista = glGenLists(1);
    	glNewList(llista, GL_COMPILE );
    	for(int i=0; i<8; i++)
    	{
            	for(int j=0; j<8; j++)
            	{
                int cond = (j+i)&1;
        		if (cond)
        		{
     				paintBlack();
        		} 
			else {
            			paintWhite();
        		} 
                casella.Render();
                glTranslatef(0,0,0.225);
            	}
            glTranslatef(0.225,0,-1.8);
    	}
    glEndList();
}

void Tauler::paintWhite()
{
    float c[4];
    c[0]=White.ka.r; c[1]=White.ka.g; c[2]=White.ka.b; c[3]=White.ka.a;
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, c);
    c[0]=White.kd.r; c[1]=White.kd.g; c[2]=White.kd.b; c[3]=White.kd.a;
    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, c);
    c[0]=White.ks.r; c[1]=White.ks.g; c[2]=White.ks.b; c[3]=White.ks.a;
    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, c);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, White.shininess);
}

void Tauler::paintBlack()
{
    float c[4];
    c[0]=Black.ka.r; c[1]=Black.ka.g; c[2]=Black.ka.b; c[3]=Black.ka.a;
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, c);
    c[0]=Black.kd.r; c[1]=Black.kd.g; c[2]=Black.kd.b; c[3]=Black.kd.a;
    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, c);
    c[0]=Black.ks.r; c[1]=Black.ks.g; c[2]=Black.ks.b; c[3]=Black.ks.a;
    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, c);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, Black.shininess);
}


void Tauler::Render()
{
  int n;
  // Mètode que envia a pintar el tauler
    glPushMatrix();
    if (display)
    {
        glCallList(llista);
    } else {
        for(int i=0,n=64; i<8; i++)
        {
            for(int j=0; j<8; j++,n--)
            {
                int cond = (j+i)&1;//color
                if (cond)
                {
                    paintBlack();
                } else {
                    paintWhite();
                }
		glLoadName(n);
                casella.Render();
                glTranslatef(0,0,0.225);
            }
            glTranslatef(0.225,0,-1.8);
        }
    }
    glPopMatrix();
}
