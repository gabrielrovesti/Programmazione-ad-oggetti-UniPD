#include "figure.h"

Figure::Figure(Shape* s):punt_shape(s){
  setFlag(QGraphicsItem::ItemIsMovable, false);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
  setFlag(QGraphicsItem::ItemIsFocusable, true);
}

Figure::~Figure(){
    delete punt_shape;
}
Shape* Figure::getPunt()const{
    return punt_shape;
}
void Figure::setPunt(Shape* s){
  if(punt_shape) delete punt_shape;
  punt_shape = s;
}
