#ifndef _LLUM
#define _LLUM 1

#include <QtOpenGL/qgl.h>
#include <QString>

#define OBSERVADOR 0
#define ESCENA 1
#define VEHICLE 2

class llum {
 
public:   
    
    llum (GLenum identificador, QString name)
    {
 id=identificador;
 nom = name;
 
 referencia = OBSERVADOR;
 posicio[0] = 0;
 posicio[1] = 0;
 posicio[2] = 0;
 posicio[3] = 1;
 
 ambient[0]= 1;
 ambient[1]= 1;
 ambient[2]= 1;
 ambient[3]= 1;
 
 difos[0] = 1;
 difos[1] = 1;
 difos[2] = 1;
 difos[3] = 1;
 
 especular[0] = 1;
 especular[1] = 1;
 especular[2] = 1;
 especular[3] = 1;
 
 spotDireccio[0] = 0;
 spotDireccio[1] = 0;
 spotDireccio[2] = 0;
 
 spotExponent =0;
 spotCutoff=180;
 
 atenuacio= GL_CONSTANT_ATTENUATION;
 grau[0] = 1;
 grau[1] = 0;
 grau[2] = 0;
 activada = false; 
    }
    
    ~llum(){};
    
    GLint referencia;
    
    GLfloat posicio[4];    
    
    GLfloat ambient[4];
    GLfloat difos[4];
    GLfloat especular[4];

    GLenum id;
    
    QString nom;
    
    //Parametres SPOT
    //Si spotCutoff != 180 es considera que la llum es spot
    
    GLfloat spotDireccio[3];
    GLfloat spotExponent;
    GLfloat spotCutoff;  
    
    GLenum atenuacio;
    GLfloat grau[3];
    
    bool activada;     

};

#endif
