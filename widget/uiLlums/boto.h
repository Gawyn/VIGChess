#ifndef BOTO_H
#define BOTO_H

#include <QPushButton>
#include <QColor>

class boto : public QPushButton
{
    Q_OBJECT
    
public:
    boto(QWidget* parent);
    int getR();
    int getG();
    int getB();
    
public slots:
    void setR(int);
    void setG(int);
    void setB(int);
    
private:
    int R,G,B;
};

#endif
