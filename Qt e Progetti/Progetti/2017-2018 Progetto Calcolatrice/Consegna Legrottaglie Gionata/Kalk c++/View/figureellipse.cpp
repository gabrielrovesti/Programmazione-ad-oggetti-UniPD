#include "figureellipse.h"

FigureEllipse::FigureEllipse(Shape* s,QGraphicsItem* p):Figure(s),QGraphicsEllipseItem(p){
  Cerchio *C =  dynamic_cast<Cerchio*>(s);
  if(C){
    QRectF e(C->get_origine().get_X() - C->get_raggio(),C->get_origine().get_Y() - C->get_raggio(),C->get_raggio()*2,C->get_raggio()*2);
    setRect(e);

    }
}

void FigureEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
  QGraphicsEllipseItem::paint(painter,option,widget);
}
QRectF FigureEllipse::boundingRect() const{
  return QGraphicsEllipseItem::boundingRect();
}
