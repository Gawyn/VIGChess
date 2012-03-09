#include "boto.h"
#include <stdio.h>

boto::boto(QWidget* parent)
     : QPushButton(parent)	
{
    R=0;
    G=0;
    B=0;
    setAutoFillBackground (true);
    setPalette(QColor( R, G, B ) );
}
			       
void boto::setR(int r){
    R=r;
    if(R>255) R=255;
    setPalette( QColor( R, G, B ) );
}

void boto::setG(int g){
    G=g;
    if(G>255) G=255;
    setPalette( QColor( R, G, B ) );
}

void boto::setB(int b){
    B=b;
    if(B>255) B=255;
    setPalette( QColor( R, G, B ) );
}

int boto::getR(){
    return R;
}

int boto::getG(){
    return G;
}

int boto::getB(){
    return B;
}

