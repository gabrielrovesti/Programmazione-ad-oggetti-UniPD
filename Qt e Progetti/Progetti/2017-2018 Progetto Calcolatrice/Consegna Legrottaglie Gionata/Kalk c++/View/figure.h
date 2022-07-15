#ifndef FIGURE_H
#define FIGURE_H
#include <QGraphicsItem>
#include"./calcolatrice/poligonoconvesso.h"
#include"./calcolatrice/cerchio.h"
class Figure:  public QGraphicsItem
{
public:
   virtual ~Figure();
   Shape * getPunt()const;
   void setPunt(Shape*);
protected:
   Figure(Shape*);
   Shape * punt_shape;

};

#endif // FIGURE_H
