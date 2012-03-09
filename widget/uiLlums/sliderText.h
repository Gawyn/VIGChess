#ifndef SLIDERTEXT_H
#define SLIDERTEXT_H

#include <QVariant>
#include <QWidget>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSlider;
class QLineEdit;

class sliderText : public QWidget
{
    Q_OBJECT
    Q_PROPERTY (int tam READ size WRITE setSize)

public:
    sliderText(QWidget* parent,  Qt::WindowFlags fl = 0);
    ~sliderText();
    
    virtual int getValue();
    virtual void setValue( int val );
    
    void setSize(int);
    int size() const;
  
signals:
    void valueChanged(int);

protected:
    QHBoxLayout* sliderTextLayout;

protected slots:
    virtual void sliderChange( int val );
    virtual void textChanged( const QString & s );


private:
    bool modif;
   
    QSlider* slider2;
    QLineEdit* lineEdit1;    
};

#endif
