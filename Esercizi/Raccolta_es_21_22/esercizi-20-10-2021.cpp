/*
Gli oggetti della classe Tree rappresentano alberi binari ricorsivamente definiti di char. Si ridefiniscano assegnazione, costruttore di copia e distruttore di Tree come assegnazione, copia e distruzione profonda. Scrivere esplicitamente eventuali dichiarazioni friend che dovessero essere richieste da tale definizione.
*/

class Nodo {
  friend class Tree;
private:
  Nodo(char c='*', Nodo* s=0, Nodo* d=0): info(c), sx(s), dx(d) {}
  char info;
  Nodo* sx;
  Nodo* dx;
  // ~Nodo() in vers. standard
};

class Tree {
private:
  Nodo* root;

  static Nodo* copia(Nodo* r) {
    if(r == nullptr)   return nullptr; 
    return new nodo(r->info,copia(r->sx),copia(r->dx));
  }
  
  static void distruggi(Nodo* r) {
    if(r != nullptr) {
      distruggi(r->sx);
      distruggi(r->dx);
      delete r;
    }
  }
  
public:
  Tree(): root(0) {}

  Tree& operator=(const Tree& t) {
    if(this != &t) {
      distruggi(root);
      root = copia(t.root)
    }
    return *this;
  }

  Tree(const Tree& t): root(copia(t.root)) {}

  ~Tree() {distruggi(root);}
};

int main() {
  Tree t1,t2;
  t1=t2;
  Tree t3=t2;
}


/* ESERCIZIO:
Definire una classe vettore i cui oggetti rappresentano array di interi.
vettore deve includere opportuni costruttori, una operazione di
concatenazione che restituisce un nuovo vettore v1+v2, una operazione di
append v1.append(v2), l'overloading dell'uguaglianza, dell'operatore di
output e dell'operatore di indicizzazione.  Deve inoltre includere il
costruttore di copia profonda, l'assegnazione profonda e la distruzione profonda.
*/

class Vettore {
private:
  int* a;
  unsigned int size;
  // vettore vuoto IFF a==nullptr && size == 0
  // vettore non vuoto IFF a!=nullptr && size > 0
public:
  // conversione indotta dal costr. 1 arg: unsigned int => Vettore
  Vettore(unsigned int dim =0, int init =0):
    a(dim == 0 ? nullptr : new int[dim]), size(dim) {
    for(unsigned int j=0; j<dim; ++j) a[j]=init;
  }
  
  Vettore& operator=(const Vettore& v) {
    if(this != &v) {
      delete[] a;
      size = v.size;
      a = size == 0 ? nullptr : new int[size];
      for(unsigned int j=0; j<size; ++j) a[j] = v.a[j];
    }
    return *this;
  }
  
  Vettore(const Vettore& v):
    a(v.size == 0 ? nullptr : new int[v.size]),
    size(v.size) {
    for(unsigned int j=0; j<size; ++j) a[j] = v.a[j];
  }
  
  ~Vettore() {delete[] a;}
  
  Vettore& append(const Vettore& v) {
    if(v.size!=0){
      int* p = new int[size+v.size];
      unsigned int j=0;
      for(; j<size; ++j) p[j]=a[j];
      for( ;j<size+v.size; ++j) p[j] = v.a[j-size];
      delete[] a; // FONDAMENTALE
      a=p;
      size+=v.size;
    }
    return *this;  
  }
  
  Vettore operator+(const Vettore& v) const {
    Vettore aux(*this);
    aux.append(v);
    return aux; 
  }
  
  bool operator==(const Vettore& v) const {
    if(this == &v) return true; 
    if(size != v.size) return false;
    for(unsigned int j=0; j<size; ++j)
      if(a[j] != v.a[j]) return false;
    return true;
  }
  
  int& operator[](unsigned int j) const {
    return *(a+j);
  }
  
  unsigned int getSize() const {return size;}
};

#include<iostream>

std::ostream& operator<<(std::ostream& os, const Vettore& v) {
  for(unsigned int j=0; j<v.getSize(); ++j)
    os << v[j] << ' ';
  return os;
}


int main() {
  Vettore v1(4), v2(3,2), v3(5,-3), v4;
  v1 = v2+v3;
  v2.append(v2);
  v3.append(v1).append(v3);
  std::cout << v1 << std::endl;
  std::cout << v2 << std::endl;
  std::cout << v3 << std::endl;
}
