#ifndef OTTAGONO_H
#define OTTAGONO_H

#include "../poligonoconvesso.h"
class Ottagono: public PoligonoConvesso
{
  friend ostream& operator<< (ostream&,const Ottagono&);

  friend  PoligonoConvesso* PoligonoConvesso::crea_poligono(QVector<Vertice>&);

public:
  Ottagono(const Ottagono&);
  virtual double get_perimetro() const;
  virtual double get_area() const;
  virtual QString toString() const;
  QString get_nomeClasse() const;
    double  get_lati(unsigned int i)const;
  unsigned int get_nLati()const;

protected:
  double lati[8];
  unsigned int nLati=8;
private:
  void set_lati(const QVector<Vertice>&);
  Ottagono(const QVector<Vertice>&,bool);

};
#endif // OTTAGONO_H
