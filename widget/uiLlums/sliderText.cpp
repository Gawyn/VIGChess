#include "sliderText.h"

#include <QVariant>
#include <QSlider>
#include <QLineEdit>
#include <QLayout>
//#include <QTooltip>
//#include <QWhatsthis>
#include <QImage>
#include <QPixmap>

/*
 *  Constructs a sliderText as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */

sliderText::sliderText(QWidget* parent, Qt::WindowFlags fl )
    : QWidget( parent, fl)
{
    sliderTextLayout = new QHBoxLayout( this);
 
    setMaximumSize( QSize( 300, 41 ) );
    setBaseSize( QSize( 300, 40 ) );

    slider2 = new QSlider( this);
    slider2->setOrientation( Qt::Horizontal );
    sliderTextLayout->addWidget( slider2 );

    lineEdit1 = new QLineEdit( this);
    lineEdit1->setMinimumSize( QSize( 40, 0 ) );
    lineEdit1->setMaximumSize( QSize( 30, 25 ) );
    sliderTextLayout->addWidget( lineEdit1 );
    resize( QSize(247, 115).expandedTo(minimumSizeHint()) );
    //clearWState( WState_Polished );

    // signals and slots connections
    connect( slider2, SIGNAL( valueChanged(int) ), this, SLOT( sliderChange(int) ) );
    connect( lineEdit1, SIGNAL( textChanged(const QString&) ), this, SLOT( textChanged(const QString&) ) );
    slider2->setValue(1);
    slider2->setValue(0);
}

/*
 *  Destroys the object and frees any allocated resources
 */
sliderText::~sliderText()
{
    // no need to delete child widgets, Qt does it all for us
}

void sliderText::sliderChange( int val)
{
   if(modif == true) modif=false;
   else{
       modif = true;
       QString s;
       s.sprintf("%d",val);
       lineEdit1->setText(s);
       emit valueChanged(val);
    }
}

void sliderText::textChanged( const QString & s)
{
   if(modif == true) modif=false;
   else{
       modif = true;
       slider2->setValue(s.toInt());
       emit valueChanged(s.toInt());
    }
}

int sliderText::getValue()
{
    return slider2->value();
}

void sliderText::setValue( int val)
{
    modif = true;
    slider2->setValue(val);

    modif=true;
    QString s;
    s.sprintf("%d",val);
    lineEdit1->setText(s);
    
    emit valueChanged(val);
}

void sliderText::setSize(int s){
    
    slider2->setMaximum(s);
}

int sliderText::size() const{
    return slider2->maximum();
}


