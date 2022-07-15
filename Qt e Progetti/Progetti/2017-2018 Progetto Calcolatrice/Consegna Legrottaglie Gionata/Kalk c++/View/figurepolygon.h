#ifndef FIGUREPOLYGON_H
#define FIGUREPOLYGON_H
#include "figure.h"

class FigurePolygon : public Figure , public QGraphicsPolygonItem
{
public:
  FigurePolygon(Shape*,QGraphicsItem* = nullptr);
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
  QRectF boundingRect() const;
};

#endif // FIGUREPOLYGON_H
