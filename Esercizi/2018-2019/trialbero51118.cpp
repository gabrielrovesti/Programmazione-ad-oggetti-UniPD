/*
ESERCIZIO DISCUSSO NELLE LEZIONI DEL 5-6.11.2018

Definire un template di classe albero<T> i cui oggetti rappresentano
un albero 3-ario ove i nodi memorizzano dei valori di tipo T ed hanno
3 figli (invece dei 2 figli di un usuale albero binario). Il template
albero<T> deve soddisfare i seguenti vincoli:
1. Deve essere disponibile un costruttore di default che costruisce l’albero vuoto.
2. Gestione della memoria senza condivisione.
3. Metodo void insert(const T&): a.insert(t) inserisce nell'albero a una nuova radice che memorizza il valore t ed avente come figli 3 copie di a
4. Metodo bool search(const T&): a.search(t) ritorna true se t occorre nell'albero a, altrimenti ritorna false.
5. Overloading dell'operatore di uguaglianza.
6. Overloading dell'operatore di output.

*/

#include<iostream>

template <class T>
class trialbero;

template <class T>
std::ostream& operator<<(std::ostream&,
			 const trialbero<T>&);

template <class T>
class trialbero {
  friend std::ostream& operator<< <T> (std::ostream&, const trialbero&);

private:

  class nodo {
  public:
    T info;
    nodo *sx, *cx, *dx;
    nodo(const T& t, nodo* s=0, nodo* c=0,
	 nodo* d=0): info(t), sx(s), cx(c), dx(d) {}
  };
  nodo* radice;
  static nodo* copia(nodo* r) {
    if(!r) return nullptr;
    return new nodo(r->info, copia(r->sx), copia(r->cx), copia(r->dx));
  }

  static void distruggi(nodo* r) {
    if(r) {
      distruggi(r->sx);
      distruggi(r->cx);
      distruggi(r->dx);
      delete r;
    }
  }
  static bool search(nodo* r, const T& t) {
    if(!r) return false;
    // albero non vuoto
    return (r->info == t || search(r->sx,t) || search(r->cx,t) || search(r->dx,t));
  }
  static bool equals(nodo* r1,nodo* r2) {
    if(!r1 && !r2) return true;
    // r1 || r2
    if(!r1 || !r2) return false;
    // r1 && r2
    return r1->info == r2->info &&
      equals(r1->sx,r2->sx) &&
      equals(r1->cx,r2->cx) &&
      equals(r1->dx,r2->dx);
  }
  static std::ostream& print(nodo* r,std::ostream& os) {
    if(!r) return os;
    os << "[" << r->info << ";";
    print(r->sx,os); os << ",";
    print(r->cx,os); os << ",";
    print(r->dx,os); os << "]";
    return os;
  }

public:
  trialbero(): radice(nullptr) {}
  trialbero(const trialbero& t):
    radice(copia(t.radice)) {}

  trialbero& operator=(const trialbero& t) {
    if(this != &t) {
      distruggi(radice);
      radice = copia(t.radice);
    }
    return *this;
  }

  ~trialbero() {distruggi(radice);}

  void insert(const T& t) {
    radice = new nodo(t,radice,copia(radice),copia(radice));
  }
  bool search(const T& t) const {
    return search(radice,t);
  }
  bool operator==(const trialbero& a) const {
    return equals(radice, a.radice);
  }
};

template <class T>
std::ostream& operator<<(std::ostream& os, const trialbero<T>& a) {
  return trialbero<T>::print(a.radice,os);
}

int main() {
  trialbero<char> t1, t2, t3;
  t1.insert('b');
  t1.insert('a');
  t2.insert('a');
  t3 = t1;
  t3.insert('c');
  std::cout << (t1 == t2) << std::endl;
  std::cout << t1.search('b') << std::endl;
  std::cout << t1 << std::endl << t2 << std::endl << t3 << std::endl;

}
