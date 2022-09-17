/* TESTO:
L'esercizio sugli alberi binari della lezione del 26/10/2015:
Gli oggetti della classe Tree rappresentano alberi binari ricorsivamente definiti di stringhe.
Si ridefiniscano assegnazione, costruttore di copia e distruttore di Tree come assegnazione, copia e distruzione profonda.
Scrivere esplicitamente eventuali dichiarazioni friend che dovessero essere richieste da tale definizione. */



#include<string> 
using std::string;

class Nodo {
  friend class Tree;
private:
  Nodo(string st="***", Nodo* s=0, Nodo* d=0): 
    info(st), sx(s), dx(d) {}
  ~Nodo() { // distruzione ricorsiva
    if(sx) delete sx; // chiamata ricorsiva 
    if(dx) delete dx; // chiamata ricorsiva
    // !sx && !dx
  }
  string info;
  Nodo* sx;
  Nodo* dx;
};

class Tree {
public:
  Tree(): radice(0) {}

  Tree(const Tree&); // costruttore di copia profonda 
  Tree& operator=(const Tree&); // assegnazione profonda
  ~Tree(); // distruzione profonda
private:
  Nodo* radice; 
  static Nodo* copia(Nodo*); // funzione di copia profonda
};

Tree::Tree(const Tree& t): radice(copia(t.radice)) {}

Nodo* Tree::copia(Nodo* r) {
  if(r) return new Nodo(r->info,copia(r->sx),copia(r->dx)); 
  // r==0
  return 0;
}

Tree& Tree::operator=(const Tree& t) {
  if(this != &t) {
    delete radice; 
    radice = copia(t.radice);
  }
  return *this;
}

Tree::~Tree() { 
  delete radice;
}