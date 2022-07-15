#ifndef QUADRILATERO_H
#define QUADRILATERO_H

#define _USE_MATH_DEFINES

#include "../poligonoconvesso.h"
class Quadrilatero: public PoligonoConvesso
{
  friend ostream& operator<< (ostream&,const Quadrilatero&);

  friend  PoligonoConvesso* PoligonoConvesso::crea_poligono(QVector<Vertice>&);
public:
  Quadrilatero(const Quadrilatero&);
  virtual double get_perimetro() const;
  virtual double get_area() const;
  virtual QString toString() const;
  QString get_nomeClasse() const;
    double  get_lati(unsigned int i)const;
  unsigned int get_nLati()const;

protected:
  double lati[4];
  unsigned int nLati=4;
private:
  void set_lati(const QVector<Vertice>&);
  Quadrilatero(const QVector<Vertice>&,bool);

};


#endif // QUADRILATERO_H
