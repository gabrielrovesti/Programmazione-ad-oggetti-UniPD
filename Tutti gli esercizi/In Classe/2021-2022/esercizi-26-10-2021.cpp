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

template <class T>
class albero; // dichiarazione incompleta del template albero<T>

template <class T>
std::ostream& operator<<(std::ostream&, const albero<T>&);

template <class T>
class albero {
  friend std::ostream& operator<< <T> (std::ostream&, const albero<T>&);
private:
  class nodo {
  public:
    T info;
    nodo *sx, *cx, *dx;
    nodo(const T& t, nodo* _sx =0, nodo* _cx =0, nodo* _dx =0):
      info(t), sx(_sx), cx(_cx), dx(_dx) {}
  };

  nodo* radice;
  
  static nodo* copia(nodo* r) {
    if(!r) return nullptr;
    return new nodo(r->info,copia(r->sx),copia(r->cx),copia(r->dx));
  }
  
  static void distruggi(nodo* r) {
    if(r != nullptr){
      distruggi(r->sx); distruggi(r->cx); distruggi(r->dx);
      delete r;
    }
  }

  static bool rec_search(const T& t, nodo* r){
    if(r == nullptr) return false;
    // l'albero radicato r non vuoto
    if(r->info == t) return true;
    // l'albero radicato r non vuoto e t non e' presente nella radice
    return rec_search(t, r->sx) || rec_search(t, r->cx) || rec_search(t, r->dx);
  }

  static bool equals(nodo* r1, nodo* r2) {
    if(r1==nullptr && r2==nullptr) return true;
    // r1 || r2
    if(r1 == nullptr || r2==nullptr) return false;
    // r1 && r2
    return r1->info == r2->info && equals(r1->sx,r2->sx) &&
      equals(r1->cx,r2->cx) && equals(r1->dx,r2->dx);
  }

  static std::ostream& rec_print(std::ostream& os, nodo* r) {
    if(r) {
      os << r->info << ' ';
      rec_print(os,r->sx); rec_print(os,r->cx); rec_print(os,r->dx); 
    }
    return os;
  }
public:
  albero(): radice(nullptr) {}
  albero& operator=(const albero& a) {
    if(this != &a) {
      distruggi(radice);
      radice = copia(a.radice);
    }
    return *this;
  }
  albero(const albero& a): radice(copia(a.radice)) {}

  ~albero() {if(radice) distruggi(radice);}
  
  void insert(const T& t) {
    radice = new nodo(t,radice, copia(radice), copia(radice)); 
  }
  
  bool search(const T& t) const {
    return rec_search(t,radice);
  }

  bool operator==(const albero& a) const {
    if(this==&a) return true;
    return equals(radice,a.radice);
  }
};

template <class T>
std::ostream& operator<<(std::ostream& os, const albero<T>& t) {
  return albero<T>::rec_print(os,t.radice);
}

int main() {  
  albero<char> t1, t2, t3;
  t1.insert('b');
  t1.insert('a');
  t2.insert('a');
  t3 = t1;
  t3.insert('c');
  std::cout << (t1 == t2) << std::endl; 
  std::cout << t1.search('b') << std::endl; 
  std::cout << t1 << std::endl << t2 << std::endl << t3 << std::endl;
}
