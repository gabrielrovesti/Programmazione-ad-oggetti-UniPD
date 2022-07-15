#ifndef EPTADECAGONO_H
#define EPTADECAGONO_H

#include "../poligonoconvesso.h"
class Eptadecagono: public PoligonoConvesso
{
  friend ostream& operator<< (ostream&,const Eptadecagono&);

  friend  PoligonoConvesso* PoligonoConvesso::crea_poligono(QVector<Vertice>&);

public:
  Eptadecagono(const Eptadecagono&);
  virtual double get_perimetro() const;
  virtual double get_area() const;
  virtual QString toString() const;
  QString get_nomeClasse() const;
    double  get_lati(unsigned int i)const;
  unsigned int get_nLati()const;

protected:
  double lati[17];
  unsigned int nLati=17;
private:
  void set_lati(const QVector<Vertice>&);
  Eptadecagono(const QVector<Vertice>&,bool);

};


#endif // EPTADECAGONO_H
