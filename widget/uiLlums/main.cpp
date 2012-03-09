#include <qapplication.h>

#include "finestraLlums.h"
#include "llum.h"


int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    llum* L[8];    
    L[0] = new llum(0,"Llum 1");
    L[1] = new llum(1,"Llum 2");
    L[2] = new llum(2,"Llum 3");
    L[3] = new llum(3,"Llum 4");
    L[4] = new llum(4,"Llum 5");
    L[5] = new llum(5,"Llum 6");
    L[6] = new llum(6,"Llum 7");
    L[7] = new llum(7,"Llum 8");
    
    finestraLlums f;
    f.iniciar(L,8);
    //a.setMainWidget(&f);
    
    f.show();

    return a.exec();
}
