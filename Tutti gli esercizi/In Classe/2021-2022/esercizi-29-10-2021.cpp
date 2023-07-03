/*
ESERCIZIO. 

Definire un template di classe dList<T> i cui oggetti rappresentano una struttura dati lista doppiamente concatenata (doubly linked list) per elementi di uno stesso tipo T. Il template dList<T> deve soddisfare i seguenti vincoli:

1. Gestione della memoria senza condivisione.

2. dList<T> rende disponibile un costruttore dList(unsigned int k, const T& t) che costruisce una 
lista contenente k nodi ed ognuno di questi nodi memorizza una copia di t.

3. dList<T> permette l’inserimento in testa ed in coda ad una lista in tempo O(1) (cioe` costante):
-- Deve essere disponibile un metodo void insertFront(const T&) con il seguente comportamento: dl.insertFront(t) inserisce l’elemento t in testa a dl in tempo O(1).
-- Deve essere disponibile un metodo void insertBack(const T&) con il seguente comportamento: dl.insertBack(t) inserisce l’elemento t in coda a dl in tempo O(1).

4. dList<T> rende disponibile un opportuno overloading di operator< che implementa l’ordinamento lessicografico (ad esempio, si ricorda che per l'ordinamento lessicografico tra stringhe abbiamo che "campana" < "cavolo" e che
"eccellente" < "ottimo").

5. dList<T> rende disponibile un tipo iteratore costante dList<T>::constiterator i cui oggetti permettono di iterare sugli elementi di una lista, e supporti il past-the-end propriamente.
*/

template<class T>
class dList {
private:
  class nodo {
  public:
    T info;
    nodo *prev, *next;
    nodo(const T& t, nodo* p, nodo* n): info(t), prev(p), next(n) {}
  };
  nodo *first, *last;
  // lista vuota IFF first == nullptr == last
  
public:
  dList(unsigned int k, const T& t);
  dList(const dList& d);
  dList& operator=(const dList& d);
  ~dList;
  void insertFront(const T& t);
  void insertBack(const T& t);
  bool operator<(const dList&) const;
  class const_iterator {
  private:
    nodo* ptr; // ptr al nodo a cui si riferisce il const_iterator
    bool pte; // true IFF il const_iterator e' past-the-end
  public:
    const_iterator();
    const T& operator*() const;
    const T* operator->() const;
    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator--();
    const_iterator operator--(int);
    bool operator==(const constiterator& cit) const;
    bool operator!=(const constiterator& cit) const;
  };
  const_iterator begin() const;
  const_iterator end() const;
};


// esempio d'uso
int main() {
  dList<int> x(4,2), y(0,0), z(6,8);
  y=x;
  x.insertFront(-2); z.insertFront(3); y.insertFront(0);
  if(x<y) std::cout << "x < y" << std::endl;
  if(z<x) std::cout << "z < x" << std::endl;
  if(y<z) std::cout << "y < z" << std::endl;
  if(z<y) std::cout << "z < y" << std::endl;

  std::cout << "x= ";
  dList<int>::constiterator j = --(x.end());
  for(; j != x.begin(); --j) std::cout << *j << ' '; 
  std::cout << *j << std::endl << "y= ";
  for(dList<int>::constiterator k = y.begin(); k != y.end(); ++k) std::cout << *k << ' ';  
  std::cout << std::endl << "z= ";
  dList<int>::constiterator i = z.begin(); 
  for( ; i != z.end(); ++i) std::cout << *i << ' ' << std::endl;
}



