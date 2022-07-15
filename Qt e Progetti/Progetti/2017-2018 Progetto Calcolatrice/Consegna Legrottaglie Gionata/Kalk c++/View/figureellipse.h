#ifndef FIGUREELLIPSE_H
#define FIGUREELLIPSE_H
#include "figure.h"
#include <QRectF>

class FigureEllipse: public Figure,  public QGraphicsEllipseItem
{
public:
  FigureEllipse(Shape*,QGraphicsItem* = nullptr);
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
  QRectF boundingRect() const;
};

#endif // FIGUREELLIPSE_H
