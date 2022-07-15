#ifndef DODECAGONO_H
#define DODECAGONO_H


#include "../poligonoconvesso.h"
class Dodecagono: public PoligonoConvesso
{
  friend ostream& operator<< (ostream&,const Dodecagono&);

  friend  PoligonoConvesso* PoligonoConvesso::crea_poligono(QVector<Vertice>&);

public:
  Dodecagono(const Dodecagono&);
  virtual double get_perimetro() const;
  virtual double get_area() const;
  virtual QString toString() const;
  QString get_nomeClasse() const;
    double  get_lati(unsigned int i)const;
  unsigned int get_nLati()const;


protected:
  double lati[12];
  unsigned int nLati=12;
private:
  void set_lati(const QVector<Vertice>&);
    Dodecagono(const QVector<Vertice>&,bool);
};
#endif // DODECAGONO_H
