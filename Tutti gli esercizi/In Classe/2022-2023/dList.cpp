/*
ESERCIZIO. 

Definire un template di classe dList<T> i cui oggetti rappresentano una struttura dati lista doppiamente concatenata (doubly linked list) per elementi di uno stesso tipo T. Il template dList<T> deve soddisfare i seguenti vincoli:

1. Gestione della memoria senza condivisione.

2. dList<T> rende disponibile un costruttore dList(unsigned int k, const T& t) che costruisce una 
lista contenente k nodi ed ognuno di questi nodi memorizza una copia di t.

3. dList<T> permette l’inserimento in testa ed in coda ad una lista in tempo O(1) (cioe` costante):
-- Deve essere disponibile un metodo void insertFront(const T&) con il seguente comportamento: dl.insertFront(t) inserisce l’elemento t in testa a dl in tempo O(1).
-- Deve essere disponibile un metodo void insertBack(const T&) con il seguente comportamento: dl.insertBack(t) inserisce l’elemento t in coda a dl in tempo O(1).

4. dList<T> rende disponibile un opportuno overloading di operator< che implementa l’ordinamento lessicografico (ad esempio, si ricorda che per l'ordinamento lessicografico tra stringhe abbiamo che "campana" < "cavolo" e che "buono" < "ottimo").

5. dList<T> rende disponibile un tipo iteratore costante dList<T>::const_iterator i cui oggetti permettono di iterare sugli elementi di una lista.
*/

template<class T>
class dList {
private:
  class nodo {
  public:
    T info;
    nodo *prev, *next;
    // convertitore da const T& => nodo
    nodo(const T& i, nodo* p =0, nodo* n =0): info(i), prev(p), next(n) {}
    // distruttore in versione standard
  };
  nodo* first;
  nodo* last;
  // dList vuota iff first == nullptr == last

  static void destroy(nodo* f) {
    if(f) {destroy(f->next); delete f;}
  }

  static void copy(nodo* fst, nodo*& f, nodo*& l){
    if(fst==nullptr) {f=l=nullptr; return;}
    // lista non vuota
    nodo* ptr = fst;
    l=f=new nodo(ptr->info,nullptr,nullptr);
    while(ptr->next !=nullptr) {
      ptr = ptr->next;
      l->next = new nodo(ptr->info,l,nullptr);
      l=l->next;
    }
  }

  static bool lex_compare(nodo* f, nodo* s) {
    if(!s) return false;
    // s
    if(!f) return true;
    // f & s
    if(f->info < s->info) return true;
    if(s->info < f->info) return false;
    return f->info == s->info && lex_compare(f->next,s->next);
  }
  
public:
  dList(const dList& d): first(nullptr), last(nullptr) {
    copy(d.first,first,last);
  }
  
  dList& operator=(const dList& d) {
    if(this != &d) {
      destroy(first);
      copy(d.first,first,last);
    }
    return *this;
  }
  
  ~dList() {if(first) destroy(first);}

  void insertFront(const T& t) {
    first = new nodo(t,nullptr,first);
    if(last==nullptr) last=first;
    if(first->next != nullptr) (first->next)->prev = first;
  }
  
  void insertBack(const T& t) {
    if(last){ // lista non vuota
      last = new nodo(t,last,nullptr);
      (last->prev)->next=last;
    }
    else // lista vuota
      first=last=new nodo(t);
  }
 
  dList(unsigned int k, const T& t): first(nullptr), last(nullptr) {
    for(unsigned int i=0; i<k; ++i) insertFront(t);
  }

  bool operator<(const dList& d) const {
    return lex_compare(first,d.first);
  }

  class const_iterator {
    friend class dList<T>;
  private:
    const nodo* ptr;
    bool pastTheEnd;
    // iteratore indefinito IFF ptr == nullptr & pastTheEnd==false
    const_iterator(const nodo* p, bool pte=false): ptr(p), pastTheEnd(pte) {}
  public:
    
    const_iterator(): ptr(nullptr), pastTheEnd(false) {}

    const_iterator& operator++() {
      // const_iterator indefinito: nulla da fare
      // ptr == 0 & pte=ff
      // const_iterator pastTheEnd: nulla da fare
      // pte=tt
      if(ptr && !pastTheEnd ) {
	if(ptr->next==nullptr) {ptr = ptr+1; pastTheEnd=true;}
	else ptr = ptr->next;
      }
      return *this;
    }
    
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      if(ptr && !pastTheEnd ) {
	if(ptr->next==nullptr) {ptr += 1; pastTheEnd=true;}
	else ptr = ptr->next;
      }
      return tmp;
    }

    const_iterator& operator--() {
      if(ptr) {
	if(pastTheEnd==true) {ptr = ptr-1; pastTheEnd=false;}
	// const_iteratore si riferisce al primo elemento
	else if(ptr->prev==nullptr) ptr=nullptr; 
	else ptr=ptr->prev;
      }
      return *this;
    }
    
    const_iterator operator--(int) {
      const_iterator tmp(*this);
      if(ptr) {
	if(ptr->prev==nullptr) ptr=nullptr;
	else if(pastTheEnd==true) {ptr = ptr-1; pastTheEnd=false;}
	else ptr=ptr->prev;
      }
      return tmp;
    }

    const T&  operator*() const {
      return ptr->info;
    }
    
    const T*  operator->() const {
      return &(ptr->info);
    }

    bool operator==(const const_iterator& cit) const {
      return ptr == cit.ptr;
    }
    
    bool operator!=(const const_iterator& cit) const {
      return ptr != cit.ptr;
    }
  };
  
  const_iterator begin() const {
    if(first != nullptr) return const_iterator(first);
    return const_iterator();
  }

  const_iterator end() const {
    if(first == nullptr) return const_iterator();
    return const_iterator(last+1,true);
  }
};

// esempio d'uso
#include<iostream>

int main() {
  dList<int> x(4,2), y(0,0), z(6,8);
  y=x;
  x.insertFront(-2); z.insertFront(3); y.insertFront(0);
  if(x<y) std::cout << "x < y" << std::endl;
  if(z<x) std::cout << "z < x" << std::endl;
  if(y<z) std::cout << "y < z" << std::endl;
  if(z<y) std::cout << "z < y" << std::endl;

  std::cout << "x= ";
  dList<int>::const_iterator j = --(x.end());
  for(; j != x.begin(); --j) std::cout << *j << ' '; 
  std::cout << *j << std::endl << "y= ";
  for(dList<int>::const_iterator k = y.begin(); k != y.end(); ++k) std::cout << *k << ' ';  
  std::cout << std::endl << "z= ";
  dList<int>::const_iterator i = z.begin(); 
  for( ; i != z.end(); ++i) std::cout << *i << ' ';  
  std::cout << std::endl;
}
