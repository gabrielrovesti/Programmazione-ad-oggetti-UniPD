#ifndef PENTAGONO_H
#define PENTAGONO_H

#include "../poligonoconvesso.h"
class Pentagono: public PoligonoConvesso
{
  friend ostream& operator<< (ostream&,const Pentagono&);

  friend  PoligonoConvesso* PoligonoConvesso::crea_poligono(QVector<Vertice>&);

public:
  Pentagono(const Pentagono&);
  virtual double get_perimetro() const;
  virtual double get_area() const;
  virtual QString toString() const;
  QString get_nomeClasse() const;
    double  get_lati(unsigned int i)const;
  unsigned int get_nLati()const;

protected:
  double lati[5];
  unsigned int nLati=5;
private:
  void set_lati(const QVector<Vertice>&);
  Pentagono(const QVector<Vertice>&,bool);


};


#endif // PENTAGONO_H
