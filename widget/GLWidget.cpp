#include "GLWidget.h"

#include <stdlib.h>
#define _USE_MATH_DEFINES 1
#include <cmath>
#include <string>
#include "Point.h"


int objecte=0;
int idPiece=0;
int indexmat=1;
int idselect=0;
bool llum0=true;
bool llum1=true;
bool filler =false;
bool moviments=false;
bool chmaterial=false;
int piece=-1;
bool NormVert=false;

// Constructora amb format per defecte
GLWidget::GLWidget(QWidget * parent):QGLWidget(parent)
{
  // per rebre events de teclat
  setFocusPolicy(Qt::ClickFocus);
  DoingInteractive = NONE;  
}


// initializeGL() - Aqui incluim les inicialitzacions del contexte grafic.
void GLWidget::initializeGL()
{
  	glClearColor(0.4f, 0.4f, 0.8f, 1.0f);
  	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_FLAT);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
	L[0]= new llum(0,"Llum 1");
	L[1]= new llum(1,"Llum 2");
	finestra.iniciar(L,2); 
	L[0]->activada=true;
	L[1]->activada=true;
	L[0]->posicio[1]=1;
	L[0]->referencia=ESCENA;
	L[1]->referencia=OBSERVADOR;
	zBuffer=true;
	culling=false;
  // dimensions escena i camera inicial
  	escena.Init();
  	computeCameraInicial();
  	display=0;
  	seleccio=0;
	clickedpiece=false;
}

void GLWidget::PermetDisplay(){
	if(display==0){display=1;}
	else{display=0;}
	escena.disp(display);
}
void GLWidget::setZBuffer(){
	if(zBuffer==true){	
		zBuffer=false;
		glDisable(GL_DEPTH_TEST);
	}
	else{	
		zBuffer=true;
		glEnable(GL_DEPTH_TEST);
	}
}
void GLWidget::setCulling(){

	if(culling==true){
		culling=false;
		glDisable(GL_CULL_FACE);
	}
	else{	
		culling=true;
		glEnable(GL_CULL_FACE);
	}
      updateGL();
}

void GLWidget::computeCameraInicial()
{
  // m�tode que inicialitza els par�metres necessaris per a
  // definir la c�mera inicial.
	VRP= Point(0,1,0);
	angleX= 90;
	angleY= 0;
	angleZ= 0;
  	dist= 2;
/*
	rightortho = 2;
	leftortho=-rightortho;
	toportho= 2;
	bottomortho=-toportho;
*/
	anglecam=45;
	ra=1;
	anterior=0.5;
	posterior= 40;
	//gluLookAt(0,0,0,0,0,0,0,0,0);
}

void GLWidget::setModelview()
{
	if(L[0]->activada==true){
		glLightfv(GL_LIGHT0,GL_POSITION,L[0]->posicio);
		glLightfv(GL_LIGHT0,GL_AMBIENT,L[0]->ambient);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,L[0]->difos);
		glLightfv(GL_LIGHT0,GL_SPECULAR,L[0]->especular);
		glEnable(GL_LIGHT0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(L[1]->activada==true){
		L[1]->posicio[0]=0;
		L[1]->posicio[1]=0;
		L[1]->posicio[2]=0;
		glLightfv(GL_LIGHT1,GL_POSITION,L[1]->posicio);
		glLightfv(GL_LIGHT1,GL_AMBIENT,L[1]->ambient);
		glLightfv(GL_LIGHT1,GL_DIFFUSE,L[1]->difos);
		glLightfv(GL_LIGHT1,GL_SPECULAR,L[1]->especular);
		glEnable(GL_LIGHT1);
	}
	glTranslatef(0,0,-dist);
	glTranslatef(-VRP.x,-VRP.z,-VRP.y);
	glRotatef(angleX, 1,0,0); //Gx (θc)
	glRotatef(angleY,0,1,0); //Gy(-Ψc)
	glRotatef(angleZ,0,0,1); //Gz(-ϕc)
}

void GLWidget::setProjection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(anglecam,ra,anterior,posterior);
}


// paintGL() - callback cridat cada cop que cal refrescar la finestra. 
void GLWidget::paintGL( void )
{ 
  // Esborrem els buffers
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  setProjection();
  setModelview();
  // Hem de pintar els objectes de l'escena.
  escena.Render();
}

// resizeGL() - Cridat quan es canvia el tamany del viewport.
void GLWidget::resizeGL (int width, int height)
{
  glViewport (0, 0, width, height);
}

// help() - Surt per la terminal des de la que hem 
// engegat el programa. En la versio amn interficie 
// hauria de crear una nova finestra amb la informacio...
void GLWidget::help( void ){
  cout<<"Tecles definides: \n";
  cout<<"f         Pinta en filferros\n";
  cout<<"s         Pinta amb omplert de pol�gons\n";
  cout<<"h,H,?     Imprimir aquesta ajuda\n";
  // Completar amb altres tecles que definiu...
  //
}

/*--------------------
*
*  teclat()
*
*  callback per quan hom prem una tecla.
*
*/
void GLWidget::keyPressEvent(QKeyEvent *e)
{
  switch( e->key() ) 
  {	    
    case Qt::Key_F: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		filler=false;
      updateGL();
      break;

    case Qt::Key_S: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		filler=true;
      updateGL();
      break;

    case  'h'  : case  'H'  : case  '?'  :  help();
      break;

    default: e->ignore(); // el propaguem cap al pare...
  }
}

/*--------------------
* mousePressEvent()
*/
void GLWidget::mousePressEvent( QMouseEvent *e){
  xClick = e->x();
  yClick = e->y();

if (seleccio==0){
  
  if (e->button()&Qt::LeftButton && 
      ! (e->modifiers()&(Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
  else if (e->button()&Qt::LeftButton &&  e->modifiers() &Qt::ShiftModifier)
  {
    DoingInteractive = ZOOM;
  }
  else if (e->button()&&Qt::RightButton)
  {
    DoingInteractive = PAN;
  }
}
	piece = funcaux();
	if (piece!=-1){
		moviments=true;
		chmaterial=true;
	}
/*
	else if (clickedpiece==true){

 		clickedpiece=false;
		int colpos = digueslloc(xClick,0);
		int filapos = digueslloc(yClick,1);
		vector<ObjectRef> copies = escena.getcopies();
		int N = copies.size();
	
		bool trobat=false;
		bool colors=false;
		copiatrobat=0;
		for(int i=0;i<N && trobat==false;i++){
			if((copies[i].fila==filapos) && (copies[i].columna==colpos)){
				trobat=true;
				copiatrobat=i;
				if(copies[i].mat.ka.r==auxcolor){
					colors=true;
				}
				else{
				}
			}
		}
		if(trobat==false){
			escena.copies[auxpiece].fila=filapos;
 			escena.copies[auxpiece].columna=colpos;
		}
		if (trobat==true && colors==false){
			escena.copies[copiatrobat].fila=0;
			escena.copies[copiatrobat].columna=0;
			escena.copies[auxpiece].fila=filapos;
 			escena.copies[auxpiece].columna=colpos;
		}
		clickedpiece=false;
		*/
  updateGL();
}
/*--------------------
*
* mouseReleaseEvent()
*
* Callback Qt cridat quan es deixa anar el bot� del
* ratol�.
*
*/
void GLWidget::mouseReleaseEvent( QMouseEvent *){
  DoingInteractive = NONE;
	moviments=false;
}

/*--------------------
*
* mouseMoveEvent()
*
* Callback Qt cridat quan s'arrosega el ratoli amb
* algun boto premut.
*
*/
void GLWidget::mouseMoveEvent(QMouseEvent *e)
{

  	float aux;  

	if(DoingInteractive == ROTATE && e->modifiers() &Qt::ShiftModifier){
	DoingInteractive=ZOOM;
	}
	else if (DoingInteractive == ROTATE){
    // Aqui cal el codi que modifica els parametres per a fer la rotacio
	angleX = angleX + (e->y() - yClick);
	//if(angleX > 180) angleX = angleX - 360;
	//else if(angleX < 180) angleX = angleX + 360;
	angleY = angleY + (e->x() - xClick);
	//if(angleY > 180) angleY = angleY - 360;
	//else if(angleY < 180) angleY = angleY + 360;
	yClick = e->y();
	xClick = e->x();
  }

  if(moviments==true && seleccio==1){
	yClick = e->y();
	xClick = e->x();
	int numerito = funcaux();
	int columna=numerito/8;
	columna=8-columna;
	int fila=numerito%8;
	if (fila==0){fila=8;}
	if(fila==8){columna++;}
	if (fila<9 && fila>0 && columna<9 && columna>0){
		vector<ObjectRef> copies2 = escena.getcopies();
		int N = copies2.size();
		bool trobat=false;
		int copiatrobat;
		bool colors=false;
		for(int i=0;i<N && trobat==false;i++){
			if((copies2[i].fila==fila) && (copies2[i].columna==columna)){
				trobat=true;
				copiatrobat=i;
				if(copies2[i].mat.ks.r==copies2[piece].mat.ks.r){
					colors=true;
				}
			}
		}
		if (trobat==false){
			escena.copies[piece].fila=fila;
			escena.copies[piece].columna=columna;
		}
		else{	
			if (colors!=true){
				escena.copies[piece].fila=fila;
				escena.copies[piece].columna=columna;
				escena.copies[copiatrobat].columna=100;
				escena.copies[copiatrobat].fila=100;
			}
		}
	}
	updateGL();
  }

  if(DoingInteractive == ZOOM && e->modifiers() &Qt::ShiftModifier){
    // Aqui cal el codi que modifica els parametres per a fer el zoom
	aux = (e->y() - yClick);
	if((anterior + aux)<(posterior - aux))
	{	
		//gluLookAt(0,aux,0,0,0,0,0,0,0);
		dist=dist+(aux*0.2);
	}
	else{
		dist=dist+(aux*0.2);

	}
	yClick = e->y();
	
  }else if (DoingInteractive == ZOOM){

	DoingInteractive = ROTATE;
  }

  if (DoingInteractive == PAN && e->modifiers() &Qt::ShiftModifier ){
    // Aqui cal el codi que modifica els parametres per a fer el pan
	float Float1 =0.15* (e->x() - xClick);
	float Float2 = 0.15*(e->y() - yClick);
	GLdouble mView[16];
	Point p1,p2;
	
	glGetDoublev(GL_MODELVIEW_MATRIX, mView);
	p1.x=mView[0];
	p1.y=mView[4];
	p1.z=mView[8];
	p2.x=mView[1];
	p2.y=mView[5];
	p2.z=mView[9];
	//p1=(mView[0] , mView[4] , mView[8]);
	//p2=(mView[1] , mView[5] , mView[9]);
	VRP.x=(VRP.x + mView[0]*Float1 +mView[1]*Float2);
	VRP.y=(VRP.y + mView[4]*Float1 + mView[5]*Float2);
	VRP.z=(VRP.z + mView[8]*Float1 + mView[9]*Float2);
	xClick = e->x();
	yClick = e->y();
  }
  updateGL();

}

int GLWidget::digueslloc(int num, int mode){

	int res;
	res=0;
	if (num>=66 && num<118){
		res=1;
	}
	else if (num>=118 && num<171){
		res=2;
	}
	else if (num>=171 && num<224){
		res=3;
	}
	else if (num>=224 && num<277){
		res=4;
	}
	else if (num>=277 && num<330){
		res=5;
	}
	else if (num>=330 && num<383){
		res=6;
	}
	else if (num>=383 && num<436){
		res=7;
	}
	else if (num>=436 && num<489){
		res=8;
	}
	if (mode==1){
		return (9-res);
	}
	else{
		return res;
	}

}



void GLWidget::OpenFile()
{
	//Select file from file dialog
	QString carrega = QFileDialog::getOpenFileName( this, "Carrega de peces",".",QString::null);	
	string aux= carrega.toStdString();
	const char * aux2=aux.c_str();
	/*	
	char* pnt=0;
	pnt=(char *)&aux;
	*/
	//const char *text = (const char *)carrega;
	//cout<<aux;
	

	if (!carrega.isEmpty())
	{
	        // the user selected a valid existing file
		Object o("piece");
		o.readObj(aux2, Scene::matlib);
		MaterialLib ML = Scene::matlib;
		indexmat++;
		const Material usable = ML.material(indexmat);
		escena.AddObject(o);
		o.updateBoundingBox();
		Box b = o.boundingBox();
		Vector v(1,1,1);
 		float f1=abs(b.maxb.x - b.minb.x);
		float f2=abs(b.maxb.y - b.minb.y);
		float f3=abs(b.maxb.z - b.minb.z);
		float eix=1;
		if(f1>=f2 && f1>=f3){
			eix=0.225/f1;
		}
		else if(f2>=f1 && f2>=f3){
			eix=0.225/f2;
		}
		else{
			eix=0.225/f3;
		}
		v.x=eix;
		v.y=eix;
		v.z=eix;

		Point p1;
		p1.x=0;
		p1.y=0;
		p1.z=0;
		Material white=usable;
		white.kd.r=0.6434;
		white.kd.g=0.6434;
		white.kd.b=0.6434;
		white.ks.r=0.5;
		white.ks.g=0.5;
		white.ks.b=0.5;
		white.ka.r=0.5;
		white.ka.g=0.5;
		white.ka.b=0.5;
		Material black=usable;
		black.ka.r=0;
		black.ka.g=0;
		black.ka.b=0;
		black.kd.r=0.1834;
		black.kd.g=0.1834;
		black.kd.b=0.1834;
		black.ks.r=0.25;
		black.ks.g=0.25;
		black.ks.b=0.25;
		if(idPiece==0){
			p1.x=(0.225/2);
			p1.y=0.225/2;
			p1.z=0.225*3+(0.225/2);
			ObjectRef oref(idPiece,objecte,p1,(double)90,v,white,display,5,1,idselect);
			idselect++;
			escena.AddObject(oref);
			p1.z=-(0.225*4)+(0.225/2);
			//p1.z=0.075+(0.225*2);
			ObjectRef oref2(idPiece,objecte,p1,(double)90,v,black,display,5,8,idselect);
			idselect++;
			escena.AddObject(oref2);
		}
		else if (idPiece==1){
			p1.x=(-0.225/2);
			p1.y=0.225/2;
			p1.z=0.225*3+(0.225/2);
			ObjectRef oref(idPiece,objecte,p1,(double)90,v,white,display,4,1,idselect);
			escena.AddObject(oref);
			idselect++;
			p1.z=-(0.225*4)+(0.225/2);
			ObjectRef oref2(idPiece,objecte,p1,(double)90,v,black,display,4,8,idselect);
			idselect++;
			escena.AddObject(oref2);
		}
		else if (idPiece==2){
			p1.x=(-0.225/2)-0.225;
			p1.y=0.225/2;
			p1.z=0.225*3+(0.225/2);
			ObjectRef oref(idPiece,objecte,p1,(double)90,v,white,display,3,1,idselect);
			idselect++;
			escena.AddObject(oref);
			p1.z=-(0.225*4)+(0.225/2);
			ObjectRef oref2(idPiece,objecte,p1,(double)90,v,black,display,3,8,idselect);
			idselect++;
			escena.AddObject(oref2);
			p1.x=(0.225/2)+0.225;
			p1.z=0.225*3+(0.225/2);
			ObjectRef oref3(idPiece,objecte,p1,(double)90,v,white,display,6,1,idselect);
			idselect++;
			escena.AddObject(oref3);
			p1.z=-(0.225*4)+(0.225/2);
			ObjectRef oref4(idPiece,objecte,p1,(double)90,v,black,display,6,8,idselect);
			idselect++;
			escena.AddObject(oref4);
		}
		else if (idPiece==3){
			p1.x=(-0.225/2)-0.225*2;
			p1.y=0.225/2;
			p1.z=0.225*3+(0.225/2);
			ObjectRef oref(idPiece,objecte,p1,(double)90,v,white,display,2,1,idselect);
			idselect++;
			escena.AddObject(oref);
			p1.z=-(0.225*4)+(0.225/2);
			ObjectRef oref2(idPiece,objecte,p1,(double)90,v,black,display,2,8,idselect);
			idselect++;
			escena.AddObject(oref2);
			p1.x=(0.225/2)+0.225*2;
			p1.z=0.225*3+(0.225/2);
			ObjectRef oref3(idPiece,objecte,p1,(double)90,v,white,display,7,1,idselect);
			idselect++;
			escena.AddObject(oref3);
			p1.z=-(0.225*4)+(0.225/2);
			ObjectRef oref4(idPiece,objecte,p1,(double)90,v,black,display,7,8,idselect);
			idselect++;
			escena.AddObject(oref4);
		}
		else if(idPiece==4){
			p1.x=(-0.225/2)-0.225*3;
			p1.y=0.225/2;
			p1.z=0.225*3+(0.225/2);
			ObjectRef oref(idPiece,objecte,p1,(double)90,v,white,display,1,1,idselect);
			idselect++;
			escena.AddObject(oref);
			p1.z=-(0.225*4)+(0.225/2);
			ObjectRef oref2(idPiece,objecte,p1,(double)90,v,black,display,1,8,idselect);
			idselect++;
			escena.AddObject(oref2);
			p1.x=(0.225/2)+0.225*3;
			p1.z=0.225*3+(0.225/2);
			ObjectRef oref3(idPiece,objecte,p1,(double)90,v,white,display,8,1,idselect);
			idselect++;
			escena.AddObject(oref3);
			p1.z=-(0.225*4)+(0.225/2);
			ObjectRef oref4(idPiece,objecte,p1,(double)90,v,black,display,8,8,idselect);
			idselect++;
			escena.AddObject(oref4);
		}
		else if(idPiece==5){
			
			p1.y=0.225/4;
			p1.z=0.225*2+(0.225/2);
			v.x=v.x/2;
			v.y=v.y/2;
			v.z=v.z/2;
			
			for(int i=0;i<8;i++){
				p1.x=(-0.225/2)+0.225*(i-3);
				if(i==0){
					ObjectRef oref(idPiece,objecte,p1,(double)90,v,white,display,1,2,idselect);
					escena.AddObject(oref);
				}
				else if(i==1){
					ObjectRef oref2(idPiece,objecte,p1,(double)90,v,white,display,2,2,idselect);
					escena.AddObject(oref2);
				}
				else if(i==2){
					ObjectRef oref3(idPiece,objecte,p1,(double)90,v,white,display,3,2,idselect);
					escena.AddObject(oref3);
				}
				else if(i==3){
					ObjectRef oref4(idPiece,objecte,p1,(double)90,v,white,display,4,2,idselect);
					escena.AddObject(oref4);
				}
				else if(i==4){
					ObjectRef oref5(idPiece,objecte,p1,(double)90,v,white,display,5,2,idselect);
					escena.AddObject(oref5);
				}
				else if(i==5){
					ObjectRef oref6(idPiece,objecte,p1,(double)90,v,white,display,6,2,idselect);
					escena.AddObject(oref6);
				}
				else if(i==6){
					ObjectRef oref7(idPiece,objecte,p1,(double)90,v,white,display,7,2,idselect);
					escena.AddObject(oref7);
				}
				else if(i==7){
					ObjectRef oref8(idPiece,objecte,p1,(double)90,v,white,display,8,2,idselect);
					escena.AddObject(oref8);
				}
				idselect++;
			}
			p1.z=-(0.225*3)+(0.225/2);
			for(int i=0;i<8;i++){
				p1.x=(-0.225/2)+0.225*(i-3);
				if(i==0){
					ObjectRef oref200(idPiece,objecte,p1,(double)90,v,black,display,1,7,idselect);
					escena.AddObject(oref200);
				}
				else if(i==1){
					ObjectRef oref9(idPiece,objecte,p1,(double)90,v,black,display,2,7,idselect);
					escena.AddObject(oref9);
				}
				else if(i==2){
					ObjectRef oref10(idPiece,objecte,p1,(double)90,v,black,display,3,7,idselect);
					escena.AddObject(oref10);
				}
				else if(i==3){
					ObjectRef oref11(idPiece,objecte,p1,(double)90,v,black,display,4,7,idselect);
					escena.AddObject(oref11);
				}
				else if(i==4){
					ObjectRef oref12(idPiece,objecte,p1,(double)90,v,black,display,5,7,idselect);
					escena.AddObject(oref12);
				}
				else if(i==5){
					ObjectRef oref13(idPiece,objecte,p1,(double)90,v,black,display,6,7,idselect);
					escena.AddObject(oref13);
				}
				else if(i==6){
					ObjectRef oref14(idPiece,objecte,p1,(double)90,v,black,display,7,7,idselect);
					escena.AddObject(oref14);

				}
				else if(i==7){
					ObjectRef oref15(idPiece,objecte,p1,(double)90,v,black,display,8,7,idselect);
					escena.AddObject(oref15);
				}
				idselect++;
			}

		}

	objecte++;
	}
	
}

void GLWidget::OpenPiece(int piece){
	idPiece=piece;
}

void GLWidget::Reset(){
	angleX=90;
	angleY= 0;
	angleZ= 0;
	dist= 2;
	VRP.x=0;
	VRP.y=1;
	VRP.z=0;
	anglecam=45;
	ra=1;
	anterior=0.5;
	posterior= 40;
	updateGL();

}

void GLWidget::ActivaSeleccio(){
	if(seleccio==0){seleccio=1;}
	else{seleccio=0;}
}
void GLWidget::setsh(int x){
 	if (chmaterial==true){
		float aux= float(x);
		aux=aux/99;
		escena.copies[piece].mat.shininess=aux;
	}
  updateGL();
}

void GLWidget::resetPiece(){
	if (chmaterial==true){
		escena.copies[piece].mat=escena.copies[auxpiece].matOrig;
	}
  updateGL();
}

void GLWidget::setAmbient(){
	QColor color=QColorDialog::getColor();
	if (chmaterial==true){
		Color aux;
		aux.r=float(color.red());
		aux.g=float(color.green());
		aux.b=float(color.blue());
		aux.r=aux.r/255;
		aux.g=aux.g/255;
		aux.b=aux.b/255;
		escena.copies[piece].mat.ka.r=aux.r;
		escena.copies[piece].mat.ka.g=aux.g;
		escena.copies[piece].mat.ka.b=aux.b;

	}
  updateGL();	
}
void GLWidget::setDifos(){
	QColor color=QColorDialog::getColor();
	if (chmaterial==true){
		Color aux;
		aux.r=float(color.red());
		aux.g=float(color.green());
		aux.b=float(color.blue());
		aux.r=aux.r/255;
		aux.g=aux.g/255;
		aux.b=aux.b/255;
		escena.copies[piece].mat.kd.r=aux.r;
		escena.copies[piece].mat.kd.g=aux.g;
		escena.copies[piece].mat.kd.b=aux.b;
	}
  updateGL();
}
void GLWidget::setEspecular(){
	QColor color=QColorDialog::getColor();
	if (chmaterial==true){
		Color aux;
		aux.r=float(color.red());
		aux.g=float(color.green());
		aux.b=float(color.blue());
		aux.r=aux.r/255;
		aux.g=aux.g/255;
		aux.b=aux.b/255;
		escena.copies[piece].mat.ks.r=aux.r;
		escena.copies[piece].mat.ks.g=aux.g;
		escena.copies[piece].mat.ks.b=aux.b;	
	}
  updateGL();
}
#define BUFFER_TAMANY 32
int GLWidget::funcaux(){
        //Declaración de variables
        GLint picks,viewport[4];
        GLint res=-1;
        GLuint buffSelect[BUFFER_TAMANY];
        glDisable(GL_LIGHTING);
        glSelectBuffer(BUFFER_TAMANY, buffSelect);
        glGetIntegerv(GL_VIEWPORT, viewport);

	//Llamamos a PROJECTION
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glRenderMode(GL_SELECT);
        glLoadIdentity();
        gluPickMatrix(xClick, viewport[3] - yClick, 1, 1, viewport);
        gluPerspective(anglecam,ra,anterior,posterior);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
	glTranslatef(0,0,-dist);
	glTranslatef(-VRP.x,-VRP.z,-VRP.y);
	glRotatef(angleX, 1,0,0); //Gx (θc)
	glRotatef(angleY,0,1,0); //Gy(-Ψc)
	glRotatef(angleZ,0,0,1); //Gz(-ϕc)
        glInitNames();
        glPushName(0);
	if (moviments==false){
        	escena.Renderselect();
	}
	else{
		escena.RenderSelectTauler();
	}
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        picks=glRenderMode(GL_RENDER);
        if(picks>=1){
            res=buffSelect[3];
        }
        glEnable(GL_LIGHTING);
        return res;
}


void GLWidget::llum0onoff(){
	if (L[0]->activada==true){
		L[0]->activada=false;
		glDisable(GL_LIGHT0);
	}
	else{
		L[0]->activada=true;
		glEnable(GL_LIGHT0);
	}
  updateGL();
}
void GLWidget::llum1onoff(){
	if (L[1]->activada==true){
		L[1]->activada=false;
		glDisable(GL_LIGHT1);
	}
	else{
		L[1]->activada=true;
		glEnable(GL_LIGHT1);
	}
  updateGL();
}
void GLWidget::setAmbientlight0(){
	QColor color=QColorDialog::getColor();
		Color aux;
		aux.r=float(color.red());
		aux.g=float(color.green());
		aux.b=float(color.blue());
		aux.r=aux.r/255;
		aux.g=aux.g/255;
		aux.b=aux.b/255;
		L[0]->ambient[0]=aux.r;
		L[0]->ambient[1]=aux.g;
		L[0]->ambient[2]=aux.b;


  updateGL();	
}
void GLWidget::setDifoslight0(){
	QColor color=QColorDialog::getColor();
		Color aux;
		aux.r=float(color.red());
		aux.g=float(color.green());
		aux.b=float(color.blue());
		aux.r=aux.r/255;
		aux.g=aux.g/255;
		aux.b=aux.b/255;
		L[0]->difos[0]=aux.r;
		L[0]->difos[1]=aux.g;
		L[0]->difos[2]=aux.b;
  updateGL();
}
void GLWidget::setEspecularlight0(){
	QColor color=QColorDialog::getColor();
		Color aux;
		aux.r=float(color.red());
		aux.g=float(color.green());
		aux.b=float(color.blue());
		aux.r=aux.r/255;
		aux.g=aux.g/255;
		aux.b=aux.b/255;
		L[0]->especular[0]=aux.r;
		L[0]->especular[1]=aux.g;
		L[0]->especular[2]=aux.b;	
  updateGL();
}
void GLWidget::setAmbientlight1(){
	QColor color=QColorDialog::getColor();
		Color aux;
		aux.r=float(color.red());
		aux.g=float(color.green());
		aux.b=float(color.blue());
		aux.r=aux.r/255;
		aux.g=aux.g/255;
		aux.b=aux.b/255;
		L[1]->ambient[0]=aux.r;
		L[1]->ambient[1]=aux.g;
		L[1]->ambient[2]=aux.b;

  updateGL();	
}
void GLWidget::setDifoslight1(){
	QColor color=QColorDialog::getColor();
		Color aux;
		aux.r=float(color.red());
		aux.g=float(color.green());
		aux.b=float(color.blue());
		aux.r=aux.r/255;
		aux.g=aux.g/255;
		aux.b=aux.b/255;
		L[1]->difos[0]=aux.r;
		L[1]->difos[1]=aux.g;
		L[1]->difos[2]=aux.b;
  updateGL();
}
void GLWidget::setEspecularlight1(){
	QColor color=QColorDialog::getColor();
		Color aux;
		aux.r=float(color.red());
		aux.g=float(color.green());
		aux.b=float(color.blue());
		aux.r=aux.r/255;
		aux.g=aux.g/255;
		aux.b=aux.b/255;
		L[1]->especular[0]=aux.r;
		L[1]->especular[1]=aux.g;
		L[1]->especular[2]=aux.b;	
  updateGL();
}

void GLWidget::NormalVertex(){
	if(NormVert==true){
		NormVert=false;
		escena.setVert(false);
	}
	else{
		NormVert=true;
		escena.setVert(true);
	}
}
