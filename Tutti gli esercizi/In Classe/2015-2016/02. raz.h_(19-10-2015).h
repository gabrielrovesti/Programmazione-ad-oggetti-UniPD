// Raz.h
#ifndef RAZ_H
#define RAZ_H
#include<iostream>

class Raz {
private:
  int num, den; // INVARIANTE: den !=0
public:
  /* costruisce il razionale a/b, attenzione se
     b==0 costruisce lo 0, costruttore a 0-1-2 args*/
  // convertitore int => Raz
  Raz(int a=0, int b=1); 
  
  // ok costruzione di copia standard
  // ok assegnazione standard
  
  // l'inverso di zero e' zero
  Raz inverso() const; 
  
  int numeratore() const;
  int denominatore() const;
  
  operator double() const;
  
  Raz operator+(const Raz&) const;
  bool operator==(const Raz&) const;
  
  Raz& operator++();
  Raz operator++(int);
  
  static Raz unTerzo();
};
Raz operator*(const Raz&, const Raz&);

std::ostream& operator<<(std::ostream&, const Raz&);
#endif