#include "finestraLlums.h"

finestraLlums::finestraLlums(QDialog *parent):QDialog(parent)
{
	ui.setupUi(this);

}

void finestraLlums::iniciar(llum **focus, int size)
{
    L = focus[0];
    llums = focus;
    
    for(int i=0;i<size;i++){
	 ui.idLlum->insertItem(i,focus[i]->nom);
    }
    
    carregarLlum();
}

void finestraLlums::carregarLlum()
{
    activarLlum(L->activada );
    ui.activa->setChecked(L->activada);
    ui.toolBox1->setEnabled(L->activada);
    
    ui.coorX->setFloat(L->posicio[0]);
    ui.coorY->setFloat(L->posicio[1]);    
    ui.coorZ->setFloat(L->posicio[2]);
    
    ui.botoA->setR((int)(L->ambient[0]*255));
    ui.botoA->setG((int)(L->ambient[1]*255));
    ui.botoA->setB((int)(L->ambient[2]*255));
    
    ui.botoD->setR((int)(L->difos[0]*255));
    ui.botoD->setG((int)(L->difos[1]*255));
    ui.botoD->setB((int)(L->difos[2]*255));
    
    ui.botoE->setR((int)(L->especular[0]*255));
    ui.botoE->setG((int)(L->especular[1]*255));
    ui.botoE->setB((int)(L->especular[2]*255));
    
    if(L->referencia == OBSERVADOR) ui.referencia->setCurrentIndex(0);
    else  if (L->referencia == ESCENA) ui.referencia->setCurrentIndex(1);
            else ui.referencia->setCurrentIndex(2);
    
    //Parametres Spot
    activarSpot(L->spotCutoff != 180 );
    ui.spot->setChecked(L->spotCutoff != 180);
    
    ui.direccioX->setFloat(L->spotDireccio[0]);
    ui.direccioY->setFloat(L->spotDireccio[1]);
    ui.direccioZ->setFloat(L->spotDireccio[2]);
     
    ui.spotExp -> setValue((int)(L->spotExponent));
    
    ui.spotAngle->setValue((int)(L->spotCutoff));
    
    ui.spotAtenuacio->setCurrentIndex(0);

    ui.grau->setFloat(L->grau[0]);
}

void finestraLlums::ambientPressed()
{
    QColor color = QColorDialog::getColor(QColor( ui.botoA->getR(),ui.botoA->getG(),ui.botoA->getB() ), this);
    ui.botoA->setR(color.red());
    ui.botoA->setG(color.green());
    ui.botoA->setB(color.blue());
    
    L->ambient[0] = color.red()/255.;
    L->ambient[1] = color.green()/255.;
    L->ambient[2] = color.blue()/255.;       
    emit llumModificada(L);
}

void finestraLlums::difusePressed()
{
    QColor color = QColorDialog::getColor(
     QColor( ui.botoD->getR(),ui.botoD->getG(),ui.botoD->getB() ),
     this);
    ui.botoD->setR(color.red());
    ui.botoD->setG(color.green());
    ui.botoD->setB(color.blue());
    
    L->difos[0] = color.red()/255.;
    L->difos[1] = color.green()/255.;
    L->difos[2] = color.blue()/255.;   
    emit llumModificada(L);
}

void finestraLlums::specularPressed()
{
    QColor color = QColorDialog::getColor(
     QColor( ui.botoE->getR(),ui.botoE->getG(),ui.botoE->getB() ),
     this);
    ui.botoE->setR(color.red());
    ui.botoE->setG(color.green());
    ui.botoE->setB(color.blue());    
    
    L->especular[0] = color.red()/255.;
    L->especular[1] = color.green()/255.;
    L->especular[2] = color.blue()/255.;
    emit llumModificada(L);
}

void finestraLlums::activarSpot( bool b)
{
    ui.groupBoxSpot->setEnabled(b);
    if(!b){
 L->spotCutoff =180;
 ui.spotAngle->setValue(180);
    }
    else {
 ui.spotAngle->setValue((int)(L->spotCutoff)); 
    }
    emit llumModificada(L);
}

void finestraLlums::activarLlum( bool b )
{
    ui.toolBox1->setEnabled(b);
    L->activada=b;
    emit llumModificada(L);
}

void finestraLlums::coorXChanged( float x)
{
    L->posicio[0] = x;
    emit llumModificada(L);
}

void finestraLlums::coorYChanged( float y)
{
    L->posicio[1] = y;
    emit llumModificada(L);
}

void finestraLlums::coorZChanged( float z)
{
    L->posicio[2] = z;
    emit llumModificada(L);
}

void finestraLlums::puntVista( int i)
{
    L->referencia = i;
    emit llumModificada(L);
}
void finestraLlums::direccioXSpot( float x)
{
    L->spotDireccio[0]=x;
    emit llumModificada(L);
}

void finestraLlums::direccioYSpot( float y)
{
    L->spotDireccio[1]=y;
    emit llumModificada(L);
}

void finestraLlums::direccioZSpot( float z)
{
    L->spotDireccio[2]=z;
    emit llumModificada(L);
}

void finestraLlums::angleSpot( int a )
{
    L->spotCutoff = a;
    emit llumModificada(L);
}

void finestraLlums::exponentSpot( int exp )
{
    L->spotExponent = exp;
    emit llumModificada(L);
}

void finestraLlums::canviarAtenuacio( int i )
{
   ui.grau->setFloat(L->grau[i]);
    emit llumModificada(L);
}

void finestraLlums::modificarAtenuacio( float a )
{
    L->grau[ui.spotAtenuacio->currentIndex()] = a;
    emit llumModificada(L);
}


void finestraLlums::canviarLlum( int i )
{
    L = llums[i];
    carregarLlum();    
}
