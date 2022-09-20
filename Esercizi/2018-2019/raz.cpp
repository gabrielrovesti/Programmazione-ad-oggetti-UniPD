#include <iostream>

class Raz {
private:
  int num, den;
  // INV: den != 0
  // oggetti a rappresentazione non unica (!!)
public:
  // Raz(int) agisce da convertitore int => Raz
  Raz(int n = 0, int d =1): num(n), den(d) {
    if(d==0) {num=0;den=1;}
  }
  Raz inverso() const {
    // costruttore e' OK anche per Raz(0,den)
    return Raz(den,num);
  }
  // Raz => double
  operator double() const {
    return static_cast<double>(num)/static_cast<double>(den);
  }

  Raz operator+(const Raz& y) const {
    return Raz(num*y.den + y.num*den,den*y.den);
  }

  Raz operator*(const Raz& y) const {
    return Raz(num*y.num, den*y.den);
  }

  bool  operator==(const Raz& y) const {
    return num*y.den == den*y.num;
  }

  Raz  operator++(int) { // postfisso
    Raz temp(*this);
    num += den;
    return temp;
  }

  Raz&  operator++() { // prefisso
    num += den;
    return *this;
  }

  static Raz unTerzo() {
    return Raz(1,3);
  }
};

std::ostream& operator<<(std::ostream& os, const Raz& r) {
  return os << r.operator double();
}

int main() {
  Raz r1(1,4), r2(3), r3, r4(2,6);
  std::cout << r1+r2 << std::endl;
  Raz r5= (++r1)*r2;
  std::cout << r5++ << std::endl;
  std::cout << r3.inverso() + Raz::unTerzo() << std::endl;
  std::cout << (r1 == r1++ + Raz(-1)) << std::endl;
}
