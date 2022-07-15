#ifndef TRIANGOLO_H
#define TRIANGOLO_H
#include "../poligonoconvesso.h"
class Triangolo: public PoligonoConvesso
{
  friend ostream& operator<< (ostream&,const Triangolo&);

  friend  PoligonoConvesso* PoligonoConvesso::crea_poligono(QVector<Vertice>&);

public:
  Triangolo(const Triangolo&);
  Triangolo(const QVector<Vertice>&);
  virtual double get_perimetro() const;
  virtual double get_area() const;
  virtual QString toString() const;
  QString get_nomeClasse() const;
      double  get_lati(unsigned int i)const;
  unsigned int get_nLati()const;

protected:
  double lati[3];
  unsigned int nLati=3;

private:
  void set_lati(const QVector<Vertice>&);
  Triangolo(const QVector<Vertice>&,bool);

};

#endif // TRIANGOLO_H
