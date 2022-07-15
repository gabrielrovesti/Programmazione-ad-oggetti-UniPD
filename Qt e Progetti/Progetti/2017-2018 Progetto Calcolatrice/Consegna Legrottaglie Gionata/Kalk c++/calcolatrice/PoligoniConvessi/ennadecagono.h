#ifndef ENNADECAGONO_H
#define ENNADECAGONO_H

#include "../poligonoconvesso.h"
class Ennadecagono: public PoligonoConvesso
{
  friend ostream& operator<< (ostream&,const Ennadecagono&);

  friend  PoligonoConvesso* PoligonoConvesso::crea_poligono(QVector<Vertice>&);

public:
  Ennadecagono(const Ennadecagono&);
  virtual double get_perimetro() const;
  virtual double get_area() const;
  virtual QString toString() const;
  QString get_nomeClasse() const;
  double  get_lati(unsigned int i)const;
  unsigned int get_nLati()const;


protected:
  double lati[19];
  unsigned int nLati=19;
private:
  void set_lati(const QVector<Vertice>&);
  Ennadecagono(const QVector<Vertice>&,bool);

};


#endif // ENNADECAGONO_H
