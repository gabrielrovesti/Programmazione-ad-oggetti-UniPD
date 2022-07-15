#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QPushButton>
#include <QWidget>
#include "MyCanvas.h"

// finestra Widget contenitore 
class MyWidget : public QWidget {
 private:
  QPushButton* button;
  MyCanvas* canvas;
 public:
  MyWidget(QWidget* parent=0); 
};
#endif

