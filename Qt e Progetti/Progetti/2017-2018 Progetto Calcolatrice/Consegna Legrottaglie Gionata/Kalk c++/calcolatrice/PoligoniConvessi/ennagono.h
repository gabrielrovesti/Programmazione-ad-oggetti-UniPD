#ifndef ENNAGONO_H
#define ENNAGONO_H

#include "../poligonoconvesso.h"
class Ennagono: public PoligonoConvesso
{
  friend ostream& operator<< (ostream&,const Ennagono&);

  friend  PoligonoConvesso* PoligonoConvesso::crea_poligono(QVector<Vertice>&);

public:
  Ennagono(const Ennagono&);
  virtual double get_perimetro() const;
  virtual double get_area() const;
  virtual QString toString() const;
  QString get_nomeClasse() const;
    double  get_lati(unsigned int i)const;
  unsigned int get_nLati()const;


protected:
  double lati[9];
  unsigned int nLati=9;
private:
  void set_lati(const QVector<Vertice>&);
  Ennagono(const QVector<Vertice>&,bool);

};
#endif // ENNAGONO_H
