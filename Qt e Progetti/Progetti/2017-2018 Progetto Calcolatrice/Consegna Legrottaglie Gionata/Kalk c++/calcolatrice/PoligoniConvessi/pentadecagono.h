#ifndef PENTADECAGONO_H
#define PENTADECAGONO_H

#include "../poligonoconvesso.h"
class Pentadecagono: public PoligonoConvesso
{
  friend ostream& operator<< (ostream&,const Pentadecagono&);

  friend  PoligonoConvesso* PoligonoConvesso::crea_poligono(QVector<Vertice>&);

public:
  Pentadecagono(const Pentadecagono&);
  virtual double get_perimetro() const;
  virtual double get_area() const;
  virtual QString toString() const;
  QString get_nomeClasse() const;
    double  get_lati(unsigned int i)const;
  unsigned int get_nLati()const;

protected:
  double lati[15];
  unsigned int nLati=15;
private:
  void set_lati(const QVector<Vertice>&);
  Pentadecagono(const QVector<Vertice>&,bool);

};


#endif // PENTADECAGONO_H
