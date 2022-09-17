//Esercizio 1

Riga problematica --> 7

//Esercizio 2

2 5 2 0x7ffe2f849e14 0x7ffe2f849e14

//Esercizio3

class Raz {
private:
  int num, den; // INV: den != 0
  
public:
  explicit Raz(int n =0, int d =1): num(n), den(d==0? 1 : d)  {}

  // inverso di Raz(0,d) è Raz(0,1)
  Raz inverso() const { 
    return Raz(num==0? 0 : den,num);
  }

  operator double() const {
    return static_cast<double>(num)/static_cast<double>(den);
  }

  Raz operator+(const Raz& r) const {
    return Raz(num*r.den + r.num*den, den*r.den);
  }

  Raz operator*(const Raz& r) const {
    return Raz(num*r.num,den*r.den);
  }

  bool operator==(const Raz& r) const {
    return num*r.den == den*r.num;
  }

  Raz& operator++() {
    num += den;
    return *this;
  }

  Raz operator++(int) {
    Raz aux(*this);
    num += den;
    return aux;
  }
  
  static Raz unTerzo() {
    return Raz(1,3);
  }
};

#include<iostream>

// output del razionale convertito a double
std::ostream& operator<<(std::ostream& os, const Raz& r) {
  return os << "il razionale in virgola mobile è: " <<
    r.operator double(); 
}

int main() {
  Raz x(2,3), y(2), z, u(1,8), v(3,2), w(8,4);

  std::cout << x+y+v*u << std::endl; // 2.85417
  std::cout << u.inverso() << std::endl; // 8
  std::cout << (y == w) << std::endl; // true
  std::cout << y++ << " " << ++w << std::endl; // 2 3
  std::cout << (++y + Raz::unTerzo()) << std::endl; // 4.33333
  std::cout << 2 + Raz(1,2) << std::endl; // 2.5
}


