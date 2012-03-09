#include "textField.h"

textField::textField( QWidget * parent)
 : QLineEdit( parent)
{
   QString s;
   s.sprintf("0");
   setText(s);
   connect( this, SIGNAL( textChanged(const QString&) ), this, SLOT( text(const QString &) ) ); 
}

void textField::setFloat(float val)
{
 QString s;
 s.sprintf("%f",val);
 s.truncate(6);
 setText(s);
}

void textField::text(const QString& s){
    emit valueChanged(s.toFloat());    
}
