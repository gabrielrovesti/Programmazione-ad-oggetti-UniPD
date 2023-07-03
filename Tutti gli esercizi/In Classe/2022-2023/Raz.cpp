#include <iostream>

class Raz {
private:
  int num, den; //rappresentazioni multiple, invariante di istanza: den != 0 
public:
  Raz(int n =0, int d =1);
  Raz inverso() const;
  operator double() const;
  Raz operator++(int); // ++ postfisso
  Raz& operator++(); // ++ prefisso
  static Raz unTerzo();
  Raz operator+(const Raz&) const;
  Raz operator*(const Raz&) const;
  bool operator==(const Raz&) const;
};

std::ostream& operator<<(std::ostream&, const Raz&);

// Raz.cpp
Raz::Raz(int n, int d): num(n), den(d==0 ? 1: d) {} // conversion int => Raz

Raz Raz::inverso() const {
  return Raz(den,num);
}

Raz::operator double() const {
  return static_cast<double>(num)/static_cast<double>(den);
}

Raz Raz::operator++(int){ // ++ postfisso
  Raz r(*this);
  num +=den;
  return r;
}
Raz& Raz::operator++(){ // ++ prefisso
 num +=den;
 return *this;
}

Raz Raz::unTerzo(){
  return Raz(1,3);
}

Raz Raz::operator+(const Raz& r) const {
  return Raz(num*r.den + r.num*den,den*r.den);  
}

Raz Raz::operator*(const Raz& r) const {
  return Raz(num*r.num,den*r.den);
}

bool Raz::operator==(const Raz& r) const {
  return num*r.den == r.num*den;
}

std::ostream& operator<<(std::ostream& os, const Raz& r) {
  return os << "il raz. come double e' = " << r.operator double();
}


// main.cpp
int main() {
  Raz x(2,3), y(2), z, u(1,8), v(3,2), w(8,4);

  std::cout << x+y+v*u << std::endl; // 2.85417
  std::cout << u.inverso() << std::endl; // 8
  std::cout << (y == w) << std::endl; // true
  std::cout << y++ << " " << ++w << std::endl; // 2 3
  std::cout << (++y + Raz::unTerzo()) << std::endl; // 4.33333
  std::cout << 2 + Raz(1,2) << std::endl; // 2.5
}
