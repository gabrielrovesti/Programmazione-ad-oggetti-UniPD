/* 
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

// dichiarazione incompleta
template <class T>
class albero;

template <class T>
std::ostream& operator<< (std::ostream&, const albero<T>&);

template <class T>
class albero {
  friend std::ostream& operator<< <T> (std::ostream&, const albero<T>&);
private:
  class nodo { // template di classe annidato associato
  public:
    T info;
    nodo *sx, *cx, *dx;
    nodo(const T& t, nodo* s=0, nodo* c=0, nodo* d=0):
      info(t), sx(s), cx(c), dx(d) {}
    // ~nodo() standard
  };

  static nodo* copy(nodo* p) {
    if(p==nullptr) return nullptr;
    // p punta ad albero non vuoto
    return new nodo(p->info,copy(p->sx),copy(p->cx),copy(p->dx));
  }
  
  static void destroy(nodo* p) {
    if(p != nullptr){
      destroy(p->sx);destroy(p->cx);destroy(p->dx);
      delete p;
    }
  }
  
  static bool rec_search(const T& t, nodo* p) {
    if(p==nullptr) return false;
    return (t==p->info) || rec_search(t,p->sx) ||
      rec_search(t,p->cx) || rec_search(t,p->dx);
  }
  
  static bool rec_eq(const nodo* p1, const nodo* p2) {
    if(!p1 && !p2) return true;
    // p1 | p2
    if(!p1 || !p2) return false;
    // p1 & p2
    return p1->info == p2->info &&
      rec_eq(p1->sx,p2->sx) && rec_eq(p1->cx,p2->cx) &&
      rec_eq(p1->dx,p2->dx);
  }
  
  static void rec_print(std::ostream& os, nodo* p) {
    if(p != nullptr) {
      rec_print(os,p->sx);
      rec_print(os,p->cx);
      rec_print(os,p->dx);
      os << p->info << ' ';
    }
  }

  nodo* root;
public:
  albero() : root(nullptr) {}

  albero(const albero& a): root(copy(a.root)) {}

  albero& operator=(const albero& a) {
    if(this != &a) {
      destroy(root);
      root = copy(a.root);
    }
    return *this;
  }

  ~albero() {if(root != nullptr) destroy(root);}

  void insert(const T& t) {
    root = new nodo(t,copy(root), copy(root), root);
  }

  bool search(const T& t) const {
    return rec_search(t,root);
  }

  bool operator==(const albero& a) const {
    return rec_eq(root,a.root);
  }
  
};

template <class T>
std::ostream& operator<< (std::ostream& os, const albero<T>& a) {
  albero<T>::rec_print(os,a.root);
  return os;
}

int main() {
  albero<char> t1, t2, t3;
  t1.insert('b');
  t1.insert('a');
  t2.insert('a');
  t3 = t1;
  t3.insert('c');
  std::cout << (t1==t2) << std::endl;
  std::cout << t3.search('c') << std::endl;
  std::cout << "t1 = " << t1 << std::endl;
  std::cout << "t2 = " << t2 << std::endl;
  std::cout << "t3 = " << t3 << std::endl;
}

