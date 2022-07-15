#ifndef POLIGONO_H
#define POLIGONO_H
#include "shape.h"


class Poligono:public Shape
{
public:
  virtual int size() const=0;

  virtual QString toString() const =0;
  virtual Poligono* aggiungi_vertice(Vertice)const=0;
  virtual Poligono* rimuovi_vertice(Vertice)const=0;
  virtual const QVector<Vertice>& getPunt_vertici()const=0;

};

#endif // POLIGONO_H
