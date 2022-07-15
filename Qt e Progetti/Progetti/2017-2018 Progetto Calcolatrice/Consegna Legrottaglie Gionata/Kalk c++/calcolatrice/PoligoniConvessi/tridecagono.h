#ifndef TRIDECAGONO_H
#define TRIDECAGONO_H

#include "../poligonoconvesso.h"
class Tridecagono: public PoligonoConvesso
{
  friend ostream& operator<< (ostream&,const Tridecagono&);
  friend  PoligonoConvesso* PoligonoConvesso::crea_poligono(QVector<Vertice>&);

public:
  Tridecagono(const Tridecagono&);
  virtual double get_perimetro() const;
  virtual double get_area() const;
  virtual QString toString() const;
  QString get_nomeClasse() const;
    double  get_lati(unsigned int i)const;
  unsigned int get_nLati()const;

protected:
  double lati[13];
  unsigned int nLati=13;
private:
  void set_lati(const QVector<Vertice>&);
  Tridecagono(const QVector<Vertice>&,bool);

};

#endif // TRIDECAGONO_H
