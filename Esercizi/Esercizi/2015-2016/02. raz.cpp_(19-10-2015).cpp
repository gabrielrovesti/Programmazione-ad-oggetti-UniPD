// Raz.cpp
#include "Raz.h"
#include <iostream>

Raz::Raz(int a, int b): num(a), den(b) {
  if(den==0) {num=0;den=1;}
}

Raz Raz::inverso() const {
  return Raz(den,num);
}

int Raz::numeratore() const {
  return num;
}

int Raz::denominatore() const {
  return den;
}

Raz Raz::operator+(const Raz& y) const {
  return Raz(num*y.den + y.num*den,den*y.den);
}

Raz operator*(const Raz& x, const Raz& y) {
  return Raz(x.numeratore()*y.numeratore(), 
	     x.denominatore()*y.denominatore());
}

bool Raz::operator==(const Raz& y) const {
  return num*y.den == den*y.num;
}

Raz Raz::operator++(int) { // operator ++ postfisso
  Raz aux(*this);
  *this = *this + Raz(1); // assegnazione standard
  return aux;
}

Raz& Raz::operator++() { // operator ++ prefisso
  (*this)++;
  return *this;
}

Raz::operator double() const {
  return static_cast<double>(num)/
    static_cast<double>(den);
}

Raz Raz::unTerzo() {
  return Raz(1,3);
}

std::ostream& operator<<(std::ostream& os, const Raz& x) {
  return os << x.numeratore() << "/" <<
    x.denominatore();
}