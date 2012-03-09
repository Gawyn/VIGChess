#ifndef TEXT_FIELD
#define TEXT_FIELD 1

#include <QLineEdit>

class textField : public QLineEdit{
Q_OBJECT

public:
  textField ( QWidget * parent);

  signals:
      void valueChanged(float);
  
public slots:
   void setFloat(float);
   
private slots:
    void text(const QString &);
 
};

#endif
