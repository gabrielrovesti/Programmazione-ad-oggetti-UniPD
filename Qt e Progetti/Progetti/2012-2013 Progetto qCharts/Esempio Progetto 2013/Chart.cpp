#ifndef CHART_H
#define CHART_H

#include <QPoint>
#include "Valori.cpp"

class Chart { // punti in coordinate Qt
protected:
  QPoint* points;
  int xGap;
public:
  Chart(const Valori& val, int xg=40): 
    points(new QPoint[val.size()]), xGap(xg) {
    for(int i=0; i<val.size(); ++i) 
      points[i] = QPoint(i*xGap,val.max()-val[i]);
  }
  virtual ~Chart() {delete[] points;}
};
#endif
