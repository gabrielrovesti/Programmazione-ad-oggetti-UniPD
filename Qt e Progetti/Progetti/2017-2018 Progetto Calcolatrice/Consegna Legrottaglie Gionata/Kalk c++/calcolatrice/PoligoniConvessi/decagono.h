#ifndef DECAGONO_H
#define DECAGONO_H

#include "../poligonoconvesso.h"
class Decagono: public PoligonoConvesso
{
  friend ostream& operator<< (ostream&,const Decagono&);

  friend  PoligonoConvesso* PoligonoConvesso::crea_poligono(QVector<Vertice>&);

public:
  Decagono(const Decagono&);
  virtual double get_perimetro() const;
  virtual double get_area() const;
  virtual QString toString() const;
  QString get_nomeClasse() const;
  double  get_lati(unsigned int)const;
  unsigned int get_nLati()const;


protected:
  double lati[10];
  unsigned int nLati=10;
private:
  void set_lati(const QVector<Vertice>&);
  Decagono(const QVector<Vertice>&,bool);

};
#endif // DECAGONO_H
