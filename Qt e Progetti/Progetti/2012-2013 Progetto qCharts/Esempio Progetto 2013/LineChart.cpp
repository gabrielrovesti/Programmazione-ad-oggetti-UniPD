LINECHART_H
#define LINECHART_H

#include <QPainter>
#include "Dati.cpp"
#include "Valori.cpp"
#include "Chart.cpp"

class LineChart: public Chart { // diagramma a linea
private:
  int textGap;
public:
  LineChart(QPainter& p, const Valori& val, const Dati& dati, int tg=20): 
    Chart(val), textGap(tg) {
    int i = 0;
    for(;i<val.size()-1;i++) {
      p.setPen(QColor(Qt::blue)); 
      p.drawLine(points[i],points[i+1]);
      p.setPen(QColor(Qt::red));
      p.drawText(points[i]+QPoint(0,val[i]+textGap),QString(QString::number(dati[i])));
    }
    p.drawText(points[i]+QPoint(0,val[i]+textGap),QString(QString::number(dati[i])));   
  }
};
#endif
        