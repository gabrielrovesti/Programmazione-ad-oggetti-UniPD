#ifndef BARCHART_H
#define BARCHART_H

#include <QPainter>
#include "Dati.cpp"
#include "Valori.cpp"
#include "Chart.cpp"

class BarChart: public Chart { // diagramma a barre
private:
  int minHeight;
  int width;
  int textGap;
public:
  BarChart(QPainter& p, const Valori& val, const Dati& dati, int mh=10, int w=20, int tg=20): 
    Chart(val), minHeight(mh), width(w), textGap(tg) {
    for(int i=0;i<val.size();i++) {
      QRect r(points[i],QSize(width,minHeight+val[i]));
      p.setPen(QColor(Qt::red)); p.drawRect(r);
      QRect r2(points[i]+QPoint(1,1),QSize(width-1,minHeight+val[i]-1));
      p.fillRect(r2, QBrush(QColor(Qt::blue),Qt::SolidPattern));
      p.setPen(QColor(Qt::red));
      p.drawText(points[i]+QPoint(0,minHeight+val[i]+textGap),QString(QString::number(dati[i])));
    }
  }
};
#endif
