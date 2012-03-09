#ifndef _GLWIDGET_H_
#define _GLWIDGET_H_

#include <QColor>
#include <QColorDialog>
#include <qtimer.h>
#include <QtOpenGL/qgl.h>
#include <QKeyEvent>
#include <iostream>
#include <qstring.h>
#include <qfiledialog.h>
#include <qtimer.h>
#include <QtDesigner/QDesignerExportWidget>
#include "uiLlums/llum.h"
#include "uiLlums/finestraLlums.h"

#include "Point.h"
#include "Scene.h"

class QDESIGNER_WIDGET_EXPORT  GLWidget : public QGLWidget
{
  Q_OBJECT

 public:
  GLWidget(QWidget * parent);

 public slots:

  // help - Ajuda per la terminal des de la que hem  engegat el programa.
  	void help(void);
  	void OpenFile();
  	void OpenPiece(int piece);
  	void Reset(); 
  	void PermetDisplay();
  	void ActivaSeleccio();
	void setZBuffer();
  	void setCulling();
	void setsh(int x);
	void resetPiece();
	void setAmbient();
	void setDifos();
	void setEspecular();
	void llum0onoff();
	void llum1onoff();
	void setAmbientlight0();
	void setDifoslight0();
	void setEspecularlight0();
	void setAmbientlight1();
	void setDifoslight1();
	void setEspecularlight1();
	void NormalVertex();




  // Afegiu aqu� la declaraci� dels slots que necessiteu

 protected:
  // initializeGL() - Aqui incluim les inicialitzacions del contexte grafic.
  virtual void initializeGL();

  // paintGL - M�tode cridat cada cop que cal refrescar la finestra.
  // Tot el que es dibuixa es dibuixa aqui.
  virtual void paintGL( void );
 
  // resizeGL() - Es cridat quan canvi la mida del widget
  virtual void resizeGL (int width, int height);

  // keyPressEvent() - Cridat quan es prem una tecla
  virtual void keyPressEvent(QKeyEvent *e);

  // mousePressEvent() i mouseReleaseEvent()
  virtual void mousePressEvent( QMouseEvent *e);
  virtual void mouseReleaseEvent( QMouseEvent *);
 
  // mouseMoveEvent() - Cridat quan s'arrosega el ratoli amb algun bot� premut.
  virtual void mouseMoveEvent(QMouseEvent *e);
 
  void computeCameraInicial(); 
 
 private:

  // par�metres de la camera perspectiva
  	float anglecam;
  	float ra;
  	double anterior, posterior; 
  	Point VRP;
  	float dist;
  	float angleX, angleY, angleZ;
  	int seleccio;
  	bool clickedpiece;
  	int display;
  	int auxpiece;
  	int digueslloc(int num, int mode);
  	float auxcolor;
  	int copiatrobat;
	llum* L[2];
	finestraLlums finestra;
	bool zBuffer;
	bool culling;
	int funcaux();


  // par�metres de la c�mera ortogonal
  Point VRPortho, OBSortho;
  Vector vUPortho;
  float leftortho, rightortho, bottomortho, toportho, nearortho, farortho;
  
  Scene escena;  // Escena a representar en el widget

  // interaccio
  typedef  enum {NONE, ROTATE, ZOOM, PAN, PECES} InteractiveAction;
  InteractiveAction DoingInteractive;
 
  int   xClick, yClick;
void setModelview();
void setProjection();


};

#endif
