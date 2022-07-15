#include "figurepolygon.h"

FigurePolygon::FigurePolygon(Shape* s,QGraphicsItem* p):Figure(s),QGraphicsPolygonItem(p){
  QPolygonF shape;
  if( dynamic_cast<PoligonoConvesso*>(s)){
      const QVector<Vertice>& V=  static_cast<PoligonoConvesso*>(s)->getPunt_vertici();
      for(auto it = V.begin(); it!= V.end();it++){

          shape << QPointF(it->get_X(),it->get_Y());
      }
      setPolygon(shape);
  }
}

void FigurePolygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
  QGraphicsPolygonItem::paint(painter,option,widget);
}
QRectF FigurePolygon::boundingRect() const{
  return QGraphicsPolygonItem::boundingRect();
}
