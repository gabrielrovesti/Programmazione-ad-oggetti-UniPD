#ifndef POLIGONOCONVESSO_H
#define POLIGONOCONVESSO_H

#include "poligono.h"
#include <stdexcept>
#include <algorithm>
#include "errori.h"

using std::vector;

class PoligonoConvesso : public Poligono
{
public:
  PoligonoConvesso();
  PoligonoConvesso(const PoligonoConvesso&);
  PoligonoConvesso(const QVector<Vertice>&,int,QString);
  QVector<Vertice> get_vertici()const;

  const QVector<Vertice>& getPunt_vertici()const;
  static PoligonoConvesso* crea_poligono(QVector<Vertice>&);

  virtual int size() const;
  virtual double get_perimetro() const =0;
  virtual double get_area() const =0;
  virtual double  get_lati(unsigned int i) const =0;
  virtual unsigned int get_nLati()const =0;
  PoligonoConvesso* aggiungi_vertice(Vertice)const;
  PoligonoConvesso* rimuovi_vertice(Vertice)const;
  bool operator ==(const PoligonoConvesso& p)const;
  bool operator !=(const PoligonoConvesso& p)const;
protected:
  virtual void set_lati(const QVector<Vertice>&) =0;
  QVector<Vertice> Lista;
  PoligonoConvesso(const QVector<Vertice>&,int,QString,bool);
private:
  static QVector<Vertice> grahamScan(QVector<Vertice>&);
  static void rimuovi_doppioni(QVector<Vertice>&);
  static bool POLAR_ORDER(Vertice, Vertice);
  static double sqrDist(Vertice, Vertice);
  static double ccw(Vertice, Vertice, Vertice);
  static bool checkVector(QVector<Vertice>&);

};
PoligonoConvesso* operator+(const PoligonoConvesso&,const PoligonoConvesso&);
PoligonoConvesso* operator-(const PoligonoConvesso&,const PoligonoConvesso&);



#endif // POLIGONOCONVESSO_H
