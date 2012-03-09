#include "ui_EditorLlums.h"
#include <QColorDialog>

class finestraLlums: public QDialog
{
	Q_OBJECT
public:
	finestraLlums(QDialog *parent=0);

public slots:
	void iniciar(llum **focus, int size);
	void carregarLlum();
	void ambientPressed();
	void difusePressed();
	void specularPressed();
	void activarSpot( bool b);
	void activarLlum( bool b );
	void coorXChanged( float x);
	void coorYChanged( float y);
	void coorZChanged( float z);
	void puntVista( int i);
	void direccioXSpot( float x);
	void direccioYSpot( float y);
	void direccioZSpot( float z);
	void angleSpot( int a );
	void exponentSpot( int exp );
	void canviarAtenuacio( int i );
	void modificarAtenuacio( float a );
	void canviarLlum( int i );

private:
	Ui::finestraLlums ui;
	
	llum** llums;
	llum* L; //llum actual

signals:
        void llumModificada(llum *);
};
