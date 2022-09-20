/*
Definire un template di classe albero<T> i cui oggetti rappresentano 
un albero 3-ario ove i nodi memorizzano dei valori di tipo T ed hanno 
3 figli (invece dei 2 figli di un usuale albero binario). Il template 
albero<T> deve soddisfare i seguenti vincoli:
(1) Deve essere disponibile un costruttore di default che costruisce l’albero vuoto. 
(2) Gestione della memoria senza condivisione.
(3) Overloading dell’operatore di uguaglianza.
(4) Overloading dell’operatore di output.
*/

#include<iostream>

template<class T>
class albero;

template<class T> 
std::ostream& operator<< (std::ostream&, const albero<T>&);

template<class T>
class albero {
  friend std::ostream& operator<< (std::ostream&, const albero<T>&);
private:
  class nodo {
  public:
    T info;
    nodo *sx, *cx, *dx;
    nodo(const T& i = T(), nodo* s=0, nodo* c=0, nodo* d=0): 
      info(i), sx(s), cx(c), dx(d) {}
    // distruzione profonda
    ~nodo() {
      if(sx) delete sx;
      if(cx) delete cx;
      if(dx) delete dx;
    }
  };
  nodo* root;  

  static bool confronta(nodo* a, nodo* b) {
    if(!a && !b) return true;
    if(a && b && a->info == b->info && confronta(a->sx,b->sx) 
       && confronta(a->cx,b->cx) && confronta(a->dx,b->dx)) return true;
    return false;
  }
  static nodo* copia(nodo* r) {
    if(!r) return 0;
    return new nodo(r->info,copia(r->sx),copia(r->cx),copia(r->dx));
  }
  static void rec_print(std::ostream& os, nodo* r) {
    if(r) {
      os << r->info << ' ';
      rec_print(os,r->sx); rec_print(os,r->cx); rec_print(os,r->dx);
    }
  }
public:
  albero(): root(0) {}
  // gestione memoria profonda
  albero(const albero& a): root(copia(a.root)) {}
  albero& operator=(const albero& a) {
    if(this != &a) {
      delete root;
      root = copia(a.root);
    }
    return *this;
  }
  ~albero() {if(root) delete root;}

  bool operator==(const albero& t) const {
    return confronta(root,t.root);
  }

};

template<class T> 
std::ostream& operator<<(std::ostream& os, const albero<T>& t) {
  albero<T>::rec_print(os, t.root);
  return os;
}