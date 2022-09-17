/*Definire una classe Point i cui oggetti rappresentano punti
nello spazio (x, y, z). Includere:
un costruttore di default, un costruttore a tre argomenti
che inizializza un punto, selettori delle coordinate cartesiane,
un metodo negate() che trasforma un punto nel suo negativo,
una funzione norm() che restituisce la distanza del punto
dall'origine, l'overloading degli operatori di
somma e di output.

Separare interfaccia ed implementazione della classe.
(cioè, fare due file separati: Point.h e Point.cpp)
*/

// file Point.h
#include<iostream>

class Point {
private:
  double _x, _y, _z;
public:
  // costruttore a 3-2-1-0 parametri
  Point(double x =0.0, double y =0.0, double z =0.0); 
  double getX() const;
  double getY() const;
  double getZ() const;
  void negate();
  double norm() const;
};

Point operator+(const Point& p1, const Point& p2);

std::ostream& operator<<(std::ostream& os, const Point& p);

// file Point.cpp
// implementazioni
#include<cmath>
#include<iostream>
// #include "Point.h"

Point::Point(double x, double y, double z) {
  _x = x; _y = y; _z=z;
}

double Point::getX() const {return _x;}

double Point::getY() const {return _y;}

double Point::getZ() const {return _z;}

void Point::negate() {
  _x *= -1.0; _y *= -1.0; _z *= -1.0;
}

double Point::norm() const {
  return sqrt(_x*_x + _y*_y + _z*_z);
}

std::ostream& operator<<(std::ostream& os, const Point& p){
  return os << "(" << p.getX() << "," << p.getY() << ","
	    << p.getZ() << ")";
}

Point operator+(const Point& p1, const Point& p2) {
  return Point(p1.getX()+p2.getX(),
	       p1.getY()+p2.getY(),
	       p1.getZ()+p2.getZ());
}

