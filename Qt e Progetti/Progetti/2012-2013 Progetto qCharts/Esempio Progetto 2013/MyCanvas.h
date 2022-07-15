#ifndef MYCANVAS_H
#define MYCANVAS_H

#include <QWidget>

// Widget canvas su cui fare painting
class MyCanvas : public QWidget {
  Q_OBJECT
public:
  MyCanvas (QWidget* parent=0);
public slots:
  void draw(); 
protected: 
  void paintEvent(QPaintEvent*); 
};
#endif
