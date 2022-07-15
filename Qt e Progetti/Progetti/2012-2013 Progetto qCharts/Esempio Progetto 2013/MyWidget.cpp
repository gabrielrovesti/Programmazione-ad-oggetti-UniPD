#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include "MyWidget.h"
#include "MyCanvas.h"

MyWidget::MyWidget(QWidget* parent) : QWidget(parent) {
  setFixedSize(QSize(420, 230));
  button = new QPushButton(tr("Draw"), this);
  button->setFont(QFont("Times", 18, QFont::Bold)); 
  canvas = new MyCanvas(this);
  QGridLayout* grid = new QGridLayout;
  grid->addWidget(button); grid->addWidget(canvas);
  setLayout(grid);
  QObject::connect(button,SIGNAL(clicked()),canvas,SLOT(draw()));
}

  
