#include<iostream>

// Vettore rappresenta un array di interi
class Vettore {
private:
  int* a; // puntatore alla prima cella dell'array
  int size; // la dimensione dell'array
public:
  // costruttore con valore iniziale
  Vettore(int init=0, int s=0): a(new int[s]), size(s) {
    for(int i=0; i<s; ++i) a[i]=init;
}  
  // ritorna la dimensione del vettore
  int getSize() const {return size;}
  // operatore di uguaglianza 
  bool operator==(const Vettore& v) const {
    if(size != v.size) return false;
    // size == v.size
    for(int i=0; i<size; ++i) 
      if(a[i] != v.a[i]) return false;
    // forall i in [0,size-1]. a[i] == v.a[i]
    return true;
  }
  // operatore di disuguaglianza
  bool operator!=(const Vettore& v) const {
    return !(*this == v);
  }
  // operatore di indicizzazione
  int& operator[](int i) const {
    return *(a+i); // return a[i];
  }
  // costruttore di copia profonda
  Vettore(const Vettore& v): a(new int[v.size]), size(v.size) {
    for(int i=0; i<v.size; ++i) a[i]=v.a[i];
  }
  // assegnazione profonda
  Vettore& operator=(const Vettore& v) {
    if(this != &v) {
      delete[] a; // pulisco lo heap
      a = new int[v.size];
      size=v.size;
      for(int i=0; i<v.size; ++i) a[i]=v.a[i];
    }
    return *this;
  }
  // distruzione profonda
  ~Vettore() {delete[] a;}
};

// output di tutte le celle di v separate da uno spazio e
// terminate da un std::endl
std::ostream& operator<<(std::ostream& os, const Vettore& v) {
  for(int i=0; i<v.getSize(); ++i) 
    os << v[i] << " ";
  os << std::endl;
  return os;
}


