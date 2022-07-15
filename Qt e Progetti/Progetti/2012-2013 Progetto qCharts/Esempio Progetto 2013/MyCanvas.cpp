#include <QWidget>

#include "MyCanvas.h"
#include "Dati.cpp"
#include "Valori.cpp"
#include "BarChart.cpp"
#include "LineChart.cpp"

MyCanvas::MyCanvas (QWidget* parent) : QWidget(parent) {}

void MyCanvas::draw() {
  update(); 
}

void MyCanvas::paintEvent(QPaintEvent*) {
  QPainter p(this); // low-level painting object p
  Dati dati(10); // 10 dati random
  int max=100; // massimo dato normalizzata
  Valori val(dati,max); // dati normalizzati
  if(dati[0]%2 == 0) BarChart(p,val,dati);
  else LineChart(p,val,dati); 
}

