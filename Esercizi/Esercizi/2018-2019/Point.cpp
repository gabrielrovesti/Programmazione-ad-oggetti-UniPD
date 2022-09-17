// Point.h
#include<iostream>

class Point {
private:
  double x,y,z;
public:
  // convertitore di tipo: double => Point
  Point(double =0,double =0,double =0);
  double getX() const;
  double getY() const;
  double getZ() const;
  void negate();
  double norm() const;
};

std::ostream& operator<<(std::ostream&, const Point&);

Point operator+(const Point&, const Point&);

// Point.cpp
#include "Punto.h"
#include <math.h>
#include <iostream>

Point::Point(double _x, double _y, double _z) {
  x=_x; y=_y; z=_z;
}

double Point::getX() const {
  return x;
}

double Point::getY() const {
  return y;
}

double Point::getZ() const {
  return z;
}

void Point::negate() {
  x *= -1.0;
  y *= -1.0;
  z *= -1.0;
}

double Point::norm() const {
  return sqrt(x*x + y*y + z*z);
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
  return os << '(' << p.getX() << ','
	    << p.getY() << ','
	    << p.getZ() << ')';
}

Point operator+(const Point& p1, const Point& p2) {
  return Point(p1.getX() + p2.getX(),
	       p1.getY() + p2.getY(),
	       p1.getZ() + p2.getZ() );
}

int main() {
  Point p1(2,3.4,-2.3), p2(1,2.4), p3;
  p1.negate();
  std::cout << "norma di p2 = " << p2.norm() << std::endl;
  std::cout << "p1 = " << p1 << std::endl;
  std::cout << "p1 + p2 = " << p1+p2 << std::endl;
  std::cout << "p2 + 4.3 = " << p2+4.3 << std::endl;
}
