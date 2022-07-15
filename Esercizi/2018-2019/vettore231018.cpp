/* ESERCIZIO:
Definire una classe vettore i cui oggetti rappresentano array di interi.
vettore deve includere un costruttore di default, una operazione di
concatenazione che restituisce un nuovo vettore v1+v2, una operazione di
append v1.append(v2), l'overloading dell'uguaglianza, dell'operatore di
output e dell'operatore di indicizzazione.  Deve inoltre includere il
costruttore di copia profonda, l'assegnazione profonda e la distruzione profonda.
*/

#include<iostream>

class vettore {
private:
  int* a;
  unsigned int size;

  int* copy() const {
    int* b = !size ? nullptr : new int[size];
    for(int j=0; j<size; j++) b[j] = a[j];
    return b;
  }

public:
  vettore(): a(nullptr), size(0) {}

  vettore(int x): size(1), a(new int[1]) {a[0]=x;}

  vettore(const vettore& v):
    size(v.size), a(v.copy()) {}
  vettore& operator=(const vettore& v) {
    if(this != &v) {
      if(a) delete[] a;
      a = v.copy();
      size = v.size;
    }
    return *this;
}
  ~vettore() {
    if(a) delete[] a;
  }

  bool empty() const {return !size;}

  unsigned int getSize() const {return size;}

  vettore operator+(const vettore& v) const {
    vettore w;
    unsigned int x = size + v.size;
    if(x) {
    w.a = new int[x];
    w.size = x;
    for(unsigned int j=0; j<size; ++j)
      w.a[j] = a[j];
    for(unsigned int j=0; j<v.size; ++j)
      w.a[size+j] = v.a[j];
    }
    return w;
  }

   void append(const vettore& v) {
    *this = *this + v;
  }

  bool operator==(const vettore& v) const {
    if(size != v.size) return false;
    for(unsigned int j=0; j<size; ++j)
      if(a[j] != v.a[j]) return false;
    return true;
  }

  int& operator[](unsigned int i) const {
    return a[i];
  }
};

std::ostream& operator<<(std::ostream& os, const vettore& v) {
  for(int j=0; j<v.getSize(); ++j) os << v[j] << ' ';
  return os;
}

int main() {
  vettore v1, v2(3), v3(5);
  v1 = v2+v3;
  v2.append(v2);
  v3.append(v1);
  std::cout << v1 << std::endl;
  std::cout << v2 << std::endl;
  std::cout << v3 << std::endl;
}
