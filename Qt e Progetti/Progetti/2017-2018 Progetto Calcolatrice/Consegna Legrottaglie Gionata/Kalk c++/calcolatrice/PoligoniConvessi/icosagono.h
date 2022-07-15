#ifndef ICOSAGONO_H
#define ICOSAGONO_H

#include "../poligonoconvesso.h"
class Icosagono: public PoligonoConvesso
{
  friend ostream& operator<< (ostream&,const Icosagono&);

  friend  PoligonoConvesso* PoligonoConvesso::crea_poligono(QVector<Vertice>&);

public:
  Icosagono(const Icosagono&);
  virtual double get_perimetro() const;
  virtual double get_area() const;
  virtual QString toString() const;
  QString get_nomeClasse() const;
    double  get_lati(unsigned int i)const;
  unsigned int get_nLati()const;

protected:
  double lati[20];
  unsigned int nLati=20;
private:
  void set_lati(const QVector<Vertice>&);
  Icosagono(const QVector<Vertice>&,bool);

};

#endif // ICOSAGONO_H
